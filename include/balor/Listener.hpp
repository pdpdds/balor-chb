#pragma once

#include <new>
#include <type_traits>
#include <utility>

#include <balor/test/noMacroAssert.hpp>


namespace balor {



/**
 * Event �������Ɏ��Ԓl�̖����֐���֐��I�u�W�F�N�g�����A�ǉ��ł���֐��I�u�W�F�N�g�B
 *
 * std::function<void (Event)> �Ƃ��������������� .NET �̃f���Q�[�g�̂悤�� operator+= �ɂ�镡���̊֐��ǉ����T�|�[�g����B
 * operator-= �ɂ��֐��̍폜�͊֐��I�u�W�F�N�g�̔�r���@���������ߖ������� operator= �ŏ㏑�����邩 pop �֐��Ŗ�������폜���邵���Ȃ��B
 * std::function ���l�A�������ϊ��\�ł���Έ������Ⴄ�^�̊֐����o�^�ł���B�i�Ⴆ�Όp���֌W�̂���Q�ƌ^���m�Ȃǁj
 * �����_����������ꍇ�̓|�C���^����܂ł̃L���v�`���Ȃ�΃��������蓖�Ă͔������Ȃ��B
 * 
 * <h3>�E�֐��|�C���^�̔�r�Ɋւ�����</h3>
 * �֐��|�C���^�⃁���o�֐��|�C���^�̔�r������ꍇ�ADLL �v���W�F�N�g���܂����Ŏg���Ɠ����֐��ł��A�h���X���قȂ�ꍇ������B
 * SymGetSymFromAddr�֐��ɂ��V���{�����̎擾�́A�K�� pdb �t�@�C����Y�t���Ȃ���΂Ȃ�Ȃ��̂ł��܂���p�I�ł͂Ȃ��B
 * ���̖��� balor ���X�^�e�B�b�N���C�u�����ł͂Ȃ� DLL �ɂ��Ă��܂��Ώ��Ȃ��Ƃ� balor �����ł͉������邪
 * ���[�U�֐��ɂ��Ă͈ˑR�Ƃ��Ċ֐���DLL���Œ�`���Ȃ������肪��������B
 */
#pragma warning(push)
#pragma warning(disable : 4521) // '::balor::Listener<Sender, Event>' : �����̃R�s�[ �R���X�g���N�^�[���w�肳��Ă��܂��B
#pragma warning(disable : 4522) // '::balor::Listener<Sender, Event>' : �����̑�����Z�q���w�肳��Ă��܂��B
template<typename Event>
class Listener {
public:
	/// �֐��o�^�����ŏ������B
	Listener() { new (function()) Function(); }
	/// �֐��|�C���^�ŏ������B
	template<typename EventType>
	Listener(void (*pointer)(EventType)) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(pointer != nullptr);
#endif
		new (function()) FunctionPointer<EventType>(pointer);
	}
	/// �֐��I�u�W�F�N�g�ŏ������B
	template<typename T>
	Listener(T&& functionObject) {
#pragma warning(push)
#pragma warning(disable : 4127) // ���������萔�ł��B
		if (sizeof(FunctionObject<std::remove_reference<T>::type>) <= sizeof(data)) {
#pragma warning(pop)
			new (function()) FunctionObject<std::remove_reference<T>::type>(std::forward<T>(functionObject));
		} else {
			new (function()) AllocatedFunctionObject<std::remove_reference<T>::type>(std::forward<T>(functionObject));
		}
	}
	Listener(Listener& value) { value.function()->clone(*function()); } // T&&�ł̌Ăяo���h�~
	Listener(const Listener& value) { value.function()->clone(*function()); }
	Listener(Listener&& value) { value.function()->moveTo(*function()); }
	Listener(const Listener&& value) { value.function()->clone(*function()); } // T&&�ł̌Ăяo���h�~
	~Listener() { function()->~Function(); }

	/// �֐��I�u�W�F�N�g�̑���B
	template<typename T>
	Listener& operator=(T&& functionObject) {
		this->~Listener();
		new (this) Listener(std::forward<T>(functionObject));
		return *this;
	}
	Listener& operator=(Listener& value) { // T&&�ł̌Ăяo���h�~
		if (&value != this) {
			function()->~Function();
			value.function()->clone(*function());
		}
		return *this;
	}
	Listener& operator=(const Listener& value) {
		if (&value != this) {
			function()->~Function();
			value.function()->clone(*function());
		}
		return *this;
	}
	Listener& operator=(Listener&& value) {
		if (&value != this) {
			function()->~Function();
			value.function()->moveTo(*function());
		}
		return *this;
	}
	Listener& operator=(const Listener&& value) { // T&&�ł̌Ăяo���h�~
		if (&value != this) {
			function()->~Function();
			value.function()->clone(*function());
		}
		return *this;
	}

public:
	/// �Ō�ɒǉ������֐����폜����B
	void pop() {
		FunctionType type = function()->type();
		if (type == otherFunctionType) {
			this->~Listener();
			new (this) Listener();
		} else if (type == listenerChainFunctionType) {
			auto chain = static_cast<ListenerChain*>(function());
			auto size = chain->size();
			if (size == 1) {
				this->~Listener();
				new (this) Listener();
			} else {
				ListenerChain newChain(std::move(*chain), size - 1);
				function()->~Function();
				new (function()) ListenerChain(std::move(newChain));
			}
		}
	}

private:
	typedef void (Listener::*SafeBool)();
	void safeBoolTrueValue() {}
public:
	/// �֐����o�^����Ă��邩�ǂ����B
	operator SafeBool() const { return function()->type() != nullFunctionType ? &Listener::safeBoolTrueValue : nullptr; }
	/// �֐��Ăяo���B�֐����o�^����Ă��Ȃ��ꍇ�͉������Ȃ��B
	void operator() (Event event) const { (*function())(event); }
	/// �֐��̒ǉ��B
	template<typename T>
	void operator+=(T&& anyFunction) {
		FunctionType type = function()->type();
		if (type == nullFunctionType) {
			*this = std::forward<T>(anyFunction);
		} else if (type == otherFunctionType) {
			Listener backup = std::move(*this);
			function()->~Function();
			new (function()) ListenerChain(std::move(backup), std::forward<T>(anyFunction));
		} else {
			static_cast<ListenerChain*>(function())->add(std::forward<T>(anyFunction));
		}
	}


private:
	enum FunctionType {
		 nullFunctionType
		,listenerChainFunctionType
		,otherFunctionType
	};

	struct Function {
		virtual ~Function() {}
		virtual void operator() (Event ) {}
		virtual void clone(Function& dest) const { new (&dest) Function(*this); }
		virtual void moveTo(Function& dest)  { new (&dest) Function(*this); }
		virtual FunctionType type() const { return nullFunctionType; }
	};

	template<typename T>
	struct FunctionPointer : public Function {
		explicit FunctionPointer(void (*pointer)(T )) : pointer(pointer) {}
		virtual void operator() (Event event) { (*pointer)(event); }
		virtual void clone(Function& dest) const { new (&dest) FunctionPointer(pointer); }
		virtual void moveTo(Function& dest)  { new (&dest) FunctionPointer(pointer); }
		virtual FunctionType type() const { return otherFunctionType; }
	private:
		void (*pointer)(T);
	};

	template<typename T>
	struct FunctionObject : public Function {
		explicit FunctionObject(const T& object) : object(object) {}
		explicit FunctionObject(T&& object) : object(std::move(object)) {}
		virtual void operator() (Event event) { object(event); }
		virtual void clone(Function& dest) const { new (&dest) FunctionObject(object); }
		virtual void moveTo(Function& dest)  { new (&dest) FunctionObject(std::move(object)); }
		virtual FunctionType type() const { return otherFunctionType; }
	private:
		FunctionObject& operator=(const FunctionObject& );
		T object;
	};

	template<typename T>
	struct AllocatedFunctionObject : public Function {
		explicit AllocatedFunctionObject(const T& object) : pointer(new T(object)) {}
		explicit AllocatedFunctionObject(T&& object) : pointer(new T(std::move(object))) {}
		AllocatedFunctionObject(const AllocatedFunctionObject& object) : pointer(new T(*object.pointer)) {}
		AllocatedFunctionObject(AllocatedFunctionObject&& object) : pointer(object.pointer) {
			object.pointer = nullptr;
			object.~AllocatedFunctionObject();
		}
		virtual ~AllocatedFunctionObject() { delete pointer; pointer = nullptr; }
		virtual void clone(Function& dest) const { new (&dest) AllocatedFunctionObject(*this); }
		virtual void moveTo(Function& dest)  { new (&dest) AllocatedFunctionObject(std::move(*this)); }
		virtual void operator() (Event event) { (*pointer)(event); }
		virtual FunctionType type() const { return otherFunctionType; }
	private:
		T* pointer;
	};

	struct ListenerChain : public Function {
		struct Listeners {
			Listeners() : pointer(nullptr) {}
			~Listeners() {
				delete [] pointer;
				pointer = nullptr;
			}
			Listener* pointer; // vector ���g���� ListenerChain ���傫�����ă��������蓖�Ă���������
		};
		template<typename T>
		explicit ListenerChain(Listener&& listener, T&& function) {
			listeners.pointer = new Listener[3];
			listeners.pointer[0] = std::move(listener);
			listeners.pointer[1] = std::forward<T>(function);
		}
		ListenerChain(const ListenerChain& chain) {
			int size = chain.size();
			listeners.pointer = new Listener[size + 1];
			for (int i = 0; i < size; ++i) {
				listeners.pointer[i] = chain.listeners.pointer[i];
			}
		}
		ListenerChain(ListenerChain&& chain) {
			listeners.pointer = chain.listeners.pointer;
			chain.listeners.pointer = nullptr;
			chain.~ListenerChain();
		}
		ListenerChain(ListenerChain&& chain, int size) {
			listeners.pointer = new Listener[size + 1];
			for (int i = 0; i < size; ++i) {
				listeners.pointer[i] = std::move(chain.listeners.pointer[i]);
			}
		}
		virtual void clone(Function& dest) const { new (&dest) ListenerChain(*this); }
		virtual void moveTo(Function& dest)  { new (&dest) ListenerChain(std::move(*this)); }
		virtual void operator() (Event event) {
			for (Listener* i = listeners.pointer; *i; ++i) {
				(*i)(event);
			}
		}
		virtual FunctionType type() const { return listenerChainFunctionType; }
		template<typename T>
		void add(T&& function) {
			Listeners newListeners;
			int oldSize = size();
			newListeners.pointer = new Listener[oldSize + 2];
			for (int i = 0; i < oldSize; ++i) {
				newListeners.pointer[i] = std::move(listeners.pointer[i]);
			}
			newListeners.pointer[oldSize] = std::forward<T>(function);
			Listener* tempPointer = listeners.pointer;
			listeners.pointer = newListeners.pointer;
			newListeners.pointer = tempPointer;
		}
		int size() const {
			int i = 0;
			for (; listeners.pointer[i]; ++i) {} // ������ nullFunctionType ���Ԑl�B
			return i;
		}
		Listeners listeners;
	};

	Function* function() const { return const_cast<Function*>(reinterpret_cast<const Function*>(&data)); }

	typename std::aligned_storage<sizeof(FunctionPointer<Event>), std::alignment_of<FunctionPointer<Event> >::value>::type data;
};
#pragma warning(pop)



}
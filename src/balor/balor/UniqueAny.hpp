#pragma once

#include <typeinfo>
#include <utility>

#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>


namespace balor {



/**
 * �C�ӂ�?�̒l����Ԃł���N���X�B
 * 
 * boost::any �Ƃ����������������A�R�s?����?���Ă���̂ŃR�s?�ł��Ȃ�?����Ԃł���B
 * ����ł͂ǂ�ȃT�C�Y��?�ł��낤�ƴ��Ԃ���ƃ��������蓖�Ă𔺂��B����œK����?�n�͂��邩������Ȃ���
 * �N���X�̃T�C�Y�͏��?�C��?����ł���Abalor::gui::ListBox �� balor::gui::ListView �� balor::gui::TreeView ���̃N���X�͂���𗘗p���Ď������Ă���B
 *
 * <h3>�E�T���v���R?�h</h3>
 * <pre><code>
	UniqueAny any;

	any = int(128);
	int i = any_cast<int>(any);
	assert(i == 128);

	any = String(L"abc");
	String s = any_cast<String>(any);
	assert(s == L"abc");
 * </code></pre>
 */
#pragma warning(push)
#pragma warning(disable : 4521) // '::balor::Any' : �����̃R�s? �R���X�g���N??���w�肳��Ă��܂��B
#pragma warning(disable : 4522) // '::balor::Any' : �����̴��ԉ��Z�q���w�肳��Ă��܂��B
class UniqueAny : private NonCopyable {
public:
	/// any_cast ���� Any �̓��e���󂾂�����A?���Ԉ���Ă����ꍇ�ɓ��������O�B
	class BadCastException : public Exception {};

public:
	/// ��̏�Ԃō쐬�B
	UniqueAny() : _holder(nullptr) {}
	UniqueAny(UniqueAny&& value) : _holder(value._holder) { value._holder = nullptr; }
	/// �C�ӂ�?�̒l����쐬�B
	template<typename T>
	UniqueAny(T&& value) : _holder(new ConcreteHolder<std::remove_const<std::remove_reference<T>::type>::type>(std::forward<T>(value))) {}
	~UniqueAny() {
		delete _holder;
		//_holder = nullptr;
	}

	UniqueAny& operator=(UniqueAny&& value) {
		std::swap(_holder, value._holder);
		return *this;
	}
	/// �C�ӂ�?�̒l����ԁB
	template<typename T>
	UniqueAny& operator=(T&& value) {
		UniqueAny temp(std::forward<T>(value));
		std::swap(_holder, temp._holder);
		return *this;
	}

public:
	/// �e���v��?�g�����Ŏw�肵��?�Ńf�t�H���g�R���X�g���N�g���Ă��̎Q�Ƃ�Ԃ��B�R�s?��ړ�����?����Ȃ�?�p�B
	template<typename T>
	T& assign() {
		delete _holder;
		_holder = new ConcreteHolder<T>();
		return static_cast<ConcreteHolder<T>*>(_holder)->content;
	}
	///	�l�����Ԃ���Ă��邩�ǂ����B
	bool empty() const { return _holder == nullptr; }
	/// ���Ԃ���Ă���l��?���B���Ԃ���Ă��Ȃ��ꍇ�� void ��?����Ԃ��B
	const type_info& type() const { return _holder ? _holder->type() : typeid(void); }

	/// �l��?���w�肵�Ď擾����B���Ԃ���Ă��Ȃ��ꍇ��?���Ԉ���Ă���ꍇ�� UniqueAny::BadCastException �𓊂���B
	template<typename T>
	friend T any_cast(UniqueAny& any) {
		typedef std::remove_const<std::remove_reference<T>::type>::type PureT;
		ConcreteHolder<PureT>* _holder = dynamic_cast<ConcreteHolder<PureT>*>(any._holder);
		if (!_holder) {
			throw BadCastException();
		}
		return _holder->content;
	}
	template<typename T>
	friend T any_cast(const UniqueAny& any) {
		typedef std::remove_const<std::remove_reference<T>::type>::type PureT;
		return any_cast<const PureT&>(const_cast<UniqueAny&>(any));
	}

private:
	class Holder {
	public:
		virtual ~Holder() {}
		virtual const type_info& type() const = 0;
	};

	template<typename T>
	class ConcreteHolder : public Holder {
	public:
		ConcreteHolder() {}
		ConcreteHolder(T&& value) : content(std::move(value)) {}
		virtual ~ConcreteHolder() {}

		virtual const type_info& type() const { return typeid(T); }

	private:
		ConcreteHolder(const ConcreteHolder& );
		ConcreteHolder& operator=(const ConcreteHolder& );

	public:
		T content;
	};

private:
	Holder* _holder;
};
#pragma warning(pop)



}
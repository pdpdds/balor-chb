#pragma once

#include <typeinfo>
#include <utility>

#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>


namespace balor {



/**
 * 任意の型の値を代入できるクラス。
 * 
 * boost::any とだいたい同じだが、コピーを禁止しているのでコピーできない型も代入できる。
 * 現状ではどんなサイズの型であろうと代入するとメモリ割り当てを伴う。今後最適化の余地はあるかもしれないが
 * クラスのサイズは常にポインタ一個分であり、balor::gui::ListBox や balor::gui::ListView や balor::gui::TreeView 等のクラスはこれを利用して実装している。
 *
 * <h3>・サンプルコード</h3>
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
#pragma warning(disable : 4521) // '::balor::Any' : 複数のコピー コンストラクターが指定されています。
#pragma warning(disable : 4522) // '::balor::Any' : 複数の代入演算子が指定されています。
class UniqueAny : private NonCopyable {
public:
	/// any_cast した Any の内容が空だったり、型が間違っていた場合に投げられる例外。
	class BadCastException : public Exception {};

public:
	/// 空の状態で作成。
	UniqueAny() : _holder(nullptr) {}
	UniqueAny(UniqueAny&& value) : _holder(value._holder) { value._holder = nullptr; }
	/// 任意の型の値から作成。
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
	/// 任意の型の値を代入。
	template<typename T>
	UniqueAny& operator=(T&& value) {
		UniqueAny temp(std::forward<T>(value));
		std::swap(_holder, temp._holder);
		return *this;
	}

public:
	/// テンプレート引数で指定した型でデフォルトコンストラクトしてその参照を返す。コピーや移動が定義されない型用。
	template<typename T>
	T& assign() {
		delete _holder;
		_holder = new ConcreteHolder<T>();
		return static_cast<ConcreteHolder<T>*>(_holder)->content;
	}
	///	値が代入されているかどうか。
	bool empty() const { return _holder == nullptr; }
	/// 代入されている値の型情報。代入されていない場合は void の型情報を返す。
	const type_info& type() const { return _holder ? _holder->type() : typeid(void); }

	/// 値を型を指定して取得する。代入されていない場合や型が間違っている場合は UniqueAny::BadCastException を投げる。
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
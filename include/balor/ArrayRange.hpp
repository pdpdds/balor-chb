#pragma once

#include <balor/test/noMacroAssert.hpp>


namespace std {
	namespace tr1 {
#ifdef  _WIN64
		template<typename T, unsigned __int64> class array;
#else
		template<typename T, __w64 unsigned int> class array;
#endif
	}
	template<typename T> class allocator;
	template<typename T, typename A> class vector;
}


namespace balor {



/**
 * �z��̎n�_�ƏI�_�������Astd::vector�Astd::array�A�Œ蒷�z��A�|�C���^����ϊ��ł���B�l�X�Ȕz��\�������ʂ̊֐��C���^�[�t�F�[�X�Ŏ����ł���悤�ɂ���B
 *
 * ���̃N���X�͊֐��̈����Ɏg������z�肵�Ă���̂ŁA���[�J���ϐ���N���X�ϐ��ł̎g�p�͂��Ȃ����ƁB
 * �Ⴆ�΃R���X�g���N�^�� vector �̃e���|�����I�u�W�F�N�g��n���� ArrayRange �̃��[�J���ϐ����쐬�����
 * ArrayRange �͊��ɔj�󂳂ꂽ���������e���Q�Ƃ��Ă���̂ŃA�N�Z�X����΃v���O�����̓N���b�V������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Bitmap bitmap(100, 100, Bitmap::Format::palette8bpp);

	// ArrayRange �����ɌŒ蒷�z���n���B
	Color staticArray[] = {Color::red(), Color::green(), Color::blue()};
	bitmap.palette(staticArray);

	// ArrayRange ������ vector ��n���B
	std::vector<Color> stdVector;
	stdVector.push_back(Color::red());
	stdVector.push_back(Color::green());
	stdVector.push_back(Color::blue());
	bitmap.palette(stdVector);

	// ArrayRange �����Ƀ|�C���^�[�Ɣz��T�C�Y��n���B
	Color* pointer = staticArray;
	bitmap.palette(ArrayRange<const Color>(pointer, 3));
 * </code></pre>
 */
template<typename T>
class ArrayRange {
private:
	template<typename T> struct removeConst { typedef T type; };
	template<typename T> struct removeConst<const T> { typedef T type; };
	typedef typename removeConst<T>::type PureT;

public:
	/// �Œ蒷�z��ŏ������B
	template<int Size> ArrayRange(T (&array)[Size]) : _begin(array), _length(Size) {}
	/// �|�C���^�ƒ����ŏ������B
	ArrayRange(T* begin, int length) : _begin(begin), _length(length) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
#endif
	}
	/// vector �ŏ������B
	template<typename Allocator> ArrayRange(std::vector<PureT, Allocator>& array) : _begin(array.data()), _length(array.size()) {}
	/// const vector �ŏ������B
	template<typename Allocator> ArrayRange(const std::vector<PureT, Allocator>& array) : _begin(array.data()), _length(array.size()) {}
	/// array �ŏ������B
	template<int Size> ArrayRange(std::tr1::array<PureT, Size>& array) : _begin(array.data()), _length(Size) {}
	/// const array �ŏ������B
	template<int Size> ArrayRange(const std::tr1::array<PureT, Size >& array) : _begin(array.data()), _length(Size) {}

public:
	T* begin() { return _begin; }
	T* end() { return _begin + _length; }
	const T* begin() const { return _begin; }
	const T* end() const { return _begin + _length; }
	/// �z��T�C�Y���O�ł��邩�ǂ����B
	bool empty() const { return !_length; }
	int length() const { return _length; }
	int size() const { return _length; }

public:
	/// �z��v�f�ւ̃A�N�Z�X
	T& operator[](int index) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= index);
		::balor::test::noMacroAssert(index < length());
#endif
		return _begin[index];
	}

private:
	T* _begin;
	int _length;
};



}
#include "noMacroAssert.hpp"

#include <cassert>


namespace balor {
	namespace test {



#pragma warning(push)
#pragma warning(disable : 4100) // 'expression' : �����͊֐��̖{�̕��� 1 �x���Q�Ƃ���܂���B
void noMacroAssert(bool expression) {
	assert(expression);
}
#pragma warning(pop)



	}
}
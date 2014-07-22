#pragma once


namespace balor {


namespace detail {
/// scopeExit �Ŏg���֐����s�N���X�B
template<typename Function>
class ScopeExitFunctionHolder {
public:
	ScopeExitFunctionHolder(const Function& function) : function(function) {
	}
	ScopeExitFunctionHolder(const ScopeExitFunctionHolder& value) : function(value.function) {
		static_assert(false, "RVO (Return Value Optimization) is indispensable!"); // �߂�l�œK������Ȃ���������֐����Ă΂�Ă��܂��̂ŃG���[�ɂ���
	}
	~ScopeExitFunctionHolder() {
		function();
	}

private:
	ScopeExitFunctionHolder& operator=(const ScopeExitFunctionHolder& );

	Function function;
};
} // detail


template<typename Function>
::balor::detail::ScopeExitFunctionHolder<Function> makeScopeExit(const Function& function) {
	return ::balor::detail::ScopeExitFunctionHolder<Function>(function);
}

#if defined BALOR_DETAIL_CAT_STRING
#error BALOR_DETAIL_CAT_STRING macro is already defined
#endif
/// �}�N���萔���܂߂ĕ������A������}�N���֐�
#define BALOR_DETAIL_CAT_STRING(a, b) BALOR_DETAIL_CAT_STRING_IMPL(a, b)
#define BALOR_DETAIL_CAT_STRING_IMPL(a, b) a ## b


/**
 * �֐��I�u�W�F�N�g���f�X�g���N�g���Ɏ��s����I�u�W�F�N�g��������������}�N���֐��B
 *
 * boost/scope_exit.hpp �Ƃ������������B������ RAII �C�f�B�I���Ɏg�p����B
 * ���̋��낵���}�N���̓v���O������ scopeExit �Ƃ����P���S�ď��������Ă��܂��̂Ō����ăw�b�_�t�@�C���� include ���Ă͂Ȃ�Ȃ��B
 * �����̓R���p�C���̖߂�l�œK���̋����Ɉˑ����Ă���A�߂�l�œK������Ȃ������ꍇ�� static_assert �Ō��o���Ă���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Debug::enableMemoryLeakCheck();
	try {
		int* buffer = new int[64];
		scopeExit([&] () {
			delete [] buffer;
		});
		throw 0;
	} catch (...) { // �����Ń������J������Ă���B
	}
 * </code></pre>
 */
#define scopeExit auto BALOR_DETAIL_CAT_STRING(balor_scopeExit, __COUNTER__) = ::balor::makeScopeExit



}
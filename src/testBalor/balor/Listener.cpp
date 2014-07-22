#include <balor/Listener.hpp>

#include <string>
#include <utility>

#include <balor/test/InstanceTracer.hpp>
#include <balor/test/UnitTest.hpp>


namespace balor {
	namespace testListener {


using std::move;
using std::string;
using namespace balor::test;


namespace {
int callCount = 0;


void function(int) {
	++callCount;
}


struct TracedFunction {
	TracedFunction() {}
	TracedFunction(const TracedFunction& function) : tracer(function.tracer) {}
	TracedFunction(TracedFunction&& function) : tracer(move(function.tracer)) {}

	TracedFunction& operator=(const TracedFunction& function) {
		if (this != &function) {
			tracer = function.tracer;
		}
		return *this;
	}
	TracedFunction& operator=(TracedFunction&& function) {
		if (this != &function) {
			tracer = move(function.tracer);
		}
		return *this;
	}

	void operator()(int) {
		++callCount;
	}

	InstanceTracer tracer;
};


struct BigTracedFunction {
	BigTracedFunction() {}
	BigTracedFunction(const BigTracedFunction& function) : tracer(function.tracer) {}
	BigTracedFunction(BigTracedFunction&& function) : tracer(move(function.tracer)) {}

	BigTracedFunction& operator=(const BigTracedFunction& function) {
		if (this != &function) {
			tracer = function.tracer;
		}
		return *this;
	}
	BigTracedFunction& operator=(BigTracedFunction&& function) {
		if (this != &function) {
			tracer = move(function.tracer);
		}
		return *this;
	}

	void operator()(int) {
		dummy[0] = this;
		++callCount;
	}

	InstanceTracer tracer;
	void* dummy[10];
};


bool checkCallCount(const Listener<int>& listener) {
	if (!listener) {
		return false;
	}
	callCount = 0;
	listener(0);
	return callCount == 1;
}
} // namespace



testCase(nullFunction) {
	{// ���Listener
		Listener<int> empty;
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// copy construct
		Listener<int> empty;
		Listener<int> listener = empty;
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// const copy construct
		const Listener<int> empty;
		Listener<int> listener = empty;
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// move construct
		Listener<int> empty;
		Listener<int> listener = move(empty);
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// const move construct
		const Listener<int> empty;
		Listener<int> listener = move(empty);
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// ���
		Listener<int> empty;
		Listener<int> listener = [](int) {};
		testAssert(listener);
		testNoThrow(listener(0));
		Listener<int>& result = listener = empty;
		testAssert(&result == &listener);
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// const ���
		const Listener<int> empty;
		Listener<int> listener = [](int) {};
		Listener<int>& result = listener = empty;
		testAssert(&result == &listener);
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// �E�Ӓl���
		Listener<int> empty;
		Listener<int> listener = [](int) {};
		Listener<int>& result = listener = move(empty);
		testAssert(&result == &listener);
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
	{// const �E�Ӓl���
		const Listener<int> empty;
		Listener<int> listener = [](int) {};
		Listener<int>& result = listener = move(empty);
		testAssert(&result == &listener);
		testAssert(!listener);
		testNoThrow(listener(0));
		testAssert(!empty);
		testNoThrow(empty(0));
	}
}


testCase(functionPointer) {
	typedef void (*FunctionPointer)(int);

	{// �k���֐��|�C���^�ŏ�����
#if !defined(NDEBUG)
		typedef Listener<int> ListenerType;
		testAssertionFailed(ListenerType listener = (FunctionPointer)nullptr);
#else
		testAssert(true); // �e�X�g�������킹
#endif
	}
	{// �֐��|�C���^�ŏ�����
		Listener<int> listener = function;
		testAssert(checkCallCount(listener));
	}
	{// �k���֐��|�C���^�̑��
		Listener<int> listener;
#if !defined(NDEBUG)
		testAssertionFailed(listener = (FunctionPointer)nullptr);
#else
		testAssert(true); // �e�X�g�������킹
#endif
	}
	{// �֐��|�C���^�̑��
		Listener<int> listener;
		listener = function;
		testAssert(checkCallCount(listener));
	}
	{// copy construct
		Listener<int> source = function;
		Listener<int> listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const copy construct
		const Listener<int> source = function;
		Listener<int> listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// move construct
		Listener<int> source = function;
		Listener<int> listener = move(source);
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const move construct
		const Listener<int> source = function;
		Listener<int> listener = move(source);
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// ���
		Listener<int> source = function;
		Listener<int> listener;
		listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const ���
		const Listener<int> source = function;
		Listener<int> listener;
		listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// �E�Ӓl���
		Listener<int> source = function;
		Listener<int> listener;
		listener = move(source);
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const �E�Ӓl���
		const Listener<int> source = function;
		Listener<int> listener;
		listener = move(source);
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
}


testCase(functionObject) {
	{// �֐��I�u�W�F�N�g�ŏ�����
		TracedFunction tracedFunction;
		{
			InstanceTracer::clearAllCount();
			Listener<int> listener = tracedFunction;
			testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
			testAssert(checkCallCount(listener));
		}
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 1)); // �f�X�g���N�^�Ăяo�����`�F�b�N
	}
	{// �֐��I�u�W�F�N�g�̉E�Ӓl�ŏ�����
		TracedFunction tracedFunction;
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��I�u�W�F�N�g�̑��
		TracedFunction tracedFunction;
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = tracedFunction;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��I�u�W�F�N�g�̉E�Ӓl�̑��
		TracedFunction tracedFunction;
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �㏑���Ńf�X�g���N�^���Ă΂�鎖�̊m�F
		Listener<int> listener = TracedFunction();
		InstanceTracer::clearAllCount();
		listener = Listener<int>();
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 1));
		testAssert(!listener);
	}
	{// copy construct
		Listener<int> source = TracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const copy construct
		const Listener<int> source = TracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// move construct
		Listener<int> source = TracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const move construct
		const Listener<int> source = TracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// ���
		Listener<int> source = TracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
		InstanceTracer::clearAllCount();
		listener = listener; // ���ȑ���̃`�F�b�N
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0));
	}
	{// const ���
		const Listener<int> source = TracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
		const Listener<int>& constListener = listener;
		InstanceTracer::clearAllCount();
		listener = constListener; // ���ȑ���̃`�F�b�N
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0));
	}
	{// �E�Ӓl���
		Listener<int> source = TracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
		InstanceTracer::clearAllCount();
		listener = move(listener); // ���ȑ���̃`�F�b�N
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0));
	}
	{// const �E�Ӓl���
		const Listener<int> source = TracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
		const Listener<int>& constListener = listener;
		InstanceTracer::clearAllCount();
		listener = move(constListener); // ���ȑ���̃`�F�b�N
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0));
	}
}


testCase(allocatedFunctionObject) {
	// AllocatedFunctionObject�����蓖�Ă���������`�F�b�N
	testAssert(sizeof(void*) < sizeof(BigTracedFunction));

	{// �֐��I�u�W�F�N�g�ŏ�����
		BigTracedFunction tracedFunction;
		{
			InstanceTracer::clearAllCount();
			Listener<int> listener = tracedFunction;
			testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
			testAssert(checkCallCount(listener));
		}
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 1)); // �f�X�g���N�^�Ăяo�����`�F�b�N
	}
	{// �֐��I�u�W�F�N�g�̉E�Ӓl�ŏ�����
		BigTracedFunction tracedFunction;
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��I�u�W�F�N�g�̑��
		BigTracedFunction tracedFunction;
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = tracedFunction;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��I�u�W�F�N�g�̉E�Ӓl�̑��
		BigTracedFunction tracedFunction;
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �㏑���Ńf�X�g���N�^���Ă΂�鎖�̊m�F
		Listener<int> listener = BigTracedFunction();
		InstanceTracer::clearAllCount();
		listener = Listener<int>();
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 1));
		testAssert(!listener);
	}
	{// copy construct
		Listener<int> source = BigTracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const copy construct
		const Listener<int> source = BigTracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// move construct
		Listener<int> source = BigTracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0)); // �|�C���^�ړ��̂�
		testAssert(checkCallCount(listener));
		testAssert(!source);
	}
	{// const move construct
		const Listener<int> source = BigTracedFunction();
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// ���
		Listener<int> source = BigTracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// const ���
		const Listener<int> source = BigTracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// �E�Ӓl���
		Listener<int> source = BigTracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0)); // �|�C���^�ړ��̂�
		testAssert(checkCallCount(listener));
		testAssert(!source);
	}
	{// const �E�Ӓl���
		const Listener<int> source = BigTracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
}


testCase(lambdaFunctionObject) {
	auto lambda = [](int) { ++callCount; };
	{// lambda�ŏ�����
		Listener<int> listener = lambda;
		testAssert(checkCallCount(listener));
	}
	{// lambda�̑��
		Listener<int> listener;
		listener = lambda;
		testAssert(checkCallCount(listener));
	}
	{// copy construct
		Listener<int> source = lambda;
		Listener<int> listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// ���
		Listener<int> source = lambda;
		Listener<int> listener;
		listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
}


testCase(bigLambdaFunctionObject) {
	int a = 11;
	int b = 21;
	auto lambda = [&](int) { callCount = callCount + (a * 2) - b; };
	// AllocatedFunctionObject�����蓖�Ă�������̃`�F�b�N
	testAssert(sizeof(void*) < sizeof(lambda));

	{// lambda�ŏ�����
		Listener<int> listener = lambda;
		testAssert(checkCallCount(listener));
	}
	{// lambda�̑��
		Listener<int> listener;
		listener = lambda;
		testAssert(checkCallCount(listener));
	}
	{// copy construct
		Listener<int> source = lambda;
		Listener<int> listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
	{// ���
		Listener<int> source = lambda;
		Listener<int> listener;
		listener = source;
		testAssert(checkCallCount(listener));
		testAssert(checkCallCount(source));
	}
}


testCase(listenerChain) {
	auto dummyFunction = [](int) {};

	{// �֐��I�u�W�F�N�g�̒ǉ�
		TracedFunction tracedFunction;
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener += tracedFunction;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��I�u�W�F�N�g�̒ǉ��i��Ԗځj
		TracedFunction tracedFunction;
		Listener<int> listener;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += tracedFunction;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��I�u�W�F�N�g�̒ǉ��i�O�Ԗځj
		TracedFunction tracedFunction;
		Listener<int> listener;
		listener += dummyFunction;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += tracedFunction;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �E�Ӓl�֐��I�u�W�F�N�g�̒ǉ�
		TracedFunction tracedFunction;
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener += move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �E�Ӓl�֐��I�u�W�F�N�g�̒ǉ��i��Ԗځj
		TracedFunction tracedFunction;
		Listener<int> listener;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �E�Ӓl�֐��I�u�W�F�N�g�̒ǉ��i�O�Ԗځj
		TracedFunction tracedFunction;
		Listener<int> listener;
		listener += dummyFunction;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += move(tracedFunction);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �C�x���g�̒ǉ�
		Listener<int> add = TracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener += add;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �C�x���g�̒ǉ��i��Ԗځj
		Listener<int> add = TracedFunction();
		Listener<int> listener;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += add;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �C�x���g�̒ǉ��i�O�Ԗځj
		Listener<int> add = TracedFunction();
		Listener<int> listener;
		listener += dummyFunction;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += add;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallCount(listener));
	}
	{// �E�Ӓl�C�x���g�̒ǉ�
		Listener<int> add = TracedFunction();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener += move(add);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �E�Ӓl�C�x���g�̒ǉ��i��Ԗځj
		Listener<int> add = TracedFunction();
		Listener<int> listener;
		listener += dummyFunction;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += move(add);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �E�Ӓl�C�x���g�̒ǉ��i�O�Ԗځj
		Listener<int> add = TracedFunction();
		Listener<int> listener;
		listener += dummyFunction;
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener += move(add);
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 0));
		testAssert(checkCallCount(listener));
	}
	{// �֐��ǉ����̏���
		Listener<int> listener = TracedFunction();;
		InstanceTracer::clearAllCount();
		listener += dummyFunction;
		testAssert(InstanceTracer::checkAllCount(0, 0, 2, 2));
		InstanceTracer::clearAllCount();
		listener += dummyFunction;
		testAssert(InstanceTracer::checkAllCount(0, 0, 1, 1));
		testAssert(checkCallCount(listener));
	}
	{// �㏑���Ńf�X�g���N�^���Ă΂�鎖�̊m�F
		Listener<int> listener = TracedFunction();
		listener += dummyFunction;
		InstanceTracer::clearAllCount();
		listener = Listener<int>();
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 1));
		testAssert(!listener);
	}

	string result;
	auto functionA = [&] (int) { result += "a"; };
	auto functionB = [&] (int) { result += "b"; };
	auto getTestListener = [&] () -> Listener<int> {
		Listener<int> listener;
		listener += functionA;
		listener += functionB;
		listener += TracedFunction();
		return move(listener);
	};
	auto checkCallChain = [&](const Listener<int>& listener) -> bool {
		result.clear();
		if (!checkCallCount(listener)) {
			return false;
		}
		return result == "ab";
	};

	{// copy construct
		Listener<int> source = getTestListener();
		InstanceTracer::clearAllCount();
		Listener<int> listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallChain(listener));
		testAssert(checkCallChain(source));
	}
	{// const copy construct
		const Listener<int> source = getTestListener();
		InstanceTracer::clearAllCount();
		Listener<int> listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallChain(listener));
		testAssert(checkCallChain(source));
	}
	{// move construct
		Listener<int> source = getTestListener();
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0)); // �|�C���^�ړ��̂�
		testAssert(checkCallChain(listener));
		testAssert(!source);
	}
	{// const move construct
		const Listener<int> source = getTestListener();
		InstanceTracer::clearAllCount();
		Listener<int> listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallChain(listener));
		testAssert(checkCallChain(source));
	}
	{// ���
		Listener<int> source = getTestListener();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallChain(listener));
		testAssert(checkCallChain(source));
	}
	{// const ���
		const Listener<int> source = getTestListener();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = source;
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallChain(listener));
		testAssert(checkCallChain(source));
	}
	{// �E�Ӓl���
		Listener<int> source = getTestListener();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 0, 0, 0)); // �|�C���^�ړ��̂�
		testAssert(checkCallChain(listener));
		testAssert(!source);
	}
	{// const �E�Ӓl���
		const Listener<int> source = getTestListener();
		Listener<int> listener;
		InstanceTracer::clearAllCount();
		listener = move(source);
		testAssert(InstanceTracer::checkAllCount(0, 1, 0, 0));
		testAssert(checkCallChain(listener));
		testAssert(checkCallChain(source));
	}
}


testCase(pop) {
	{// ��� Listener
		Listener<int> listener;
		callCount = 0;
		listener.pop();
		listener(0);
		testAssert(callCount == 0);
	}
	{// �֐���� Listener
		Listener<int> listener;
		listener += [&] (int ) { ++callCount; };
		callCount = 0;
		listener.pop();
		listener(0);
		testAssert(callCount == 0);
	}
	{// �����֐��� Listener
		Listener<int> listener;
		listener += [&] (int ) { ++callCount; };
		listener += [&] (int ) { ++callCount; };
		callCount = 0;
		listener.pop();
		listener(0);
		testAssert(callCount == 1);
	}
	{// �����֐�����ɂ��� Listener
		Listener<int> listener;
		listener += [&] (int ) { ++callCount; };
		listener += [&] (int ) { ++callCount; };
		callCount = 0;
		listener.pop();
		listener.pop();
		listener(0);
		testAssert(callCount == 0);
	}
}



	}
}
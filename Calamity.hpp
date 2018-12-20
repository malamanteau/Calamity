#pragma once

#include <cassert>
#include <csignal>
#include <cstdint>
#include <exception>
#include <vector>

// Based on: 
//     https://spin.atomicobject.com/2013/01/13/exceptions-stack-traces-c/
//     https://www.codeproject.com/Articles/154686/SetUnhandledExceptionFilter-and-the-C-C-Runtime-Li
// Used for testing of error handling.
// Run any of these static methods to trigger the calamitous error condition of your choosing!

#ifdef CALAMITY_NS
	namespace CALAMITY_NS {
#endif	 

class Calamity
{
public:
	static void DivideByZero();
	static void InvalidAccess();
	static void StackOverflow();
	static void AssertFalse();
	static void AbortCall();
	static void OutOfBoundsStdVector();
	static void UninitedVirtCallInCtor();
	static void InfiniteLoop();
	static void IllegalInstruction();
	static void ThrowStdException();
	static void ThrowNumber42();

	class CustomException { };
	static void ThrowCustomException();
};

// static 
inline void Calamity::DivideByZero()
{
	volatile uint64_t a = 1;
	volatile uint64_t b = 1;
	b--;
	volatile uint64_t c = a / b;
}

// static
inline void Calamity::InvalidAccess()
{
	char * p = 0;
	*p = 5;
}

static uint64_t calamity_helper_so(volatile uint64_t & i)
{
	if (i < 1) return i;
	return calamity_helper_so(++i);
}

// static
inline void Calamity::StackOverflow()
{
	volatile uint64_t i = 1;
	calamity_helper_so(i);
}

// static 
inline void Calamity::AssertFalse()
{
	assert(false);
}

// static
inline void Calamity::AbortCall()
{
	abort();
}

// static 
inline void Calamity::OutOfBoundsStdVector()
{
	std::vector<int> v;
	v[0] = 5;
}

// static 
inline void Calamity::UninitedVirtCallInCtor()
{
	struct B
	{
		B() { Bar(); }
		virtual void Foo() = 0;
		void Bar() { Foo(); }
	};

	struct D: public B
	{
		void Foo() { }
	};

	B * b = new D;
	// Just to silence the warning C4101:
	//    'VirtualFunctionCallCrash::B::Foo' : unreferenced local variable
	b->Foo(); 
}

// break out with ctrl+c to test SIGINT handling
// static 
inline void Calamity::InfiniteLoop()
{
	while(true) {};
}

// static 
inline void Calamity::IllegalInstruction()
{
	// I couldn't find an easy way to cause this one, so I'm cheating
	raise(SIGILL);
}

// static 
inline void Calamity::ThrowStdException()
{
	throw std::exception();
}

// static 
inline void Calamity::ThrowNumber42()
{
	throw 42;
}

// static 
inline void Calamity::ThrowCustomException()
{
	throw CustomException();
}	
	
#ifdef CALAMITY_NS
}
#endif

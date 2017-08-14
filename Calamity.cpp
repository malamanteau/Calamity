
#include "Calamity.hpp"

#include <cassert>
#include <csignal>
#include <exception>
#include <vector>

// static 
int Calamity::DivideByZero()
{
	int a = 1;
	int b = 0; 
	return a / b;
}

// static
void Calamity::Segfault()
{
	int * p = (int*)0x12345678;
	*p = 0;
}

// static
void Calamity::InvalidAccess()
{
	char * p = 0;
	*p = 5;
}

// static
void Calamity::StackOverflow()
{
	int foo[1000]; //allocate something big on the stack
	(void)foo;
	StackOverflow();
}

// static 
void Calamity::AssertFalse()
{
	assert(false);
}

// static
void Calamity::AbortCall()
{
	abort();
}

// static 
void Calamity::OutOfBoundsStdVector()
{
	std::vector<int> v;
	v[0] = 5;
}

// static 
void Calamity::UninitedVirtCallInCtor()
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
void Calamity::InfiniteLoop()
{
	while(true) {};
}

// static 
void Calamity::IllegalInstruction()
{
	// I couldn't find an easy way to cause this one, so I'm cheating
	raise(SIGILL);
}

// static 
void Calamity::ThrowStdException()
{
	throw std::exception("This is a std::exception.");
}

// static 
void Calamity::ThrowNumber42()
{
	throw 42;
}

// static 
void Calamity::ThrowCustomException()
{
	throw CustomException();
}
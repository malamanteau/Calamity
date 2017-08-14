#pragma once

// Based on: 
//     https://spin.atomicobject.com/2013/01/13/exceptions-stack-traces-c/
//     https://www.codeproject.com/Articles/154686/SetUnhandledExceptionFilter-and-the-C-C-Runtime-Li
// Used for testing of error handling.
// Run any of these static methods to trigger the calamitous error condition of your choosing!
class Calamity
{
public:
	static int  DivideByZero();
	static void Segfault();
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

#pragma once
#include <csignal>
#include<string>


namespace Debug
{

	class AssertClass
	{
	public:




		void Assertion(bool condition, const char* currentFile = __builtin_FILE(),
			const char* currentFonction = __builtin_FUNCTION(),
			const int line = __builtin_LINE());
		AssertClass();
		~AssertClass();


	};
	static AssertClass* Assert = new Debug::AssertClass();


}




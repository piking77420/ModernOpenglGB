#include <Core/Debug/AssertClass.h>
#include<Core/Debug/LogClass.h>
#include <cassert>







using namespace Debug;





void AssertClass::Assertion(bool condition , const char* currentFile,
	const char* currentFonction,
	const int line)
{
#ifdef _DEBUG	
	if (!condition)
	{

		__debugbreak();
	}
#endif
#ifdef NDEBUG 
	if (!condition)
	{
		std::string file = GetCurrentFile(currentFile);
		std::string Fonction = currentFonction;	
		std::string Line = currentFile;
		std::string assertAt = file + ' ' + Fonction + ' ' + Line;

			

		if (IDYES == ::MessageBoxA(NULL, assertAt.c_str(), NULL, MB_YESNO))
			::PostQuitMessage(1);

		exit(0);
	}

#endif // NDEBUG 



}


AssertClass::AssertClass()
{
	
	if (Assert != nullptr)
		return;


}


AssertClass::~AssertClass()
{
}

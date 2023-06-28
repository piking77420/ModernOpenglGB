#include <Core/Debug/LogClass.h>




using namespace Debug;




void PrintConsole(const std::string color, const std::string& time, const std::string& message)
{

	std::cout << color;
	std::cout << time;
	std::cout << message << '\n';
	std::cout << WHITE;

}


void OpengFileAndPrint(std::fstream& debugLogStream, const std::string color, const std::string& time,const std::string& message)
{



	if (debugLogStream.is_open())
	{
		debugLogStream << time;
		debugLogStream << message;
		debugLogStream << '\n';
		debugLogStream.flush();
	}

	// out put in vs code
	OutputDebugStringA(time.c_str());
	OutputDebugStringA(message.c_str());

}



std::string GetTime()
{

	SYSTEMTIME st, lt;
	GetLocalTime(&lt);


	std::string time = "[" +  std::to_string(lt.wDay) + "D:" + std::to_string(lt.wHour) + "H:" + std::to_string(lt.wMinute) + "M:" + std::to_string(lt.wSecond) + "s" + "]\n" ;

	return time;
}



std::string GetCurrentFile(const std::string& currentPath)
{

	std::string tmpr ; 

	int count = 0;
	int currentIndexOflast = 0;
	for (size_t i = 0; i < currentPath.size(); i++)
	{
		if (currentPath.at(i) == '\\')
		{
			count++;
			currentIndexOflast = i;
		}
		
	}


	for (size_t i = currentIndexOflast + 1; i < currentPath.size(); i++)
	{
		tmpr.push_back(currentPath[i]);
	}


	return tmpr;
}


std::string ReturnMessage(const std::string& currentMessage ,const std::string& currentFile, const std::string& currentFonction,int line )
{
	std::string File = GetCurrentFile(currentFile);
	std::string Function = currentFonction;
	std::string message = currentMessage + " " + '\n' + File + '(' + std::to_string(line) + ')' + ": " + Function + '\n';


	return message;
}


void LogClass::LogWarning(const std::string& currentMessage
	, const char* currentFile,
	const char* currentFonction,
	const int line)
{

	std::string output = ReturnMessage(currentMessage, currentFile, currentFonction, line);
	std::string time = GetTime();
	PrintConsole(RED, time, output);

	OpengFileAndPrint(*debugLogStream, RED, time, output);


}

void LogClass::LogInfo(const std::string& currentMessage, const char* currentFile, const char* currentFonction, const int line )
{
	

#ifdef _DEBUG

	std::string output = ReturnMessage(currentMessage, currentFile, currentFonction, line);
	std::string time = GetTime();

	PrintConsole(WHITE, time, output);


	OpengFileAndPrint(*debugLogStream,WHITE, time, output);
#endif
}
void LogClass::LogGood(const std::string& currentMessage, const char* currentFile, const char* currentFonction, const int line)
{
	if (debugLogStream == nullptr || Log == nullptr)
		return;
#ifdef _DEBUG


	std::string output = ReturnMessage(currentMessage, currentFile, currentFonction, line);
	std::string time = GetTime();


	PrintConsole(GREEN, time, output);
	OpengFileAndPrint(*debugLogStream, GREEN, time, output);
#endif 

}

void Debug::LogClass::LogTODO(const std::string& currentMessage, const char* currentFile, const char* currentFonction, const int line)
{
#ifdef _DEBUG


	std::string output = ReturnMessage(currentMessage, currentFile, currentFonction, line);
	std::string time = GetTime();


	PrintConsole(PURPLE, time, output);
	OpengFileAndPrint(*debugLogStream, PURPLE, time, output);
#endif 

}

LogClass::LogClass()
{
	if (Log != nullptr)
		return;



}

LogClass::~LogClass()
{
}


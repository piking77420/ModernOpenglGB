#include <Core/Debug/LogClass.h>








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

	SYSTEMTIME lt;
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
			currentIndexOflast = (int)i;
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

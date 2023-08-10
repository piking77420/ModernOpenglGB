#pragma once
#include <iostream>
#include <string>
#include <stdarg.h>
#include <cassert>
#include <ostream>	
#include <fstream>
#include<chrono>
#include <filesystem>
#include <ctime>
#include <windows.h>	
#include <thread>


#define MAX_LOG_SIZE 10
#define LOG_PATH "Log/"
#define FORMAT "%"
const std::string LogFileName = "LOG";
const std::string LogFileformat = ".log";
const std::string FileName = LOG_PATH + LogFileName + LogFileformat;



#define WHITE "\x1b[0m"
#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define PURPLE "\x1b[35m"	



	





std::string GetTime();
std::string GetCurrentFile(const std::string& currentPath);
void OpengFileAndPrint(std::fstream& debugLogStream, const std::string color, const std::string& time, const std::string& message);
enum class STATELOG
{
	NONE, GOOD, WARNING, CRITICALERROR
};


namespace Debug
{


#define LOG(message, stateLog) \
        switch (stateLog)\
        { \
            case STATELOG::NONE: \
                std::cout << WHITE; \
                break; \
            case STATELOG::GOOD: \
                std::cout << GREEN; \
                break; \
            case STATELOG::WARNING: \
                std::cout << YELLOW; \
                break; \
            case STATELOG::CRITICALERROR: \
                std::cout << RED; \
                break; \
            default: \
                std::cout << WHITE; \
                break; \
        } \
        std::cout << GetTime() << message << GetCurrentFile(__builtin_FILE()) << " " << __builtin_FUNCTION() << " " << __builtin_LINE() << '\n' << '\n' << WHITE; \

}


/*


	inline void ReadePrint(int currentIndex,std::string& output, const std::string& currentMessage)
	{

	}

	template<typename First , typename... Rest>
	inline void ReadePrint(int& currentIndex,std::string& output,const std::string& currentMessage, const First& first , const Rest&... rest)
	{


		for (size_t i = currentIndex; i < currentMessage.size();)
		{
			i = currentIndex;

			if ((currentMessage[i] == '%' && currentMessage[i + 1] == 'f') || (currentMessage[i] == '%' && currentMessage[i + 1] == 'i'))
			{
				std::string currentOutpur = std::to_string(first) + " ";
				output += currentOutpur;	
				break;	
			}
			else
			{
				output.push_back(currentMessage[i]);
				currentIndex++;
			}
		}
		ReadePrint(currentIndex,output, currentMessage, rest...);



	}

	template<typename ...Param>
	inline void LogClass::Print(const char* format, Param ...param)
	{
		std::string currentMessage = format;
		std::string output;
		int index = 0;

		ReadePrint(index,output, currentMessage, param...);

		std::cout << output << std::endl;
		OpengFileAndPrint(*debugLogStream, WHITE ,GetTime(), output);

	}

}
*/
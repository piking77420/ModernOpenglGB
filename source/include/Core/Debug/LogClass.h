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

namespace Debug
{	
	// Need to init here due to variadique template 
	static std::fstream* debugLogStream = new std::fstream(FileName, std::ios_base::out);

	class LogClass
	{
	public:
		
		
		template<typename ...Param>
		void Print(const char* format, Param ...param);
		
		void LogInfo(const std::string& currentMessage
			, const char* currentFile = __builtin_FILE(),
			const char* currentFonction = __builtin_FUNCTION(),
			const int line = __builtin_LINE());


		void LogWarning(const std::string& currentMessage
			, const char* currentFile = __builtin_FILE(),
			const char* currentFonction = __builtin_FUNCTION(),
			const int line = __builtin_LINE());

		void LogGood(const std::string& currentMessage
			, const char* currentFile = __builtin_FILE(),
			const char* currentFonction = __builtin_FUNCTION(),
			const int line = __builtin_LINE());

		void LogTODO(const std::string& currentMessage
			, const char* currentFile = __builtin_FILE(),
			const char* currentFonction = __builtin_FUNCTION(),
			const int line = __builtin_LINE());

		LogClass();
		~LogClass();
	};

	static LogClass* Log = new Debug::LogClass();



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

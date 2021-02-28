#pragma once
#include <fstream>
#include <iomanip>
#include <string>

namespace ErrorList
{
class ErrorCatch
	{
	public:
		ErrorCatch(const char* name, const char* filename = { "" });
		~ErrorCatch();

		void setError(std::string errorName);
		void clear();
	private:
		std::string* logs = new std::string[25];
		std::string filename;
		int errorCount;
		std::string sessionName;
	};

}
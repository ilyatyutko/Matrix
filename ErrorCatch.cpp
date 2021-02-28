#include "ErrorCatch.h"

namespace ErrorList
{
	ErrorCatch::ErrorCatch(const char* name, const char* filename): sessionName(name)
	{
		this->filename = filename;
		std::ofstream out;
		out.open(this->filename, std::ios_base::app);
		out << std::endl << "NEW SESSION: " << sessionName << std::endl;
		out.close();
		errorCount = 0;
	}

	ErrorCatch::~ErrorCatch()
	{
		if (errorCount != 0)
		{
			std::ofstream out;
			out.open(filename, std::ios_base::app);
			for (int i = 0; i < errorCount; ++i)
				out << std::setw(10) << sessionName << ": "<< logs[i] << std::endl;
			out.close();
		}
		delete[] logs;
	}

	void ErrorCatch::setError(std::string errorName)
	{
		logs[errorCount] = errorName;
		++errorCount;
		if (errorCount == 25)
			this->clear();
	}

	void ErrorCatch::clear()
	{
		std::ofstream out;
		out.open(filename, std::ios_base::app);
		for (int i = 0; i < errorCount; ++i)
			out << std::setw(10) << sessionName << ": " << logs[i] << std::endl;
		out.close();
		errorCount = 0;
	}

}
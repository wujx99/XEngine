#pragma once

#include <string>
namespace XEg
{
	class FileDialogs
	{
	public:
		// return empty strings if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}

#pragma once

#include <string>
#include <optional>
namespace XEg
{
	class FileDialogs
	{
	public:
		// return empty strings if cancelled
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};
}

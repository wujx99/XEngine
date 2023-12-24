#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace XEg
{
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;

	public:
		Instrumentor()
			:m_CurrentSession(nullptr), m_ProfileCount(0)
		{

		}
		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";
			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');
			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";
			m_OutputStream.flush();
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};


	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			:m_Name(name), m_Stop(false)
		{
			m_TimeBegin = std::chrono::high_resolution_clock::now();
		}
		~InstrumentationTimer()
		{
			if (!m_Stop)
				Stop();
		}
		void Stop()
		{
			auto TimeEnd = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_TimeBegin).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(TimeEnd).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });
			m_Stop = true;

			
		}

	private:
		const char* m_Name;
		bool m_Stop;
		std::chrono::time_point<std::chrono::steady_clock> m_TimeBegin;
	};
	
}

#define XE_PROFILE 1
#if XE_PROFILE
#define XE_PROFILE_BEGIN_SESSION(name, filepath) ::XEg::Instrumentor::Get().BeginSession(name, filepath)
#define XE_PROFILE_END_SESSION() ::XEg::Instrumentor::Get().EndSession()
#define CONCAT(x, y) x ## y
#define C(x, y) CONCAT(x, y)
#define XE_PROFILE_SCOPE(name) ::XEg::InstrumentationTimer C(timer, __LINE__)(name);
#define XE_PROFILE_FUNCTION() XE_PROFILE_SCOPE(__FUNCSIG__)
#else
#define XE_PROFILE_BEGIN_SESSION(name, filepath)
#define XE_PROFILE_END_SESSION()
#define XE_PROFILE_SCOPE(name)
#define XE_PROFILE_FUNCTION()
#endif
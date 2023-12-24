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
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;

	public:
		Instrumentor()
			:m_CurrentSession(nullptr)
		{

		}
		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					XE_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();

			}
			m_OutputStream.open(filepath);
			if (m_OutputStream.is_open()) 
			{
				m_CurrentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else 
			{
				if (Log::GetCoreLogger()) 
				{ // Edge case: BeginSession() might be before Log::Init()
					XE_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;
			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.End - result.Start) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start;
			json << "}";
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) 
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
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
		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession() 
		{
			if (m_CurrentSession) 
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
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

			Instrumentor::Get().WriteProfile({ m_Name, start, end, std::this_thread::get_id() });
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
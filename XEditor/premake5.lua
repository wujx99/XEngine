project "XEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/XEngine/vendor/spdlog/include",
		"%{wks.location}/XEngine/src",
		"%{wks.location}/XEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"XEngine"
	}

	filter "system:windows"
		
		systemversion "latest"

		
		
	filter "configurations:Debug"
		defines "XE_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "XE_RELEASE"
		runtime "Release"
		optimize "on"
	filter "configurations:Debug"
		defines "XE_DIST"
		runtime "Release"
		optimize "on"
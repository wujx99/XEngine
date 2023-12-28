workspace "XEngine"
	architecture "x86_64"
	
	startproject "XEditor"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "XEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "XEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "XEngine/vendor/imgui"
IncludeDir["glm"] = "XEngine/vendor/glm"
IncludeDir["stb_image"] = "XEngine/vendor/stb_image"
IncludeDir["entt"] = "XEngine/vendor/entt/include"

group "Dependencies"
	include "XEngine/vendor/GLFW"
	include "XEngine/vendor/Glad"
	include "XEngine/vendor/imgui"
group ""

project "XEngine"
	location "XEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "xepch.h"
	pchsource "XEngine/src/xepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}"
	}
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib",
	}

	filter "system:windows"
		
		systemversion "latest"

		defines
		{
		}

		


	filter "configurations:Debug"
		defines "XE_DEBUG"
		runtime "Debug"
		symbols "on"
		optimize "Off"
		
	filter "configurations:Release"
		defines "XE_RELEASE"
		runtime "Release"
		optimize "On"
	filter "configurations:Debug"
		defines "XE_DIST"
		runtime "Release"
		optimize "On"


		project "XEditor"
	location "XEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"XEngine/vendor/spdlog/include",
		"XEngine/src",
		"XEngine/vendor",
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


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"XEngine/vendor/spdlog/include",
		"XEngine/src",
		"XEngine/vendor",
		"%{IncludeDir.glm}"
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


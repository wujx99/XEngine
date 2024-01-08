include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "XEngine"
	architecture "x86_64"
	
	startproject "XEditor"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



group "Dependencies"
	include "vendor/premake"
	include "XEngine/vendor/GLFW"
	include "XEngine/vendor/Glad"
	include "XEngine/vendor/imgui"
	include "XEngine/vendor/yaml-cpp"
group ""

include "XEngine"
include "Sandbox"
include "XEditor"







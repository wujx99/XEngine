include "./vendor/premake/premake_customization/solution_items.lua"

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

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/XEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/XEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/XEngine/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/XEngine/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/XEngine/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/XEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/XEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/XEngine/vendor/ImGuizmo"


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







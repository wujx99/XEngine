
-- XEngine Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/XEngine/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/XEngine/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/XEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/XEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/XEngine/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/XEngine/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/XEngine/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/XEngine/vendor/entt/include"
IncludeDir["shaderc"] = "%{wks.location}/XEngine/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/XEngine/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/XEngine/vendor/VulkanSDK/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
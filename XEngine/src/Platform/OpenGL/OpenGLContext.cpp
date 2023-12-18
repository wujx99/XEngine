#include "xepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace XEg
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		XE_CORE_ASSERT(m_WindowHandle, "window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		XE_CORE_ASSERT(status, "Failed to initial glad");

		XE_CORE_INFO("OpenGL Info:");
		XE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		XE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		XE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}


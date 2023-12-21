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

#ifdef XE_DEBUG
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		XE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Hazel requires at least OpenGL version 4.5!");
#endif

	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}


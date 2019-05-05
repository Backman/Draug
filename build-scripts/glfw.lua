function glfwProject()
	project "glfw"
	kind "StaticLib"
	language "C"
	files {
		path.join(GLFW_DIR, "include/GLFW/*.h"),
		path.join(GLFW_DIR, "src/context.c"),
		path.join(GLFW_DIR, "src/egl_context.*"),
		path.join(GLFW_DIR, "src/init.c"),
		path.join(GLFW_DIR, "src/input.c"),
		path.join(GLFW_DIR, "src/internal.h"),
		path.join(GLFW_DIR, "src/monitor.c"),
		path.join(GLFW_DIR, "src/osmesa_context.*"),
		path.join(GLFW_DIR, "src/vulkan.c"),
		path.join(GLFW_DIR, "src/window.c"),
	}
	includedirs { path.join(GLFW_DIR, "include") }
	configuration { "windows" }
		defines {
			"_GLFW_WIN32"
		}
		files {
			path.join(GLFW_DIR, "src/win32_*.*"),
			path.join(GLFW_DIR, "src/wgl_context.*")
		}
	configuration { "linux" }
		defines { 
			"_GLFW_X11"
		}
		files {
			path.join(GLFW_DIR, "src/glx_context.*"),
			path.join(GLFW_DIR, "src/linux*.*"),
			path.join(GLFW_DIR, "src/posix*.*"),
			path.join(GLFW_DIR, "src/x11*.*"),
			path.join(GLFW_DIR, "src/xkb*.*")
		}
	configurations { "vs*" }
		defines "_CRT_SECURE_NO_WARNINGS"
	configurations{}
end

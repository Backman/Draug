newoption {
	trigger = "window-api",
	description = "Choose a particular window API",
	allowed = {
		{ "glfw", "GLFW" },
		{ "sdl", "SDL" }
	}
}

ROOT_DIR = (path.getabsolute("..") .. "/")
DRAUG_RESOURCE_DIR = path.join(ROOT_DIR, "resources/")
DRAUG_SRC_DIR = path.join(ROOT_DIR, "src/")
DRAUG_PLAYGROUND_SRC_DIR = path.join(ROOT_DIR, "playground/")

BUILD_DIR = path.join(ROOT_DIR, ".build/")
OUTPUT_DIR = path.join(BUILD_DIR, "bin/")
PROJECT_DIR = path.join(BUILD_DIR, "projects/")
DEPS_DIR = path.join(ROOT_DIR, "deps/")

SPDLOG_DIR = path.join(DEPS_DIR, "spdlog/")
SPDLOG_INCLUDE_DIR = path.join(SPDLOG_DIR, "include/")

SDL_DIR = path.join(DEPS_DIR, "SDL2/")
SDL_INCLUDE_DIR = path.join(SDL_DIR, "include/")
SDL_LIB_DIR = path.join(SDL_DIR, "lib/")

SDL_IMAGE_DIR = path.join(DEPS_DIR, "SDL2_Image/")
SDL_IMAGE_INCLUDE_DIR = path.join(SDL_IMAGE_DIR, "include/")
SDL_IMAGE_LIB_DIR = path.join(SDL_IMAGE_DIR, "lib/")

GLFW_DIR = path.join(DEPS_DIR, "glfw/")
GLFW_INCLUDE_DIR = path.join(GLFW_DIR, "include/")

ENTT_DIR = path.join(DEPS_DIR, "entt/")
ENTT_INCLUDE_DIR = path.join(ENTT_DIR, "src/")
ENTT_SINGLE_INCLUDE_DIR = path.join(ENTT_DIR, "single_include/")

BGFX_DIR = path.join(DEPS_DIR, "bgfx/")
BGFX_SCRIPTS_DIR = path.join(BGFX_DIR, "scripts/")
BGFX_INCLUDE_DIR = path.join(BGFX_DIR, "include/")

BX_DIR = path.join(DEPS_DIR, "bx/")
BX_SCRIPTS_DIR = path.join(BX_DIR, "scripts/")
BX_INCLUDE_DIR = path.join(BX_DIR, "include/")

BIMG_DIR = path.join(DEPS_DIR, "bimg/")
BIMG_SCRIPTS_DIR = path.join(BIMG_DIR, "scripts/")
BIMG_INCLUDE_DIR = path.join(BIMG_DIR, "include/")

IMGUI_DIR = path.join(DEPS_DIR, "imgui/")
IMGUI_SRC_DIR = path.join(IMGUI_DIR, "dear-imgui/")

function createProject(_name, _kind, _projectDir, _libs, _includes) 
	project (_name)
		uuid (os.uuid(_name))
		kind (_kind)
		language "C++"
		flags {
			"NoExceptions",
			"NoRTTI",
		}
		defines {
			"DRAUG_BGFX_RENDERER",
		}
		files {
			_projectDir .. "**.h",
			_projectDir .. "**.cpp",
		}



		includedirs {
			DRAUG_SRC_DIR,
			SPDLOG_INCLUDE_DIR,
			GLFW_INCLUDE_DIR,
			BGFX_INCLUDE_DIR,
			BX_INCLUDE_DIR,
			BIMG_INCLUDE_DIR,
			ENTT_INCLUDE_DIR,
			IMGUI_DIR,
		}

		links {
			"bgfx",
			"bx",
			"bimg",
			"bimg_encode",
			"bimg_decode",
			"imgui",
		}

		for _, _lib in ipairs(_libs) do
			links {
				_lib
			}
		end

		for _, _dir in ipairs(_includes) do
			includedirs {
				_dir
			}
		end
		
		local useSDL = false
		local useGLFW = false
		if _OPTIONS["window-api"] then
			useSDL = _OPTIONS["window-api"] == "sdl"
			useGLFW = _OPTIONS["window-api"] == "glfw"
		else
			useGLFW = true
		end

		if useSDL then
			defines {
				"DRAUG_SDL",
			}
			includedirs {
				SDL_INCLUDE_DIR,
			}
			links {
				"SDL2",
				"bz2",
				"freetype",
				"jpeg",
				"libpng16",
				"lzma",
				"SDL2_image",
				"SDL2_ttf",
				"tiff",
				"tiffxx",
				"turbojpeg",
				"zlib",
			}
		elseif useGLFW then
			defines {
				"DRAUG_GLFW",
			}
			includedirs {
				GLFW_INCLUDE_DIR,
			}
			links {
				"glfw3",
			}
		end

		configuration { "not osx", "not asmjs" }
			defines {
				"DRAUG_RESOURCE_PATH=\"" .. DRAUG_RESOURCE_DIR .. "\"",
			}

		configuration {}
end

-- Required for bgfx
function copyLib()
end

solution "Draug"
	configurations {
		"Release",
		"Debug"
	}
	platforms {
		"x64"
	}
	language "C++"
	startproject "DraugPlayground"

dofile "toolchain.lua"
draugToolchain(BUILD_DIR, PROJECT_DIR, OUTPUT_DIR, DEPS_DIR)

group "Deps"
dofile "glfw.lua"
glfwProject()

dofile "imgui.lua"
imguiProject()

dofile(BGFX_SCRIPTS_DIR .. "/bgfx.lua")
dofile(BX_SCRIPTS_DIR .. "/bx.lua")
dofile(BIMG_SCRIPTS_DIR .. "/bimg.lua")
dofile(BIMG_SCRIPTS_DIR .. "/bimg_encode.lua")
dofile(BIMG_SCRIPTS_DIR .. "/bimg_decode.lua")

bgfxProject("", "StaticLib", {})
project "bimg_encode"
	configuration { "vs*", "not asmjs" }
        buildoptions {
            "/wd4244", -- warning C4244: '=': conversion from 'int' to 'vtype', possible loss of data
        }

	configuration {}

group "Draug"
createProject("Draug", "StaticLib", DRAUG_SRC_DIR, {}, {})

group "Playground"
createProject("DraugPlayground", "ConsoleApp", DRAUG_PLAYGROUND_SRC_DIR,
{
	"Draug",
},
{
	DRAUG_PLAYGROUND_SRC_DIR,
})

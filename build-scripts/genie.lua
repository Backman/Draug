
ROOT_DIR = (path.getabsolute("..") .. "/")
DRAUG_SRC_DIR = path.join(ROOT_DIR, "src/")
DRAUG_PLAYGROUND_SRC_DIR = path.join(ROOT_DIR, "playground/")

BUILD_DIR = path.join(ROOT_DIR, ".bin/")
PROJECT_DIR = path.join(ROOT_DIR, ".projects/")
DEPS_DIR = path.join(ROOT_DIR, "deps/")

SPDLOG_DIR = path.join(DEPS_DIR, "spdlog/")
SPDLOG_INCLUDE_DIR = path.join(SPDLOG_DIR, "include/")

SDL_DIR = path.join(DEPS_DIR, "SDL2/")
SDL_INCLUDE_DIR = path.join(SDL_DIR, "include/")
SDL_LIB_DIR = path.join(SDL_DIR, "lib/")

SDL_IMAGE_DIR = path.join(DEPS_DIR, "SDL2_Image/")
SDL_IMAGE_INCLUDE_DIR = path.join(SDL_IMAGE_DIR, "include/")
SDL_IMAGE_LIB_DIR = path.join(SDL_IMAGE_DIR, "lib/")

function createProject(_name, _kind, _projectDir, _libs, _includes) 
	project (_name)
		uuid (os.uuid(_name))
		kind (_kind)
		files {
			_projectDir .. "**.h",
			_projectDir .. "**.cpp",
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
draugToolchain(BUILD_DIR, PROJECT_DIR, DEPS_DIR)

group "Draug"
createProject("Draug", "StaticLib", DRAUG_SRC_DIR, {
	"SDL2",
	"SDL2main",
	"SDL2_image",
}, {
	DRAUG_SRC_DIR,
	SPDLOG_INCLUDE_DIR,
})

group "Playground"
createProject("DraugPlayground", "ConsoleApp", DRAUG_PLAYGROUND_SRC_DIR, {
	"Draug",
	"SDL2",
	"SDL2main",
	"SDL2_image",
},{
	DRAUG_PLAYGROUND_SRC_DIR,
	DRAUG_SRC_DIR,
	SPDLOG_INCLUDE_DIR,
})

postbuildcommands {
	"robocopy \"" .. DRAUG_PLAYGROUND_SRC_DIR .. "/Assets\" \"" .. path.join(PROJECT_DIR, _ACTION, "Assets") .. "\" /S /XO",
	"robocopy \"" .. DRAUG_PLAYGROUND_SRC_DIR .. "/Assets\" \"" .. path.join(BUILD_DIR, "x64_" .. _ACTION, "bin/Assets") .. "\" /S /XO"
}

configurations { "Debug" }
	postbuildcommands {
		"robocopy \"" .. DRAUG_PLAYGROUND_SRC_DIR .. "/Assets\" \"" .. path.join(BUILD_DIR, "x64_" .. _ACTION, "Debug/bin/Assets") .. "\" /S /XO"
	}
configurations { "Release" }
	postbuildcommands {
		"robocopy \"" .. DRAUG_PLAYGROUND_SRC_DIR .. "/Assets\" \"" .. path.join(BUILD_DIR, "x64_" .. _ACTION, "Release/bin/Assets") .. "\" /S /XO"
	}

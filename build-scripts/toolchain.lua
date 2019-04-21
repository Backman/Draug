
function draugToolchain(_buildDir, _projDir, _libDir)

	if (_ACTION == nil) then return false end

	location (path.join(_projDir, _ACTION))
	includedirs {
		SDL_INCLUDE_DIR,
		SDL_IMAGE_INCLUDE_DIR,
	}
	links {
		"SDL2",
		"SDL2_image",
		"turbojpeg",
		"libpng16",
		"zlib",
		"SDL2_ttf",
		"tiff",
		"lzma",
	}
	configuration { "Debug" }
		defines { "DEBUG", "_DEBUG" }
		flags { "Symbols" }
	configuration { "Release" }
		defines { "NDEBUG" }
		flags { "Optimize" }

	configuration { "Debug", "x64" }
		local output_dir = path.join(_buildDir, "x64_" .. _ACTION, "Debug")
        targetdir (path.join(output_dir, "bin"))
        objdir (path.join(output_dir, "obj"))
        libdirs {
			path.join(SDL_LIB_DIR, "x64", "Debug"),
			path.join(SDL_IMAGE_LIB_DIR, "x64", "Debug"),
		}
	configuration { "Release", "x64" }
		local output_dir = path.join(_buildDir, "x64_" .. _ACTION, "Release")
        targetdir (path.join(output_dir, "bin"))
        objdir (path.join(output_dir, "obj"))
        libdirs {
			path.join(SDL_LIB_DIR, "x64", "Release"),
			path.join(SDL_IMAGE_LIB_DIR, "x64", "Release"),
		}
	
	configuration { "vs*" }
		defines {
			"WIN32",
			"_WIN32",
			"_HAS_EXCEPTIONS=0",
		}
        buildoptions {
			"/wd 4345", -- Disable 'An object of POD type constructed with an initializer of the form () will be default-initialized'. It's an obsolete warning.
			"/wd 26495", -- Disable 'Always initialize a member variable'
        }
        linkoptions {
            "/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
			"/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
			"/ignore:4099", -- LNK4099: The linker was unable to find your .pdb file.
        }

	configuration { "x64", "vs*" }
		defines { "_WIN64" }
        libdirs {
            "$(DXSDK_DIR)/lib/x64",
		}

	configuration "windows"
		links { 
			"user32",
			"gdi32",
			"imm32",
			"version",
			"psapi",
			"winmm",
		}
		defines {
			"DRAUG_WINDOWS"
		}

	configuration {}
end
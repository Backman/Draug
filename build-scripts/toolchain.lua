function setBxCompat()
	configuration { "vs*" }
		includedirs {
			path.join(BX_INCLUDE_DIR, "compat/msvc")
		}
	configuration { "windows", "gmake*" }
		includedirs {
			path.join(BX_INCLUDE_DIR, "compat/mingw")
		}
	configuration {}
end


function draugToolchain(_buildDir, _projDir, _libDir)

	if (_ACTION == nil) then return false end
	defines {
		"SDL_MAIN_HANDLED",
		"__STDC_LIMIT_MACROS",
		"__STDC_FORMAT_MACROS",
		"__STDC_CONSTANT_MACROS",
		"_CRT_SECURE_NO_WARNINGS",
	}
	setBxCompat()

	location (path.join(_projDir, _ACTION))
	configuration { "Debug" }
		defines {
			"DEBUG",
			"_DEBUG",
			"DRAUG_DEBUG",
			"BGFX_CONFIG_DEBUG=1",
		}
		flags {
			"Symbols"
		}
	configuration { "Release" }
		defines {
			"NDEBUG",
		}
		flags {
			"Optimize"
		}

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
			"/EHsc",
        }
        linkoptions {
            "/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
			"/ignore:4221", -- LNK4221: This object file does not define any previously undefined public symbols, so it will not be used by any link operation that consumes this library
			"/ignore:4099", -- LNK4099: The linker was unable to find your .pdb file.
		}

	configuration { "x64", "vs*" }
		defines { 
			"_WIN64"
		}
        libdirs {
            "$(DXSDK_DIR)/lib/x64",
		}

	configuration "windows"
		links { 
			"user32",
			"kernel32",
			"opengl32",
			"gdi32",
			"opengl32",
			"imm32",
			"version",
			"psapi",
			"winmm",
		}
		defines {
			"DRAUG_WINDOWS",
			"SDL_MAIN_HANDLED",
			"NOMINMAX",
		}

	configuration {}
end
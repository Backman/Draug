
function copyLib()
end


function draugToolchain(_buildsDir, _projectDir, _libDir)
	newoption {
		trigger = "static-lib",
		description = "Enable building static library.",
	}

    if (_ACTION == nil) then return false end

	location (path.join(_projectDir, _ACTION))

	configuration { "vs*" }
		defines { 
			"DRAUG_PLATFORM_WINDOWS"
		}

	configuration { "x32", "vs*" }
		defines { 
			"_WIN32",
			"DRAUG_X32"
		}
		targetdir (path.join(_buildsDir, "win32_" .. _ACTION, "bin"))
		objdir (path.join(_buildsDir, "win32_" .. _ACTION, "obj"))
		libdirs {
			path.join(_libDir, "lib/win32_" .. _ACTION),
			"$(DXSDK_DIR)/lib/x32",
		}

	configuration { "x64", "vs*" }
		defines { 
			"_WIN64",
			"DRAUG_X64"
		}
		targetdir (path.join(_buildsDir, "win64_" .. _ACTION, "bin"))
		objdir (path.join(_buildsDir, "win64_" .. _ACTION, "obj"))
		libdirs {
			path.join(_libDir, "lib/win64_" .. _ACTION),
			"$(DXSDK_DIR)/lib/x64",
		}
end
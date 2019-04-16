
function copyLib()
end

function includeDirs(...) 
	for _, dir in ipairs({...}) do
		includedirs {
			dir
		}
	end
end

function draugToolchain(_buildsDir, _projectDir, _libDirs)

    if (_ACTION == nil) then return false end

	local output_dir = path.join(_buildsDir, "win64_" .. _ACTION, "bin")
	location (path.join(_projectDir, _ACTION))
	targetdir (output_dir)
	objdir (path.join(_buildsDir, "win64_" .. _ACTION, "obj"))

	configuration { "Debug" }
		flags { "Symbols" }
		defines { "DEBUG" }
		links {	
			"sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-system-s-d",
			-- "sfml-audio-s-d",
			-- "sfml-network-s-d"
		}

	configuration { "Release" }
		defines { "NDEBUG" }
		flags { "Optimize" }
		links {	
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			-- "sfml-audio-s",
			-- "sfml-network-s"
		}

	configuration { "*" }
		defines { "SFML_STATIC" }
		libdirs {
			(_libDirs .. "**"),
		}

	configuration "windows"
		links { 
			"user32",
			"gdi32",
			"opengl32",
			"freetype",
			"winmm",
		}
		defines {
			"DRAUG_WINDOWS"
		}
end
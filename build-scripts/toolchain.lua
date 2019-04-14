
function copyLib()
end

function includeDeps(...) 
	for _, depDir in ipairs({...}) do
		includedirs {
			depDir
		}
	end
end

function draugToolchain(_buildsDir, _projectDir)

    if (_ACTION == nil) then return false end

	location (path.join(_projectDir, _ACTION))
	configuration { "Debug" }
		flags { "Symbols" }

	configuration "windows"
		links { 
			"user32", "gdi32"
		}
		defines {
			"DRAUG_WINDOWS"
		}

	targetdir (path.join(_buildsDir, "win64_" .. _ACTION, "bin"))
	objdir (path.join(_buildsDir, "win64_" .. _ACTION, "obj"))
end
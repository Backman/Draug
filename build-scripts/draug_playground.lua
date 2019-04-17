
function draugPlayground(_projectDir, _buildsDir, ...)
	project "DraugPlayground"
		uuid (os.uuid("DraugPlayground"))
		kind "ConsoleApp"
		files {
			_projectDir .. "**.h",
			_projectDir .. "**.cpp",
		}

		links {
			"Draug"
		}

		includeDirs(_projectDir, {...})

		local output_dir = path.join(_buildsDir, "win64_" .. _ACTION, "bin")
		postbuildcommands {
			"robocopy \"" .. _projectDir .. "Assets\" \"" .. output_dir .. "/Assets\" /S /XO"
		}
end
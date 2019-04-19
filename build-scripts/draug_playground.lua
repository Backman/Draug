
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
end
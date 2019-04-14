
function draugPlayground(_projectDir, _draugDir, ...)
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

        includedirs {
			_draugDir,
			_projectDir,
		}

		includeDeps(...)
end
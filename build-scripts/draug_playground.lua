
function draugPlayground(_projectDir, _draugDir, _depDir)
	project "DraugPlayground"
		uuid (os.uuid("DraugPlayground"))
		kind "ConsoleApp"
		files {
			_projectDir .. "**.h",
			_projectDir .. "**.cpp",
		}
		
        includedirs {
			_depDir,
			_draugDir,
			_projectDir,
		}
end
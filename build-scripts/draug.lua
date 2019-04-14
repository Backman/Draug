
function draugProject(_projectDir, ...)
	project "Draug"
		uuid (os.uuid("Draug"))
		kind "StaticLib"

		pchheader "draugpch.h"
		pchsource (_projectDir .. "draugpch.cpp")

		files {
			_projectDir .. "**.h",
			_projectDir .. "**.cpp"
		}
		
        includedirs {
			_projectDir,
		}

		includeDeps(...)
end
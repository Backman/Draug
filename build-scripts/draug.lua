
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
		
		defines {
			"DRAUG_SFML",
		}

		includeDirs(_projectDir, {...})
end
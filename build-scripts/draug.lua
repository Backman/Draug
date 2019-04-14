
function draugProject(_projectDir, _depsDir)
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
			_depsDir,
			_projectDir,
		}
end
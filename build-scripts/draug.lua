
function draugProject(_projectDir, _depsDir)
	local KIND = ""
	if _OPTIONS["static-lib"] then
		KIND = "StaticLib"
	else
		KIND = "SharedLib"
	end
	project "Draug"
		uuid (os.uuid("Draug"))
		if _OPTIONS["static-lib"] then
			kind "StaticLib"
		else
			kind "SharedLib"
			defines {
				"DRAUG_DYNAMIC_LIB",
				"HELLO"
			}
		end
		files {
			_projectDir .. "**.h",
			_projectDir .. "**.cpp",
		}
		
        includedirs {
			_depsDir,
			_projectDir,
		}

		copyLib()
end
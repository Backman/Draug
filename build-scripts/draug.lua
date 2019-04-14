
function draugProject(_projectDir, _depsDir)
	local KIND = ""
	if _OPTIONS["static-lib"] then
		KIND = "StaticLib"
	else
		KIND = "SharedLib"
	end
	project "Draug"
		uuid (os.uuid("Draug"))
		kind (KIND)
		if KIND == "SharedLib" then
			defines {
				"DRAUG_DYNAMIC_LIB",
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
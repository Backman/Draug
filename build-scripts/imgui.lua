function imguiProject()
	project "imgui"
		kind "StaticLib"
		language "C++"
		files {
			path.join(IMGUI_SRC_DIR, "*.h"),
			path.join(IMGUI_SRC_DIR, "*.cpp"),
		}
		includedirs {
			IMGUI_SRC_DIR
		}

		
		configuration{ "windows", "Release" }
			buildoptions {
				"/MT",
			}

		configuration{}
end

function glfwProject()
	project "entt"
		kind "StaticLib"
		language "C++"
		files {
			path.join(ENTT_INCLUDE_DIR, "entt/*.h"),
		}
		includedirs { path.join(ENTT_INCLUDE_DIR, "src/") }
		
		configuration{}
end

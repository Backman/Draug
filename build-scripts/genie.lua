
local ROOT_DIR = (path.getabsolute("..") .. "/")
local DRAUG_DIR = (ROOT_DIR .. "Draug/")
local DRAUG_PLAYGROUND_DIR = (ROOT_DIR .. "DraugPlayground/")

local BUILDS_DIR = (ROOT_DIR .. "_builds/")
local PROJECTS_DIR = (ROOT_DIR .. "_projects/")
local DEPS_DIR = (ROOT_DIR .. "deps/")

solution "Draug"
	configurations {
		"Release",
		"Debug"
	}
	platforms {
		"x64"
	}
	language "C++"
	startproject "DraugPlayground"

dofile "toolchain.lua"
draugToolchain(BUILDS_DIR, PROJECTS_DIR, DEPS_DIR)

dofile "draug.lua"
group "Draug"
draugProject(DRAUG_DIR, DEPS_DIR)

group "Playground"
dofile "draug_playground.lua"
draugPlayground(DRAUG_PLAYGROUND_DIR, DRAUG_DIR, DEPS_DIR)

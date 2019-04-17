
local ROOT_DIR = (path.getabsolute("..") .. "/")
local DRAUG_SRC_DIR = (ROOT_DIR .. "src/")
local DRAUG_PLAYGROUND_SRC_DIR = (ROOT_DIR .. "playground/")

local BUILDS_DIR = (ROOT_DIR .. ".bin/")
local PROJECTS_DIR = (ROOT_DIR .. ".projects/")
local DEPS_DIR = (ROOT_DIR .. "deps/")
local LIB_DIRS = (DEPS_DIR .. "libs/")

local SPDLOG_INCLUDE_DIR = (DEPS_DIR .. "spdlog/include/")
local SFML_INCLUDE_DIR = (DEPS_DIR .. "SFML/include/")


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
draugToolchain(BUILDS_DIR, PROJECTS_DIR, LIB_DIRS)

dofile "draug.lua"
group "Draug"
draugProject(DRAUG_SRC_DIR, SPDLOG_INCLUDE_DIR, SFML_INCLUDE_DIR)

group "Playground"
dofile "draug_playground.lua"
draugPlayground(DRAUG_PLAYGROUND_SRC_DIR, BUILDS_DIR, DRAUG_SRC_DIR, SFML_INCLUDE_DIR)

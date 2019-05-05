
VS2019_DEVENV_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
GENIE = ./build-scripts/genie.exe

PROJECTS_DIR_NAME = .projects
BUILDS_DIR_NAME = .bin

.PHONY: all
all: vs2017

.PHONY: all
all-sdl: vs2017-sdl

.PHONY: clean-projects
clean-projects:
	$(call remove_folder, $(PROJECTS_DIR_NAME))

.PHONY: clean-build
clean-build:
	$(call remove_folder, $(BUILDS_DIR_NAME))

.PHONY: clean
clean: clean-build clean-projects

.PHONY: .projects/vs2017 
vs2017:
	$(call make_project,vs2017,--window-api=glfw)
vs2017-sdl:
	$(call make_project,vs2017,--window-api=sdl)
vs-debug64:
	"$(subst /,\\,$(VS2019_DEVENV_DIR))\devenv" $(PROJECT_DIR)/vs2017/Draug.sln /Build "Debug|x64"
vs-release64:
	"$(subst /,\\,$(VS2019_DEVENV_DIR))\devenv" $(PROJECT_DIR)/vs2017/Draug.sln /Build "Release|x64"

define remove_folder
	@echo Removing $(1) folder
	-@rm -rf $(1)
endef

define make_project
	$(GENIE) --file=build-scripts/genie.lua $(2) $(1)
endef


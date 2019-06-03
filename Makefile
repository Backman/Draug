
VS2019_DEVENV_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE

ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
GENIE = ./tools/bin/genie.exe
SHADERC = ./tools/bin/shaderc.exe

BUILD_DIR = .build

.PHONY: all
all: vs2017

.PHONY: all
all-sdl: vs2017-sdl

.PHONY: clean
clean:
	$(call remove_folder, $(BUILD_DIR))

.PHONY: .projects/vs2017 
vs2017:
	$(call make_project,vs2017,--window-api=glfw)
vs2017-sdl:
	$(call make_project,vs2017,--window-api=sdl)
vs-debug64:
	"$(subst /,\\,$(VS2019_DEVENV_DIR))\devenv" $(PROJECT_DIR)/vs2017/Draug.sln /Build "Debug|x64"
vs-release64:
	"$(subst /,\\,$(VS2019_DEVENV_DIR))\devenv" $(PROJECT_DIR)/vs2017/Draug.sln /Build "Release|x64"

.PHONY: build-shaders
build-shaders:
	@make -s --no-print-directory rebuild -C resources

define remove_folder
	@echo Removing $(1) folder
	-@rm -rf $(1)
endef

define make_project
	$(GENIE) --file=build-scripts/genie.lua $(2) $(1)
endef


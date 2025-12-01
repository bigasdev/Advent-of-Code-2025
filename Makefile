# set the App name
NAME = fte_project
# set compiler
CC = g++ -std=c++17 -Wno-narrowing
STATIC_LIBS = -static-libstdc++ -static-libgcc
INCLUDES = -Isrc -Iinclude -Llib
LIBS = -lstdc++fs -lmingw32 -lSDL3 -lSDL3main -lole32 -mwindows -lopengl32
DEBUG_LIBS = -lstdc++fs -lmingw32 -lSDL3 -lSDL3_ttf -lpsapi -lpdh -lole32 -mwindows -lopengl32
# set all the files needed
DEBUG_FOLDER = build
RELEASE_FOLDER = release

ICON_DIR = res/icon/icon.res
BIN = bin/*.o
DEBUG_FLAGS = -D_DEBUG
APP_FLAGS = -DWIN_WIDTH=1024 -DWIN_HEIGHT=768

# needed folders
debug_folder:
	- mkdir ${DEBUG_FOLDER}
release_folder:
	- mkdir ${RELEASE_FOLDER}
bin_folder:
	- mkdir bin

SRC_DIRS := src/imgui src/core src/renderer src/res src/app src/tools

OBJ_FILES := $(foreach dir, $(SRC_DIRS), $(patsubst $(dir)/%.cpp, bin/%.o, $(wildcard $(dir)/*.cpp)))

vpath %.cpp $(SRC_DIRS)

bin/%.o: %.cpp
	$(CC) $(GAME_FLAGS) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -MMD -MP -c $< -o $@

debug: debug_folder bin_folder $(OBJ_FILES)
	${CC} -g -O0 $(STATIC_LIBS) $(INCLUDES) -o $(DEBUG_FOLDER)/fortress.exe $(OBJ_FILES) $(ICON_DIR) $(DEBUG_LIBS) -mconsole

build: release_folder bin_folder $(OBJ_FILES)
	${CC} -s -O3 -finline-functions -flto $(STATIC_LIBS) $(INCLUDES) -o $(RELEASE_FOLDER)/${NAME}.exe $(OBJ_FILES) $(ICON_DIR) $(LIBS)

-include $(OBJ_FILES:.o=.d)

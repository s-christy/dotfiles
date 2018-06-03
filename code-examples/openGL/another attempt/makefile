WORKDIR = `pwd`

CC = gcc
CXX = g++
LD = g++

INC =
CFLAGS = -Wall
RESINC =
LIBDIR =
LIB = -lSDL2 -lGLEW -lGL
LDFLAGS =

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE =
OUT_RELEASE = bin/Release/OpenGLTest

OBJ_RELEASE = $(OBJDIR_RELEASE)/texture.o $(OBJDIR_RELEASE)/stb_image.o $(OBJDIR_RELEASE)/shader.o $(OBJDIR_RELEASE)/obj_loader.o $(OBJDIR_RELEASE)/mesh.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/display.o

all: release

clean: clean_release

before_release:
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release:

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/texture.o: texture.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c texture.cpp -o $(OBJDIR_RELEASE)/texture.o

$(OBJDIR_RELEASE)/stb_image.o: stb_image.c
	$(CC) $(INC_RELEASE) -c stb_image.c -o $(OBJDIR_RELEASE)/stb_image.o

$(OBJDIR_RELEASE)/shader.o: shader.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c shader.cpp -o $(OBJDIR_RELEASE)/shader.o

$(OBJDIR_RELEASE)/obj_loader.o: obj_loader.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c obj_loader.cpp -o $(OBJDIR_RELEASE)/obj_loader.o

$(OBJDIR_RELEASE)/mesh.o: mesh.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c mesh.cpp -o $(OBJDIR_RELEASE)/mesh.o

$(OBJDIR_RELEASE)/main.o: main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.cpp -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/display.o: display.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c display.cpp -o $(OBJDIR_RELEASE)/display.o

clean_release:
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_release after_release clean_release


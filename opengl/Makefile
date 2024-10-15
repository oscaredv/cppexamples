all: dice

CPPFLAGS=-std=c++20
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lGLEW
OBJS=window.o dice.o scene.o camera.o shape.o overlay.o label.o

dice: $(OBJS) Makefile
	g++ $(OBJS) -o dice $(LDFLAGS)

.PHONY: clean
clean:
	$(RM) *.o dice

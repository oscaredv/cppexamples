all: dice

dice: window.o dice.o scene.o camera.o shape.o Makefile
	g++ window.o dice.o scene.o camera.o shape.o -o dice -lSDL2 -lSDL2_image -lGL -lGLU -lGLEW

.PHONY: clean
clean:
	$(RM) *.o dice

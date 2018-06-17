all: main

run: main
	./main.out

main: main.cpp body.o bodypart.o box.o table.o chair.o fridge.o television.o lamp.o room.o file.o rectangle.o light.o bezier.o
	g++ main.cpp body.o bodypart.o box.o table.o chair.o fridge.o television.o lamp.o room.o file.o rectangle.o light.o bezier.o -o main.out -lglut -lGLU -lGL


body.o: body.cpp body.h
	g++ -c body.cpp -o body.o -lglut -lGLU -lGL
	
bodypart.o: bodypart.cpp bodypart.h file.o
	g++ -c bodypart.cpp -o bodypart.o -lglut -lGLU -lGL
	
box.o: box.cpp box.h rectangle.h file.o
	g++ -c box.cpp -o box.o -lglut -lGLU -lGL
	
table.o: table.cpp table.h rectangle.h file.o
	g++ -c table.cpp -o table.o -lglut -lGLU -lGL

chair.o: chair.cpp chair.h rectangle.h file.o
	g++ -c chair.cpp -o chair.o -lglut -lGLU -lGL
	
fridge.o: fridge.cpp fridge.h rectangle.h file.o
	g++ -c fridge.cpp -o fridge.o -lglut -lGLU -lGL

television.o: television.cpp television.h rectangle.h file.o
	g++ -c television.cpp -o television.o -lglut -lGLU -lGL

lamp.o: lamp.cpp lamp.h light.h rectangle.h file.o
	g++ -c lamp.cpp -o lamp.o -lglut -lGLU -lGL

room.o: room.cpp room.h rectangle.h file.o
	g++ -c room.cpp -o room.o -lglut -lGLU -lGL

rectangle.o: rectangle.cpp rectangle.h
	g++ -c rectangle.cpp -o rectangle.o -lglut -lGLU -lGL

light.o: light.cpp light.h
	g++ -c light.cpp -o light.o -lglut -lGLU -lGL

file.o: file.cpp file.h
	g++ -c file.cpp -o file.o -lglut -lGLU -lGL

bezier.o: bezier.cpp bezier.h
	g++ -c bezier.cpp -o bezier.o -lglut -lGLU -lGL
	
clean:
	-rm -f *.o main.out


glad.o: ./glad/src/glad.c
	clang -I./glad/include -c ./glad/src/glad.c

main.o: ./main.cpp
	clang++ -std=c++2a -I./glad/include -c main.cpp

#-L/usr/local/Cellar/boost/1.72.0_2/lib
engine.build: glad.o main.o
	clang++ -std=c++2a -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L/usr/local/lib -lglfw3 ./main.o ./glad.o -o engine.build

clean: 
	- rm *.o
	- rm engine.build

rebuild: clean engine.build

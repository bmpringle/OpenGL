default:
	clang++ -std=c++2a -I./glad/include -I/usr/local/Cellar/boost/1.72.0_2/include -I. ./glad/src/glad.c Scene.cpp Engine.cpp Node.cpp main.cpp -o engine.build -L/usr/local/Cellar/boost/1.72.0_2/lib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L/usr/local/lib -lglfw3
lib:
	clang++ -c -std=c++2a -I./glad/include -I/usr/local/Cellar/boost/1.72.0_2/include -L/usr/local/Cellar/boost/1.72.0_2/lib Engine.cpp ./glad/src/glad.c
	ar rcs libengine.a Engine.o glad.o
	clang++ -lengine -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L. -L/usr/local/lib -lglfw3 -L/usr/local/Cellar/boost/1.72.0_2/lib main.cpp -o engine.build
clean: 
	rm -r main.o glad.o lib.a
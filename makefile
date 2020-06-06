default:
	make lib ./games/adventure.cpp
package:
	clang++ -std=c++2a -I./glad/include -I/usr/local/Cellar/boost/1.72.0_2/include -I. ./glad/src/glad.c Scene.cpp Engine.cpp Node.cpp main.cpp -o engine.build -L/usr/local/Cellar/boost/1.72.0_2/lib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L/usr/local/lib -lglfw3
lib:
	clang++ -c -std=c++2a -I./glad/include -I/usr/local/Cellar/boost/1.72.0_2/include -L/usr/local/Cellar/boost/1.72.0_2/lib Scene.cpp Engine.cpp Node.cpp ./glad/src/glad.c
	ar rcs libengine.a Scene.o Engine.o Node.o glad.o
	clang++ -lengine -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -I. -I./glad/include -L. -L/usr/local/lib -lglfw3 -L/usr/local/Cellar/boost/1.72.0_2/lib $(filter-out $@,$(MAKECMDGOALS)).cpp -o engine
	mv *.o ./build/src
	-rm -r ./build/target/$(filter-out $@, $(MAKECMDGOALS))/
	mkdir  ./build/target/$(filter-out $@, $(MAKECMDGOALS))/
	mv libengine.a ./build/target/$(filter-out $@, $(MAKECMDGOALS))/
	mv engine ./build/target/$(filter-out $@, $(MAKECMDGOALS))/
clean: 
	-rm -r ./build/src/* ./build/target/*
	-mkdir ./build/target/games/
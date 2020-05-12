default:
	clang++ -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -L/usr/local/lib -lglfw3 -I./glad/include ./glad/src/glad.c hw0.cpp
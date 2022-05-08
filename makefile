 
LDFLAGS= -L/usr/local/lib    -lm   -framework GLUT -framework OpenGL -framework Cocoa 


LinuxFLAGS= -lGL -lGLU -lglut -lm -I/usr/include 



#
# How to make .c into .o
#
.cpp.o: commonstuff.h
	g++   -c $< -w



osX_STL:	Shape.o  Ball.o Bullet.o mainAsteroidsSTL.o commonstuff.h Man.o ObjectsListSTL.o GLstuff.o
	g++ Shape.o GLstuff.o  Bullet.o Man.o Ball.o mainPANG.o ObjectsListSTL.o $(LDFLAGS)  -o PANG_STL -w


osX:	Shape.o  Ball.o Bullet.o mainPANG.o commonstuff.h Man.o ObjectsList.o GLstuff.o
	g++ Shape.o GLstuff.o Bullet.o Man.o Ball.o  mainPANG.o ObjectsList.o  $(LDFLAGS)  -o PANG_2022 -w


Linux:	Shape.o  Ball.o Bullet.o mainPANG.o commonstuff.h Man.o ObjectsList.o GLstuff.o
	g++ Shape.o  Bullet.o Man.o GLstuff.o Ball.o mainPANG.o ObjectsList.o $(LinuxLFLAGS)  -o PANG_2022 -w

clean:
	rm -f *~
	rm -f *.o

BUILDDIR = build
OBJS = Vectors.o CustomMath.o Colours.o Primatives.o Materials.o IntersectPoint.o Screen.o View.o Camera.o Scene.o
CC = gcc
DEBUGFLAGS = -g
LFLAGS = -lm
CFLAGS = -c

all: VectorTest ColourTest PrimativesTest ScreenTest SceneTest

RayTraceTest: RayTraceTest.c $(OBJS)
	$(CC) $(LFLAGS) RayTraceTest.c $(OBJS) -o RayTraceTest
	cp ScreenTest $(BUILDDIR)/ScreenTest

ScreenTest: ScreenTest.c $(OBJS)
	$(CC) $(LFLAGS) ScreenTest.c $(OBJS) -o ScreenTest
	cp ScreenTest $(BUILDDIR)/ScreenTest

PrimativesTest: PrimativesTest.c $(OBJS)
	$(CC) $(LFLAGS) PrimativesTest.c $(OBJS) -o PrimativesTest
	cp PrimativesTest $(BUILDDIR)/PrimativesTest

ColourTest: ColourTest.c $(OBJS)
	$(CC) $(LFLAGS) ColourTest.c $(OBJS) -o ColourTest
	cp ColourTest $(BUILDDIR)/ColourTest

VectorTest: VectorTest.c $(OBJS)
	$(CC) $(LFLAGS) VectorTest.c $(OBJS) -o VectorTest
	cp VectorTest $(BUILDDIR)/VectorTest

SceneTest: SceneTest.c $(OBJS)
	$(CC) $(LFLAGS) SceneTest.c $(OBJS) -o SceneTest


Scene.o: Scene.h Scene.c
	$(CC) Scene.c $(CFLAGS)

Camera.o: Camera.h Camera.c
	$(CC) Camera.c $(CFLAGS)

Colours.o: Colours.h Colours.c Vectors.h
	$(CC) Colours.c $(CFLAGS)

Vectors.o: Vectors.h Vectors.c CustomMath.h
	$(CC) Vectors.c $(CFLAGS)

CustomMath.o: CustomMath.h CustomMath.c
	$(CC) CustomMath.c $(CFLAGS)

Primatives.o: Primatives.h Primatives.c
	$(CC) Primatives.c $(CFLAGS)

Materials.o: Materials.h Materials.c
	$(CC) Materials.c $(CFLAGS)

Ray.o: Ray.h Ray.c
	$(CC) Ray.c $(CFLAGS)
	
IntersectPoint.o: IntersectPoint.h IntersectPoint.c
	$(CC) IntersectPoint.c $(CFLAGS)

Screen.o: Screen.h Screen.c
	$(CC) Screen.c $(CFLAGS)

View.o: View.h View.c
	$(CC) View.c $(CFLAGS)

clean:
	\rm *.o *.gch *.c~ *.h~ *.sh~ *Makefile~ VectorTest ColourTest PrimativesTest ScreenTest RayTraceTest SceneTest --force

LIBS = -lglut -lGLU -lGL -lm
CC = gcc
OBJECTS = parent child co-processor lib_myLibrary.a



parent child co-processor: parent.o child.o co-processor.o lib_myLibrary.a
	$(CC) -o child child.o $(LIBS) -L. lib_myLibrary.a
	$(CC) -o co-processor co-processor.o $(LIBS) -L. lib_myLibrary.a
	$(CC) -o parent parent.o $(LIBS) -L. lib_myLibrary.a 

lib_myLibrary.a: util.o
	ar rcs lib_myLibrary.a util.o

co-processor.o: co-processor.c
	$(CC) co-processor.c -c -o co-processor.o $(LIBS)

child.o: child.c
	$(CC) child.c -c -o child.o $(LIBS)

parent.o: parent.c
	$(CC) parent.c -c -o parent.o $(LIBS)
	
util.o: util.c
	$(CC) -c util.c -o util.o 
	
run: parent
	./parent arguments.txt

clean:
	rm -f *.o $(OBJECTS)


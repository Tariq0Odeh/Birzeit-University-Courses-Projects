LIBS = -lglut -lGLU -lGL -lm -lpthread
CC = gcc
OBJECTS = parent 

all: $(OBJECTS)

%: %.c
	$(CC) $< -o $@ $(LIBS)

%.o: %.c
	$(CC) $< -c -o $@ $(LIBS)

run: parent
	./parent arguments.txt

clean:
	rm -f *.o $(OBJECTS)
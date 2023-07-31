LIBS = -lglut -lGLU -lGL -lm
CC = gcc
OBJECTS = sender spy receiver master_spy helper parent sender_children

all: $(OBJECTS)

%: %.c
	$(CC) $< -o $@ $(LIBS)

%.o: %.c
	$(CC) $< -c -o $@ $(LIBS)

run: parent
	./parent arguments.txt

clean:
	rm -f *.o $(OBJECTS)

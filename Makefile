TARGET=overflow
SOURCES =$(wildcard *.c)
OBJECTS =$(SOURCES:.c=.o)
CC=gcc
CFLAGS= -fno-stack-protector -g
all:$(TARGET)
$(TARGET):$(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $?
clean:
	rm -f $(TARGET) $(OBJECTS) 

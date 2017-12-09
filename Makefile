CC = gcc
CFLAGS = -Wall
OBJFILES = main.o memory_region.o
TARGET = bin/memory_maps

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET)

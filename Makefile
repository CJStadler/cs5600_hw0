CC = gcc
CFLAGS = -Wall
OBJFILES = src/main.o src/memory_region.o
TARGET = bin/memory_maps

all: $(TARGET)

run: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(OBJFILES) $(TARGET)

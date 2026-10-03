CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/contact.c src/file.c src/populate.c
TARGET = addressbook

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all run clean

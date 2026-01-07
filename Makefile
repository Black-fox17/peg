CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11 -Iinclude
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:.c=.o)
TARGET  = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

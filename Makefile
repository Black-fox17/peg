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


ifeq ($(OS),Windows_NT)
    RM = del /Q
    FixPath = $(subst /,\,$1)
    TARGET_EXT = .exe
else
    RM = rm -f
    FixPath = $1
    TARGET_EXT = 
endif

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(call FixPath,src/*.o) $(TARGET)$(TARGET_EXT)

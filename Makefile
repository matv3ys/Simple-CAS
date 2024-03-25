TARGET = psf
CC = gcc

CCFLAGS = -Wall -Wextra

SRC = main.c PSform.c

all: $(TARGET)

memory: CCFLAGS += -fsanitize=memory
memory: CC := clang
memory: $(TARGET)

address: CCFLAGS += -fsanitize=address
address: CC := clang
address: $(TARGET)

profiling: CCFLAGS += -pg
profiling: $(TARGET)

$(TARGET): clean $(SOURCES)
	$(CC) $(CCFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

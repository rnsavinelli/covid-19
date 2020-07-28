CC = g++
CFLAGS = -std=c++17 -Wall -pedantic-errors
INCLUDES = -I ./src
SOURCES = src/*.cpp

OUTPUT = covid-tool

.PHONY: compile debug clean

compile:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) $(INCLUDES) -g3 -o $(OUTPUT) && gdb -se $(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)

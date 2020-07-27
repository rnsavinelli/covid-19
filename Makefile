CC = g++
CFLAGS = -std=c++17 -Wall -pedantic-errors
SOURCES = covid.cpp

OUTPUT = covid-tool

.PHONY: compile debug clean

compile:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT)

debug:
	$(CC) $(CFLAGS) $(SOURCES) -g3 -o $(OUTPUT) && gdb -se $(OUTPUT)

clean:
	$(RM) ./$(OUTPUT)

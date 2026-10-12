CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -I.

all: app

app: main.cpp analyzer.cpp analyzer.h
	$(CXX) $(CXXFLAGS) main.cpp analyzer.cpp -o app

run: app
	./app

clean:
	$(RM) app app.exe

.PHONY: all run clean

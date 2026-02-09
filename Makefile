CXX = g++
CXXFLAGS = -std=c++20 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

TARGET = Main
SOURCES = Main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)
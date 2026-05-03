CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/opt/sfml/include -Iinclude
LDFLAGS = -L/opt/homebrew/opt/sfml/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = oyun
SRC = src/main.cpp src/Paddle.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) $(LIBS)

run:
	./$(TARGET)

clean:
	rm -f $(TARGET)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer

SRCS = src/main.cpp src/game.cpp src/player.cpp src/world.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = LegendOfHaiku

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./include -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
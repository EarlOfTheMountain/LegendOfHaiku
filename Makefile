CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer

# Debug configuration
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CXXFLAGS += -g -O0
	TARGET_SUFFIX = _debug
else
	CXXFLAGS += -O2
	TARGET_SUFFIX = 
endif

SRCS = src/main.cpp src/game.cpp src/player.cpp src/world.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = LegendOfHaiku$(TARGET_SUFFIX)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I./include -c $< -o $@

clean:
	rm -f $(OBJS) LegendOfHaiku LegendOfHaiku_debug

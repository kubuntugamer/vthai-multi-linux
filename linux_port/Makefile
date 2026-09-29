# VTHAI Multi-Linux Driver Port Build Automation Template
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17 -I.

# Source configurations and compiled targets
SRCS = main.cpp vthai_engine.cpp vthai_font.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = vthai_suite

.PHONY: all clean run test_stream

# Default target rule to compile the entire project workspace
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Convenience rule to build and immediately fire up the interactive suite
run: all
	./$(TARGET)

# Convenience rule to immediately test custom file input parsing streams
test_stream: all
	./$(TARGET) -f ../hello.txt

# Cleanup intermediate object files and compiled diagnostic binaries
clean:
	rm -f *.o $(TARGET)

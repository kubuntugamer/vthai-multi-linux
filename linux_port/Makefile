# VTHAI Multi-Linux Driver Port Build Automation Template
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17 -I.

SRCS = main.cpp vthai_engine.cpp vthai_font.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = vthai_suite

.PHONY: all clean run test_v200 test_v300

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

test_v200: all
	./$(TARGET) -v 2.00/THAI.COM 0xA1 0xD4

# Passes character index values mapping to active linguistic text font clusters inside v3.00
test_v300: all
	./$(TARGET) -v 3.00/THAI.COM 0xA1 0xD4

clean:
	rm -f *.o $(TARGET)

# Specify the compiler
CXX = g++
# Cpp flags
CXXFLAGS = -Wall -std=c++11
# Specify the name of the executable
TARGET = simulator

# Source files
SRCS = trace_handler.cpp functions.cpp

all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Make clean
clean:
	rm $(TARGET)

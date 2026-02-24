# Windows Makefile for Calendar Project

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Executable name
TARGET = calendar_app.exe

# Source files
SRCS = calendar_project.cpp UserFiles.cpp TestCases.cpp Calendar.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	del /Q $(OBJS) $(TARGET)

# Run program
run: $(TARGET)
	$(TARGET)
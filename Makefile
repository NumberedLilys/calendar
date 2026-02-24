CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

# ---- Main Application ----
app:
	$(CXX) $(CXXFLAGS) src/calendar_project.cpp src/Calendar.cpp src/UserFiles.cpp -o calendar.exe

run: app
	calendar.exe


# ---- Test Runner ----
test:
	$(CXX) $(CXXFLAGS) src/test_main.cpp src/TestCases.cpp src/Calendar.cpp src/UserFiles.cpp -o tests.exe
	tests.exe


# ---- Clean ----
clean:
	del /Q *.exe 2>nul

# # Compiler
# CXX = g++
# CXXFLAGS = -Wall -std=c++17 -Iinclude

# # Automatically grab all .cpp files from src/
# SRC = $(wildcard src/*.cpp)

# # Convert src/file.cpp -> build/file.o
# OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))

# # Output executable
# TARGET = build/calendar.exe

# # Default target
# all: build $(TARGET)

# # Link object files into executable
# $(TARGET): $(OBJ)
# 	@echo Linking...
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# # Compile .cpp -> build/.o
# build/%.o: src/%.cpp | build
# 	@echo Compiling $<
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Ensure build folder exists (Windows-safe)
# build:
# 	if not exist build mkdir build

# # Run program (build first if needed)
# run: all
# 	@echo Running program...
# 	$(TARGET)

# # Clean build files
# clean:
# 	@echo Cleaning...
# 	del /Q build\*.exe build\*.o 2>nul
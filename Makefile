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

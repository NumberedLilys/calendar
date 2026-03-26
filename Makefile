CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -pg

# ---- Main Application ----
app:
	$(CXX) $(CXXFLAGS) src/calendar_project.cpp src/calendar.cpp src/userFiles.cpp -o calendarlogic.exe -Wl,--subsystem,console

run: app
	calendarlogic.exe


# ---- Test Runner ----
test:
	$(CXX) $(CXXFLAGS) src/test_main.cpp src/TestCases.cpp src/calendar.cpp src/userFiles.cpp -o tests.exe
	tests.exe


# ---- Clean ----
clean:
	del /Q *.exe 2>nul

# Calendar
Using c++, we will be creating a calendar app. 
Most calendar apps that are available for the public tend to have annoying downsides while using them. 
For example, some calendar apps tend to have minimal options for repeating events (does not have an option for every x number of weeks).
This calendar app will have more options and a more user-friendly interface that makes navigating the app easier.
We will be using c++ framwork with QT for the ui

# rough notes / ideas
- multiple calenders for personal/friends/family
- basic calendar functions like events and todos
- be able to reschedule events with more customization ie. reschedule this event every 10 days
- collaborative calenders (Family, friends, etc)
- Task page? (checklist?)
- Goal Setting?

# build instructions


// using makefile, mingw32-make to compile in terminal and mingw32-make run to run the program.
// E.g. cd calendar, mingw32-make, mingw32-make run in terminal

// to run tests, mingw32-make test in terminal, which compiles test_main.cpp and runs the tests

1. Clone the repository
git clone https://github.com/NumberedLilys/calendar.git
cd calendar

2. Running the program
In the terminal, type mingw32-make to compile the program and mingw32-make run to execute the program.
To run the tests (test-cases), type mingw32-make test in the terminal.

There is no need to download anything else.

# project structure

"Calender"
- ".vscode"
    - "tasks.json" - needed for automation tasks

- "database"
    - "calander project.exe" - main .exe file that runs everything

- "ui"
    - "SLD3.dll" - needed to run .exe file
    - "userWindow.cpp" - code for the ui
    - "userWindow.exe" - .exe to make ui pop up

- ".gitignore" - for git to ignore changes to .exe files
- "calender_project.cpp" - main .cpp file 
- "README.md"



# limitations

App is not fully implemented and does not have working backend.

# why?
- most calanders dont give you the amount of customization needed
- Having a more accessible and collaborative calendar would make daily tasks more convenient

# Name

<details>
    <summary>Table of Contents</summary>

    - Description
        - Features
        - Background

    - Visuals

    - Installation
        - Requirements

    - Usage

    - Roadmap
    
    - Contributing

</details>

## Description
(Name of program) is a versatile calendar app that implements a multitude of features. I displays the date in a typical calendar format (month, week, date, year) in a rectangular program for users to quickly and easily access the date and see written events.

### Features
(Name of program) includes all basic calendar features, such as the date, notification implementations, and event planning. Additionally, the calendar gives users the ability to make recurring events with a chosen number of days and times. For example, users will be able to plan events to reoccur every x number of weeks for a certain amount of time. Another feature gives users the ability to make a shared calendar. With this, users can choose between multiple options (family, friends, etc) and allow multiple people to add, delete, and work with events collaboratively.

List of features: 
    - Date display
    - Notifications/event reminders
    - Event creation
    - Reoccurring events
    - Shared calendar (Family, friends)

# Build Instructions
1. Clone the repository
git clone https://github.com/NumberedLilys/calendar.git
cd calendar

2. Run the pre-compiled executable (Windows)
./database/"calander project.exe"

# Project Structure
```
Calendar/
├── .vscode/
│   └── tasks.json             # Automation tasks for building the project
├── database/
│   └── calander project.exe   # Main application executable
├── ui/
│   ├── SDL3.dll               # Dynamic Link Library required for graphics
│   ├── userWindow.cpp         # Source code for the UI implementation
│   └── userWindow.exe         # Executable for UI testing
├── .gitignore                 # Instructions for Git to ignore binary files
├── calender_project.cpp       # Main entry point for the application
└── README.md                  # Project documentation
```
Limitations
The application is currently a Work in Progress (WIP).
The backend logic for saving data to a permanent database is not yet implemented.
The UI is in the early stages of SDL3 implementation.

# Why?
- most calanders dont give you the amount of customization needed
- Having a more accessible and collaborative calendar would make daily tasks more convenient

## Visuals
- Photos/video of what it does

## Roadmap
- Task Page
- Goal Setting

# rough notes / ideas
- multiple calenders for personal/friends/family
- basic calendar functions like events and todos
- be able to reschedule events with more customization ie. reschedule this event every 10 days
- collaborative calenders (Family, friends, etc)
- Task page? (checklist?)
- Goal Setting?
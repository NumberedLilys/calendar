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

    - Benchmark and Profiling

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

## Installations

- Only need to download the calendar.exe file.

## Usage/Download instruction 

You can also download the latest release, and then unzip the folder and run the calender.exe file.
Or you can just download the calendar.exe.

### Build instructions

1. Clone the repository
git clone https://github.com/NumberedLilys/calendar.git
cd calendar

2. Running the program
In the terminal, type mingw32-make to compile the program and mingw32-make run to execute the program.
To run the tests (test-cases), type mingw32-make test in the terminal.

3. Download Docker 
To create the container, run: docker build -t calendar_docker .
in the terminal
To run the Docker container:
In the terminal, type docker run --name calendar_docker (image name)

## Benchmark and Profiling

For Benchmark and Profiling information, refer to profile.txt.

We used gprof for the benchmarking.

The most time consuming part of the program is the UI, which takes about 366.9 ms to run. 

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

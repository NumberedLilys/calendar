# calendar

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

git clone --recursive https://github.com/NumberedLilys/calendar.git
cd calendar

./calendar

there is no need to download anything else

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
    <summary>Table of Contents<summary>
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

## Visuals

- Photos/video of what it does

## Installation

- How to install the project/step by step

### Requirements

## Usage

## Roadmap

- Task Page
- Goal Setting

## Contributing

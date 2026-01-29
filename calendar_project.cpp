#include <iostream>

class Calendar {
    private:
        int year;
        int month;
        int day;

    public:
        Calendar(int y, int m, int d): year(y), month(m), day(d) {};
        void displayDate() {
            std::cout << "Date: " << year << "-" << month << "-" << day << std::endl;
        }
        // Put into a .h file later, add extra functionalities. Mainly display and basics for the calendar application
        // Figure out how to get the proper date/time, maybe a library?

};

class TaskNotifications {
    // Notification class, sends notifications for tasks/events. Put in .h file later
};

int main() {
    std::cout << "Hello World" << std::endl;
    std::cout << "Will have to change this to a calendar project later" << std::endl;
    
    return 0;
}
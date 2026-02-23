
class Calendar {
    private:
        int year;
        int month;
        int day;

    public:
        Calendar(int y, int m, int d): year(y), month(m), day(d) {};

        std::string displayDate(std::chrono::system_clock::time_point tp) {
            std::time_t t = std::chrono::system_clock::to_time_t(tp); // changes time_point to time_t   
            std::tm now;
            localtime_s(&now, &t); // Converts to local time

            std::ostringstream ss;
            ss << std::put_time(&now, "%Y-%m-%d"); // Formats the date in YYYY-MM-DD format using stringstream
            return ss.str();
        }

};
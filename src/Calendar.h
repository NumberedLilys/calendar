
class Calendar {
    private:
        int year;
        int month;
        int day;

    public:
        Calendar(int y, int m, int d): year(y), month(m), day(d) {};

        void getLoginDetails(std::string& username, 
                             std::string& password) {

            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
        }

        void getSignupDetails(std::string& email,
                              std::string& username,
                              std::string& password) {

            while (true) {
                std::cout << "Enter email: ";
                std::getline(std::cin, email);

                std::cout << "Enter username: ";
                std::getline(std::cin, username);

                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                if (!email.empty() && !username.empty() && !password.empty()) {
                    break;
                }

                std::cout << "Error: All fields are required.\n\n";
            }
        }
        std::string displayDate(std::chrono::system_clock::time_point tp) {
            std::time_t t = std::chrono::system_clock::to_time_t(tp); // changes time_point to time_t   
            std::tm now;
            localtime_s(&now, &t); // Converts to local time

            std::ostringstream ss;
            ss << std::put_time(&now, "%Y-%m-%d"); // Formats the date in YYYY-MM-DD format using stringstream
            return ss.str();
        }

        std::string createUser() {
            std::string username;
            std::string password;
            std::string email;

            getSignupDetails(email, username, password); // initial account creation, requires email and username and password, with password confirmation.

            std::ifstream check_file("users.txt");
            std::string line;

            while(std::getline(check_file, line)) {
                std::istringstream iss(line);
                std::string stored_email, stored_username, stored_password;
                iss >> stored_email >> stored_username >> stored_password;

                if(stored_email == email || stored_username == username) {
                    return "User already exists.";
                }
            }

            std::cout << "Please confirm your password: ";
            std::string confirm_password;
            std::getline(std::cin, confirm_password);

            while (confirm_password != password) {  // Password confirmation loop
                std::cout << "Passwords do not match. Please try again." << std::endl;
                std::cout << "Please confirm your password: ";
                std::getline(std::cin, confirm_password);
            }
            std::ofstream user_file("users.txt", std::ios::app);
            if (!user_file.is_open()) {
                return "Error opening user file.";
            }

            user_file << email << " " << username << " " << password << std::endl;
            user_file.close();

            return "User " + username + " created successfully!";
        }

        struct User { // Struct to hold user data
            std::string actual_username;
            std::string actual_password;
            std::string actual_email;
        };

        bool userLogin() { 
            std::ifstream user_file("users.txt"); // Read user data from file
            std::string line;
            std::vector<User> users;

            if (!user_file.is_open()) { // Error handling for file opening
                std::cerr << "Error opening user file." << std::endl;
                return false;
            } else {
                while (std::getline(user_file, line)) { // Read each line from file

                    // TEST CASE ==================
                    std::cout << line << std::endl; // DELETE LATER, just to check that we're reading the file correctly !!!!!!!!!!
                    // TEST CASE ==================
                    
                    // Get data from file and store in vector of User structs, then check against input
                    std::istringstream iss(line);
                    User u;
                    iss >> u.actual_email >> u.actual_username >> u.actual_password;
                    users.push_back(u);
                }
            }

            std::string input_username;
            std::string input_password;
            getLoginDetails(input_username, input_password); // Get user input for login, only needs username/email and password

            for (const User& user : users) {
                if ((user.actual_username == input_username || user.actual_email == input_username) && user.actual_password == input_password) {
                    std::cout << "Login successful!" << std::endl;
                    return true;
                }
            }
            
            std::cout << "Login failed. Please check your username and password." << std::endl;
            return false;
        }

};
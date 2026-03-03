#ifndef APP_LOGIC_H
#define APP_LOGIC_H

#include <SDL3/SDL.h>
#include <string>

class Calendar;

// Simple screen state for the app
enum Screen {
    LOGIN,
    CALENDAR
};

struct CalendarColors {
    SDL_Color background = {243, 244, 246, 255};
    SDL_Color card       = {255, 255, 255, 255};
    SDL_Color primary    = {59, 130, 246, 255};
    SDL_Color text       = {31, 41, 55, 255};
    SDL_Color grid       = {229, 231, 235, 255};
    SDL_Color white      = {255, 255, 255, 255};
    SDL_Color shadow     = {0, 0, 0, 20};
};

// Application State – single source of truth
struct AppState {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Calendar* currentCalendar = nullptr;
    CalendarColors colors;
    float margin = 40.0f;

    // Screen / navigation
    Screen screen = LOGIN;

    // User / login state
    bool isLoggedIn = false;
    std::string currentUsername;
    std::string currentEmail;

    // Login / signup UI mode
    bool loginModeIsSignup = false; // false = Login, true = Signup
    int loginActiveField = 0;       // index of currently focused field

    // Login fields (Login mode)
    std::string loginIdentifierInput; // username or email
    std::string loginPasswordInput;

    // Signup fields (Signup mode)
    std::string signupEmailInput;
    std::string signupUsernameInput;
    std::string signupPasswordInput;

    // Feedback from last auth action
    std::string authMessage;
};

// Function prototypes
void RenderBackground(AppState* state);
void RenderCalendarBody(AppState* state, SDL_FRect* cardRect);
void RenderHeader(AppState* state, SDL_FRect* cardRect);
void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight);

// Login / Signup screen
void RenderLoginScreen(AppState* state, SDL_FRect* cardRect);

#endif


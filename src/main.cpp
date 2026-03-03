#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <chrono>
#include <ctime>
#include <sstream>
#include "appLogic.h"
#include "calendar.h"
#include "UserFiles.h"

// --- UI functions ---
void RenderBackground(AppState* state);
void RenderCalendarBody(AppState* state, SDL_FRect* cardRect);
void RenderHeader(AppState* state, SDL_FRect* cardRect);
void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight);
void RenderLoginScreen(AppState* state, SDL_FRect* cardRect);

static void HandleLoginKeyDown(AppState* state, const SDL_KeyboardEvent& keyEvent) {
    SDL_Keycode key = keyEvent.key;

    int fieldCount = state->loginModeIsSignup ? 3 : 2;

    // Field navigation
    if (key == SDLK_TAB || key == SDLK_DOWN) {
        state->loginActiveField = (state->loginActiveField + 1) % fieldCount;
        return;
    }
    if (key == SDLK_UP) {
        state->loginActiveField = (state->loginActiveField - 1 + fieldCount) % fieldCount;
        return;
    }

    // Determine which string to edit
    std::string* currentField = nullptr;
    if (!state->loginModeIsSignup) {
        if (state->loginActiveField == 0) currentField = &state->loginIdentifierInput;
        else if (state->loginActiveField == 1) currentField = &state->loginPasswordInput;
    } else {
        if (state->loginActiveField == 0) currentField = &state->signupEmailInput;
        else if (state->loginActiveField == 1) currentField = &state->signupUsernameInput;
        else if (state->loginActiveField == 2) currentField = &state->signupPasswordInput;
    }

    if (key == SDLK_BACKSPACE) {
        if (currentField && !currentField->empty()) {
            currentField->pop_back();
        }
        return;
    }

    // Submit
    if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
        UserFiles uf("database/users.txt");
        std::stringstream in;
        std::ostringstream out;

        if (!state->loginModeIsSignup) {
            // Login flow: identifier + password
            in << state->loginIdentifierInput << "\n"
               << state->loginPasswordInput << "\n";

            bool success = uf.userLogin(in, out);
            if (success) {
                state->isLoggedIn = true;
                state->currentUsername = state->loginIdentifierInput;
                state->screen = CALENDAR;
                state->authMessage.clear();
            } else {
                state->authMessage = "Login failed. Please check your username and password.";
            }
        } else {
            // Signup flow: email, username, password (+ implicit confirm = password)
            in << state->signupEmailInput << "\n"
               << state->signupUsernameInput << "\n"
               << state->signupPasswordInput << "\n"
               << state->signupPasswordInput << "\n"; // confirmation

            std::string result = uf.createUser(in, out);
            state->authMessage = result;

            // After successful signup, return to Login mode so user logs in explicitly
            if (result.rfind("User ", 0) == 0 && result.find("created successfully") != std::string::npos) {
                state->loginModeIsSignup = false;
                state->loginActiveField = 0;
                state->loginIdentifierInput = state->signupUsernameInput;
                state->loginPasswordInput.clear();
                state->signupEmailInput.clear();
                state->signupUsernameInput.clear();
                state->signupPasswordInput.clear();
            }
        }

        // Clear password fields after attempts
        state->loginPasswordInput.clear();
        state->signupPasswordInput.clear();
        return;
    }

    // Append printable character input
    if (currentField) {
        if (key >= 32 && key <= 126) {
            currentField->push_back(static_cast<char>(key));
        }
    }
}

static void HandleCalendarKeyDown(AppState* state, const SDL_KeyboardEvent& keyEvent) {
    if (!state->currentCalendar) {
        return;
    }
    SDL_Keycode key = keyEvent.key;
    if (key == SDLK_LEFT) {
        state->currentCalendar->changeMonth(-1);
    } else if (key == SDLK_RIGHT) {
        state->currentCalendar->changeMonth(1);
    } else if (key == SDLK_UP) {
        state->currentCalendar->changeMonth(12);
    } else if (key == SDLK_DOWN) {
        state->currentCalendar->changeMonth(-12);
    }
}

// 1. INITIALIZE: Runs once at the start
extern "C" SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return SDL_APP_FAILURE;
    }

    AppState* state = new AppState();

    if (!SDL_CreateWindowAndRenderer("Calendar v1.0", 800, 700, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        delete state;
        return SDL_APP_FAILURE;
    }

    // Get real current date
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm* parts = std::localtime(&now_c);

    // Initialize Calendar logic
    state->currentCalendar = new Calendar(parts->tm_year + 1900, parts->tm_mon + 1, parts->tm_mday);

    // Initialize UI settings
    state->margin = 40.0f;
    state->colors.background = {30, 30, 35, 255};
    state->colors.card = {45, 45, 50, 255};
    state->colors.primary = {0, 120, 215, 255};
    state->colors.text = {200, 200, 200, 255};
    state->colors.white = {255, 255, 255, 255};
    state->colors.shadow = {10, 10, 10, 150};
    state->colors.grid = {60, 60, 65, 255};

    // Start at login screen
    state->screen = LOGIN;
    state->isLoggedIn = false;
    state->loginModeIsSignup = false;
    state->loginActiveField = 0;

    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);
    *appstate = state;

    return SDL_APP_CONTINUE;
}

// 2. EVENTS: Runs whenever you click, resize, or close the window
extern "C" SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState* state = (AppState*)appstate;

    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // This closes the app
    }

    // Mouse support for login/signup UI
    if (state->screen == LOGIN && event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int w, h;
        SDL_GetRenderOutputSize(state->renderer, &w, &h);

        SDL_FRect cardRect = {
            state->margin,
            state->margin,
            (float)w - (state->margin * 2),
            (float)h - (state->margin * 2)
        };

        float headerHeight = 80.0f;
        float contentTop = cardRect.y + headerHeight + 40.0f;
        float contentLeft = cardRect.x + 40.0f;

        SDL_FRect loginBtn = { contentLeft, contentTop, 140.0f, 40.0f };
        SDL_FRect signupBtn = { contentLeft + 160.0f, contentTop, 140.0f, 40.0f };

        auto pointInRect = [](float x, float y, const SDL_FRect& r) {
            return x >= r.x && x <= r.x + r.w && y >= r.y && y <= r.y + r.h;
        };

        float mx = (float)event->button.x;
        float my = (float)event->button.y;

        if (pointInRect(mx, my, loginBtn)) {
            state->loginModeIsSignup = false;
            state->loginActiveField = 0;
            state->authMessage.clear();
        } else if (pointInRect(mx, my, signupBtn)) {
            state->loginModeIsSignup = true;
            state->loginActiveField = 0;
            state->authMessage.clear();
        } else {
            // Also allow clicking directly into fields to focus them
            float fieldTop = contentTop + 70.0f;
            float fieldHeight = 36.0f;
            float fieldWidth = cardRect.w - 80.0f;

            SDL_FRect fields[3];
            int fieldCount = 0;

            if (!state->loginModeIsSignup) {
                // Login: identifier + password
                fields[0] = { contentLeft, fieldTop, fieldWidth, fieldHeight };
                fields[1] = { contentLeft, fieldTop + 60.0f, fieldWidth, fieldHeight };
                fieldCount = 2;
            } else {
                // Signup: email, username, password
                fields[0] = { contentLeft, fieldTop, fieldWidth, fieldHeight };
                fields[1] = { contentLeft, fieldTop + 60.0f, fieldWidth, fieldHeight };
                fields[2] = { contentLeft, fieldTop + 120.0f, fieldWidth, fieldHeight };
                fieldCount = 3;
            }

            for (int i = 0; i < fieldCount; ++i) {
                if (pointInRect(mx, my, fields[i])) {
                    state->loginActiveField = i;
                    break;
                }
            }
        }
    }

    if (event->type == SDL_EVENT_KEY_DOWN) {
        if (state->screen == LOGIN) {
            HandleLoginKeyDown(state, event->key);
        } else if (state->screen == CALENDAR) {
            HandleCalendarKeyDown(state, event->key);
        }
    }

    return SDL_APP_CONTINUE;
}

// 3. LOOP: Runs as fast as possible to draw the screen
extern "C" SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState* state = (AppState*)appstate;
    int w, h;
    SDL_GetRenderOutputSize(state->renderer, &w, &h);

    // Calculate dimensions
    SDL_FRect cardRect = { state->margin, state->margin, (float)w - (state->margin * 2), (float)h - (state->margin * 2) };

    // Draw everything
    RenderBackground(state);

    if (state->screen == LOGIN) {
        RenderLoginScreen(state, &cardRect);
    } else {
        RenderCalendarBody(state, &cardRect);
        RenderHeader(state, &cardRect);
        RenderGrid(state, &cardRect, 80.0f);
    }

    SDL_RenderPresent(state->renderer);
    return SDL_APP_CONTINUE;
}

// 4. CLEANUP: Runs when the app closes
extern "C" void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState* state = (AppState*)appstate;
    if (state) {
        if (state->currentCalendar) delete state->currentCalendar;
        if (state->renderer) SDL_DestroyRenderer(state->renderer);
        if (state->window) SDL_DestroyWindow(state->window);
        delete state;
    }
    SDL_Quit();
}

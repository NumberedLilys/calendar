#include "appLogic.h"
#include "calendar.h"
#include <chrono>
#include <ctime>

// Reduces code duplication for setting colors
void SetDrawColor(SDL_Renderer* renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// Helper to draw larger debug text without changing layout math
static void DrawTextScaled(SDL_Renderer* renderer, float x, float y, const char* text, float scale) {
    SDL_SetRenderScale(renderer, scale, scale);
    SDL_RenderDebugText(renderer, x / scale, y / scale, text);
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}

void RenderBackground(AppState* state) {
    SetDrawColor(state->renderer, state->colors.background);
    SDL_RenderClear(state->renderer);
}

void RenderCalendarBody(AppState* state, SDL_FRect* cardRect) {
    // Draw Shadow
    SDL_FRect shadow = { cardRect->x + 4, cardRect->y + 4, cardRect->w, cardRect->h };
    SetDrawColor(state->renderer, state->colors.shadow);
    SDL_RenderFillRect(state->renderer, &shadow);

    // Draw Main Card
    SetDrawColor(state->renderer, state->colors.card);
    SDL_RenderFillRect(state->renderer, cardRect);
}

void RenderHeader(AppState* state, SDL_FRect* cardRect) {
    float headerHeight = 80.0f;
    SDL_FRect headerRect = { cardRect->x, cardRect->y, cardRect->w, headerHeight };

    SetDrawColor(state->renderer, state->colors.primary);
    SDL_RenderFillRect(state->renderer, &headerRect);

    // Title text: dynamic month and year from Calendar
    const char* fallbackTitle = "Calendar";
    char title[64];

    if (state->currentCalendar != nullptr) {
        std::string monthName = state->currentCalendar->getMonthName();
        int year = state->currentCalendar->getYear();
        SDL_snprintf(title, sizeof(title), "%s %d", monthName.c_str(), year);
    } else {
        SDL_snprintf(title, sizeof(title), "%s", fallbackTitle);
    }

    SetDrawColor(state->renderer, state->colors.white);
    DrawTextScaled(state->renderer, cardRect->x + 20, cardRect->y + 25, title, 2.2f);
}

void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight) {
    const char* days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    float cellW = cardRect->w / 7;
    float labelY = cardRect->y + headerHeight + 20;

    // Draw Labels
    SetDrawColor(state->renderer, state->colors.text);
    for (int i = 0; i < 7; i++) {
        DrawTextScaled(
            state->renderer,
            cardRect->x + (i * cellW) + (cellW / 2) - 16,
            labelY,
            days[i],
            1.6f
        );
    }

    // Grid Logic
    float gridTop = labelY + 30;
    float cellH = (cardRect->h - (gridTop - cardRect->y) - 20) / 6;

    int startOffset = 0;
    int totalDays = 30;

    // Get actual today's date so we only highlight "today" when viewing the current month/year
    int todayYear = 0, todayMonth = 0, todayDay = 0;
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tmNow;
#ifdef _WIN32
        localtime_s(&tmNow, &t);
#else
        localtime_r(&t, &tmNow);
#endif
        todayYear = tmNow.tm_year + 1900;
        todayMonth = tmNow.tm_mon + 1;
        todayDay = tmNow.tm_mday;
    }

    if (state->currentCalendar != nullptr) {
        startOffset = state->currentCalendar->getStartDayOfWeek(); // 0 = Sunday
        totalDays = state->currentCalendar->getDaysInMonth();
    }

    for (int i = 0; i < 42; i++) {
        int dayNum = i + 1 - startOffset;
        if (dayNum >= 1 && dayNum <= totalDays) {
            int row = i / 7;
            int col = i % 7;
            float x = cardRect->x + (col * cellW);
            float y = gridTop + (row * cellH);

            // Draw Cell
            SetDrawColor(state->renderer, state->colors.grid);
            SDL_FRect cellRect = { x, y, cellW, cellH };
            SDL_RenderRect(state->renderer, &cellRect);

            // Highlight only when this cell is actually "today" (same year, month, and day as real today)
            bool isToday = state->currentCalendar != nullptr
                && state->currentCalendar->getYear() == todayYear
                && state->currentCalendar->getMonth() == todayMonth
                && dayNum == todayDay;

            if (isToday) {
                SetDrawColor(state->renderer, state->colors.primary);
                SDL_FRect marker = { x + 5, y + 5, 25, 25 };
                SDL_RenderFillRect(state->renderer, &marker);
                SetDrawColor(state->renderer, state->colors.white);
            } else {
                SetDrawColor(state->renderer, state->colors.text);
            }

            char buf[3];
            SDL_snprintf(buf, sizeof(buf), "%d", dayNum);
            DrawTextScaled(state->renderer, x + 10, y + 6, buf, 1.6f);
        }
    }
}

void RenderLoginScreen(AppState* state, SDL_FRect* cardRect) {
    // Background card similar to calendar
    RenderCalendarBody(state, cardRect);

    // Header area
    float headerHeight = 80.0f;
    SDL_FRect headerRect = { cardRect->x, cardRect->y, cardRect->w, headerHeight };
    SetDrawColor(state->renderer, state->colors.primary);
    SDL_RenderFillRect(state->renderer, &headerRect);

    SetDrawColor(state->renderer, state->colors.white);
    const char* title = state->loginModeIsSignup ? "Sign Up" : "Login";
    DrawTextScaled(state->renderer, cardRect->x + 20, cardRect->y + 25, title, 2.2f);

    float contentTop = cardRect->y + headerHeight + 40.0f;
    float contentLeft = cardRect->x + 40.0f;

    // Mode buttons: Login / Signup
    SDL_FRect loginBtn = { contentLeft, contentTop, 140.0f, 40.0f };
    SDL_FRect signupBtn = { contentLeft + 160.0f, contentTop, 140.0f, 40.0f };

    // Login button
    SetDrawColor(state->renderer, state->loginModeIsSignup ? state->colors.card : state->colors.primary);
    SDL_RenderFillRect(state->renderer, &loginBtn);
    SetDrawColor(state->renderer, state->colors.text);
    DrawTextScaled(state->renderer, loginBtn.x + 22, loginBtn.y + 10, "Login", 1.8f);

    // Signup button
    SetDrawColor(state->renderer, state->loginModeIsSignup ? state->colors.primary : state->colors.card);
    SDL_RenderFillRect(state->renderer, &signupBtn);
    SetDrawColor(state->renderer, state->colors.text);
    DrawTextScaled(state->renderer, signupBtn.x + 16, signupBtn.y + 10, "Sign Up", 1.8f);

    float fieldTop = contentTop + 70.0f;
    float fieldHeight = 36.0f;
    float fieldWidth = cardRect->w - 80.0f;

    auto drawField = [&](float y, const char* label, const std::string& value, bool focused) {
        SetDrawColor(state->renderer, state->colors.text);
        DrawTextScaled(state->renderer, contentLeft, y - 20.0f, label, 1.6f);

        SDL_FRect box = { contentLeft, y, fieldWidth, fieldHeight };
        SetDrawColor(state->renderer, state->colors.grid);
        SDL_RenderRect(state->renderer, &box);

        if (focused) {
            SDL_FRect highlight = { box.x, box.y, 4.0f, box.h };
            SetDrawColor(state->renderer, state->colors.primary);
            SDL_RenderFillRect(state->renderer, &highlight);
        }

        SetDrawColor(state->renderer, state->colors.text);
        DrawTextScaled(state->renderer, box.x + 10.0f, box.y + 8.0f, value.c_str(), 1.6f);
    };

    if (!state->loginModeIsSignup) {
        // Login fields
        drawField(fieldTop, "Email or Username", state->loginIdentifierInput, state->loginActiveField == 0);
        drawField(fieldTop + 60.0f, "Password", state->loginPasswordInput, state->loginActiveField == 1);
    } else {
        // Signup fields
        drawField(fieldTop, "Email", state->signupEmailInput, state->loginActiveField == 0);
        drawField(fieldTop + 60.0f, "Username", state->signupUsernameInput, state->loginActiveField == 1);
        drawField(fieldTop + 120.0f, "Password", state->signupPasswordInput, state->loginActiveField == 2);
    }

    // Submit hint
    SetDrawColor(state->renderer, state->colors.text);
    DrawTextScaled(
        state->renderer,
        contentLeft,
        cardRect->y + cardRect->h - 80.0f,
        "Press ENTER to submit. TAB/up/down to switch fields.",
        1.4f
    );

    // Auth status message — centered, red for errors / neutral for signup feedback
    if (!state->authMessage.empty()) {
        // Position near vertical center of the card
        float msgY = cardRect->y + (cardRect->h * 0.48f);
        bool isError = (state->authMessage.find("failed") != std::string::npos
            || state->authMessage.find("Error") != std::string::npos
            || state->authMessage.find("already") != std::string::npos
            || state->authMessage.find("invalid") != std::string::npos);
        if (isError) {
            SetDrawColor(state->renderer, SDL_Color{ 220, 50, 50, 255 });
        } else {
            SetDrawColor(state->renderer, state->colors.text);
        }
        DrawTextScaled(
            state->renderer,
            contentLeft,
            msgY,
            state->authMessage.c_str(),
            1.6f
        );
    }
}


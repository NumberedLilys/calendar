#include "appLogic.h"
#include "calendar.h"
#include <chrono>
#include <ctime>

inline void SetDrawColor(SDL_Renderer* renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

// Helper to draw larger debug text without changing layout math
static inline void DrawTextScaled(SDL_Renderer* renderer, float x, float y, const char* text, float scale) {
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
    SDL_FRect shadow = { cardRect->x + 4.0f, cardRect->y + 4.0f, cardRect->w, cardRect->h };
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
    char title[64];

    if (state->currentCalendar != nullptr) {
        // Use const auto& to prevent potential std::string copy allocations per frame
        const auto& monthName = state->currentCalendar->getMonthName();
        SDL_snprintf(title, sizeof(title), "%s %d", monthName.c_str(), state->currentCalendar->getYear());
    } else {
        SDL_snprintf(title, sizeof(title), "Calendar");
    }

    SetDrawColor(state->renderer, state->colors.white);
    DrawTextScaled(state->renderer, cardRect->x + 20.0f, cardRect->y + 25.0f, title, 2.2f);
}

void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight) {
    static const char* days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    float cellW = cardRect->w / 7.0f;
    float labelY = cardRect->y + headerHeight + 20.0f;

    // Draw Labels
    SetDrawColor(state->renderer, state->colors.text);
    for (int i = 0; i < 7; i++) {
        DrawTextScaled(
            state->renderer,
            cardRect->x + (i * cellW) + (cellW * 0.5f) - 16.0f,
            labelY,
            days[i],
            1.6f
        );
    }

    // Grid Logic
    float gridTop = labelY + 30.0f;
    float cellH = (cardRect->h - (gridTop - cardRect->y) - 20.0f) / 6.0f;

    int startOffset = 0;
    int totalDays = 30;

    static int todayYear = 0, todayMonth = 0, todayDay = 0;
    static auto lastTime = std::chrono::system_clock::time_point::min();
    auto now = std::chrono::system_clock::now();

    if (now - lastTime > std::chrono::seconds(1)) {
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
        lastTime = now;
    }

    bool isCurrentMonth = false;
    if (state->currentCalendar != nullptr) {
        startOffset = state->currentCalendar->getStartDayOfWeek(); 
        totalDays = state->currentCalendar->getDaysInMonth();
        
        // Hoist standard year/month checks outside of the loop
        isCurrentMonth = (state->currentCalendar->getYear() == todayYear && 
                          state->currentCalendar->getMonth() == todayMonth);
    }

    SetDrawColor(state->renderer, state->colors.grid);
    for (int i = 0; i < 42; i++) {
        int dayNum = i + 1 - startOffset;
        if (dayNum >= 1 && dayNum <= totalDays) {
            int row = i / 7;
            int col = i % 7;
            SDL_FRect cellRect = { cardRect->x + (col * cellW), gridTop + (row * cellH), cellW, cellH };
            SDL_RenderRect(state->renderer, &cellRect);
        }
    }

    static const char* dayStrings[32] = {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
        "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
        "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"
    };

    // Pass 2: Render highlights and text
    for (int i = 0; i < 42; i++) {
        int dayNum = i + 1 - startOffset;
        if (dayNum >= 1 && dayNum <= totalDays && dayNum <= 31) {
            int row = i / 7;
            int col = i % 7;
            float x = cardRect->x + (col * cellW);
            float y = gridTop + (row * cellH);

            if (isCurrentMonth && dayNum == todayDay) {
                SetDrawColor(state->renderer, state->colors.primary);
                SDL_FRect marker = { x + 5.0f, y + 5.0f, 25.0f, 25.0f };
                SDL_RenderFillRect(state->renderer, &marker);
                SetDrawColor(state->renderer, state->colors.white);
            } else {
                SetDrawColor(state->renderer, state->colors.text);
            }

            DrawTextScaled(state->renderer, x + 10.0f, y + 6.0f, dayStrings[dayNum], 1.6f);
        }
    }
}

void RenderLoginScreen(AppState* state, SDL_FRect* cardRect) {
    RenderCalendarBody(state, cardRect);

    float headerHeight = 80.0f;
    SDL_FRect headerRect = { cardRect->x, cardRect->y, cardRect->w, headerHeight };
    
    SetDrawColor(state->renderer, state->colors.primary);
    SDL_RenderFillRect(state->renderer, &headerRect);

    SetDrawColor(state->renderer, state->colors.white);
    const char* title = state->loginModeIsSignup ? "Sign Up" : "Login";
    DrawTextScaled(state->renderer, cardRect->x + 20.0f, cardRect->y + 25.0f, title, 2.2f);

    float contentTop = cardRect->y + headerHeight + 40.0f;
    float contentLeft = cardRect->x + 40.0f;

    SDL_FRect loginBtn = { contentLeft, contentTop, 140.0f, 40.0f };
    SDL_FRect signupBtn = { contentLeft + 160.0f, contentTop, 140.0f, 40.0f };

    // Batch drawing rects
    SetDrawColor(state->renderer, state->loginModeIsSignup ? state->colors.card : state->colors.primary);
    SDL_RenderFillRect(state->renderer, &loginBtn);
    SetDrawColor(state->renderer, state->loginModeIsSignup ? state->colors.primary : state->colors.card);
    SDL_RenderFillRect(state->renderer, &signupBtn);

    // Batch drawing rect text
    SetDrawColor(state->renderer, state->colors.text);
    DrawTextScaled(state->renderer, loginBtn.x + 22.0f, loginBtn.y + 10.0f, "Login", 1.8f);
    DrawTextScaled(state->renderer, signupBtn.x + 16.0f, signupBtn.y + 10.0f, "Sign Up", 1.8f);

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

        if (!value.empty()) {
            SetDrawColor(state->renderer, state->colors.text);
            DrawTextScaled(state->renderer, box.x + 10.0f, box.y + 8.0f, value.c_str(), 1.6f);
        }
    };

    if (!state->loginModeIsSignup) {
        drawField(fieldTop, "Email or Username", state->loginIdentifierInput, state->loginActiveField == 0);
        drawField(fieldTop + 60.0f, "Password", state->loginPasswordInput, state->loginActiveField == 1);
    } else {
        drawField(fieldTop, "Email", state->signupEmailInput, state->loginActiveField == 0);
        drawField(fieldTop + 60.0f, "Username", state->signupUsernameInput, state->loginActiveField == 1);
        drawField(fieldTop + 120.0f, "Password", state->signupPasswordInput, state->loginActiveField == 2);
    }

    SetDrawColor(state->renderer, state->colors.text);
    DrawTextScaled(
        state->renderer,
        contentLeft,
        cardRect->y + cardRect->h - 80.0f,
        "Press ENTER to submit. TAB/up/down to switch fields.",
        1.4f
    );

    if (!state->authMessage.empty()) {
        // STRING OPTIMIZATION: Only parse the string for keywords if it has actually changed
        static std::string lastCheckedMsg = "";
        static bool isErrorCached = false;

        if (state->authMessage != lastCheckedMsg) {
            lastCheckedMsg = state->authMessage;
            isErrorCached = (lastCheckedMsg.find("failed") != std::string::npos
                || lastCheckedMsg.find("Error") != std::string::npos
                || lastCheckedMsg.find("already") != std::string::npos
                || lastCheckedMsg.find("invalid") != std::string::npos);
        }

        if (isErrorCached) {
            SetDrawColor(state->renderer, SDL_Color{ 220, 50, 50, 255 });
        } else {
            SetDrawColor(state->renderer, state->colors.text);
        }
        
        float msgY = cardRect->y + (cardRect->h * 0.48f);
        DrawTextScaled(state->renderer, contentLeft, msgY, state->authMessage.c_str(), 1.6f);
    }
}
#include "app_logic.h"
#include "calendar.h"

// Reduces code duplication for setting colors
void SetDrawColor(SDL_Renderer* renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
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
    SDL_SetRenderScale(state->renderer, 2.0f, 2.0f);
    SDL_RenderDebugText(
        state->renderer,
        (cardRect->x + 20) / 2,
        (cardRect->y + 25) / 2,
        title
    );
    SDL_SetRenderScale(state->renderer, 1.0f, 1.0f);
}

void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight) {
    const char* days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    float cellW = cardRect->w / 7;
    float labelY = cardRect->y + headerHeight + 20;

    // Draw Labels
    SetDrawColor(state->renderer, state->colors.text);
    for (int i = 0; i < 7; i++) {
        SDL_RenderDebugText(state->renderer, cardRect->x + (i * cellW) + (cellW / 2) - 12, labelY, days[i]);
    }

    // Grid Logic
    float gridTop = labelY + 30;
    float cellH = (cardRect->h - (gridTop - cardRect->y) - 20) / 6;

    int startOffset = 0;
    int totalDays = 30;
    int currentDay = -1;

    if (state->currentCalendar != nullptr) {
        startOffset = state->currentCalendar->getStartDayOfWeek(); // 0 = Sunday
        totalDays = state->currentCalendar->getDaysInMonth();
        currentDay = state->currentCalendar->getDay();
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

            if (currentDay != -1 && dayNum == currentDay) {
                SetDrawColor(state->renderer, state->colors.primary);
                SDL_FRect marker = { x + 5, y + 5, 25, 25 };
                SDL_RenderFillRect(state->renderer, &marker);
                SetDrawColor(state->renderer, state->colors.white);
            } else {
                SetDrawColor(state->renderer, state->colors.text);
            }

            char buf[3];
            SDL_snprintf(buf, sizeof(buf), "%d", dayNum);
            SDL_RenderDebugText(state->renderer, x + 10, y + 10, buf);
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
    SDL_SetRenderScale(state->renderer, 2.0f, 2.0f);
    const char* title = state->loginModeIsSignup ? "Sign Up" : "Login";
    SDL_RenderDebugText(
        state->renderer,
        (cardRect->x + 20) / 2,
        (cardRect->y + 25) / 2,
        title
    );
    SDL_SetRenderScale(state->renderer, 1.0f, 1.0f);

    float contentTop = cardRect->y + headerHeight + 40.0f;
    float contentLeft = cardRect->x + 40.0f;

    // Mode buttons: Login / Signup
    SDL_FRect loginBtn = { contentLeft, contentTop, 140.0f, 40.0f };
    SDL_FRect signupBtn = { contentLeft + 160.0f, contentTop, 140.0f, 40.0f };

    // Login button
    SetDrawColor(state->renderer, state->loginModeIsSignup ? state->colors.card : state->colors.primary);
    SDL_RenderFillRect(state->renderer, &loginBtn);
    SetDrawColor(state->renderer, state->colors.text);
    SDL_RenderDebugText(state->renderer, loginBtn.x + 20, loginBtn.y + 12, "Login (1)");

    // Signup button
    SetDrawColor(state->renderer, state->loginModeIsSignup ? state->colors.primary : state->colors.card);
    SDL_RenderFillRect(state->renderer, &signupBtn);
    SetDrawColor(state->renderer, state->colors.text);
    SDL_RenderDebugText(state->renderer, signupBtn.x + 15, signupBtn.y + 12, "Sign Up (2)");

    float fieldTop = contentTop + 70.0f;
    float fieldHeight = 36.0f;
    float fieldWidth = cardRect->w - 80.0f;

    auto drawField = [&](float y, const char* label, const std::string& value, bool focused) {
        SetDrawColor(state->renderer, state->colors.text);
        SDL_RenderDebugText(state->renderer, contentLeft, y - 18.0f, label);

        SDL_FRect box = { contentLeft, y, fieldWidth, fieldHeight };
        SetDrawColor(state->renderer, state->colors.grid);
        SDL_RenderRect(state->renderer, &box);

        if (focused) {
            SDL_FRect highlight = { box.x, box.y, 4.0f, box.h };
            SetDrawColor(state->renderer, state->colors.primary);
            SDL_RenderFillRect(state->renderer, &highlight);
        }

        SetDrawColor(state->renderer, state->colors.text);
        SDL_RenderDebugText(state->renderer, box.x + 8.0f, box.y + 10.0f, value.c_str());
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
    SDL_RenderDebugText(
        state->renderer,
        contentLeft,
        cardRect->y + cardRect->h - 80.0f,
        "Press ENTER to submit. TAB/up/down to switch fields."
    );

    // Auth status message
    if (!state->authMessage.empty()) {
        SetDrawColor(state->renderer, state->colors.text);
        SDL_RenderDebugText(
            state->renderer,
            contentLeft,
            cardRect->y + cardRect->h - 50.0f,
            state->authMessage.c_str()
        );
    }
}

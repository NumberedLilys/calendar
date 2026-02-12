#include "app_logic.h"

// Helper: Reduces code duplication for setting colors
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

    // Title text
    SetDrawColor(state->renderer, state->colors.white);
    SDL_SetRenderScale(state->renderer, 2.0f, 2.0f);
    SDL_RenderDebugText(state->renderer, (cardRect->x + 20) / 2, (cardRect->y + 25) / 2, "JANUARY 2026");
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
    int startOffset = 4; // Jan 1st 2026 = Thursday
    int totalDays = 31;

    for (int i = 0; i < 42; i++) { // 6 rows * 7 columns
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

            // Highlight Today
            if (dayNum == 29) {
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
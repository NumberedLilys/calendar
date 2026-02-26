#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <chrono>
#include <ctime>
#include "app_logic.h"
#include "Calendar.h"

// --- Prototypes for your UI functions (lives in calendar_ui.cpp) ---
void RenderBackground(AppState* state);
void RenderCalendarBody(AppState* state, SDL_FRect* cardRect);
void RenderHeader(AppState* state, SDL_FRect* cardRect);
void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight);

// 1. INITIALIZE: Runs once at the start
extern "C" SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return SDL_APP_FAILURE;
    }
    
    AppState* state = new AppState();
    
    if (!SDL_CreateWindowAndRenderer("Calendar v1.0", 800, 700, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
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

    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);
    *appstate = state;
    
    return SDL_APP_CONTINUE;
}

// 2. EVENTS: Runs whenever you click, resize, or close the window
extern "C" SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; // This closes the app
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
    RenderCalendarBody(state, &cardRect);
    RenderHeader(state, &cardRect);
    RenderGrid(state, &cardRect, 80.0f);

    SDL_RenderPresent(state->renderer);
    return SDL_APP_CONTINUE;
}

// 4. CLEANUP: Runs when the app closes
extern "C" void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState* state = (AppState*)appstate;
    if (state) {
        if (state->currentCalendar) delete state->currentCalendar;
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        delete state;
    }
    SDL_Quit();
}
#ifndef APP_LOGIC_H
#define APP_LOGIC_H

#include <SDL3/SDL.h>

// Using Structs instead of Macros
struct CalendarColors {
    SDL_Color background = {243, 244, 246, 255};
    SDL_Color card       = {255, 255, 255, 255};
    SDL_Color primary    = {59, 130, 246, 255};
    SDL_Color text       = {31, 41, 55, 255};
    SDL_Color grid       = {229, 231, 235, 255};
    SDL_Color white      = {255, 255, 255, 255};
    SDL_Color shadow     = {0, 0, 0, 20};
};

// Application State
struct AppState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    CalendarColors colors;
    float margin = 40.0f;
};

// Function prototypes
void RenderBackground(AppState* state);
void RenderCalendarBody(AppState* state, SDL_FRect* cardRect);
void RenderHeader(AppState* state, SDL_FRect* cardRect);
void RenderGrid(AppState* state, SDL_FRect* cardRect, float headerHeight);

#endif
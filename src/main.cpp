#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include "app_logic.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    
    AppState* state = new AppState();
    if (!SDL_CreateWindowAndRenderer("Calendar v1.0", 800, 700, SDL_WINDOW_RESIZABLE, &state->window, &state->renderer)) {
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderDrawBlendMode(state->renderer, SDL_BLENDMODE_BLEND);
    *appstate = state;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    if (event->type == SDL_EVENT_QUIT) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState* state = (AppState*)appstate;
    int w, h;
    SDL_GetRenderOutputSize(state->renderer, &w, &h);

    // Calculation of core dimensions
    SDL_FRect cardRect = { state->margin, state->margin, w - (state->margin * 2), h - (state->margin * 2) };

    RenderBackground(state);
    RenderCalendarBody(state, &cardRect);
    RenderHeader(state, &cardRect);
    RenderGrid(state, &cardRect, 80.0f);

    SDL_RenderPresent(state->renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    AppState* state = (AppState*)appstate;
    if (state) {
        SDL_DestroyRenderer(state->renderer);
        SDL_DestroyWindow(state->window);
        delete state; // Clean up memory
    }
    SDL_Quit();
}
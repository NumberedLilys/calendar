#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Colors - Using macros for quick color setting
#define COLOR_BG      0xF3, 0xF4, 0xF6, 255 
#define COLOR_CARD    255, 255, 255, 255    
#define COLOR_PRIMARY 0x3B, 0x82, 0xF6, 255 
#define COLOR_TEXT    0x1F, 0x29, 0x37, 255 
#define COLOR_GRID    0xE5, 0xE7, 0xEB, 255 

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Calendar UI", 800, 700, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    int winW, winH;
    SDL_GetRenderOutputSize(renderer, &winW, &winH);

    // 1. Draw Background
    SDL_SetRenderDrawColor(renderer, COLOR_BG);
    SDL_RenderClear(renderer);

    // 2. Setup Calendar Dimensions
    float margin = 40.0f;
    float cardW = (float)winW - (margin * 2);
    float cardH = (float)winH - (margin * 2);
    SDL_FRect cardRect = { margin, margin, cardW, cardH };

    // Draw Shadow
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 20);
    SDL_FRect shadow = { margin + 4, margin + 4, cardW, cardH };
    SDL_RenderFillRect(renderer, &shadow);

    // Draw Calendar Body
    SDL_SetRenderDrawColor(renderer, COLOR_CARD);
    SDL_RenderFillRect(renderer, &cardRect);

    // Draw Header
    float headerHeight = 80.0f;
    SDL_SetRenderDrawColor(renderer, COLOR_PRIMARY);
    SDL_FRect headerRect = { margin, margin, cardW, headerHeight };
    SDL_RenderFillRect(renderer, &headerRect);

    // Draw Month Title
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    SDL_RenderDebugText(renderer, (margin + 20) / 2, (margin + 25) / 2, "JANUARY 2026");
    SDL_SetRenderScale(renderer, 1.0f, 1.0f); 

    // 4. Draw Days of the Week Labels
    const char *days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    float cellW = cardW / 7;
    float labelY = margin + headerHeight + 20;

    SDL_SetRenderDrawColor(renderer, COLOR_TEXT);
    for (int i = 0; i < 7; i++) {
        SDL_RenderDebugText(renderer, margin + (i * cellW) + (cellW / 2) - 12, labelY, days[i]);
    }

    // 5. Draw the Date Grid 
    float gridTop = labelY + 30;
    float gridBottom = cardH + margin - 20;
    float cellH = (gridBottom - gridTop) / 6; // Changed to 6 rows to ensure Feb/Mar fits properly

    /* 
       WHY: January 1st, 2026 is a Thursday (Index 4). 
       Added 'startOffset' so the dates align with the correct day of the week.
    */
    int startOffset = 4; 
    int totalDays = 31;

    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 7; col++) {
            // Calculate which day of the month this cell represents
            int dayNum = (row * 7) + col + 1 - startOffset;

            // Only draw if the day is between 1 and 31
            if (dayNum >= 1 && dayNum <= totalDays) {
                float x = margin + (col * cellW);
                float y = gridTop + (row * cellH);

                // Draw cell border
                SDL_SetRenderDrawColor(renderer, COLOR_GRID);
                SDL_FRect cellRect = { x, y, cellW, cellH };
                SDL_RenderRect(renderer, &cellRect);

                // Highlight "Today" (January 29th)
                if (dayNum == 29) {
                    SDL_SetRenderDrawColor(renderer, COLOR_PRIMARY);
                    SDL_FRect todayMarker = { x + 5, y + 5, 25, 25 };
                    SDL_RenderFillRect(renderer, &todayMarker);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White text for highlight
                } else {
                    SDL_SetRenderDrawColor(renderer, COLOR_TEXT);
                }

                char buf[3];
                SDL_snprintf(buf, sizeof(buf), "%d", dayNum);
                SDL_RenderDebugText(renderer, x + 10, y + 10, buf);
            }
        }
    }

    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* 
      Manually destroy renderer when closing to prevent memory leaks
    */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#include "Sonic.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return -1;
    if (IMG_Init(IMG_isPNG) == 0) return -1;

    SDL_Window* window;
    SDL_Renderer* renderer;
    if (!SDL_CreateWindowAndRenderer("Sonic Demo", 800, 600, 0, &window, &renderer)) return -1;

    Sonic sonic(renderer);

    for (int i = 0; i < 1000; ++i) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        sonic.update();
        sonic.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}

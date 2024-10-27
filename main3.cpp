#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <cstdio>
#include <thread>
#include <atomic>

#define INITIAL_WINDOW_WIDTH 800
#define INITIAL_WINDOW_HEIGHT 600

std::atomic<bool> running(true);  // Atomic boolean to signal the main loop

void eventLoop(SDL_Event* event) {
    while (running) {
        while (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT) {
                running = false;
            }
            // Handle other events as needed
        }
        SDL_Delay(1); // Yield to avoid busy-waiting
    }
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    printf("INITED SDL\n");

    // Create a resizable window and renderer with hardware acceleration
    SDL_Window* window = SDL_CreateWindow("SDL2 Rectangles Grid",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer) {
        SDL_Log("Failed to create window or renderer: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    printf("Hello, World!\n");

    SDL_Event event; 
    std::thread eventThread(eventLoop, &event); // Start the event handling thread

    // Main rendering loop
    while (running) {
        // Render scene
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue background
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        // Limit frame rate to ~60 FPS
        SDL_Delay(16); // Approximately 60 FPS
    }

    // Clean up
    eventThread.join(); // Wait for the event thread to finish
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

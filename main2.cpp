#include <SDL.h>
#define WIN32_LEAN_AND_MEAN
//#define NOMINMAX
#include <Windows.h>
#include <SDL_syswm.h>
#include <cstdio>

#define RECT_COUNT 100000
#define RECT_SIZE 10

SDL_Renderer* renderer = nullptr;

uint8_t counter = 0;


void render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue background
    SDL_RenderClear(renderer);


    // Render rectangles
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White rectangles
    for (int i = 0; i < RECT_COUNT; ++i) {
        SDL_Rect rect = { (i % (800 / RECT_SIZE)) * RECT_SIZE,
                            (i / (600 / RECT_SIZE)) * RECT_SIZE,
                            RECT_SIZE, RECT_SIZE };
        SDL_RenderFillRect(renderer, &rect);
    }

        SDL_RenderPresent(renderer);


       counter++;
       printf("Render %d\n", counter);
}

int event_filter(void* userdata, SDL_Event* event) {

 
    //printf("Event %d\n", counter);

    if (event->type == SDL_QUIT) {
        SDL_Log("Quit event received");
        SDL_Quit();
        exit(0);
    } else if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        //printf("Window size changed to %d x %d", event->window.data1, event->window.data2);
        SDL_RenderSetViewport(renderer, nullptr);
        render();
    }

    return 1; // Return 1 to process the event, 0 to ignore it
}


int main(int argc, char* argv[])
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    if (!window || !renderer) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }

    render();

    SDL_SetEventFilter(event_filter, nullptr);

    SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);

    int running = 1;
    SDL_Event event;
    while (running) {
        
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
    }

    // clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


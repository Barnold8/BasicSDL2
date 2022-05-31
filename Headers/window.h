#ifndef WINDOW
#define WINDOW

#include "includes.h"

class Window {
    private:
        bool Running;

        SDL_Window* Surf_Display = NULL;
        SDL_Renderer* Rend = NULL;

    public:
        Window();
 
        int OnExecute();
 
    public:
 
        bool OnInit();
 
        void OnEvent(SDL_Event* Event);
 
        void OnLoop();
 
        void OnRender(SDL_Rect*);
 
        void OnCleanup();
};
 


#endif
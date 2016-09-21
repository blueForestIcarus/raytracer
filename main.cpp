/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

//SDL defines
#define SCREEN_BPP 32 //bits per pixel

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

int exit_flg = 0;

//functions
void Print_WindowEvent(const SDL_Event * event);

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screen = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "Raygun v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//init
	 		Uint32 windowID = SDL_GetWindowID(window);
			SDL_Rect text_surface_pos;
			SDL_Surface* text_surface;
			SDL_Rect display_surface_pos;
			SDL_Surface* display_surface;
			SDL_Rect border;


			//main event loop
			SDL_Event event;
			while(!exit_flg){
				//poll and event from queue
				while(SDL_PollEvent(&event)){
					//check event type and delegate
					switch(event.type){
						case SDL_WINDOWEVENT:
							Print_WindowEvent(&event);
							if(event.window.windowID==windowID){
								switch(event.window.event){	
									case SDL_WINDOWEVENT_SIZE_CHANGED: 
										screen = SDL_GetWindowSurface( window );	
										SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x33, 0x33, 0x33 ) );

										if(screen->w > screen->h){
											display_surface_pos = {screen->w/2 + 2, 5, screen->w/2 - 7, screen->h - 10};
											border = {display_surface_pos.x-1, display_surface_pos.y-1, display_surface_pos.w+2, display_surface_pos.h+2}; 
											display_surface = SDL_CreateRGBSurface(0,display_surface_pos.w,display_surface_pos.h,SCREEN_BPP,0,0,0,0);
											SDL_FillRect( screen, &border, SDL_MapRGB( screen->format, 0xFF, 0xEF, 0xD9 ) );
											SDL_FillRect( screen, &display_surface_pos, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

											text_surface_pos = {5, 5, screen->w/2 - 7, screen->h - 10};
											border = {text_surface_pos.x-1, text_surface_pos.y-1, text_surface_pos.w+2, text_surface_pos.h+2}; 
											display_surface = SDL_CreateRGBSurface(0,text_surface_pos.w,text_surface_pos.h,SCREEN_BPP,0,0,0,0);
											SDL_FillRect( screen, &border, SDL_MapRGB( screen->format, 0xFF, 0xEF, 0xD9) );
											SDL_FillRect( screen, &text_surface_pos, SDL_MapRGB( screen->format, 0xDB, 0xC3, 0xA0 ) );
										}else{	
											display_surface_pos = {5, 5, screen->w -10, screen->h/2 - 7};
											border = {display_surface_pos.x-1, display_surface_pos.y-1, display_surface_pos.w+2, display_surface_pos.h+2}; 
											display_surface = SDL_CreateRGBSurface(0,display_surface_pos.w,display_surface_pos.h,SCREEN_BPP,0,0,0,0);
											SDL_FillRect( screen, &border, SDL_MapRGB( screen->format, 0xFF, 0xEF, 0xD9 ) );
											SDL_FillRect( screen, &display_surface_pos, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );

											text_surface_pos = {5, screen->h/2 + 2, screen->w -10 , screen->h/2 - 7};
											border = {text_surface_pos.x-1, text_surface_pos.y-1, text_surface_pos.w+2, text_surface_pos.h+2}; 
											display_surface = SDL_CreateRGBSurface(0,text_surface_pos.w,text_surface_pos.h,SCREEN_BPP,0,0,0,0);
											SDL_FillRect( screen, &border, SDL_MapRGB( screen->format, 0xFF, 0xEF, 0xD9) );
											SDL_FillRect( screen, &text_surface_pos, SDL_MapRGB( screen->format, 0xDB, 0xC3, 0xA0 ) );
										}

										SDL_UpdateWindowSurface( window );
										break;
									case SDL_WINDOWEVENT_CLOSE:  
										event.type = SDL_QUIT;
										SDL_PushEvent(&event);
										break;
									
									case SDL_WINDOWEVENT_SHOWN:
										screen = SDL_GetWindowSurface( window );
										//fill screen with white and flush changes
										SDL_FillRect( screen, NULL, SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF ) );
										SDL_UpdateWindowSurface( window );
										break;
								}
							}
							break;
						case SDL_QUIT: 
							//kill the event loop
							printf("EVENT: SDL_QUIT\n");
							exit_flg = true; 
							break;
					}
				}

				//draw subscreen
			} 
		}
	}
	//de-initialise
	printf("cleaning up...\n");
	
	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	printf("END OF PROGRAM\n");
	return 0;
}

void Print_WindowEvent(const SDL_Event * event){
//taken from: https://wiki.libsdl.org/SDL_WindowEvent
if (event->type == SDL_WINDOWEVENT) {
switch (event->window.event) {
case SDL_WINDOWEVENT_SHOWN:
SDL_Log("Window %d shown", event->window.windowID);
break;
case SDL_WINDOWEVENT_HIDDEN:
SDL_Log("Window %d hidden", event->window.windowID);
break;
case SDL_WINDOWEVENT_EXPOSED:
SDL_Log("Window %d exposed", event->window.windowID);
break;
case SDL_WINDOWEVENT_MOVED:
SDL_Log("Window %d moved to %d,%d",
event->window.windowID, event->window.data1,
event->window.data2);
break;
case SDL_WINDOWEVENT_RESIZED:
SDL_Log("Window %d resized to %dx%d",
event->window.windowID, event->window.data1,
event->window.data2);
break;
case SDL_WINDOWEVENT_SIZE_CHANGED:
SDL_Log("Window %d size changed to %dx%d",
event->window.windowID, event->window.data1,
event->window.data2);
break;
case SDL_WINDOWEVENT_MINIMIZED:
SDL_Log("Window %d minimized", event->window.windowID);
break;
case SDL_WINDOWEVENT_MAXIMIZED:
SDL_Log("Window %d maximized", event->window.windowID);
break;
case SDL_WINDOWEVENT_RESTORED:
SDL_Log("Window %d restored", event->window.windowID);
break;
case SDL_WINDOWEVENT_ENTER:
SDL_Log("Mouse entered window %d",
event->window.windowID);
break;
case SDL_WINDOWEVENT_LEAVE:
SDL_Log("Mouse left window %d", event->window.windowID);
break;
case SDL_WINDOWEVENT_FOCUS_GAINED:
SDL_Log("Window %d gained keyboard focus",
event->window.windowID);
break;
case SDL_WINDOWEVENT_FOCUS_LOST:
SDL_Log("Window %d lost keyboard focus",
event->window.windowID);
break;
case SDL_WINDOWEVENT_CLOSE:
SDL_Log("Window %d closed", event->window.windowID);
break;
default:
SDL_Log("Window %d got unknown event %d",
event->window.windowID, event->window.event);
break;
}
}
}

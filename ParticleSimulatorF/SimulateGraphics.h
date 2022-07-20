#include <SDL.h>
#include <string>
#include <wtypes.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "GetScreenResolution.h"

/*PARTS OF THIS FILE HAVE BEEN TAKEN FROM LAZYFOO'S SDL TUTORIAL*/
/*FILL_CIRCLE FUNCTION HAS BEEN TAKEN FROM https://gist.github.com/derofim/912cfc9161269336f722 */


using namespace std;
class SimulateGraphics : virtual private GetScreenResolution {
private:
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	SDL_Event e;
	bool quit = false;

	bool init()
	{
		//Initialization flag
		bool success = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//Create window
			gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
			if (gWindow == NULL)
			{
				cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Create renderer for window
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
				if (gRenderer == NULL)
				{
					cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
					success = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
			}
		}

		return success;
	}

	void main_loop(ifstream& ifs)
	{
		double x, y;
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 251, 227, 213, 2);
		SDL_RenderClear(gRenderer);
		ifs >> x;
		ifs >> y;
		y = get_height() - y;
		fill_circle(gRenderer, x, y, 20, 251, 74, 116, 255);
		ifs >> x;
		ifs >> y;
		y = get_height() - y;
		fill_circle(gRenderer, x, y, 20, 5, 178, 177, 255);
		ifs >> x;
		ifs >> y;
		y = get_height() - y;
		fill_circle(gRenderer, x, y, 20, 3, 117, 130, 255);
		SDL_Delay(25);
		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	void close()
	{
		//Destroy window    
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gRenderer = NULL;
		gWindow = NULL;
		SDL_Quit();
	}

	void fill_circle(SDL_Renderer* surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		// Note that there is more to altering the bitrate of this 
		// method than just changing this value.  See how pixels are
		// altered at the following web page for tips:
		//   http://www.libsdl.org/intro.en/usingvideo.html
		static const int BPP = 4;

		//double ra = (double)radius;

		for (double dy = 1; dy <= radius; dy += 1.0)
		{
			// This loop is unrolled a bit, only iterating through half of the
			// height of the circle.  The result is used to draw a scan line and
			// its mirror image below it.

			// The following formula has been simplified from our original.  We
			// are using half of the width of the circle because we are provided
			// with a center and we need left/right coordinates.

			double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
			int x = cx - dx;
			SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
			SDL_RenderDrawLine(gRenderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
			SDL_RenderDrawLine(gRenderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
		}
	}

public:
	int LoadTheCircles()
	{
		SCREEN_WIDTH = get_width();
		SCREEN_HEIGHT = get_height();
		//Start up SDL and create window
		if (!init())
		{
			printf("Failed to initialize!\n");
			return 0;
		}
		ifstream ifs;
		ifs.open("Coordinates.txt");
		if (!ifs.is_open())
		{
			return -1;
		}
		//While application is running
		chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		while (!quit)
		{
			main_loop(ifs);
			if (std::chrono::steady_clock::now() - start > std::chrono::seconds(40))
				break;
		}

		//Free resources and close SDL
		close();
		ifs.close();

		return 0;
	}
};
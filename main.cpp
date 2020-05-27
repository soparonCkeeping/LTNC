#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

void renderPlayer (SDL_Renderer* renderer, SDL_Rect snakeBlock, int x, int y, int scale, vector <int> tailX, vector<int> tailY, int slength) {
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);

    snakeBlock.w = scale;
    snakeBlock.h = scale;

    for (int i=0; i<slength; i++) {
        snakeBlock.x = tailX[i];
        snakeBlock.y = tailY[i];
        SDL_RenderFillRect (renderer, &snakeBlock);
    }
    // for the font of the snake ;
    snakeBlock.x = x;
    snakeBlock.y = y;
    SDL_RenderFillRect (renderer, &snakeBlock);
}

void renderFood (SDL_Renderer* renderer, SDL_Rect food) {
    SDL_SetRenderDrawColor (renderer, 0 , 255, 0, 255 );
    SDL_RenderFillRect (renderer, &food);
}
bool checkCollision (int foodx, int foody, int snakeblockx, int snakeblocky) {
    if (foodx == snakeblockx && foody == snakeblocky) {
        return true;
    }
    return false;
}
pair <int, int> getFoodSpawn (vector<int>tailX, vector<int>tailY, int playerx, int playery, int scale, int wScale, int slength) {

    srand(time(NULL));
    bool test = false;
    int x = scale * ( rand() % wScale );
    int y = scale * ( rand() % wScale );
    test = true;

    for (int i=0 ; i<slength; i++) {
        if (x == tailX[i] && y == tailY[i]) {
            test = false;
        }
    }

    if (test == false) {
        x = -100;
        y = -100;
    }

    pair <int, int> foodloca ;
    foodloca = make_pair (x, y);
    return foodloca;
}

void youWin (SDL_Renderer* renderer, SDL_Event event, int scale, int wscale, int slength) {
   SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	// Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"lazy.ttf", 10);
	if (font == NULL) {
		cout << "failed to get the font" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(slength * 10)).c_str(), Black);

	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((scale*wscale) / 2)-(gameoverRect.w/2);
	gameoverRect.y = ((scale*wscale) / 2)-(gameoverRect.h/2)-50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wscale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wscale) / 2) - ((retryRect.h / 2))+150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wscale) / 2) - (scoreRect.w / 2);
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Show game over screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}
}

void gameOver (SDL_Renderer* renderer, SDL_Event event, int scale, int wscale, int slength) {
    SDL_Color Red = { 255, 0, 0 };
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	// Get the font used for displaying text
	TTF_Font* font = TTF_OpenFont((char*)"lazy.ttf", 10);
	if (font == NULL) {
		cout << "failed to get the font" << endl;
		return;
	}

	SDL_Surface* gameover = TTF_RenderText_Solid(font, "Game Over", Red);
	SDL_Surface* retry = TTF_RenderText_Solid(font, "Press Enter to retry", White);
	SDL_Surface* score = TTF_RenderText_Solid(font, (string("Score: ") + to_string(slength * 10)).c_str(), Black);

	SDL_Texture* gameoverMessage = SDL_CreateTextureFromSurface(renderer, gameover);
	SDL_Texture* retryMessage = SDL_CreateTextureFromSurface(renderer, retry);
	SDL_Texture* scoreMessage = SDL_CreateTextureFromSurface(renderer, score);
	SDL_Rect gameoverRect;
	SDL_Rect retryRect;
	SDL_Rect scoreRect;
	gameoverRect.w = 200;
	gameoverRect.h = 100;
	gameoverRect.x = ((scale*wscale) / 2)-(gameoverRect.w/2);
	gameoverRect.y = ((scale*wscale) / 2)-(gameoverRect.h/2)-50;
	retryRect.w = 300;
	retryRect.h = 50;
	retryRect.x = ((scale*wscale) / 2) - ((retryRect.w / 2));
	retryRect.y = (((scale*wscale) / 2) - ((retryRect.h / 2))+150);
	scoreRect.w = 100;
	scoreRect.h = 30;
	scoreRect.x = ((scale*wscale / 2) - (scoreRect.w / 2));
	scoreRect.y = 0;
	SDL_RenderCopy(renderer, gameoverMessage, NULL, &gameoverRect);
	SDL_RenderCopy(renderer, retryMessage, NULL, &retryRect);
	SDL_RenderCopy(renderer, scoreMessage, NULL, &scoreRect);

	TTF_CloseFont(font);

	// Show game over screen while space has not been pressed
	while (true) {
		SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				exit(0);
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
				return;
			}

		}

	}
}
void renderScore (SDL_Renderer* renderer, int slength, int scale, int wscale) {
    SDL_Color Black = {0, 0, 0};

    TTF_Font* font = TTF_OpenFont ((char*)"lazy.ttf",10);

    if (font == NULL) {
        cout<<"failed to get the font"<<endl;
    }
    SDL_Surface* score = TTF_RenderText_Solid (font, (string("Score: ") + to_string(slength * 10)).c_str(),Black);
    SDL_Texture* scoreMassage = SDL_CreateTextureFromSurface (renderer, score);
    SDL_Rect scoreRect;
        scoreRect.w = 100;
        scoreRect.h = 30;
        scoreRect.x = ((scale*wscale) / 2) - (scoreRect.w / 2);
        scoreRect.y = 0;
    SDL_RenderCopy (renderer, scoreMassage, NULL, &scoreRect);

    TTF_CloseFont (font);
}

int main (int argc, char* argv[] ) {

    SDL_Window* window ;
    SDL_Renderer* renderer ;
    SDL_Event event;

    int slength = 0;

    vector <int> tailX;
    vector <int> tailY;

    int scale = 24;
    int wscale = 24;

    // saving the snake previous state
    int x = 0;
    int y = 0;
    int preX = 0;
    int preY = 0;

    bool UP = false;
    bool DOWN = false;
    bool RIGHT = false;
    bool LEFT = false;

    bool inPutThisFrame = false;
    bool relapse = false;

    SDL_Init (SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow ("snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scale*wscale+1, scale*wscale+1, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);

    // the snake cell rectangles detail
    SDL_Rect snakeBlock;
        snakeBlock.x = 0;
        snakeBlock.y = 0;
        snakeBlock.h = 0;
        snakeBlock.w = 0;

    // the food rectangle detail
    SDL_Rect food;
        food.x = 0;
        food.y = 0;
        food.h = scale;
        food.w = scale;

    pair <int, int> foodloca = getFoodSpawn (tailX, tailY, x, y, scale, wscale, slength);
    food.x = foodloca.first;
    food.y = foodloca.second;

    cout<<food.x<<"   "<<food.y<<endl;

    float time = SDL_GetTicks() / 100;

    while (true) {
        float newtime = SDL_GetTicks() / 75;
        float deltatime = newtime - time;
        time = newtime;

        inPutThisFrame = false;

        if (slength>575) {
            youWin (renderer, event, scale, wscale, slength);
            x = 0;
            y = 0;
            UP = false;
            RIGHT = false;
            DOWN = false;
            LEFT = false;
            slength = 0;
            relapse = false;

            foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
            if (food.x == -100, food.y == -100) {
                relapse = true;
            }
            food.x = foodloca.first;
            food.y = foodloca.second;
        }


        if (SDL_PollEvent (&event)) {

            if (event.type == SDL_QUIT ) {
                exit (0);
            }

            if (event.type == SDL_KEYDOWN && inPutThisFrame == false) {
                if (DOWN == false && event.key.keysym.scancode == SDL_SCANCODE_UP) {
					UP = true;
					LEFT = false;
					RIGHT = false;
					DOWN = false;
					inPutThisFrame = true;
				}
				else if (RIGHT == false && event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					UP = false;
					LEFT = true;
					RIGHT = false;
					DOWN = false;
					inPutThisFrame = true;
				}
				else if (UP == false && event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					UP = false;
					LEFT = false;
					RIGHT = false;
					DOWN = true;
					inPutThisFrame = true;
				}
				else if (LEFT == false && event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					UP = false;
					LEFT = false;
					RIGHT = true;
					DOWN = false;
					inPutThisFrame = true;
				}
            }

        }

        // if snake go beyond the map, let it go out of the wall being opposite to its direction

        if (x >= scale*24)
            x = 0;
        if (x <0 )
            x = (scale-1) *24;
        if (y>= scale*24)
            y = 0;
        if (y< 0)
            y= (scale-1) *24;

        preX = x;
        preY = y;

        if (UP)
            y -= deltatime*scale;
        else if (DOWN)
            y += deltatime*scale;
        else if (RIGHT)
            x += deltatime*scale;
        else if (LEFT)
            x -= deltatime*scale;

        cout<<x<<endl;

        if (relapse == true) {

			relapse = false;
			foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
			food.x = foodloca.first;
			food.y = foodloca.second;

			if (food.x == -100 && food.y == -100) {
				relapse = true;
			}

		}

        if (checkCollision(food.x, food.y, x, y)) {
            foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
			food.x = foodloca.first;
			food.y = foodloca.second;

			if (food.x == -100 && food.y == -100) {
				relapse = true;
			}

			slength++;
        }

        if ( deltatime * scale == 24) {

            if (tailX.size() != slength) {
                tailX.push_back(preX);
                tailY.push_back(preY);
            }

            for (int i=0; i<slength; i++) {
                if (i>0) {
                    tailX[i-1] = tailX[i];
                    tailY[i-1] = tailY[i];
                }
            }
            if (slength > 0 ) {
                tailX[slength-1] = preX;
                tailY[slength-1] = preY;
            }
        }

        for (int i=0; i<slength; i++) {
            if (x == tailX[i] && y == tailY[i]) {
                gameOver (renderer, event, scale, wscale, slength);
                x = 0;
                y = 0;
                UP = false;
                RIGHT = false;
                DOWN = false;
                LEFT = false;
                slength = 0;
                relapse = false;

                foodloca = getFoodSpawn(tailX, tailY, x, y, scale, wscale, slength);
                if (food.x == -100, food.y == -100) {
                    relapse = true;
                }
                food.x = foodloca.first;
                food.y = foodloca.second;
            }
        }

        renderFood (renderer, food);
        renderPlayer (renderer, snakeBlock, x, y, scale, tailX, tailY, slength);
        renderScore (renderer, slength, scale, wscale);


        SDL_RenderDrawLine(renderer, 0, 0, 0, scale*wscale);
		SDL_RenderDrawLine(renderer, 0, scale*wscale, scale*wscale, scale*wscale);
		SDL_RenderDrawLine(renderer, scale*wscale, scale*wscale, scale*wscale, 0);
		SDL_RenderDrawLine(renderer, scale*wscale, 0, 0, 0);


        SDL_RenderPresent (renderer);

        SDL_SetRenderDrawColor (renderer, 105, 105, 105, 255);

        SDL_RenderClear (renderer);
    }

    SDL_DestroyWindow (window);

    TTF_Quit();
    SDL_Quit();

    return 0;
}


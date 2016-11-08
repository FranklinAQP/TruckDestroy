#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

//#include <SDL/SDL.h>
//#include <SDL/SDL_image.h>
#include "SDL.h"
#include <iostream>
#include "Configuration.h"
#include "Nave.h"
#include "SDL_image.h"

using namespace std;

SDL_Surface *nave = NULL;
SDL_Surface *misil = NULL;
SDL_Surface *meteorito = NULL;
SDL_Surface *navered = NULL;
SDL_Surface *explosion = NULL;

SDL_Surface *enter = NULL;
SDL_Surface *linea = NULL;
SDL_Surface *tiempo = NULL;
SDL_Surface *puntos = NULL;
SDL_Surface *nivel = NULL;
SDL_Surface *n0 = NULL;
SDL_Surface *n1 = NULL;
SDL_Surface *n2 = NULL;
SDL_Surface *n3 = NULL;
SDL_Surface *n4 = NULL;
SDL_Surface *n5 = NULL;
SDL_Surface *n6 = NULL;
SDL_Surface *n7 = NULL;
SDL_Surface *n8 = NULL;
SDL_Surface *n9 = NULL;
SDL_Surface *gano = NULL;
SDL_Surface *perdio = NULL;
SDL_Surface *dpts = NULL;

int count_a = 0;
int count_b = 0;
int count_c = 0;
int level=1;
int lpuntos=0;

void addpuntos(int pts){
    ++lpuntos;
    if(count_c==9){
        if(count_b==9){
            ++count_a;
            count_b=0;
            count_c=0;
        }else{
            ++count_b;
            count_c=0;
        }
    }else{
        ++count_c;
    }
}

int temp_a=0;
int temp_b=0;
int temp_c=0;
int temp_d=0;
int temp = 0;
int temporizador=0;

void reset_counters(){
    lpuntos=0;
    level=1;
    count_a = 0;
    count_b = 0;
    count_c = 0;
    temp_a=0;
    temp_b=0;
    temp_c=0;
    temp_d=0;
    temporizador=0;
    temp = 0;
}

int confirmar=0;
int pantalla = -1;
SDL_Surface *LoadSurfaceFromFile(std::string filename);
void DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
bool updateimg(SDL_Surface* destination);
bool updategano(SDL_Surface* destination);
bool updateinit(SDL_Surface* destination);
bool updateperdio(SDL_Surface* destination);
bool updatefiles();
int zzz=0;

int main(int argc, char* args[])
{
    SDL_Surface* displaysurface = NULL;
	SDL_Event sdlevent;
	unsigned boxcolor;

	bool running;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cerr << "SDL_Init Failed: " << SDL_GetError() << endl;
		return -1;
	}

	displaysurface = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE);

	updatefiles();

	if(displaysurface == NULL){
		cerr << "SDL_SetVideoMode Failed: " << SDL_GetError() << endl;
		return -1;
	}

	SDL_WM_SetCaption("Truck Destroy", NULL);



	unsigned backgroundcolor = SDL_MapRGB(displaysurface->format, 200, 200, 200);
	unsigned snakeheadcolor = SDL_MapRGB(displaysurface->format, 255, 0, 0);
	unsigned snakebodycolor = SDL_MapRGB(displaysurface->format, 0, 255, 0);
	unsigned coincolor = SDL_MapRGB(displaysurface->format, 255, 255, 0);

    Nave xmen(400,500);

	boxcolor = SDL_MapRGB(displaysurface->format, 255, 0, 0);
	running  = true;


    while(running)
	{

		while(SDL_PollEvent(&sdlevent))
		{
			switch(sdlevent.type)
			{
			case SDL_QUIT:
				{
					running = false;
				}
				break;
			case SDL_KEYDOWN:
				{
					if(sdlevent.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
					}
					if(sdlevent.key.keysym.sym == SDLK_RETURN)
					{
						if(pantalla==-1) pantalla=0;
						if(pantalla==1){
                            reset_counters();
                            pantalla=-1;
						}
						if(pantalla==2){
                            reset_counters();
                            pantalla=-1;
						}
					}
				}
				break;
			}
		}
		if(pantalla ==0){
            xmen.Update();
		}
		SDL_FillRect(displaysurface, NULL, backgroundcolor);

		if(pantalla==0){
            xmen.Render_all(displaysurface);
            if(temporizador==0){
                xmen.run_meteoritos(level);
            }else if(temporizador==25){
                level=2;
                xmen.run_meteoritos(level);
            }else if(temporizador==45){
                level=3;
                xmen.run_meteoritos(level);
            }else if(temporizador==60){
                level=4;
                xmen.run_meteoritos(level);
            }else if(temporizador==70){
                level=5;
                xmen.run_meteoritos(level);
            }else if(temporizador==80){
                pantalla=1;
            }
            //cout<< "t = "<<temporizador<<" "<<xmen.dead<<endl;

            if(xmen.dead){
                pantalla=2;
                reset_counters();
                xmen.Restart();
            }
            if(xmen.misil_colision()){
                addpuntos(1);
            }




            updateimg(displaysurface);
		}else if(pantalla==-1){
            updateinit(displaysurface);
        }else if(pantalla==1){
            updategano(displaysurface);
        }else if(pantalla==2){
            updateperdio(displaysurface);
        }

		SDL_Flip(displaysurface);
		SDL_Delay(20);
	}
    xmen.UnloadFiles();
	SDL_Quit();

///////////////////////////////////////////////////////////////////////////////////////////////////END////////////////////

    return 0;
}

bool updategano(SDL_Surface* destination){
    DrawSurface(0, 0, gano, destination);
    return true;
}

bool updateinit(SDL_Surface* destination){
    DrawSurface(0, 0, enter, destination);
    return true;
}

bool updateperdio(SDL_Surface* destination){
    DrawSurface(0, 0, perdio, destination);
    return true;
}

bool updateimg(SDL_Surface* destination){
    DrawSurface(0, 620, linea, destination);
    DrawSurface(400, 650, tiempo, destination);
    DrawSurface(100, 650, puntos, destination);

    //nivel
    DrawSurface(220, 710, nivel, destination);
    if(level==1)
        DrawSurface(350, 710, n1, destination);
    else if(level==2)
        DrawSurface(350, 710, n2, destination);
    else if(level==3)
        DrawSurface(350, 710, n3, destination);
    else if(level==4)
        DrawSurface(350, 710, n4, destination);
    else if(level==5)
        DrawSurface(350, 710, n5, destination);

    //Dibujando puntos
        if(count_a==0)
            DrawSurface(220, 650, n0, destination);
        else if(count_a==1)
            DrawSurface(220, 650, n1, destination);
        else if(count_a==2)
            DrawSurface(220, 650, n2, destination);
        else if(count_a==3)
            DrawSurface(220, 650, n3, destination);
        else if(count_a==4)
            DrawSurface(220, 650, n4, destination);
        else if(count_a==5)
            DrawSurface(220, 650, n5, destination);
        else if(count_a==6)
            DrawSurface(220, 650, n6, destination);
        else if(count_a==7)
            DrawSurface(220, 650, n7, destination);
        else
            DrawSurface(220, 650, n0, destination);

        //countb
        if(count_b==0)
            DrawSurface(260, 650, n0, destination);
        else if(count_b==1)
            DrawSurface(260, 650, n1, destination);
        else if(count_b==2)
            DrawSurface(260, 650, n2, destination);
        else if(count_b==3)
            DrawSurface(260, 650, n3, destination);
        else if(count_b==4)
            DrawSurface(260, 650, n4, destination);
        else if(count_b==5)
            DrawSurface(260, 650, n5, destination);
        else if(count_b==6)
            DrawSurface(260, 650, n6, destination);
        else if(count_b==7)
            DrawSurface(260, 650, n7, destination);
        else if(count_b==8)
            DrawSurface(260, 650, n8, destination);
        else if(count_b==9)
            DrawSurface(260, 650, n9, destination);

        //countc
        if(count_c==0)
            DrawSurface(300, 650, n0, destination);
        else if(count_c==1)
            DrawSurface(300, 650, n1, destination);
        else if(count_c==2)
            DrawSurface(300, 650, n2, destination);
        else if(count_c==3)
            DrawSurface(300, 650, n3, destination);
        else if(count_c==4)
            DrawSurface(300, 650, n4, destination);
        else if(count_c==5)
            DrawSurface(300, 650, n5, destination);
        else if(count_c==6)
            DrawSurface(300, 650, n6, destination);
        else if(count_c==7)
            DrawSurface(300, 650, n7, destination);
        else if(count_c==8)
            DrawSurface(300, 650, n8, destination);
        else
            DrawSurface(300, 650, n9, destination);

        temp++;

        if(temp>50){
            //cout<<"temp = "<<temp<<endl;
            ++temporizador;
            temp=0;
            if(temp_d==9){
                if(temp_c==5){
                    if(temp_b==9){
                        ++temp_a;
                        temp_b=0;
                        temp_c=0;
                        temp_d=0;
                    }else{
                        ++temp_b;
                        temp_c=0;
                        temp_d=0;
                    }
                }else if(temp_c>=0){
                    ++temp_c;
                    temp_d=0;
                }
            }else if(temp_d>=0){
                ++temp_d;
            }
        }

        DrawSurface(650, 650, dpts, destination);

        if(temp_a==0)
            DrawSurface(580, 650, n0, destination);
        else if(temp_a==1)
            DrawSurface(580, 650, n1, destination);
        else if(temp_a==2)
            DrawSurface(580, 650, n2, destination);
        else if(temp_a==3)
            DrawSurface(580, 650, n3, destination);
        else if(temp_a==4)
            DrawSurface(580, 650, n4, destination);
        else if(temp_a==5)
            DrawSurface(580, 650, n5, destination);
        else if(temp_a==6)
            DrawSurface(580, 650, n6, destination);
        else if(temp_a==7)
            DrawSurface(580, 650, n7, destination);
        else if(temp_a==8)
            DrawSurface(580, 650, n8, destination);
        else
            DrawSurface(580, 650, n9, destination);



        if(temp_b==0)
            DrawSurface(615, 650, n0, destination);
        else if(temp_b==1)
            DrawSurface(615, 650, n1, destination);
        else if(temp_b==2)
            DrawSurface(615, 650, n2, destination);
        else if(temp_b==3)
            DrawSurface(615, 650, n3, destination);
        else if(temp_b==4)
            DrawSurface(615, 650, n4, destination);
        else if(temp_b==5)
            DrawSurface(615, 650, n5, destination);
        else if(temp_b==6)
            DrawSurface(615, 650, n6, destination);
        else if(temp_b==7)
            DrawSurface(615, 650, n7, destination);
        else if(temp_b==8)
            DrawSurface(615, 650, n8, destination);
        else
            DrawSurface(615, 650, n9, destination);


        if(temp_c==0)
            DrawSurface(680, 650, n0, destination);
        else if(temp_c==1)
            DrawSurface(680, 650, n1, destination);
        else if(temp_c==2)
            DrawSurface(680, 650, n2, destination);
        else if(temp_c==3)
            DrawSurface(680, 650, n3, destination);
        else if(temp_c==4)
            DrawSurface(680, 650, n4, destination);
        else if(temp_c==5)
            DrawSurface(680, 650, n5, destination);
        else if(temp_c==6)
            DrawSurface(680, 650, n6, destination);
        else if(temp_c==7)
            DrawSurface(680, 650, n7, destination);
        else if(temp_c==8)
            DrawSurface(680, 650, n8, destination);
        else
            DrawSurface(680, 650, n9, destination);




        if(temp_d==0)
            DrawSurface(715, 650, n0, destination);
        else if(temp_d==1)
            DrawSurface(715, 650, n1, destination);
        else if(temp_d==2)
            DrawSurface(715, 650, n2, destination);
        else if(temp_d==3)
            DrawSurface(715, 650, n3, destination);
        else if(temp_d==4)
            DrawSurface(715, 650, n4, destination);
        else if(temp_d==5)
            DrawSurface(715, 650, n5, destination);
        else if(temp_d==6)
            DrawSurface(715, 650, n6, destination);
        else if(temp_d==7)
            DrawSurface(715, 650, n7, destination);
        else if(temp_d==8)
            DrawSurface(715, 650, n8, destination);
        else
            DrawSurface(715, 650, n9, destination);


    return true;
}

bool updatefiles(){
    nave = LoadSurfaceFromFile("nave.png");

    linea = LoadSurfaceFromFile("linea.png");
    tiempo = LoadSurfaceFromFile("tiempo.png");
    puntos = LoadSurfaceFromFile("puntos.png");
    dpts = LoadSurfaceFromFile("dpts.png");
    gano = LoadSurfaceFromFile("gano.png");
    perdio = LoadSurfaceFromFile("perdio.png");
    enter = LoadSurfaceFromFile("enter.png");
    nivel = LoadSurfaceFromFile("nivel.png");
    n0 = LoadSurfaceFromFile("n0.png");
    n1 = LoadSurfaceFromFile("n1.png");
    n2 = LoadSurfaceFromFile("n2.png");
    n3 = LoadSurfaceFromFile("n3.png");
    n4 = LoadSurfaceFromFile("n4.png");
    n5 = LoadSurfaceFromFile("n5.png");
    n6 = LoadSurfaceFromFile("n6.png");
    n7 = LoadSurfaceFromFile("n7.png");
    n8 = LoadSurfaceFromFile("n8.png");
    n9 = LoadSurfaceFromFile("n9.png");
    return true;
}

void DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
    // Crea una superfice rectangular
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    // Blit
    SDL_BlitSurface(source, NULL, destination, &offset);
}

SDL_Surface *LoadSurfaceFromFile(std::string filename)
{
    // Superficies
    SDL_Surface* LoadedImage = NULL;
    SDL_Surface* OptimizedImage = NULL;

    // Cargar Imagen
    LoadedImage = IMG_Load( filename.c_str() );

    // Si la imagen es cargada
    if (LoadedImage != NULL)
    {
        // Crea una nueva imagen optimizada
        OptimizedImage = SDL_DisplayFormat(LoadedImage);

        // Liberar la superficie anterior
        SDL_FreeSurface(LoadedImage);
    }

    // retornar la nueva imagen optimizada
    return OptimizedImage;
}



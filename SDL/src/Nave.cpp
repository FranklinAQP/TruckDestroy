#include "Nave.h"

//Constructor del entorno misiles, nave y meteoritos
Nave::Nave(unsigned x, unsigned y)
{
    this->x = x;
	this->y = y;
	llevel=0;
	Restart();

	//dx = 10;
	//dy = 10;
	//dead = false;

	//this->escenario = nescenario;
	SDL_Surface *lnave = NULL;
    SDL_Surface *lmisil= NULL;
    SDL_Surface *lmeteorito= NULL;
    updatefiles();
    //meteoritos.resize(0);
}

//Reinicia valores predeterminados de la nave meteoritos y misiles
void Nave::Restart(){
    cout<<"restart/n";
    x=400;
    y=480;
    dx = 10;
	dy = 10;
	time = 0;
	confirmar=0;
	timeout = 6;
	llevel =0;
	dead = false;
	misiles.clear();
    misiles.resize(0);
    //cout<<"misiles = "<<misiles.size()<<endl;


    meteoritos.clear();
    meteoritos.resize(0);
    //cout<<"meteoritos= "<<meteoritos.size()<<endl;
    SDL_Surface *lnave = NULL;
    SDL_Surface *lmisil= NULL;
    SDL_Surface *lmeteorito= NULL;
    updatefiles();
}
Nave::~Nave()
{
    //dtor
}

//Carga imagenes a usarse de nave, meteoritos y misiles
bool Nave::updatefiles(){
    lnave = LoadSurfaceFromFile("nave.png");
    lmisil = LoadSurfaceFromFile("misil.png");
    lmeteorito = LoadSurfaceFromFile("meteorito.png");
    return true;
}

//Renderiza todo: nave misiles y meteoritos
bool Nave::Render_all(SDL_Surface* dest){
    if (dead) { return false; }

    Render_nave(dest);
    Render_meteoritos(dest);
    Render_misiles(dest);
    return true;

}

//Renderiza misiles
void Nave::Render_misiles(SDL_Surface* dest){
    for(register size_t i=0; i<misiles.size(); ++i){
        DrawSurface(misiles[i]->x, misiles[i]->y, lmisil, dest);
    }

}

//Renderiza nave
void Nave::Render_nave(SDL_Surface* dest){
    DrawSurface(x, y, lnave, dest);
}

//Renderiza meteoritos
void Nave::Render_meteoritos(SDL_Surface* dest){
    for(register size_t i=0; i<meteoritos.size(); ++i){
        if(meteoritos[i]->y > -30 && meteoritos[i]->y < 580){
            DrawSurface(meteoritos[i]->x, meteoritos[i]->y, lmeteorito, dest);
        }

    }
}

//Carga siguiente oleada dependiendo del nivel
void Nave::run_meteoritos(int& level){
    if (llevel!=level){
        llevel=level;
        meteoritos.clear();
        meteoritos.resize(0);
        for(int i=0; i<level; ++i){
            for(int j=40; j<920; j+=50){
                Meteorito *xmeteorito = new Meteorito(j,0 - i*50,level);
                meteoritos.push_back(xmeteorito);
            }
        }
    }

}

//Controles de la nave
void Nave::UpdateInputControls()
{
    unsigned char* keys = SDL_GetKeyState(NULL);

    if (keys[SDLK_UP])
    {
        if(y>20)
            this->y -= dy;
    }
    else if (keys[SDLK_DOWN])
    {
        if(y<500)
            this->y += dy;
    }
    else if (keys[SDLK_LEFT])
    {
        if(x>20)
            this->x -= dx;
    }
    else if (keys[SDLK_RIGHT])
    {
        if(x<890)
            this->x += dx;
    }
    else if (keys[SDLK_RETURN])
    {
        Misil *xmisil = new Misil(x+30,y-10,10);
        misiles.push_back(xmisil);
    }



}

//Retorna si hubo colision de la nave con un meteorito
bool Nave::nave_colision(){
    for(register size_t i=0; i<meteoritos.size(); ++i){
        if( (meteoritos[i]->x)+40 > (this->x) && (meteoritos[i]->x) < ((this->x)+60) && (meteoritos[i]->y) + 45 > (this->y) ){//&& (meteoritos[i]->y) + 40 > (this->y)
            //meteoritos.erase(meteoritos.begin()+i);
            if(meteoritos.size()>0){
            cout<<"meteoritos = "<<meteoritos.size()<<endl;
            cout<<"i = "<< i << endl;
            cout<< "x = " << meteoritos[i]->x<<" - "<<meteoritos[i]->x+40<<" xnave = "<<this->x<<" - "<<this->x+60<<endl;
            dead = true;
            return true;
            }
            dead=true;
            return true;
        }
    }
    return false;
}

//Retorna si hubo colision de misil y meteorito
//Si hubo elimina meteorito y misil del vector de punteros
int Nave::misil_colision(){
    int ptos=0;
    int colisiones[100];
    int choques[100];
    int n=0;
    for(register size_t i=0; i<meteoritos.size(); ++i){
        for(register size_t j=0; j<misiles.size(); ++j){
            if(misiles[j]->x > (meteoritos[i])->x && (misiles[j]->x) < (meteoritos[i]->x) + 40 && (misiles[j]->y) < (meteoritos[i]->y)+40){
                colisiones[n]=j;
                choques[n]=i;
                ++n;
                break;
            }
        }
    }
    for(int v=n-1; v>=0;--v){
        misiles.erase(misiles.begin()+colisiones[v]);
        meteoritos.erase(meteoritos.begin()+choques[v]);
    }
    return n;
}

//Carga siguiente fotograma de nave
void Nave::Update()
{
    if (dead) { return; }
    UpdateInputControls();
    time++;
    if (time < timeout)
    {
        return;
    }

    bool cr = misil_colision();
    for(register size_t i=0; i<misiles.size(); ++i){
        if(misiles[i]->y>0)
            misiles[i]->avanzar();
        else
            misiles.erase(misiles.begin()+i);
    }

    for(register size_t j=0; j<meteoritos.size(); ++j){
        meteoritos[j]->avanzar();
    }
    if(meteoritos.size()>0){
        if(nave_colision()){
            ++confirmar;
            if(confirmar >15){
            dead=true; confirmar=0;
            }
        }
    }
    time = 0;
}

//Carga imagenes a pantalla de main
void Nave::DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
    // Crea una superfice rectangular
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    // Blit
    SDL_BlitSurface(source, NULL, destination, &offset);
}

//Lee y carga archivo imagen
SDL_Surface *Nave::LoadSurfaceFromFile(std::string filename)
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

//Libera espacio
void Nave::UnloadFiles()
{
    // Liberar memoria de las superficies
    SDL_FreeSurface(lmisil);
    SDL_FreeSurface(lnave);
    SDL_FreeSurface(lmeteorito);

    //puntos y tiempo
    /*
    SDL_FreeSurface(puntos);
    SDL_FreeSurface(tiempo);
    SDL_FreeSurface(n0);
    SDL_FreeSurface(n1);
    SDL_FreeSurface(n2);
    SDL_FreeSurface(n3);
    SDL_FreeSurface(n4);
    SDL_FreeSurface(n5);
    SDL_FreeSurface(n6);
    SDL_FreeSurface(n7);
    SDL_FreeSurface(n8);
    SDL_FreeSurface(n9);
    */


    // Liberar musica
    //Mix_FreeMusic(TetrisMusic);

}


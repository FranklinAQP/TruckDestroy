#ifndef NAVE_H
#define NAVE_H
#include "Meteorito.h"
#include "Misil.h"
#include "SDL.h"
#include "Configuration.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

using namespace std;

class Nave
{
    public:
        int x;
        int y;
        int dx;
        int dy;
        unsigned time, timeout;
        int llevel;
        int confirmar;
        vector<Misil*> misiles;
        vector<Meteorito*> meteoritos;
        //SDL_Surface* escenario;
        SDL_Surface *lnave;
        SDL_Surface *lmisil;
        SDL_Surface *lmeteorito;

        bool dead;

        Nave(unsigned x, unsigned y);
        bool updatefiles();
        void DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
        SDL_Surface *LoadSurfaceFromFile(std::string filename);
        bool Render_all(SDL_Surface* dest);
        void Restart();
        void Update();

        void Render_misiles(SDL_Surface* dest);
        void Render_nave(SDL_Surface* dest);
        void Render_meteoritos(SDL_Surface* dest);
        void run_meteoritos(int &level);

        bool nave_colision();
        int misil_colision();
        void UpdateInputControls();
        void UnloadFiles();
        virtual ~Nave();

    protected:
    private:
};

#endif // NAVE_H

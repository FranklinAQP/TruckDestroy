#ifndef MISIL_H
#define MISIL_H


class Misil
{
    public:
        int x;
        int y;
        int vy;

        Misil(int x, int y, int vy);
        virtual ~Misil();
        void avanzar();
    protected:
    private:
};

#endif // MISIL_H

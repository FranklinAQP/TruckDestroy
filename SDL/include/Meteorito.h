#ifndef METEORITO_H
#define METEORITO_H


class Meteorito
{
    public:
        int x;
        int y;
        unsigned vida;
        int vx;
        int vy;

        Meteorito(int x, int y, int level);
        virtual ~Meteorito();
        void avanzar();
    protected:
    private:
};

#endif // METEORITO_H


class SnakeSegment
{
public:
	unsigned x;
	unsigned y;

	SnakeSegment(unsigned x, unsigned y);
};

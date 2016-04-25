#ifndef HEX_H
#define HEX_H

#define HEX_SIDE 20
#define SQRT_3 1.732
#define HEX_SIZE HEX_SIDE*SQRT_3/2

//#include <vector>

struct pix
{
    int x;
    int y;
};

struct cube
{
    int x;
    int y;
    int z;
    bool operator < (const cube &h) const
    {
        return (x < h.x) || (x == h.x && y < h.y);
    }
    cube operator + (const cube &h) const
    {
        return cube{x+h.x,y+h.y,z+h.z};
    }
    bool operator == (const cube &h) const
    {
        return (x == h.x && y == h.y);
    }
    bool operator != (const cube &h) const
    {
        return (x != h.x || y != h.y);
    }
    void operator ~ ()
    {
        z = -x-y;
        return;
    }
};

struct axial
{
    int q;
    int r;
};

pix cube2pix(cube h);
cube pix2cube(pix p);
cube cube_subtract(cube A, cube B);
cube cube_add(cube A, cube B);
cube cube_rotate(cube A, cube origin, bool dir);
int distance(cube A, cube B);
int distance(cube A);
int Hexant(cube A);
bool LineofSight(cube A, cube h, cube B);

const cube dir1 = {0,1,-1};
const cube dir2 = {-1,1,0};
const cube dir3 = {-1,0,1};
const cube dir4 = {0,-1,1};
const cube dir5 = {1,-1,0};
const cube dir6 = {1,0,-1};
const cube global_origin = {0,0,0};

const cube hex_dir[15] = {global_origin,dir1,dir2,dir3,dir4,dir5,dir6,dir1,global_origin,dir4,dir5,dir6,dir1,dir2,dir3};

class Hex
{
public:
    Hex(int q, int r);
    Hex(cube h);
    Hex();
    void set_cube(cube h);
    //bool LineofSight(cube h, cube B);
    int X();
    int Y();
    int Z();
    pix loc();
    cube H;

private:

};

#endif // HEX_H

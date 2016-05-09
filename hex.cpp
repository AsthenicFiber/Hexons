#include <cmath>

#include "hex.h"

Hex::Hex(int q, int r)
{
    //H = cube(q,-q-r,r);
    H.x = q;
    H.y = -q-r;
    H.z = r;
}

Hex::Hex(cube h)
{
    H = h;
}

Hex::Hex()
{
    //H = cube(0,0);
    H.x = 0;
    H.y = 0;
    H.z = 0;
}

void Hex::set_cube(cube h)
{
    H = h;
}

int Hex::X()
{
    return H.x;
}

int Hex::Y()
{
    return H.y;
}

int Hex::Z()
{
    return H.z;
}

pix Hex::loc()
{
    return cube2pix(H);
}

pix cube2pix(cube h)
{
    pix a;
    a.x = (int)(3*HEX_SIDE*h.x/2);
    a.y = (int)(HEX_SIZE*(h.y - h.z));
    return a;
}

cube pix2cube(pix p)
{
    cube h;
    double x,y,z;
    double xer,yer,zer;
    int rx,ry,rz;
    x = 1.0/HEX_SIDE*2.0/3.0*p.x;
    y = 1.0/HEX_SIDE*(-p.x/3.0 + p.y/SQRT_3);
    z = -x-y;

    rx = (int)floor(x+.5);
    ry = (int)floor(y+.5);
    rz = (int)floor(z+.5);

    xer = std::abs(x-rx);
    yer = std::abs(y-ry);
    zer = std::abs(z-rz);

    if (xer > yer)
    {
        if (xer > zer)
        {
            rx = -ry-rz;
        }
        else
        {
            rz = -rx-ry;
        }
    }
    else if (zer > yer)
    {
        rz = -rx-ry;
    }
    else
    {
        ry = -rx-rz;
    }
    h.x = rx;
    h.y = ry;
    h.z = rz;

    return h;
}

bool LineofSight(cube A, cube h, cube B)
{
    int dx = h.x - A.x;
    int dy = h.z - A.z;
    int Bx = B.x - A.x;
    int By = B.z - A.z;

    if (dx < 0)
    {
        dx = -dx;
        Bx = -Bx;
    }
    if (dy < 0)
    {
        dy = -dy;
        By = -By;
    }
    if (dy > dx)
    {
        int temp = dy;
        dy = dx;
        dx = temp;
        temp = Bx;
        Bx = By;
        By = temp;
    }
    if (dx == 0)
    {
        return true;
    }

    int y = 0;
    double m = dy/(double)dx;

    for (int i = 1; i < dx; i++)
    {
        double Yi = i*m;
        if (Yi-y > 0.5)
        {
            y++;
        }
        if ((i == Bx) && (y == By))
        {
            return false;
        }
    }
    return true;
}

cube cube_subtract(cube A, cube B)
{
    cube C;
    C.x = A.x - B.x;
    C.y = A.y - B.y;
    C.z = A.z - B.z;
    return C;
}

cube cube_add(cube A, cube B)
{
    cube C;
    C.x = A.x + B.x;
    C.y = A.y + B.y;
    C.z = A.z + B.z;
    return C;
}

int distance(cube A, cube B)
{
    A = cube_subtract(A,B);
    A.x = std::abs(A.x);
    A.y = std::abs(A.y);
    A.z = std::abs(A.z);

    if (A.x > A.y)
    {
        if (A.x > A.z)
        {
            return A.x;
        }
        else
        {
            return A.z;
        }
    }
    else if (A.y > A.z)
    {
        return A.y;
    }
    else
    {
        return A.z;
    }
}

int distance(cube A)
{
    //cube B = {0,0,0};
    return distance(A, global_origin);
}

int Hexant(cube A)
{
    int d = distance(A);
    cube B = {0,0,0};

    if (d == 0)
    {
        return 0;
    }

    if (d == A.x)
    {
        B.x = 1;
    }
    if (d == A.y)
    {
        B.y = 1;
    }
    if (d == A.z)
    {
        B.z = 1;
    }
    if (d == -A.x)
    {
        B.x = -1;
    }
    if (d == -A.y)
    {
        B.y = -1;
    }
    if (d == -A.z)
    {
        B.z = -1;
    }

    if (B.x == 1)
    {
        if ((B.y == 0) && (B.z == 0))
        {
            return 1;
        }
        else if (B.z == -1)
        {
            return -1;
        }
        else if (B.y == -1)
        {
            return -6;
        }
        else
        {
            return 1;
        }
    }
    else if (B.z == -1)
    {
        if (B.y == 0)
        {
            return 2;
        }
        else
        {
            return -2;
        }
    }
    else if (B.y == 1)
    {
        if (B.x == 0)
        {
            return 3;
        }
        else
        {
            return -3;
        }
    }
    else if (B.x == -1)
    {
        if (B.z == 0)
        {
            return 4;
        }
        else
        {
            return -4;
        }
    }
    else if (B.z == 1)
    {
        if (B.y == 0)
        {
            return 5;
        }
        else
        {
            return -5;
        }
    }
    else if (B.y == -1)
    {
        return 6;
    }
    else
    {
        return 0;
    }
}

cube cube_rotate(cube A, cube origin, bool dir)
{
    A = cube_subtract(A,origin);
    int h = Hexant(A);

    if (dir)
    {
        if (h < 0)
        {
            h = -h + 1;
        }
    }
    else
    {
        if (h < 0)
        {
            h = -h;
        }
        h += 8;
    }

    cube delta = hex_dir[h];

    A = cube_add(A,delta);
    return cube_add(A,origin);
}

cube neighbor(cube A, int h)
{
    h = std::abs(h);
    return cube_add(A,hex_dir[h]);
}

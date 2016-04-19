#ifndef MAP_H
#define MAP_H

#include "hexon.h"
#include "obstacle.h"
#include <map>
#include <vector>


struct tree_node
{
    cube h;
    std::vector <cube> branches;
    int in;
};

int find_cube(std::vector <cube> A, cube h);

class Map
{
public:
    Map();
    void map_update();
    void AddHexItem(HexItem *A);
    void RemoveHexItem(HexItem *A);
    HexItem * GetHexItem(cube h);
    HexItem * &operator [](const cube &h)
    {
        return grid[h];
    }

private:
    void generate_pcvt();
    void print_pcvt();
    std::map <cube,HexItem*> grid;
    std::map <cube,tree_node> pcvt;
    std::vector <cube> los(cube h);

};

#endif // MAP_H

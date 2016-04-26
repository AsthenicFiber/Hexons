#include "map.h"
#include <iostream>
#include <fstream>

Map::Map()
{
    //HexMap.push_back(new Hexon(3,-4));
    //xi.push_back(index{0,0});

    visibility = 4;
    generate_pcvt();
    print_pcvt();

    // http://www.cplusplus.com/forum/beginner/68340/
    // help intializing and adding elements to vector of vectors

}

void Map::map_update()
{
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        const cube h = it->first;

        if (grid[h]->has_vis())
        {
            grid[h]->set_vis(find_vis(h));
        }

        grid[h]->advance(1);

        cube H = grid[h]->get_pos();
        if (h != H)
        {
            AddHexItem(grid[h]);
            //grid[H] = grid[h];
            it = --grid.erase(it);
        }
        //it->second->advance(1);
    }
    // Update positions of hexitems in map
    /*
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        cube h = it->first;

        cube H = grid[h]->get_pos();
        if (h != H)
        {
            grid[H] = grid[h];
            grid.erase(h);
        }
    }
    */
}

void Map::AddHexItem(HexItem *A)
{
    cube h = A->get_pos();
    grid[h] = A;

    return;
}

void Map::RemoveHexItem(HexItem *A)
{

    cube h = A->get_pos();
    grid.erase(h);
    return;
}

HexItem * Map::GetHexItem(cube h)
{
    return grid[h];
}

void Map::generate_pcvt()
{
    // A = 3*(r-1)*r+1 = 3*r^2 - 3*r + 1
    cube h = global_origin;
    int ind = 0;

    std::vector <cube> cube_vector;
    tree_node node;
    node.h = h;
    node.branches = cube_vector;
    node.in = ind++;
    pcvt[h] = node;

    for (int i=1; i<visibility; i++)
    {
        h = cube_add(h,cube{1,-1,0});
        for (int j=0; j<6*i; j++)
        {
            //std::vector <cube> cube_vector;
            //tree_node node;
            node.h = h;
            node.in = ind++;
            //node.branches = cube_vector;
            pcvt[h] = node;
            //std::cout << "\n" << h.x << "\t" << h.y << "\t" << h.z;

            std::vector <cube> path = los(h);
            for (unsigned int k = 0; k < path.size()-1; k++)
            {
                int in = find_cube(pcvt[path[k]].branches, path[k+1]);
                if ((in == -1) && (distance(path[k+1]) != distance(path[k])))
                {
                    pcvt[path[k]].branches.push_back(path[k+1]);
                }
            }

            h = cube_rotate(h, global_origin, true);
        }
    }
    std::cout << "\n" << pcvt.size() << "\t" << ind << "\n";
    return;
}

void Map::print_pcvt()
{
    std::ofstream ofs;
    ofs.open("pcvt.txt", std::ofstream::out);
    if (!ofs.is_open())
    {
        std::cout << "\nCould not open file.\n";
        return;
    }
    for (std::map <cube,tree_node>::iterator it = pcvt.begin(); it != pcvt.end(); ++it)
    {
        cube h = it->first;
        ofs << "\n" << pcvt[h].in << "\n" << h.x << "\t" << h.y << "\t" << h.z;
        for (unsigned int i = 0; i < pcvt[h].branches.size(); i++)
        {
            cube H = pcvt[h].branches[i];
            ofs << "\n--\t" << H.x << "\t" << H.y << "\t" << H.z;
        }
    }
    std::cout << "\n";
    ofs.close();
}

Matrix Map::find_vis(cube h)
{
    //Matrix vision(2*(3*(visibility-1)*visibility+1),1);
    Matrix vision(2*(int)pcvt.size(),1);
    vision *= 0;
    vis_tree(h, global_origin, vision);
    return vision;
}

Matrix Map::vis_tree(cube h, cube H, Matrix vision)
{
    for (unsigned int i = 0; i < pcvt[H].branches.size(); i++)
    {
        if (grid.count(pcvt[H].branches[i] + h) == 1)
        {
            hsv color = grid[pcvt[H].branches[i] + h]->get_color();
            vision[pcvt[pcvt[H].branches[i]].in][1] = color.hue/359;
            vision[pcvt[pcvt[H].branches[i]].in + 1][1] = color.val/255;
        }
        else
        {
            vision = vis_tree(h, pcvt[H].branches[i], vision);
        }
    }
    return vision;
}

int find_cube(std::vector<cube> A, cube h)
{
    for (unsigned int i = 0; i < A.size(); i++)
    {
        if (A[i] == h)
        {
            return i;
        }
    }
    return -1;
}

std::vector <cube> Map::los(cube h)
{
    std::vector <cube> path;
    path.push_back(global_origin);

    bool f_inv_x = false;
    bool f_inv_y = false;
    bool f_x_y = false;

    pix a = cube2pix(h);

    if (a.x < 0)
    {
        a.x = -a.x;
        f_inv_x = true;
    }
    if (a.y < 0)
    {
        a.y = -a.y;
        f_inv_y = true;
    }
    if (a.y > a.x)
    {
        int temp = a.y;
        a.y = a.x;
        a.x = temp;
        f_x_y = true;
    }

    int y = 0;
    double m = a.y/(double)a.x;

    for (int x = 1; x < a.x; x++)
    {
        double Yi = x*m;
        if (Yi-y > 0.5)
        {
            y++;
        }

        pix B;
        if (f_x_y)
        {
            B.x = y;
            B.y = x;
        }
        else
        {
            B.x = x;
            B.y = y;
        }
        if (f_inv_y)
        {
            B.y = -B.y;
        }
        if (f_inv_x)
        {
            B.x = -B.x;
        }

        cube H = pix2cube(B);
        if (H == path[path.size()-1])
        //if (distance(H) == distance(path[path.size()-1]))
        {

        }
        else
        {
            path.push_back(H);
        }
    }
    return path;
}

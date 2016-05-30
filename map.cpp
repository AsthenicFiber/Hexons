#include "map.h"
#include <iostream>
#include <fstream>
#include <QGraphicsScene>

Map::Map()
{
    //HexMap.push_back(new Hexon(3,-4));
    //xi.push_back(index{0,0});

    //visibility = 6;
    generate_pcvt();
    print_pcvt();

    // http://www.cplusplus.com/forum/beginner/68340/
    // help intializing and adding elements to vector of vectors

}

Map::~Map()
{
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        delete it->second;
    }
}

void Map::map_update()
{
    std::cout << grid.size() << "\t";
    std::vector <cube> move_list;
    std::vector <cube> erase_list;
    std::vector <HexItem*> child_list;
    //QGraphicsScene* grid_scene = grid[grid.begin()->first]->scene;
    QGraphicsScene * grid_scene = grid.begin()->second->scene();
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        const cube h = it->first;

        if (grid[h]->has_vis())
        {
            grid[h]->set_vis(find_vis(h));
        }

        cube dh = grid[h]->tstep();
        if (dh != global_origin)
        {
            if (grid.count(h+dh))
            {
                int status = grid[h]->interact(grid[h+dh]);

                switch(status)
                {
                case 1:
                    // log for updating position
                    move_list.push_back(h);
                    // remove obstacle
                    erase_list.push_back(h+dh);
                    break;
                case 2:
                    // log for erasure
                    erase_list.push_back(h);
                    break;
                case 3:
                    erase_list.push_back(h+dh);
                    break;
                case 4:
                    // breed
                    cube H1 = cube_rotate(h+dh,h,true);
                    cube H2 = cube_rotate(h+dh,h,false);
                    if (!grid.count(H1))
                    {
                        child_list.push_back(breed_hexon(grid[h],grid[h+dh],H1));
                    }
                    else if (!grid.count(H2))
                    {
                        child_list.push_back(breed_hexon(grid[h],grid[h+dh],H2));
                    }

                    break;

                }
            }
            else
            {
                move_list.push_back(h);
            }
        }
    }
    // erase hex items
    for (unsigned int i = 0; i < erase_list.size(); i++)
    {
        RemoveHexItem(erase_list[i]);
        //grid.erase(erase_list[i]);
    }
    // create child hex items
    for (unsigned int i = 0; i < child_list.size(); i++)
    {
        AddHexItem(child_list[i], grid_scene);
    }
    // move hex items that move
    for (unsigned int i = 0; i < move_list.size(); i++)
    {
        MoveHexItem(move_list[i]);
    }
    // draw hex items
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        it->second->advance(1);
    }
    std::cout << move_list.size() << "\t";
    std::cout << erase_list.size() << "\t";
    std::cout << child_list.size() << "\t";
    std::cout << grid.size() << std::endl;
}

void Map::AddHexItem(HexItem *A, QGraphicsScene *scene)
{
    cube h = A->get_pos();
    grid[h] = A;
    scene->addItem(grid[h]);
    return;
}

void Map::MoveHexItem(cube h)
{
    cube H = grid[h]->update_pos();
    grid[H] = grid[h];
    grid[h] = NULL;
    grid.erase(h);
    return;
}

void Map::RemoveHexItem(HexItem *A)
{
    cube h = A->get_pos();
    RemoveHexItem(h);
    return;
}

void Map::RemoveHexItem(cube h)
{
    if (!grid.count(h))
    {
        return;
    }
    delete grid[h];
    grid.erase(h);
    return;
}

HexItem * Map::GetHexItem(cube h)
{
    return grid[h];
}

void Map::generate_pcvt()
{
    //extern int visibility;
    // A = 3*(r-1)*r+1 = 3*r^2 - 3*r + 1
    cube h = global_origin;
    int ind = 0;

    std::vector <cube> cube_vector;
    tree_node node;
    node.h = h;
    node.branches = cube_vector;
    node.in = ind++;
    pcvt[h] = node;

    for (int i=1; i<get_visibility(); i++)
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
    std::cout << "\n" << pcvt.size() << "\t" << ind << "\t" << (get_visibility()-1)*get_visibility()*3+1 << "\n";
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
    /*
    std::ofstream ofs;
    char fname[20];
    sprintf(fname,"vision_%d_%d_%d.txt",h.x,h.y,h.z);
    ofs.open(fname, std::ofstream::out);
    ofs << h.x << "\t" << h.y << "\t" << h.z << std::endl;
*/
    //extern int visibility;
    //Matrix vision(6*(3*(visibility-1)*visibility+1),1);
    Matrix vision(6*(int)pcvt.size() + 6,1); // N * vision size (+ stats?)
    //vision *= 0;
    for (int i = 1; i < vision.length(); i++)
    {
        vision[i][0] = 0;
    }
    //vis_tree(h, global_origin, vision, ofs);
    vis_tree(h, global_origin, vision);

    //ofs.close();
    return vision;
}

Matrix Map::vis_tree(cube h, cube H, Matrix vision)
{
    for (unsigned int i = 0; i < pcvt[H].branches.size(); i++)
    {
        if (grid.count(pcvt[H].branches[i] + h) == 1)
        {
            rgb color = grid[pcvt[H].branches[i] + h]->get_color();
            vision[pcvt[pcvt[H].branches[i]].in][1] = mel(color.red)/255;
            vision[pcvt[pcvt[H].branches[i]].in + 1][1] = mel(color.green)/255;
            vision[pcvt[pcvt[H].branches[i]].in + 2][1] = mel(color.blue)/255;

            color = grid[pcvt[H].branches[i] + h]->get_border();
            vision[pcvt[pcvt[H].branches[i]].in + 3][1] = mel(color.red)/255;
            vision[pcvt[pcvt[H].branches[i]].in + 4][1] = mel(color.green)/255;
            vision[pcvt[pcvt[H].branches[i]].in + 5][1] = mel(color.blue)/255;
        }
        else
        {
            vision = vis_tree(h, pcvt[H].branches[i], vision);
        }
    }
    return vision;
}

Matrix Map::vis_tree(cube h, cube H, Matrix vision, std::ofstream& ofs)
{
    for (unsigned int i = 0; i < pcvt[H].branches.size(); i++)
    {
        if (grid.count(pcvt[H].branches[i] + h) == 1)
        {
            rgb color = grid[pcvt[H].branches[i] + h]->get_color();
            vision[pcvt[pcvt[H].branches[i]].in][1] = color.red/359;
            vision[pcvt[pcvt[H].branches[i]].in + 1][1] = color.green/255;
            vision[pcvt[pcvt[H].branches[i]].in + 2][1] = color.blue/255;
            ofs << H.x  << "\t" << H.y << "\t" << H.z << "\t" << cube2pix(H).x << "\t" << cube2pix(H).y << "\t" << color.red << "\t" << color.green << "\t" << color.blue << std::endl;
        }
        else
        {
            vision = vis_tree(h, pcvt[H].branches[i], vision, ofs);
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

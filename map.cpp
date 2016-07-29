#include "map.h"
#include <iostream>
#include <fstream>
#include <QGraphicsScene>

// Map Constructor
Map::Map()
{
    generate_pcvt();
    print_pcvt();
}

// Map Destructor
// deletes elements in Map before destructing
Map::~Map()
{
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        delete it->second;
    }
}

// Map Update - performed every cycle
void Map::map_update()
{
    std::cout << grid.size() << "\t";

    // Creates list of items to be removed, moved, and added
    std::vector <cube> move_list;
    std::vector <cube> erase_list;
    std::vector <HexItem*> child_list;

    // Finds pointer to scene, to be used later
    QGraphicsScene * grid_scene = grid.begin()->second->scene();

    // Iterate over each element in Map
    for (std::map <cube,HexItem*>::iterator it = grid.begin(); it != grid.end(); ++it)
    {
        const cube h = it->first;

        // send vision data to items that have vision
        if (grid[h]->has_vis())
        {
            grid[h]->set_vis(find_vis(h));
        }

        // hex item performs action and retrieve movement decision
        cube dh = grid[h]->tstep();

        // if hex item is moving
        if (dh != global_origin)
        {
            // check if another hexitem present in intended moving location and interact
            if (grid.count(h+dh))
            {
                int status = grid[h]->interact(grid[h+dh]);

                // perform cleanup based on result of interaction
                switch(status)
                {
                case 1:
                    // log for updating position
                    move_list.push_back(h);
                    // log to erase other
                    erase_list.push_back(h+dh);
                    break;
                case 2:
                    // log for erasure
                    erase_list.push_back(h);
                    break;
                case 3:
                    // log other for erasure
                    erase_list.push_back(h+dh);
                    break;
                case 4:
                    // breed with other
                    // check for open hex between breeding hex items
                    cube H1 = cube_rotate(h+dh,h,true);
                    cube H2 = cube_rotate(h+dh,h,false);
                    if (!grid.count(H1))
                    {
                        if (breed_hexon_check(&grid[h]->stats,&grid[h+dh]->stats))
                        {
                            child_list.push_back(breed_hexon(grid[h],grid[h+dh],H1));
                        }
                    }
                    else if (!grid.count(H2))
                    {
                        if (breed_hexon_check(&grid[h]->stats,&grid[h+dh]->stats))
                        {
                            child_list.push_back(breed_hexon(grid[h],grid[h+dh],H2));
                        }
                    }

                    break;
                }
            }
            else if(grid[h]->h_type() == 'f')
            {
                // grow and add to child list to add to map
                int E = grow_food_check(&grid[h]->stats);
                if (E > 0)
                {
                    child_list.push_back(grow_food(h+dh,E));
                }
            }
            else
            {
                // log for updating position
                move_list.push_back(h);
            }
        }
    }
    // erase hex items
    for (unsigned int i = 0; i < erase_list.size(); i++)
    {
        RemoveHexItem(erase_list[i]);
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

    // debug display
    std::cout << move_list.size() << "\t";
    std::cout << erase_list.size() << "\t";
    std::cout << child_list.size() << "\t";
    std::cout << grid.size() << std::endl;
}

// Add hex item to the map and to the scene
bool Map::AddHexItem(HexItem *A, QGraphicsScene *scene)
{
    cube h = A->get_pos();
    if (grid.count(h))
    {
        return false;
    }
    grid[h] = A;
    scene->addItem(grid[h]);
    return true;
}

// move the hex item to a different key in the map
void Map::MoveHexItem(cube h)
{
    if (!grid.count(h))
    {
        return;
    }
    cube H = h + grid[h]->get_move();
    //cube H = grid[h]->update_pos();
    if (grid.count(H))
    {
        //grid[h]->set_pos(h);
        return;
    }
    H = grid[h]->update_pos();
    grid[H] = grid[h];
    grid[h] = NULL;
    grid.erase(h);
    return;
}

// remove a hex item from the map based on the stored position in the hex item
void Map::RemoveHexItem(HexItem *A)
{
    cube h = A->get_pos();
    RemoveHexItem(h);
    return;
}

// remove a hex item from the map based on the key
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

// returns a hex item from the map based on the key
HexItem * Map::GetHexItem(cube h)
{
    return grid[h];
}

// generate pcvt tree
void Map::generate_pcvt()
{
    // Number of visible hexes
    // A = 3*(r-1)*r+1 = 3*r^2 - 3*r + 1
    cube h = global_origin;
    int ind = 0;

    // set up first node in the tree - origin
    std::vector <cube> cube_vector;
    tree_node node;
    node.h = h;
    node.branches = cube_vector;
    node.in = ind++;
    pcvt[h] = node;

    // iterate over different shells of hexagons
    for (int i=1; i<get_visibility(); i++)
    {
        h = cube_add(h,cube{1,-1,0});
        // iterate over a shell of hexagons
        for (int j=0; j<6*i; j++)
        {
            // add element to pcvt
            node.h = h;
            node.in = ind++;
            pcvt[h] = node;

            // retrieve path for line of sight
            std::vector <cube> path = los(h);

            // add path to branches of pcvt elements
            for (unsigned int k = 0; k < path.size()-1; k++)
            {
                // is child already in branches of parent?
                int in = find_cube(pcvt[path[k]].branches, path[k+1]);
                // if not in branches and parent and child are not in same shell, add to branches
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

// print pcvt tree in text file
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
        // print parent
        ofs << "\n" << pcvt[h].in << "\n" << h.x << "\t" << h.y << "\t" << h.z;
        // print children
        for (unsigned int i = 0; i < pcvt[h].branches.size(); i++)
        {
            cube H = pcvt[h].branches[i];
            ofs << "\n--\t" << H.x << "\t" << H.y << "\t" << H.z;
        }
    }
    std::cout << std::endl;
    ofs.close();
}

// return vision matrix from hex position 'h'
Matrix Map::find_vis(cube h)
{
    /*
    // set up output stream
    std::ofstream ofs;
    char fname[20];
    sprintf(fname,"vision_%d_%d_%d.txt",h.x,h.y,h.z);
    ofs.open(fname, std::ofstream::out);
    ofs << h.x << "\t" << h.y << "\t" << h.z << std::endl;
*/
    //extern int visibility;
    //Matrix vision(6*(3*(visibility-1)*visibility+1),1);

    // create empty matrix for neural network inputs
    Matrix vision(6*(int)pcvt.size() + 6,1); // N * vision size (+ stats?)
    for (int i = 1; i < vision.length(); i++)
    {
        vision[i][0] = 0;
    }

    // start traveling down tree
    vis_tree(h, global_origin, vision);
    //vis_tree(h, global_origin, vision, ofs);

    //ofs.close();
    return vision;
}

// travel down pcvt branches
Matrix Map::vis_tree(cube h, cube H, Matrix vision)
{
    // iterate over each child
    for (unsigned int i = 0; i < pcvt[H].branches.size(); i++)
    {
        // if something exists at child location, write data in matrix, else move to grandchildren
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

// same as above, but with print to file
/*Matrix Map::vis_tree(cube h, cube H, Matrix vision, std::ofstream& ofs)
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
}*/

// return if cube is in a vector of cubes
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

// return line of sight path from origin to 'h'
std::vector <cube> Map::los(cube h)
{
    // crete vector, start with origin
    std::vector <cube> path;
    path.push_back(global_origin);

    // flags for inversions
    bool f_inv_x = false;
    bool f_inv_y = false;
    bool f_x_y = false;

    // convert to pixel coordinates
    pix a = cube2pix(h);

    // inversions
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

    // start at y=0 and find slope
    int y = 0;
    double m = a.y/(double)a.x;

    // iterate over x
    for (int x = 1; x < a.x; x++)
    {
        // if in next y coordinate, increment y
        double Yi = x*m;
        if (Yi-y > 0.5)
        {
            y++;
        }

        // undo inversions
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

        // if in new hexagon, add to path
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

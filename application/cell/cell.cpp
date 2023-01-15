#include "cell.h"
#include "../simulator/simulator.h"

void rwa2group22::Cell::init_cell_walls()
{
    for (int i = 0; i < 4; ++i)
        m_walls.at(i) = true;
}

bool rwa2group22::Cell::is_wall(int wall)
{
    return !m_walls.at(wall);
}

void rwa2group22::Cell::set_wall(int wall, bool is_wall)
{
    if (is_wall)
    {   
        m_walls.at(wall)=false;
        if (wall == 0)
            Simulator::setWall(m_x, m_y, 'n');
        else if (wall == 1)
            Simulator::setWall(m_x, m_y, 'e');
        else if (wall == 2)
            Simulator::setWall(m_x, m_y, 's');
        else if (wall == 3)
            Simulator::setWall(m_x, m_y, 'w');
    }
}
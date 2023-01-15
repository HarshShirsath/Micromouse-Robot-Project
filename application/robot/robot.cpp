#include "robot.h"
#include "../simulator/simulator.h"

void rwa2group22::Robot::turn_left()
{
    Simulator::turnLeft();
    int new_dir = static_cast<int>(m_direction) - 1;
    if (new_dir == -1)
    {
        new_dir = 3;
    }
    m_direction = static_cast<directions>(new_dir);
}

void rwa2group22::Robot::turn_right()
{
    Simulator::turnRight();
    m_direction = static_cast<directions>((static_cast<int>(m_direction) + 1) % 4);
}

void rwa2group22::Robot::move_forward(bool is_going_towards_goal)
{
    Simulator::moveForward();
    if (m_direction == north)
        m_position.second += 1;
    else if (m_direction == south)
        m_position.second -= 1;
    else if (m_direction == east)
        m_position.first += 1;
    else if (m_direction == west)
        m_position.first -= 1;

    if (is_going_towards_goal)
    {
        Simulator::setColor(m_position.first, m_position.second, 'c');
        m_path.push_back(m_position);
    }
    else
    {
        Simulator::setColor(m_position.first, m_position.second, 'y');
    }
}

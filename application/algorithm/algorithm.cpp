#include "algorithm.h"
#include <time.h>
#include <iostream>

rwa2group22::Algorithm::Algorithm()
{
    // Initialise robot object on heap
    m_robot = std::make_unique<Robot>();

    // set coordinates of each cell in a maze
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            m_maze.at(i).at(j).set_coordinates(i, j);
        }
    }
}

void rwa2group22::Algorithm::init_outer_walls()
{
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            if (i == 0)
                m_maze.at(i).at(j).set_wall(3, true);
            else if (i == 15)
                m_maze.at(i).at(j).set_wall(1, true);

            if (j == 0)
                m_maze.at(i).at(j).set_wall(2, true);
            else if (j == 15)
                m_maze.at(i).at(j).set_wall(0, true);
        }
    }
}

void rwa2group22::Algorithm::follow_wall_left()
{
    // Run the algorithm until the robot reaches goal
    // Check the boolean for the surrounding walls and turns accordingly
    // Priorities are given to the left turn
    // It also sets the wall detected while moving
    while (m_robot->get_position() != m_goal)
    {
        if (Simulator::wallLeft() == 0)
        {
            std::cerr << "--- turn left ---" << std::endl;
            m_robot->turn_left();
            m_robot->move_forward(true);
        }
        else if (Simulator::wallFront() == 0)
        {
            set_left_wall();
            std::cerr << "--- move forward ---" << std::endl;
            m_robot->move_forward(true);
        }
        else if (Simulator::wallRight() == 0)
        {
            set_left_wall();
            set_front_wall();
            std::cerr << "--- turn right ---" << std::endl;
            m_robot->turn_right();
            m_robot->move_forward(true);
        }
        else
        {
            set_left_wall();
            set_front_wall();
            set_right_wall();
            std::cerr << "--- turn left ---" << std::endl;
            m_robot->turn_left();
            std::cerr << "--- turn left ---" << std::endl;
            m_robot->turn_left();
            m_robot->move_forward(true);
        }
    }
}

void rwa2group22::Algorithm::follow_wall_right()
{
    // Check the boolean for the surrounding walls and turns accordingly
    // Priorities are given to the right turn
    // It also sets the wall detected while moving
    while (m_robot->get_position() != m_goal)
    {
        if (Simulator::wallRight() == 0)
        {
            std::cerr << "--- turn right ---" << std::endl;
            m_robot->turn_right();
            m_robot->move_forward(true);
        }
        else if (Simulator::wallFront() == 0)
        {
            set_right_wall();
            std::cerr << "--- move forward ---" << std::endl;
            m_robot->move_forward(true);
        }
        else if (Simulator::wallLeft() == 0)
        {
            set_right_wall();
            set_front_wall();
            std::cerr << "--- turn left ---" << std::endl;
            m_robot->turn_left();
            m_robot->move_forward(true);
        }
        else
        {
            set_right_wall();
            set_front_wall();
            set_left_wall();
            std::cerr << "--- turn right ---" << std::endl;
            m_robot->turn_right();
            std::cerr << "--- turn right ---" << std::endl;
            m_robot->turn_right();
            m_robot->move_forward(true);
        }
    }
}

void rwa2group22::Algorithm::generate_goal()
{
    // Creates seed for rand () function
    srand(time(0));
    //Generate two random numbers within ranges (0-15) and (0-3) respectively
    // Creates goal aligned to the outer walls using generated random numbers
    int coordinate = rand() % 16;
    int which_coordinate = rand() % 4;

    if (which_coordinate == 0)
        m_goal = std::pair(coordinate, 0);
    else if (which_coordinate == 1)
        m_goal = std::pair(coordinate, 15);
    else if (which_coordinate == 2)
        m_goal = std::pair(0, coordinate);
    else
        m_goal = std::pair(15, coordinate);

    // Set text & colour at goal position 
    Simulator::setText(m_goal.first, m_goal.second, "G");
    Simulator::setColor(m_goal.first, m_goal.second, 'R');
}

void rwa2group22::Algorithm::set_left_wall()
{
    int left_wall = (static_cast<int>(m_robot->get_direction())) - 1;
    if (left_wall == -1)
        left_wall = 3;

    m_maze.at(m_robot->get_position().first).at(m_robot->get_position().second).set_wall(left_wall, true);
}

void rwa2group22::Algorithm::set_right_wall()
{
    int right_wall = (static_cast<int>(m_robot->get_direction()) + 1) % 4;
    m_maze.at(m_robot->get_position().first).at(m_robot->get_position().second).set_wall(right_wall, true);
}

void rwa2group22::Algorithm::set_front_wall()
{
    int front_wall = static_cast<int>(m_robot->get_direction());
    m_maze.at(m_robot->get_position().first).at(m_robot->get_position().second).set_wall(front_wall, true);
}

void rwa2group22::Algorithm::run_left()
{
    init_outer_walls();
    generate_goal();
    follow_wall_left();
    Simulator::clearAllColor();
    Simulator::setColor(m_goal.first, m_goal.second, 'R');
    trace_back();
}

void rwa2group22::Algorithm::run_right()
{
    init_outer_walls();
    generate_goal();
    follow_wall_right();
    Simulator::clearAllColor();
    Simulator::setColor(m_goal.first, m_goal.second, 'R');
    trace_back();
}

void rwa2group22::Algorithm::trace_back()
{
    std::cerr << "--- Moving back towards home ---" << std::endl;
    
    // Gets count of path size 
    int count = m_robot->get_path().size();

    // Starts tracing from goal position towards home
    for (int i = count - 1; i > 0; --i)
    {
        // Checks whether i_th position of path is a repeated position.
        // To get lowest index of among repeated postions, we start checking
        // from home.
        for (int j = 0; j < i; ++j)
        {
            // If repeated position is detected, position index jumps from i to j
            // In between indexes are skipped
            // Then robot is moved to penultimate position
            if (m_robot->get_path().at(i) == m_robot->get_path().at(j))
            {
                i = j;
                move_to_previous_position(i);
            }
            // If no repeated position is detected, robot is moved to penultimate position
            else if (j == i - 1)
            {
                move_to_previous_position(i);
            }
        }
    }
}

int rwa2group22::Algorithm::find_direction(const std::pair<int, int> &pos1, const std::pair<int, int> &pos2)
{
    int result;
    int delta_x = pos2.first - pos1.first;
    int delta_y = pos2.second - pos1.second;
    if (delta_x > 0)
        result = rwa2group22::directions::east;
    else if (delta_x < 0)
        result = rwa2group22::directions::west;
    else if (delta_y > 0)
        result = rwa2group22::directions::north;
    else if (delta_y < 0)
        result = rwa2group22::directions::south;
    return result;
}


void rwa2group22::Algorithm::move_to_previous_position(const int &position_index)
{
    int dir = find_direction(m_robot->get_path().at(position_index), m_robot->get_path().at(position_index - 1));

    int current_dir = m_robot->get_direction();

    // Based on current direction number of rotations to move to
    // required direction are determined
    int num_rotations = dir - current_dir;
    
    // Number of rotations are optimized
    if (num_rotations * num_rotations > 5)
        num_rotations = (num_rotations % 2) * (-1);

    if (num_rotations > 0)
    {
        for (int k = 0; k < num_rotations; k++)
        {
            m_robot->turn_right();
        }
    }
    else if (num_rotations < 0)
    {
        for (int k = 0; k < 0 - num_rotations; k++)
        {
            m_robot->turn_left();
        }
    }
    m_robot->move_forward(false);
}

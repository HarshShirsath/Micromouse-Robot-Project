#pragma once
#include <utility>
#include <memory>
#include <array>
#include <string>
#include "../robot/robot.h"
#include "../cell/cell.h"
#include "../simulator/simulator.h"
/**
 * @brief This is namespace rwa2group22
 *
 */
namespace rwa2group22
{
    /**
     * @brief This class implements the search algorithm.
     */
    class Algorithm
    {

    public:
        Algorithm();

    public:
        /**
         * @brief initialize outer walls, generate goal, execute
         * search algorithm for left hand rule and traces back to home position.
         *
         */
        void run_left();

        /**
         * @brief initialize outer walls, generate goal, execute
         * search algorithm for right hand rule and traces back to home position.
         *
         */
        void run_right();

        /**
         * @brief color outer walls
         *
         */
        void init_outer_walls();

        /**
         * @brief algorithm for left-hand rule approach
         *
         */
        void follow_wall_left();

        /**
         * @brief algorithm for right-hand rule approach
         *
         * @return * void
         */
        void follow_wall_right();

        /**
         * @brief generate random goal adjacent to an outer wall
         *
         */
        void generate_goal();

        /**
         * @brief set right wall in m_maze and in simulator
         *
         */
        void set_right_wall();

        /**
         * @brief set left wall in m_maze and in simulator
         *
         */
        void set_left_wall();

        /**
         * @brief set front wall in m_maze and in simulator
         *
         */
        void set_front_wall();

        /**
         * @brief This function traces the optimised path back to home
         *
         */
        void trace_back();

        /**
         * @brief This function helps find the direction of
         * motion from position1 to position2
         *
         * @param pos1 std::pair<int, int> coordinates of position1
         * @param pos2 std::pair<int, int> coordinates of position2
         * @return int Integer representing direction
         *
         */
        int find_direction(const std::pair<int, int> &pos1, const std::pair<int, int> &pos2);

        /**
         * @brief This represents the function to move the robot to previous position.
         *
         * @param position_index
         */
        void move_to_previous_position(const int &position_index);

    private:
        //!<@brief A maze is a 2D array of cells.
        std::array<std::array<Cell, 16>, 16> m_maze;
        std::unique_ptr<Robot> m_robot;
        std::pair<int, int> m_goal;

    }; // class Algorithm
} // namespace rwa2group22
#pragma once
#include <utility>
#include <vector>

/**
 * @brief This is namespace rwa2group22
 */
namespace rwa2group22
{
    /**
     * @brief This is enum for directions
     */
    enum directions
    {
        north = 0,
        east = 1,
        south = 2,
        west = 3
    };

    /**
     * @brief This is the class for robot.
     * It initialises the robot position at [0,0] facing North.
     * It has methods for turning and moving the robot.
     * It also has getter methods for robot's position, direction and path.
     */
    class Robot
    {
    public:
        Robot() : m_position(0, 0), m_direction(north)
        {
            m_path.push_back(m_position);
        }

        /**
         * @brief This method turns the robot left and updates robot direction.
         *
         */
        void turn_left();

        /**
         * @brief This method turns the robot right and updates robot direction.
         *
         */
        void turn_right();

        /**
         * @brief This method moves robot forward and updates robot position.
         * If the robot is moving towards the goal,
         * it colors the path cells cyan color and adds cell to robot path.
         * If not then it colors path yellow.
         * @param is_going_towards_goal Boolean for whether the robot
         * is moving towards the goal
         */
        void move_forward(bool is_going_towards_goal);

        /**
         * @brief Get the position of the robot
         *
         * @return const std::pair<int, int>&
         */
        const std::pair<int, int> &get_position()
        {
            return m_position;
        }

        /**
         * @brief Get the direction of the robot
         *
         * @return const directions&
         */
        const directions &get_direction()
        {
            return m_direction;
        }

        /**
         * @brief Get the path of the robot
         *
         * @return const std::vector<std::pair<int, int>>&
         */
        const std::vector<std::pair<int, int>> &get_path()
        {
            return m_path;
        }

    private:
        std::pair<int, int> m_position;
        directions m_direction;
        std::vector<std::pair<int, int>> m_path;

    }; // class Robot
} // namespace rwa2group22
#pragma once
#include <array>

namespace rwa2group22
{
    /**
     * @brief This class represents a cell in the maze.
     */
    class Cell
    {
    public:
        Cell() {}
        Cell(int x, int y) : m_x(x), m_y(y) {}
        /**
         * @brief initialize all 4 walls of a cell
         *
         */
        void init_cell_walls();

        /**
         * @brief set one of the walls based on is_wall
         * 
         * @param wall Integer representing the wall
         * @param is_wall Boolean to depict that the wall is close or open
         */
        void set_wall(int wall, bool is_wall);

        /**
         * @brief return true if wall is closed
         * 
         * @param wall Integer representing the wall
         * @return true If wall is closed
         * @return false If wall is open
         */
        bool is_wall(int wall);

        /**
         * @brief Set the coordinates of the cell
         * 
         * @param x x coordinate
         * @param y y coordinate
         */
        void set_coordinates(const int &x, const int &y)
        {
            m_x = x;
            m_y = y;
        }

    private:
        //!<@brief The walls of the cell.
        //!< true means the wall is open
        //!< false means the wall is closed
        //!< 0 = North, 1 = East, 2 = South, 3 = West
        std::array<bool, 4> m_walls;

        // X and Y coordinate of the cell
        int m_x; 
        int m_y;
    }; // class Cell
} // namespace rwa2group22
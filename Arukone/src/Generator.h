#pragma once
#include <memory>
#include <array>

class Grid{
public:
    Grid(uint32_t fieldSize, uint32_t pairCount);
    ~Grid();

    inline uint8_t GetValue(uint32_t x, uint32_t y) const {
        if(m_grid)
            return m_grid[CoordsToIndex(x,y)] != 0;
        return 0;
    }
    

    inline uint8_t HasValue(uint32_t x, uint32_t y) const {
        if(m_grid)
            return m_grid[CoordsToIndex(x,y)] != 0;
        return false;
    } 

private:
	inline constexpr uint32_t CoordsToIndex(uint32_t x, uint32_t y) const {
        return x * m_fieldSize + y;
	}

    uint8_t* m_grid;

    uint32_t m_fieldSize;
    uint32_t m_pairCount;
};
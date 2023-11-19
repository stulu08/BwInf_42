#pragma once
#include "Core.h"
#include "Vector.h"

#include <string>
#include <vector>

class Grid {
public:
    Grid(uvec2 fieldSize);
    ~Grid(){}

    void ExportToConsole() const;
    std::string ExportToText() const;
    void ExportToFile(const std::string& fName) const;

    void Erase(uint32_t value);
    void Clear();
    
    // returns true if a number is assigned to that field
    bool HasValue(uint32_t x, uint32_t y) const;
    uint32_t GetValueSafe(uint32_t x, uint32_t y) const;
    inline uint32_t GetValue(uint32_t x, uint32_t y) const { return m_grid[x][y]; }
    inline void SetValue(uint32_t x, uint32_t y, uint32_t value) { m_grid[x][y] = value; }
    
    inline uint32_t SetNumPairs(uint32_t value) { return m_numPairs = value; }
    inline uint32_t GetNumPairs() const { return m_numPairs; }

    inline uvec2 GetSize() const { return m_fieldSize; }
private:
	inline uint32_t CoordsToIndex(uint32_t x, uint32_t y) const {
        return x * m_fieldSize.x + y;
	}
    inline bool InRange(uint32_t x, uint32_t y) const {
        return x >= 0 && x < m_fieldSize.x && y >= 0 && y < m_fieldSize.y;
    }
   
    std::vector<std::vector<uint32_t>> m_grid;
    uvec2 m_fieldSize;
    uint32_t m_numPairs;
};
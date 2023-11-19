#include "Grid.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <Windows.h>

Grid::Grid(uvec2 fieldSize)
	: m_fieldSize(fieldSize) {
    m_grid.reserve(m_fieldSize.x);
    for (uint32_t x = 0; x < m_fieldSize.x; x++) {
        m_grid.push_back(std::vector<uint32_t>());
        m_grid.reserve(m_fieldSize.y);
    }
    Clear();
}

uint32_t Grid::GetValueSafe(uint32_t x, uint32_t y) const {
    if (InRange(x, y))
        return m_grid[x][y];
    else
        return 0;
}
bool Grid::HasValue(uint32_t x, uint32_t y) const {
    if (InRange(x, y))
        return m_grid[x][y] != 0;
    return false;
}

void Grid::Erase(uint32_t value) {
    for (uint32_t x = 0; x < m_fieldSize.x; x++) {
        for (uint32_t y = 0; y < m_fieldSize.y; y++) {
            if (GetValue(x, y) == value)
                SetValue(x, y, 0);
        }
    }
}

void Grid::Clear() {
    for (uint32_t x = 0; x < m_fieldSize.x; x++) {
        for (uint32_t y = 0; y < m_fieldSize.y; y++) {
            m_grid[x].push_back(0);
        }
    }
}

void Grid::ExportToConsole() const {
    std::cout << m_fieldSize.x << "\n" << m_numPairs << "\n";
    for (uint32_t x = 0; x < m_fieldSize.x; x++) {
        for (uint32_t y = 0; y < m_fieldSize.y; y++) {
            uint32_t value = GetValue(x, y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value == 0 ? 15 : value);

            if (value < 10)
                std::cout << '0' << value << ' ';
            else
                std::cout << value << ' ';
        }
        std::cout << '\n';
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

std::string Grid::ExportToText() const {
    std::stringstream stream;
    stream << m_fieldSize.x << "\n" << m_numPairs << "\n";
    for (uint32_t x = 0; x < m_fieldSize.x; x++) {
        for (uint32_t y = 0; y < m_fieldSize.y; y++) {
            uint32_t value = GetValue(x, y);
            if(value < 10)
                stream << '0' << std::to_string(value) << ' ';
            else
                stream << std::to_string(value) << ' ';
        }
        stream << '\n';
    }
    return stream.str();
}

void Grid::ExportToFile(const std::string& fName) const {
    std::ofstream fStream;
    fStream.open(fName, std::ios::out | std::ios::trunc);

    ST_ASSERT(fStream.is_open(), "Could not open ofstream");

    fStream << m_fieldSize.x << "\n" << m_numPairs << "\n";
    for (uint32_t x = 0; x < m_fieldSize.x; x++) {
        for (uint32_t y = 0; y < m_fieldSize.y; y++) {
            uint32_t value = GetValue(x, y);
            fStream << std::to_string(value) << ' ';
        }
        fStream << '\n';
    }
    fStream.close();
}

#include "Generator.h"


Grid::Grid(uint32_t fieldSize, uint32_t pairCount)
	: m_fieldSize(fieldSize), m_pairCount(pairCount) {
	m_grid = new uint8_t[m_fieldSize * m_fieldSize];
}
Grid::~Grid(){
	if(m_grid)
		delete[] m_grid;
}
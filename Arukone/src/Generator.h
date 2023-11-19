#pragma once
#include "Grid.h"

class Generator {
public:
	Generator(const Ref<Grid>& grid);
	~Generator(){}

	// returns number of pairs
	uint32_t Generate();

	inline Ref<Grid> GetPathGrid() const { return m_pathGrid; }
private:
	Ref<Grid> m_grid;
	Ref<Grid> m_pathGrid;

};
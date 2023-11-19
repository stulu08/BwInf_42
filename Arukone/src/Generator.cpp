#include "Generator.h"

#include <vector>
#include <algorithm>
#include <random>

Generator::Generator(const Ref<Grid>& grid) 
	: m_grid(grid) {
}

inline uint32_t random(uint32_t max) {
	static std::random_device rd;
	static std::mt19937 engine(rd());

	std::uniform_int_distribution<uint32_t> distr(0,max);
	return distr(engine);
}

/*
Regeln:
	> Jeder Linienzug besteht nur aus horizontalen
	und vertikalen Abschnitten (nicht schräg).

	> In jedem Feld mit einer Zahl beginnt oder
	endet genau ein Linienzug.

	> Jedes Feld ohne Zahl wird von genau einem
	Linienzug durchlaufen oder ist leer.
*/
uint32_t Generator::Generate() {
	const uvec2 size = m_grid->GetSize();

	m_grid->Clear();
	m_pathGrid = std::make_shared<Grid>(size);

	const uint32_t MaxNumTries = 2 * size.x;

	// we try a maximum amount of times to generate paths
	uint32_t path = 0;
	for (uint32_t itTry = 0; itTry < MaxNumTries; itTry++) {
		uint32_t sX, x;
		uint32_t sY, y;
		// generate a random starting point
		sX = x = random(size.x - 1);
		sY = y = random(size.y - 1);

		// if there is already a value assigned we just jump to the next iteration
		if (m_pathGrid->HasValue(x, y)) {
			continue;
		}

		// set the starting point in the grid
		m_pathGrid->SetValue(sX, sY, ++path);

		// keep track of some stats
		uint32_t repeatCounter = 0;
		uint32_t lengthCounter = 0;
		while (true) {
			// generare a random direction, move to it, 
			// if there is no value, border and check for neighbouring cells
			uint32_t dir = random(3);
			if (dir == 0 && x < size.x - 1) {
				/*
				0 1>1 <-- Should not happen, check y-1 and y+1 for same
				0 1 1
				0 0 1
				*/
				if (!m_pathGrid->HasValue(x + 1, y)) {
					if (m_pathGrid->GetValueSafe(x + 1, y + 1) != path && 
						m_pathGrid->GetValueSafe(x + 1, y - 1) != path) {
						x++;
						lengthCounter++;
					}
				}
			}
			else if (dir == 1 && x > 1) {
				/*
				1<1 0 <-- Should not happen, check y+1 and y-1 for same
				0 1 1
				0 0 1
				*/
				if (!m_pathGrid->HasValue(x - 1, y)) {
					if (m_pathGrid->GetValueSafe(x - 1, y + 1) != path && 
						m_pathGrid->GetValueSafe(x - 1, y - 1) != path) {
						x--;
						lengthCounter++;
					}
				}
			}
			else if (dir == 2 && y < size.y - 1) {
				/*
				1 1 1 <-- Should not happen, check x+1 and x-1 for same
				0 1 1
				0 0 0
				*/
				if (!m_pathGrid->HasValue(x, y + 1)) {
					if (m_pathGrid->GetValueSafe(x + 1, y + 1) != path &&
						m_pathGrid->GetValueSafe(x - 1, y + 1) != path) {
						y++;
						lengthCounter++;
					}
				}
			}
			else if (dir == 3 && y > 1) {
				/*
				1 1 0
				0 1 1
				0 0 1 <-- Should not happen, check x-1 and x+1 for same
				*/
				if (!m_pathGrid->HasValue(x, y - 1)) {
					if (m_pathGrid->GetValueSafe(x + 1, y - 1) != path && 
						m_pathGrid->GetValueSafe(x - 1, y - 1) != path) {
						y--;
						lengthCounter++;
					}
				}
			}
			
			// count how many times we have been on the same field and break if to many
			if (m_pathGrid->HasValue(x, y)) {
				repeatCounter++;
			}
			else {
				repeatCounter = 0;
			}

			m_pathGrid->SetValue(x, y, path);

			if (repeatCounter == 5 || lengthCounter > size.x) {
				// if path is to small remove it
				if (lengthCounter < 2) {
					m_pathGrid->Erase(path);
					path--;
				}
				else {
					// if path wasnt erased save it to the original grid
					m_grid->SetValue(sX, sY, path);
					m_grid->SetValue(x, y, path);
				}
				break;
			}
		}
	}
	// save the number of pairs
	m_grid->SetNumPairs(path);
	m_pathGrid->SetNumPairs(path);
	return path;
}

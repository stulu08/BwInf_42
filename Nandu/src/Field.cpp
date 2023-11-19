#include "Field.h"

#include "Construction.h"

void BlockField::SetConstruction(uint32_t xPos, uint32_t yPos, Construction* construction) {
	m_x = xPos;
	m_y = yPos;
	m_construction = construction;
}

Ref<BlockField> BlockField::GetOtherPair() const {
	// first check left
	if (m_x > 0) {
		Ref<Field> otherField = m_construction->At(m_x - 1, m_y);
		if (otherField->GetType() == GetType()) {
			Ref<BlockField> possiblePair = std::dynamic_pointer_cast<BlockField>(otherField);
			// now if at x-2 there is also one and one before that and so on, this isnt our pair (RrRr would not work otherwise), we can check this by just comparing his pair to us
			if (possiblePair->GetOtherPair().get() == this) {
				return std::dynamic_pointer_cast<BlockField>(otherField);
			}
		}
	}
	// then right
	if (m_x < m_construction->GetWidth()-1) {
		Ref<Field> otherField = m_construction->At(m_x + 1, m_y);
		if (otherField->GetType() == GetType())
			return std::dynamic_pointer_cast<BlockField>(otherField);
	}
	// othwewise fail
	ST_ASSERT(false, "Invalid field list");
	return nullptr;
}

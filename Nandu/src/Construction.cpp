#include "Construction.h"

#include <algorithm>
#include <sstream>

void Construction::Reset() {
	const uint32_t height = GetHeight();
	const uint32_t width = GetWidth();

	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			Ref<Field> field = At(x, y);
			field->SetLight(false);
			if (field->GetType() > FieldType::BlockField) {
				std::dynamic_pointer_cast<BlockField>(field)->SetConstruction(x, y, this);
			}
		}
	}
}

std::vector<Ref<Field>> Construction::GetAllOfType(FieldType type) const {
	std::vector<Ref<Field>> matches;
	for (const auto& vec : m_fields) {
		for(const Ref<Field>& field : vec){
			if(field->GetType() == type)
				matches.push_back(field);
		}
	}
	// already sort everything needed to sort
	if (type == FieldType::Flashlight) {
		std::sort(matches.begin(), matches.end(), [](Ref<Field> left, Ref<Field> right) {
			return std::dynamic_pointer_cast<FlashlightField>(left)->GetName() < std::dynamic_pointer_cast<FlashlightField>(right)->GetName();
		});
	}
	else if (type == FieldType::LED) {
		std::sort(matches.begin(), matches.end(), [](Ref<Field> left, Ref<Field> right) {
			return std::dynamic_pointer_cast<LEDField>(left)->GetName() < std::dynamic_pointer_cast<LEDField>(right)->GetName();
		});
	}

	return matches;
}

Construction::Construction(const std::vector<std::vector<Ref<Field>>>& initFieldList) 
	: m_fields(initFieldList) {
	Reset();
}

void Construction::Simulate() {
	const uint32_t height = GetHeight();
	const uint32_t width = GetWidth();

	// iterate from top to bottom, left to right
	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			if (y >= height - 1)
				continue;
			Ref<Field> field = At(x, y);
			Ref<Field> below = At(x, y + 1);
			
			// tell the field below me if its lit up
			bool on = field->IsLightOn();
			below->SetLight(on);
		}
	}
}

std::string Construction::ExportToString() const {
	const uint32_t height = GetHeight();
	const uint32_t width = GetWidth();

	std::stringstream stream;

	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			Ref<Field> field = At(x, y);
			switch (field->GetType())
			{
			case FieldType::None:
				stream << "X ";
				break;
			case FieldType::Flashlight:
				stream << "Q" << std::dynamic_pointer_cast<FlashlightField>(field)->GetName();
				break;
			case FieldType::LED:
				stream << "L" << std::dynamic_pointer_cast<LEDField>(field)->GetName();
				break;
			case FieldType::White:
				stream << "W ";
				break;
			case FieldType::Red:
				stream << (std::dynamic_pointer_cast<RedField>(field)->IsSensor() ? "R " : "r ");
				break;
			case FieldType::Blue:
				stream << "B ";
				break;
			}
			stream << " ";
		}
		stream << "\n";
	}
	return stream.str();
}
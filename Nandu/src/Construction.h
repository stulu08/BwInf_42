#pragma once
#include <Field.h>

#include <vector>
#include <string>

class Construction {
public:
	Construction(const std::vector<std::vector<Ref<Field>>>& initFieldList);

	void Simulate();
	// Resets the values of the actual fields, this does not clear everything
	void Reset();

	std::vector<Ref<Field>> GetAllOfType(FieldType type) const;

	inline uint32_t GetHeight() const { return (uint32_t)m_fields.size(); }
	inline uint32_t GetWidth() const { return (uint32_t)m_fields[GetHeight() - 1].size(); }
	inline Ref<Field> At(uint32_t x, uint32_t y) const { return m_fields[y][x]; }
	inline Ref<Field>& At(uint32_t x, uint32_t y) { return m_fields[y][x]; }

	std::string ExportToString() const;
private:
	std::vector<std::vector<Ref<Field>>> m_fields;
};
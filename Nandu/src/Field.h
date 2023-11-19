#pragma once
#include <Core.h>

class Construction;

enum class FieldType {
	None, /* X */
	Flashlight, /* Q* */
	LED, /* L* */

	BlockField,

	White, /* WW */
	Red, /* RR */
	Blue, /* BB */
};

class Field {
public:
	virtual ~Field() = default;

	virtual void SetLight(bool value) = 0;
	virtual bool IsLightOn() const = 0;

	virtual FieldType GetType() const = 0;
};

class EmptyField : public Field {
public:
	EmptyField() {}
	virtual ~EmptyField() = default;

	virtual void SetLight(bool value) override {}
	virtual bool IsLightOn() const override { return false; }

	virtual FieldType GetType() const override {
		return FieldType::None;
	}
};

class FlashlightField : public Field {
public:
	FlashlightField(uint32_t name)
		: m_name(name) {}

	virtual ~FlashlightField() = default;

	virtual void SetLight(bool value) override { m_isON = value; }
	virtual bool IsLightOn() const override { return m_isON; }

	virtual FieldType GetType() const override {
		return FieldType::Flashlight;
	}
	uint32_t GetName() const {
		return m_name;
	}
private:
	uint32_t m_name;
	bool m_isON = false;
};

class LEDField : public Field {
public:
	LEDField(uint32_t name) 
		: m_name(name){}

	virtual ~LEDField() = default;

	virtual void SetLight(bool value) override { m_receiving = value; }
	virtual bool IsLightOn() const override { return m_receiving; }

	virtual FieldType GetType() const override {
		return FieldType::LED;
	}
	uint32_t GetName() const {
		return m_name;
	}
private:
	uint32_t m_name;
	bool m_receiving = false;
};
// for fields that are in pairs
class BlockField : public Field {
public:
	BlockField() {};
	virtual ~BlockField() = default;
	virtual void SetLight(bool value) override { m_receiving = value; }

	inline bool IsReceiving() const { return m_receiving; }
	void SetConstruction(uint32_t xPos, uint32_t yPos, Construction* construction);
protected:
	bool m_receiving = false;
	uint32_t m_x = 0, m_y = 0;
	Construction* m_construction = nullptr;
	
	Ref<BlockField> GetOtherPair() const;
};

class WhiteField : public BlockField {
public:
	WhiteField() {}
	virtual ~WhiteField() = default;

	// Die LEDs leuchten immer beide, außer wenn beide Sensoren bestrahlt werden
	virtual bool IsLightOn() const override {
		return !(this->IsReceiving() && GetOtherPair()->IsReceiving());
	}
	
	virtual FieldType GetType() const override {
		return FieldType::White;
	}
private:
};

class RedField : public BlockField {
public:
	RedField(bool isSensor)
		: m_isSensor(isSensor) {}

	virtual ~RedField() = default;

	// Beide LEDs strahlen dann, wenn kein Licht auf den Sensor fällt
	virtual bool IsLightOn() const override {
		if (m_isSensor) {
			return !m_receiving;
		}
		Ref<RedField> other = std::dynamic_pointer_cast<RedField>(GetOtherPair());
		return other->IsLightOn();
	}

	virtual FieldType GetType() const override {
		return FieldType::Red;
	}
	inline bool IsSensor() { return m_isSensor; };
private:
	bool m_isSensor = false;
};

class BlueField : public BlockField {
public:
	BlueField() {}
	virtual ~BlueField() = default;

	// Bei den blauen Bausteinen wird das Licht einfach weitergegeben
	virtual bool IsLightOn() const override { return m_receiving; }

	virtual FieldType GetType() const override {
		return FieldType::Blue;
	}
};
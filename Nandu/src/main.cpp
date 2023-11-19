#include "Construction.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef ST_RELEASE
#define USER_INPUT 1
#endif

// structure to store simulation result
struct SimulationData {
    std::vector<std::pair<uint32_t, bool>> flashlights;
    std::vector<std::pair<uint32_t, bool>> leds;
};
/*
Jede Datei beschreibt eine Konstruktion und enthält
•    in der ersten Zeile die Breite n und die Höhe m der Konstruktion
•    und in den folgenden m Zeilen eine Darstellung der Konstruktion.
*/
void TakeUserInput(std::vector<std::vector<Ref<Field>>>& fields) {
#ifdef USER_INPUT

    // taking file as input
    std::string fName;
    std::cout << "Input datei: ";
    std::cin >> fName;

    // opening file
    std::ifstream fStream;
    fStream.open(fName);

    ST_ASSERT(fStream.is_open(), "Datei konnte nicht geöffnet werden");

    // reading the first line as descriped in the instructions
    uint32_t width, height;
    fStream >> width >> height;

    for (uint32_t i = 0; i < height; i++) {
        std::vector<Ref<Field>> cRow;

        for (uint32_t j = 0; j < width; j++) {
            std::string in;
            // everything should work out with the default fstream since it skips and stops at tabs/spaces/breaks
            fStream >> in;

            char c = in[0];
            // here er find a flashlight or led
            if (in.size() == 2) {
                // if we subtract the value of the '0' char we get our char an in (only for 0-9)
                uint32_t num = ((uint32_t)in[1]) - ((uint32_t)'0');
                if (c == 'Q') {
                    cRow.push_back(std::make_shared<FlashlightField>(num));
                }
                else if (c == 'L') {
                    cRow.push_back(std::make_shared<LEDField>(num));
                }
            }
            // every other symbol
            else if (in.size() == 1) {
                switch (c)
                {
                case 'X':
                    cRow.push_back(std::make_shared<EmptyField>());
                    break;
                case 'W':
                    cRow.push_back(std::make_shared<WhiteField>());
                    break;
                case 'r':
                    cRow.push_back(std::make_shared<RedField>(false));
                    break;
                case 'R':
                    cRow.push_back(std::make_shared<RedField>(true));
                    break;
                case 'B':
                    cRow.push_back(std::make_shared<BlueField>());
                    break;
                }
            }
        }

        fields.push_back(cRow);
    }
#else
    // example from task hard coded
    std::vector<Ref<Field>> cRow;
    {
        // X  Q1 Q2 X
        cRow.push_back(std::make_shared<EmptyField>());
        cRow.push_back(std::make_shared<FlashlightField>(1));
        cRow.push_back(std::make_shared<FlashlightField>(2));
        cRow.push_back(std::make_shared<EmptyField>());
        fields.push_back(cRow);
        cRow.clear();

        // X  W  W  X
        cRow.push_back(std::make_shared<EmptyField>());
        cRow.push_back(std::make_shared<WhiteField>());
        cRow.push_back(std::make_shared<WhiteField>());
        cRow.push_back(std::make_shared<EmptyField>());
        fields.push_back(cRow);
        cRow.clear();

        // r  R  R  r
        cRow.push_back(std::make_shared<RedField>(false));
        cRow.push_back(std::make_shared<RedField>(true));
        cRow.push_back(std::make_shared<RedField>(true));
        cRow.push_back(std::make_shared<RedField>(false));
        fields.push_back(cRow);
        cRow.clear();

        // X  B  B  X
        cRow.push_back(std::make_shared<EmptyField>());
        cRow.push_back(std::make_shared<BlueField>());
        cRow.push_back(std::make_shared<BlueField>());
        cRow.push_back(std::make_shared<EmptyField>());
        fields.push_back(cRow);
        cRow.clear();

        // X  W  W  X
        cRow.push_back(std::make_shared<EmptyField>());
        cRow.push_back(std::make_shared<WhiteField>());
        cRow.push_back(std::make_shared<WhiteField>());
        cRow.push_back(std::make_shared<EmptyField>());
        fields.push_back(cRow);
        cRow.clear();

        // X  L1 L2 X
        cRow.push_back(std::make_shared<EmptyField>());
        cRow.push_back(std::make_shared<LEDField>(1));
        cRow.push_back(std::make_shared<LEDField>(2));
        cRow.push_back(std::make_shared<EmptyField>());
        fields.push_back(cRow);
        cRow.clear();
        std::vector<Ref<Field>> cRow;
    }
#endif
}
void PrintResults(const std::vector<SimulationData>& combinations, const Construction& constr) {
    // get it once
    auto flashLights = constr.GetAllOfType(FieldType::Flashlight);
    auto leds = constr.GetAllOfType(FieldType::LED);

    // first header row
    for (uint32_t i = 0; i < flashLights.size(); i++) {
        std::cout << "|Q" << std::dynamic_pointer_cast<FlashlightField>(flashLights[i])->GetName();
    }
    for (uint32_t i = 0; i < leds.size(); i++) {
        std::cout << "|L" << std::dynamic_pointer_cast<LEDField>(leds[i])->GetName();
    }
    std::cout << "|\n";

    // now print every single result captured in the simulation
    for (uint32_t i = 0; i < combinations.size(); i++) {
        const SimulationData& data = combinations[i];

        for (uint32_t i = 0; i < flashLights.size(); i++) {
            std::cout << "| " << data.flashlights[i].second;
        }
        for (uint32_t i = 0; i < leds.size(); i++) {
            std::cout << "| " << data.leds[i].second;
        }
        std::cout << "|\n";
    }

    // finally show our construction
    std::cout << "\n\n\n" << constr.ExportToString();
}

int main() {
    // write user input into 2D array
    std::vector<std::vector<Ref<Field>>> fields;
    TakeUserInput(fields);

    Construction constr(fields);

    // get a list to all flashlights and leds
    auto flashLights = constr.GetAllOfType(FieldType::Flashlight);
    auto leds = constr.GetAllOfType(FieldType::LED);

    std::vector<SimulationData> combinations;

    // calculate the total number possible of combinations (2^n)
    uint32_t totalCombinations = 1 << (uint32_t)flashLights.size();

    for (uint32_t i = 0; i < totalCombinations; i++) {
        SimulationData data;
        // reset the simulation
        constr.Reset();

        // using a binary representation we can generate the current combinations
        for (uint32_t j = 0; j < flashLights.size(); j++) {
            // extract the j'th bit
            bool value = (i >> j) & 1;
            // save the value to be printed later and set it in the construction
            data.flashlights.push_back({ j, value });
            flashLights[j]->SetLight(value);
        }
        constr.Simulate();

        // save the reusults
        for (uint32_t j = 0; j < leds.size(); ++j) {
            data.leds.push_back({ j, leds[j]->IsLightOn() });
        }
        combinations.push_back(data);
    }

    PrintResults(combinations, constr);

#ifdef USER_INPUT
    system("pause");
#endif

    return 0;
}
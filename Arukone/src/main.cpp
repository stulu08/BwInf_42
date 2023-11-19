#include "Grid.h"
#include "Generator.h"

#include <iostream>

#ifdef ST_RELEASE
#define USER_INPUT 1
#endif

/*
Schreibe ein Programm, das für ein 
gegebenes n ≥ 4 verschiedene lösbare 
Arukone-Rätsel mit Gittergröße n × n 
erstellt, welche mindestens n/2 
verschiedene Zahlen enthalten.
*/

int main() {
#ifdef USER_INPUT
    std::cout << "Gitter Dimension: "; 
    uint32_t size;
    std::cin >> size;
#else
    constexpr uint32_t size = 16;
#endif

    // create the grid as shared pointer to controle ownership correctly
    Ref<Grid> grid = std::make_shared<Grid>(uvec2{ size, size });

    Generator generator = Generator(grid);

    // generate until valid
    while(generator.Generate() < (uint32_t)std::ceil((float)size/2.0f)){}

    // print result in a fancy way to console
    grid->ExportToConsole();
    std::cout << "\n\nLoesung:\n";
    generator.GetPathGrid()->ExportToConsole();

    // also export to file
    grid->ExportToFile("export.txt");


#ifdef USER_INPUT
    system("pause");
#endif

    return 0;
}
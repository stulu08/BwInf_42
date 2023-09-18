#include <iostream>

#include "Core.h"
#include "Generator.h"

int main(){
    uint32_t size = 0, pairs = 0;
    std::cout << "Gitter Dimension: ";
    std::cin >> size;
    std::cout << "Anzal Paare: ";
    std::cin >> pairs;

    Scope<Grid> gen = create_scope<Grid>(size, pairs);

    return pairs;
}
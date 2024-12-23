#include "Scanner.h"
#include <iostream>
#include <limits>

void Scanner::use(GameField& field) {
    int x, y;
    while (true) {
        std::cout << "Enter coordinates for scanner (x, y): ";
        std::cin >> x >> y;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }
        break;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (!field.isCellEmpty(x + j, y + i)) {
                std::cout << "Scanner has detected a ship" << std::endl;
                return;
            }
        }
    }
    std::cout << "Scanner has detected no ships" << std::endl;
}

std::string Scanner::getName() {
    return "Scanner";
}
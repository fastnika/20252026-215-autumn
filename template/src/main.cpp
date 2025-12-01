/*!
\file main.cpp
\author Мусин А.Р.
\date 1 Декабря 2025
\brief Главная программа
*/

#include "interface.h"
#include "polygon.h"
#include "resource.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, char* argv[]) {
    DEBUG_LOGGING("Start program");
    
    std::vector<Polygon> polygons;
    std::istream* input = &std::cin;
    std::ifstream file_input;
    bool is_interactive = true;

#ifdef SELFTEST
    if (argc != 2) {
        return CODE_SELFTEST_ERROR;
    }
    
    file_input.open(argv[1]);
    if (!file_input.is_open()) {
        return CODE_SELFTEST_ERROR;
    }
    
    input = &file_input;
    is_interactive = false;
#else
    if (argc > 1) {
        return CODE_INCORRECT_CONFIGURATION;
    }
#endif

    if (is_interactive) {
        std::cout << "\n=== Polygon Distance Calculator ===" << std::endl;
        std::cout << "Available commands:" << std::endl;
        std::cout << "1. Create polygon" << std::endl;
        std::cout << "2. Remove polygon" << std::endl;
        std::cout << "3. Calculate distance" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "===================================\n" << std::endl;
    }

    std::string line;
    while (true) {
        if (is_interactive) {
            std::cout << "Enter command: ";
            std::cout.flush();
        }

        if (!std::getline(*input, line)) {
            break;
        }

        if (line.empty()) continue;

        int command = 0;
        try {
            command = std::stoi(line);
        } catch (...) {
            if (is_interactive) {
                std::cout << "Invalid command. Please enter 1-4." << std::endl;
            }
            continue;
        }

        if (command == INTERFACE_COMMAND_1) {
            if (is_interactive) {
                std::cout << "Enter number of vertices: ";
                std::cout.flush();
            }

            int n = 0;
            if (!(*input >> n)) break;

            std::vector<Point> vertices;
            for (int i = 0; i < n; ++i) {
                if (is_interactive) {
                    std::cout << "Enter vertex " << (i + 1) << " (x y): ";
                    std::cout.flush();
                }

                double x = 0, y = 0;
                if (!(*input >> x >> y)) {
                    return CODE_NO_ERROR;
                }

                vertices.push_back(Point(x, y));
            }

            std::getline(*input, line);

            try {
                polygons.push_back(Polygon(vertices));
                if (is_interactive) {
                    std::cout << "Polygon created successfully." << std::endl;
                }
            } catch (...) {
                if (is_interactive) {
                    std::cout << "Error creating polygon." << std::endl;
                }
            }

        } else if (command == INTERFACE_COMMAND_2) {
            if (!polygons.empty()) {
                polygons.pop_back();
                if (is_interactive) {
                    std::cout << "Last polygon removed." << std::endl;
                }
            } else {
                if (is_interactive) {
                    std::cout << "No polygons to remove." << std::endl;
                }
            }

        } else if (command == INTERFACE_COMMAND_3) {
            if (polygons.size() >= 2) {
                try {
                    double dist = polygons[polygons.size()-2].Distance(polygons.back());
                    std::cout << dist << std::endl;
                    if (is_interactive) {
                        std::cout << "Distance calculated." << std::endl;
                    }
                } catch (...) {
                    if (is_interactive) {
                        std::cout << "Error calculating distance." << std::endl;
                    }
                }
            } else {
                if (is_interactive) {
                    std::cout << "Need at least 2 polygons to calculate distance." << std::endl;
                }
            }

        } else if (command == INTERFACE_COMMAND_EXIT) {
            if (is_interactive) {
                std::cout << "Goodbye!" << std::endl;
            }
            break;

        } else {
            if (is_interactive) {
                std::cout << "Unknown command. Please enter 1-4." << std::endl;
            }
        }
    }

    if (file_input.is_open()) {
        file_input.close();
    }

    polygons.clear();
    return CODE_NO_ERROR;
}
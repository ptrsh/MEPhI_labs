#include "app.h"

#include <string>
#include <climits>

void App::printMenu() const {
    std::cout << "\nMenu:\n";
    std::cout << "1) Enter new main vector\n";
    std::cout << "2) Enter 2 vectors and add up them \n";
    std::cout << "3) Enter 2 vectors and find the difference \n";
    std::cout << "4) Enter 2 vectors and multiply them \n";
    std::cout << "5) Print vector\n";
    std::cout << "6) Get norm\n";
    std::cout << "7) Exit\n\n";
}

App::App() {
    controllers = {
        [this]() { setVector(); },
        [this]() { getAddition(); },
        [this]() { getSubstraction(); },
        [this]() { getMultiplication(); },
        [this]() { printVector(); },
        [this]() { getNorm(); },
        [this]() { exit(); }
    };
}

void App::setVector() { 
    Vector new_vector;
    std::cin >> new_vector; 
    vector = new_vector;
}

void App::getAddition() {
    while (true) {
        try {
            Vector vector1;
            Vector vector2;

            std::cout << "\nEnter vector #1:\n";
            std::cin >> vector1;

            std::cout << "Enter vector #2:\n";
            std::cin >> vector2;

            std::cout << vector1 + vector2 << "\n";
            return;
        }
        catch (Vector::DifferentIndexesException &e) {handleInvalidInput(std::cin); }

    }

}

void App::getSubstraction() {
    while (true) {
        try {
            Vector vector1;
            Vector vector2;

            std::cout << "\nEnter vector #1:\n";
            std::cin >> vector1;

            std::cout << "Enter vector #2:\n";
            std::cin >> vector2;
            
            std::cout << vector1 - vector2 << "\n";
            return;
        }
        catch (Vector::DifferentIndexesException &e) {handleInvalidInput(std::cin); }

    }
}

void App::getMultiplication() {
    while (true) {
        try {
            Vector vector1;
            Vector vector2;

            std::cout << "\nEnter vector #1:\n";
            std::cin >> vector1;

            std::cout << "Enter vector #2:\n";
            std::cin >> vector2;
            
            std::cout << vector1 * vector2 << "\n";
            return;
        }
        catch (Vector::DifferentIndexesException &e) {handleInvalidInput(std::cin); }

    }

}

void App::getNorm() { std::cout << "Norm of vector:\n" << vector.getNorm() << "\n"; }

void App::printVector() const { std::cout << "Vector:\n" << vector << "\n"; }

void App::exit() { active = false; }

void App::start() {
    setVector();
    active = true;
    while (active) {
        printMenu();
        int command = scan<int>(std::cin, ":") - 1;
        if (command >= controllers.size()) {
            handleInvalidInput(std::cin);
        } else controllers[command]();
    }
}
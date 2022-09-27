#include "app.h"
#include <string>
#include <climits>

void handleInvalidInput(std::istream &input) {
    std::cout << "Invalid input! Try again!\n";
    input.clear();
    input.ignore(1024, '\n');
}

template<typename T>
T scan(std::istream &input, const std::string &message) {
    T value;
    bool error = true;
    while (error) {
        std::cout << message << ": ";
        input >> value;
        error = input.fail();
        if (error) handleInvalidInput(input);
    }
    return value;
}

std::istream &operator>>(std::istream &input, Nephroid &nephroid) {
    while (true) {
        try {
            double radius = scan<double>(input, "Radius");
            nephroid.setRadius(radius);
            return input;
        }
        catch (Nephroid::InvalidRadiusException &e) { handleInvalidInput(input); }
    }
}

void App::printMenu() const {
    std::cout << "\nMenu:\n";
    std::cout << "1) Set radius\n";
    std::cout << "2) Get arclength\n";
    std::cout << "3) Get radius of curvature by t\n";
    std::cout << "4) Get area\n";
    std::cout << "5) Get x and y by t\n";
    std::cout << "6) Get equation\n";
    std::cout << "7) Exit\n\n";
}

App::App() {
    controllers = {
        [this]() { setRadius(); },
        [this]() { getLength(); },
        [this]() { getRadiusOfCurvature(); },
        [this]() { getArea(); },
        [this]() { getXY(); },
        [this]() { getEquation(); },
        [this]() { exit(); }
    };
}

void App::setRadius() { std::cin >> nephroid; }

void App::getLength() const { std::cout << "Length: " << nephroid.getLength() << "\n"; }
    
void App::getRadiusOfCurvature() const {
    while (true) {
        try {
            double t = scan<double>(std::cin, "t");
            double radius = nephroid.getRadiusOfCurvature(t);
            std::cout << "Radius of curvature: " << radius << "\n";
            return;
        }
        catch (Nephroid::InvalidParameterException &e) { handleInvalidInput(std::cin); }
    }  
}

void App::getArea() const { std::cout << "Area: " << nephroid.getArea() << "\n"; }

void App::getXY() const {
    while (true) {
        try {
            double t = scan<double>(std::cin, "t");
            std::string xy = nephroid.getXY(t);
            std::cout << xy << "\n";
            return;
        }
        catch (Nephroid::InvalidParameterException &e) { handleInvalidInput(std::cin); }
    }   
}

void App::getEquation() const { std::cout << "Equation: " << nephroid.getEquation() << "\n"; }

void App::exit() { active = false; }

void App::start() {
    setRadius();
    active = true;
    while (active) {
        printMenu();
        int command = scan<int>(std::cin, ":") - 1;
        if (command >= controllers.size()) {
            handleInvalidInput(std::cin);
        } else controllers[command]();
    }
}
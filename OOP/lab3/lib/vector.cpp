#include "vector.h"
#include <cassert>

#define abs(x) ((x) > 0 ? (x) : -(x))
#define MAX 2147483647

template<typename T>
T scan(std::istream &input, const std::string &message) {
    T value;
    bool fail;
    do {
        if (!message.empty()) std::cout << message << ": ";
        input >> value;
        if ((fail = input.fail())) handleInvalidInput(input);
    } while (fail);
    return value;

}

void handleInvalidInput(std::istream &input) {
    std::cout << "Invalid input! Try again!\n";
    input.clear();
    input.ignore(MAX, '\n');
}

std::istream &operator>>(std::istream &input, Vector &vector) {
    int size = scan<int>(input, "Enter the number of numbers");
    for (int i = 0; i < size; i++) {
        input.clear();
        input.ignore(MAX, '\n');
        double num = scan<double>(input, "Num " + std::to_string(i + 1));
        vector.push(num);
    }
    return input;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < size);
    return data[index];
}

const double& Vector::operator[](int index) const {
    assert(index >= 0 && index < size);
    return data[index];
}

std::ostream &operator<<(std::ostream &out, const Vector &vector) {
    for (int i = 0; i < vector.size; i++) out << vector[i] << " ";
    return out;
}

Vector::Vector(const Vector &vector) {
    this->size = vector.size;
    this->data = new double [this->size];
    for (int i = 0; i < vector.size; i++) this[i] = vector[i];
}

Vector::Vector(double num) {
    size = 1;
    data = new double [1];
    data[0] = num;
}

Vector::Vector(size_t size, double nums[]) {
  
    this->size = size;
    data = new double [size];
    for (int i = 0; i < size; i++) data[i] = nums[i];
}

Vector& Vector::operator= (const Vector &vector) {
    if (this == &vector) return *this;
    if (this->size > 0) delete[] data;
    this->size = vector.size;
    this->data = new double [this->size];
    for (int i = 0; i < vector.size; i++) (*this)[i] = vector[i];
    return *this;
}

Vector Vector::operator+(const Vector &vector) {
    if (vector.size != this->size) throw Vector::DifferentIndexesException();
    Vector result;
    for (int i = 0; i < this->size; i++) result.push(vector[i] + (*this)[i]);
    return result;
}

Vector Vector::operator-(const Vector &vector) {
    if (vector.size != this->size) throw Vector::DifferentIndexesException();
    Vector result;
    for (int i = 0; i < this->size; i++) result.push(vector[i] - (*this)[i]);
    return result;
}

double Vector::operator*(const Vector &vector) {
    if (vector.size != this->size) throw Vector::DifferentIndexesException();
    double result = 0;
    for (int i = 0; i < this->size; i++) result += vector[i] * (*this)[i];
    return result;
}

Vector::~Vector() {
    if (size > 0) delete[] data;
}

void Vector::push(double num) {
    double *arr = new double [size + 1];
    for (int i = 0; i < size; i++) arr[i] = data[i];
    arr[size] = num;
    if (size) delete[] data;
    data = arr;
    size += 1;
}

double Vector::getNorm() {
    int max_index = 0;
    for (int i = 0; i < size; i++) max_index = (abs(data[i]) > abs(data[max_index])) ? i : max_index;
    return data[max_index];
}

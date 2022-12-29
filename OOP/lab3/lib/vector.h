#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#ifndef VECTOR_H
#define VECTOR_H

class Vector {
    private:
        double *data;
        size_t size;
    public:
        class DifferentIndexesException : std::exception {};
        Vector() : data(nullptr), size(0) {}
        Vector(const Vector &vector); 
        Vector(Vector &&vector) noexcept;
        Vector(double num);
        Vector(size_t size, double nums[]);
        ~Vector();

        double getNorm();
        void push(double num);  

        friend std::istream &operator>>(std::istream &input, Vector &vector); 
        friend std::ostream &operator<<(std::ostream &out, const Vector &vector);
        Vector &operator= (const Vector &vector);
        Vector &operator= (Vector &&vector) noexcept;
        Vector operator+(const Vector &vector);
        Vector operator-(const Vector &vector);
        const double &operator[] (int index) const;
        double &operator[] (int index);
        double operator*(const Vector &vector);
        FRIEND_TEST(Vector, AdditionResult);
        FRIEND_TEST(Vector, SubstitutionResult);
        FRIEND_TEST(Vector, MultiplicationResult);
        FRIEND_TEST(Vector, Equal);
};


template<typename T> T scan(std::istream &input, const std::string &message);
void handleInvalidInput(std::istream &input);

#endif
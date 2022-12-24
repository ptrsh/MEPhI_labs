#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iterator>
#include <cstddef>
#include <cassert>

template <typename T>
class myVector{
private:
    int mLength{};
    T* mData{};
 
public:
  
    myVector() = default;
	myVector(int length);
    ~myVector();
    void erase();
    T& operator[](int index);
    void reallocate(int newLength);
    void resize(int newLength);
    void insertBefore(T value, int index);
    void remove(int index);
    void insertAtBeginning(T value);
    void push_back(T value);
    int size() const;
};

#include "container.inl"

#endif
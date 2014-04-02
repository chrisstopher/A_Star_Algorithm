#ifndef DYNAMIC2DARRAY_H
#define DYNAMIC2DARRAY_H

#include <iostream>
#include <memory>

template <class T>
class Dynamic2dArray {
public:
    Dynamic2dArray(unsigned int columns = 0, unsigned int rows = 0);
    Dynamic2dArray(const Dynamic2dArray& arr) = delete;             //TO DO
    Dynamic2dArray(Dynamic2dArray&& arr) = delete;                  //TO DO
    ~Dynamic2dArray();
    Dynamic2dArray& operator=(const Dynamic2dArray& arr) = delete;  //TO DO
    Dynamic2dArray& operator=(Dynamic2dArray&& arr) = delete;       //TO DO
    void create(unsigned int columns, unsigned int rows);
    void clear();
    T& operator()(unsigned int x, unsigned int y);
    const T& operator()(unsigned int x, unsigned int y) const;
    unsigned maxRows() const;
    unsigned maxColumns() const;
private:
    std::unique_ptr<T[]> Array;
    unsigned columnCount, rowCount;
};



template <class T>
Dynamic2dArray<T>::Dynamic2dArray(unsigned int columns, unsigned int rows) {
    create(columns, rows);
}

template <class T>
Dynamic2dArray<T>::~Dynamic2dArray() {
    clear();
}

template <class T>
void Dynamic2dArray<T>::create(unsigned int columns, unsigned int rows) {
    if (columns == 0 || rows == 0) {
        columnCount = 0;
        rowCount = 0;
        return;
    }
    columnCount = columns;
    rowCount = rows;
    Array = std::unique_ptr<T[]>(new T[columnCount * rowCount]);
}

template <class T>
void Dynamic2dArray<T>::clear() {
    rowCount = columnCount = 0;
    Array.reset();
}

template <class T>
T& Dynamic2dArray<T>::operator()(unsigned int x, unsigned int y) {
    return Array[y * maxColumns() + x];
}

template <class T>
const T& Dynamic2dArray<T>::operator()(unsigned int x, unsigned int y) const {
    return Array[y * maxColumns() + x];
}

template <class T>
unsigned Dynamic2dArray<T>::maxRows() const {
    return rowCount;
}

template <class T>
unsigned Dynamic2dArray<T>::maxColumns() const {
    return columnCount;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Dynamic2dArray<T>& arr) {
    os << "\n";
    for (int y = 0; y < arr.maxRows(); y++) {
        for (int x = 0; x < arr.maxColumns(); x++) {
            os << arr(x, y) << " | ";
        }
        os << "\n";
    }
    return os;
}

#endif // DYNAMIC2DARRAY_H

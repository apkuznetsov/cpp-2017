#include <cstddef>

/* Реализуйте шаблонную версию класса Array.
 * Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.
 *
 * В предыдущей версии предполагается, что для типа T определены оператор присваивания и конструктор по умолчанию.
 * При создании шаблонных классов контейнеров (вроде Array и не только)
 * разумно стараться минимизировать требования к типам шаблонных параметров.
 * Поэтому усложним задачу, реализуйте класс Array не полагаясь на то,
 * что для типа T определен оператор присваивания и конструктор по умолчанию.
 * Конструктор копирования у типа T есть.
 *
 * Используйте placement new и явный вызов деструктора, чтобы создавать и уничтожать объекты,
 * выделять правильно выровненную память можно с помощью new char[N * sizeof(T)],
 * где N – количество элементов массива. */

template<typename T>
class Array {

public:
    explicit Array(size_t size, const T &value = T()) : dataSize(size) {

        data = static_cast<T *>(operator new[](dataSize * sizeof(T)));
        for (size_t i = 0; i < dataSize; ++i)
            new(data + i) T(value);
    }

    Array() {
        dataSize = 0;
        data = 0;
    }

    Array(const Array &rhs) : dataSize(rhs.size()) {

        data = static_cast<T *>(operator new[](dataSize * sizeof(T)));
        for (size_t i = 0; i < dataSize; ++i)
            new(data + i) T(rhs.data[i]);
    }

    ~Array() {
        for (size_t i = 0; i < dataSize; ++i)
            data[i].~T();
        operator delete[](data);
    }

    Array &operator=(Array const &rhs) {
        if (this != &rhs) {
            this->~Array();
            dataSize = rhs.size();
            data = static_cast<T *>(operator new[](dataSize * sizeof(T)));
            for (size_t i = 0; i < dataSize; ++i)
                new(data + i) T(rhs.data[i]);
        }

        return *this;
    }

    size_t size() const {
        return dataSize;
    }

    T &operator[](size_t i) {
        return data[i];
    }

    const T &operator[](size_t i) const {
        return data[i];
    }

private:
    size_t dataSize;
    T *data;
};

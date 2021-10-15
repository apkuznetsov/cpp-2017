#include <cstddef>

/*
 * Реализуйте шаблонную версию класса Array.
 * Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.
 */

template<typename T>
class Array {
public:
    /* explicit Array(size_t size = 0, const T& value = T())
     * конструктор класса, который создаёт Array размера size,
     * заполненный значениями value типа T.
     *
     * Считайте что у типа T есть конструктор,
     * который можно вызвать без параметров, либо он ему не нужен. */
    explicit Array(size_t size = 0, const T &value = T()) :
            data(new T[size]), dataSize(size) {

        for (size_t i = 0; i < dataSize; ++i) {
            data[i] = value;
        }
    }

    /* Array(const Array &)
     * конструктор копирования, который создаёт копию параметра.
     *
     * Считайте, что для типа T определён оператор присваивания. */
    Array(const Array<T> &other) {
        dataSize = other.dataSize;
        data = new T[dataSize];

        for (size_t i = 0; i < dataSize; ++i) {
            data[i] = other[i];
        }
    }

    ~Array() {
        dataSize = 0;
        delete[] data;
        data = NULL;
    }

    Array &operator=(Array<T> &other) {
        if (this == &other) {
            return *this;
        }

        dataSize = other.dataSize;
        delete[] data;

        data = new T[dataSize];
        for (size_t i = 0; i < dataSize; ++i) {
            data[i] = other[i];
        }

        return *this;
    }

    size_t size() const {
        return dataSize;
    }

    T &operator[](size_t index) {
        return data[index];
    }

    const T &operator[](size_t index) const {
        return data[index];
    }

private:
    T *data;
    size_t dataSize;
};

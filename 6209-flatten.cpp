/* Шаблонный класс Array может хранить объекты любого типа,
 * для которого определён конструктор копирования,
 * в том числе и другой Array, например, Array< Array<int> >.
 * Глубина вложенности может быть произвольной.
 *
 * Напишите шаблонную функцию (или несколько) flatten,
 * которая принимает на вход такой "многомерный" Array неизвестной заранее глубины вложенности
 * и выводит в поток out через пробел все элементы, хранящиеся на самом нижнем уровне.
 *
 * Примеры работы функции flatten:
 *
 * Array<int> ints(2, 0);
 * ints[0] = 10;
 * ints[1] = 20;
 * flatten(ints, std::cout);
 *
 * Array< Array<int> > array_of_ints(2, ints);
 * flatten(array_of_ints, std::cout);
 *
 * Array<double> doubles(10, 0.0);
 * flatten(doubles, std::cout);
 *
 * Лидирующие и завершающие пробельные символы будут игнорироваться проверяющей системой,
 * т. е. там где ожидается "10 20" будет так же принят, например, вариант "   10 20   ", но не вывод "1020".
 * Шаблонные функции тоже можно перегружать, из нескольких шаблонных функций будет выбрана наиболее специфичная. */

#include <iostream>

template<typename T>
void flatten(const T &elem, std::ostream &out) {
    out << elem << " ";
}

template<typename T>
void flatten(const Array <T> &array, std::ostream &out) {
    for (size_t i = 0; i < array.size(); ++i)
        flatten(array[i], out);
}
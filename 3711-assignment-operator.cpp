/*
Завершите класс String, добавив к нему оператор присваивания. Будьте аккуратны при работе с памятью. Инвариант класса остается тем же (в size хранится размер строки без завершающего 0 символа, str указывает на C-style строку, т. е. с завершающим нулевым символом).

Требования к реализации: вы можете заводить любые вспомогательные методы или функции, но не реализуйте заново методы из предыдущих заданий — они уже реализованы. При реализации не нужно вводить или выводить что-либо. Реализовывать main не нужно. Не используйте функции из cstdlib (malloc, calloc, realloc и free).
*/

#include <algorithm>
#include <cstddef>
#include <cstring>

struct String {
	String(const char *str = "");
	String(size_t n, char c);
	String(const String &other);
	~String();

	String &operator=(const String &other){
        if(this != &other) {
            delete [] str;
            new (this) String(other.str);
        }
        
        return *this;
    }

	void append(const String &other);

	size_t size;
	char *str;
};

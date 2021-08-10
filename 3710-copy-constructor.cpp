/*
Добавьте в класс String реализацию конструктора копирования. Инвариант класса остается тем же (в size хранится размер строки без завершающего 0 символа, str указывает на C-style строку, т. е. с завершающим нулевым символом).

Требования к реализации: вы можете заводить любые вспомогательные методы или функции, но не реализуйте заново методы из предыдущих заданий — они уже реализованы. При реализации не нужно вводить или выводить что-либо. Реализовывать main не нужно. Не используйте функции из cstdlib (malloc, calloc, realloc и free).
*/

#include <cstddef>
#include <cstring>

struct String {
	String(const char *str = "");
	String(size_t n, char c);
	~String();

    String(const String &other): String(other.str) {};

	void append(const String &other);

	size_t size;
	char *str;
};

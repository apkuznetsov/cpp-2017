﻿/*
В этой задаче вам требуется реализовать оператор [] для уже известного вам класса String. Однако на этот раз оператор должен реализовывать нестандартное поведение: оператор нужно реализовать таким образом, чтобы для объекта str класса String можно было писать str[i][j] и это выражение возвращало подстроку начинающуюся в позиции i (считая с 0) и заканчивающуюся в позиции j (не включая).

Например:

String const hello("hello");
String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"

Обратите внимание, что i может равняться j, в этом случае результатом должна быть пустая строка. Гарантируется, что i никогда не будет больше j, и они не будут выходить за пределы длины строки.

Требования к реализации: При выполнении задания вы можете создавать любые методы/конструкторы или даже структуры/классы, если они вам нужны. Реализовывать методы, которые уже объявленны в шаблоне, не нужно  они уже реализованы. При выполнении задания не вводите и не выводите что-либо. Реализовывать функцию main не нужно.
*/

#include <cstddef>

struct String {
	String(const char *str = "");
	String(size_t n, char c);
	~String();

    String(const String &other);
    String &operator=(const String &other);

	void append(const String &other);

    struct SubStr;
    SubStr operator[](size_t i) const;

	size_t size;
	char *str;
};

struct String::SubStr
{
    SubStr(const String& s, size_t shft) : sub(s), shift(shft) {}

    String operator[](size_t i)
    {
        sub.str[i - shift] = 0;
        return String(sub.str);
    }

    String sub;
    size_t shift;
};

String::SubStr String::operator[](size_t i) const
{
    return String::SubStr(String(str + i), i);
}

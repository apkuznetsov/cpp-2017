﻿/*
Вам требуется написать программу, которая "переворачивает" последовательность положительных целых чисел.

На вход подается последовательность разделённых пробелами положительных целых чисел. Последовательность заканчивается нулем. Требуется вывести эту последовательность в обратном порядке.
На выводе числа нужно так же разделить пробелами. Завершающий ноль — это просто индикатор конца последовательности, он не является ее частью, т.е. выводить его не нужно.

Требования к реализации: в данном задании запрещено использовать циклы, а также дополнительную память: массивы, строки или контейнеры (даже, если вы с ними уже знакомы). Вам разрешено заводить вспомогательные функции, если они вам нужны.
*/

#include <iostream>

void rev()
{
	int x;
	std::cin >> x;

	if (x != 0) {
		rev();
		std::cout << x << " ";
	}
}

int main()
{
	rev();
	return 0;
}
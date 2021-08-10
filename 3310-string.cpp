﻿/*
В этой и последующих задачах мы создадим свой простой аналог стандартного класса string для удобной работы со строками. Начнём мы с написания конструктора.

В этой задаче вам требуется реализовать конструктор, который принимает на вход C-style строку, вычисляет ее размер (без учета завершающего 0 символа) и сохраняет его в поле size, кроме того, конструктор должен аллоцировать память достаточную для хранения копии переданной строки (вместе с завершающим 0 символом), копирует переданную строку в выделенную память и сохраняет указатель на начало этой области памяти в поле str. Т.е. в результате работы конструктора в поле str должен оказаться указатель на C-строку c копией исходной строки, а в поле size — длина строки без учета завершающего нулевого символа.
*/

#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {
	String(const char *str = "")
        : size(strlen(str))
        , str(strcpy(new char[strlen(str) + 1], str))
    {}

	size_t size;
	char *str;
};
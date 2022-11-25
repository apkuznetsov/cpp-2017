/*
ВАРИАНТ № 13.
Написать программу, которая для заданного текстового файла, имя которого вводится с клавиатуры, строит в оперативной памяти массив
записей(структур) вида <длина_строки, количество_строк>, анализируя строки файла. Отсортировать полученный массив по возрастанию
значений поля "количество_строк", результирующий массив вывести на экран. Для поиска и сортировки элементов массива использовать
стандартные функции языка С lsearch() и qsort() соответственно.
*/

#include "stdafx.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <Windows.h>

#define LEN 50	// длина массива

struct line {		// структуры-записи
	int lenOfStr;	// длина строки
	int numOfWords;	// количество слов
};

/*void getString(char str[]) {
	int i = -1;
	do {
		if (i == (LEN - 1))
			break;
		++i;
	} while ((str[i] = (char)getchar()) != '\n');
	str[i] = '\0';
}*/

int getNumOfLinesInFile(char fileName[]) // подсчёт количества строк в файле
{
	FILE* myFile = fopen(fileName, "rt");

	char ch;
	int count = 0;
	while (!feof(myFile))
		if ((ch = fgetc(myFile)) == '\n' || ch == EOF)
			++count;

	fclose(myFile);

	return count;
}

void fillArr(char fileName[], struct line arr[])	// заполнение массива структур
{
	FILE* myFile = fopen(fileName, "rt");

	char ch;
	int countOfLen = 0;
	int countOfWords = 1;
	int i = 0;

	while ((ch = (char)fgetc(myFile)) != EOF)
	{
		if (ch == '\n')
		{
			arr[i].lenOfStr = countOfLen;
			if (countOfLen == 0)
				arr[i++].numOfWords = 0;
			else
				arr[i++].numOfWords = countOfWords;
			countOfLen = 0;
			countOfWords = 1;
			continue;
		}
		if (ch == ' ')
			++countOfWords;
		++countOfLen;
	}
	arr[i].lenOfStr = countOfLen;
	if (countOfLen == 0)
		arr[i++].numOfWords = 0;
	else
		arr[i++].numOfWords = countOfWords;

	fclose(myFile);
}

int compForqsort(const void* p1, const void* p2) {
	return ((struct line*)p1)->numOfWords > ((struct line*)p2)->numOfWords;
}

void main() {
	char fileName[LEN];	// строка для имени файла
	FILE* myFile;		// указатель на файл

	setlocale(LC_ALL, "RUS");

	printf("Лабораторная работа № 2.\nОсновы языка С++. Язык С. Работа с текстовыми файлами.\n");
	printf("Вариант № 13. Выполнил: Андрей Кузнецов, группа 6213.\n\n");

	// поиск файла:
	printf("введите имя файла ... ");
	//getString(fileName);
	scanf("%49s", fileName); // записываем в строку 49 символов, 50-ым запишется '\0'
	printf("");

	if ((myFile = fopen(fileName, "r")) == NULL) {	// открытия файла и подключения его к программе
		printf("ОШИБКА: файл %s не существует\n\nзавершение работы программы...\n", fileName);
		printf("\n");
		system("pause");
		return;
	}
	fclose(myFile);	// закрытие файла -- освобождение памяти

	// создание в ОП массива:
	int count = getNumOfLinesInFile(fileName);	// количество строк в файле
	puts("");
	struct line* arr = (struct line*)malloc(count * sizeof(struct line));

	fillArr(fileName, arr);

	printf("массив:\n");
	for (int i = 0; i < count; i++)
		printf("строка %d: длина строки = %d, количество слов = %d\n", i + 1, arr[i].lenOfStr, arr[i].numOfWords);
	printf("\n");

	printf("отсортированный массив:\n");
	qsort(arr, count, sizeof(struct line), (int(*) (const void*, const void*)) compForqsort);
	for (int i = 0; i < count; i++)
		printf("строка %d: длина строки = %d, количество слов = %d\n", i + 1, arr[i].lenOfStr, arr[i].numOfWords);
	printf("\n");

	free(arr);	// освобождение памяти

	system("pause");
}

/*
	FILE *fopen(const char *fname, const char *mode)
Функция fopen() открывает файл, имя которого указано аргументом fname, и возвращает свя­занный с ним указатель. Тип операций,
разрешенных над файлом, определяется аргументом mode. Разрешенные для mode значения показаны в таблице.

	int printf(const char *format, arg-list)
Функция printf() записывает в stdout аргументы из списка arg-list под управлением строки, на которую указывает аргумент format.
	Строка, на которую указывает format, состоит из объектов двух различных назначений. Во- первых, это символы, которые сами
должны быть выведены на экран. Во-вторых, это специфика­торы формата, определяющие вид, в котором будут выведены аргументы из
списка arg-list. Спе­цификаторы формата состоят из символа процент, за которым следует код формата. Команды форматирования
приведены в таблице. Количество аргументов должно точно соответство­вать количеству спецификаторов формата, причем следовать они
должны в одинаковом порядке. Например, следующий вызов функции printf()

	void qsort(void *base, size_t num, size_t size, int (*compare) (const void *, const void *))
Функция qsort() сортирует массив, на который указывает параметр base, используя quicksort — алгоритм сортировки широкого
назначения, разработанный С. Р. Хори. После завершения фун­кции массив становится отсортированным. Параметр num задает число
элементов массива, пара­метр size задает размер в байтах каждого элемента.

	int scanf(const char *format, arg-list)
Функция scanf() является процедурой ввода общего назначения, считывающей данные из пото­ка stdin. Она может считывать данные всех
базовых типов и автоматически конвертировать их в нужный внутренний формат. Если бы printf() выполняла ввод, а не вывод, ее можно
было бы назвать аналогом scanf().

	int fgetc( FILE * filestream );
Функция fgetc возвращает символ на который ссылается внутренний индикатор позиции файла указанного потока. После чего, внутренний
индикатор позиции в файле сдвигается на одни символ, таким образом он уже указывает на следующий символ.
*/
#include "stdafx.h"
#include <locale.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#pragma warning(disable:4996)

#define NOT_FOUND -1	// константа для проверки

// константы -- имена для файлов:
#define FNAME "NAME.DAT"
#define FSPORT "SPORT.DAT"
#define FLINK "LINK.DAT"

// константы для размеров строк:
#define MAX_NAMESIZE 256	// для размера ФИО
#define MAX_SPORTSIZE 32	// для размера названия вида спорта


// указатели на файлы:
FILE* fname;	// ФИО
FILE* fsport;	// спорт
FILE* flink;	// индексы записи


// структура, связывающая между собой фамилию и вид спорта:
struct link {
	unsigned long idOfName;		// индекс записи в файле NAME.DAT
	unsigned long idOfSport;	// индекс записи в файле SPORT.DAT
};


// добавление студента [его ФИО] в файл:
unsigned long addNameToFile(const char* name) {		// name -- ФИО студента
	fname = fopen(FNAME, "at");						// "at" -- дописывает информацию к концу текстового файла
	fseek(fname, 0, SEEK_END);

	unsigned long id = ftell(fname);				// id -- последняя (текущая) позиция в файле (потоке) fname
	fputs(name, fname);								// вывод (запись) строки в файл (поток)
	fclose(fname);									// закрытие файла: освобождение памяти

	return id;
}

// добавление вида спорта в файл:
unsigned long addSportToFile(const char* sport) {	// sport -- название группы
	fsport = fopen(FSPORT, "at");
	fseek(fsport, 0, SEEK_END);

	unsigned long id = ftell(fsport);
	fputs(sport, fsport);

	fclose(fsport);

	return id;										// ИД вставленной группы
}

// добавление записи о студенте в файл:
void addLinkToFile(const link l) {
	flink = fopen(FLINK, "ab");

	fwrite(&l, sizeof(link), 1, flink);				/* "ab" -- Дописывает информацию к концу двоичного файла,
													   sizeof(link) -- длина объекта в байтах,
													   1 -- количество записываемых объектов,
													   flink -- поток, в который записываем */

	fclose(flink);
}


// получение номера вида спорта по его названию:
unsigned long getIdOfSport(const char* value) {
	fsport = fopen(FSPORT, "a+t");					// открывает или создаёт текстовый файл для чтения и записи

	char* sport;									// создание строки
	sport = (char*)malloc(MAX_SPORTSIZE);
	unsigned long id = 0;
	bool found = false;								// флаг, если найден

	while (fgets(sport, MAX_SPORTSIZE, fsport)) {	/* Функция fgets считывает из потока данных строку пока не встретится символ
													   "новая строка" или не закончится файл или пока длина считываемой строки
													   не превысит ограничение аргумента n (считывается не более чем n - 1 символов). */

		if (strcmp(sport, value) == 0) {			// сравнение переданной в функцию строки и считанной в sport
			found = true;							// если найден -- флаг true, завершаем цикл
			break;
		}
		id = ftell(fsport);							// fgets переместил указатель на файл
	}

	free(sport);
	fclose(fsport);

	if (!found)										// если не найден -- -1
		id = NOT_FOUND;

	return id;
}


// ввод строки:
void getString(int len, char str[]) {
	if (len == 0)
	{
		puts("ОШИБКА: строка нулевой длины");
		return;
	};

	int i = -1;
	if (len > 1)
	{
		do {
			if (i == (len - 2))
				break;
			++i;
		} while ((str[i] = (char)getchar()) != '\n');
	};
	str[++i] = '\0';
}

// добавление нового вида вида спорта:
void createNewSport() {
	char* sport;
	sport = (char*)malloc(MAX_SPORTSIZE);								// создание строка размером SPORTSIZE

	printf("введите название вида спорта ... ");
	getString(MAX_SPORTSIZE, sport);									// заполнение строки
	puts("");

	if (getIdOfSport(sport) == NOT_FOUND) {								// если в файле такой строки нет, то
		unsigned long idOfSport = addSportToFile(sport);				// добавление данного вида спорта файла, присваивая ему ИД
		sport[strlen(sport) - 1] = '\0';								// чтобы корректно отобразилось
		printf("вид спорта «%s» успешно добавлен в базу\n", sport);
	}
	else
		puts("ОШИБКА: такой вид спорта уже записан");

	free(sport);														// освобождение памяти: строка больше не нужна в программе
}

// добавление нового студента в базу:
void createNewName() {
	char* name;
	name = (char*)malloc(MAX_NAMESIZE);
	printf("введите ФИО студента ... ");
	getString(MAX_NAMESIZE, name);

	char* sport;
	sport = (char*)malloc(MAX_SPORTSIZE);
	printf("введите вид спорта   ... ");
	getString(MAX_SPORTSIZE, sport);
	puts("");

	link student;
	unsigned long idOfSport = getIdOfSport(sport);			// проверка наличия введённого вида спорта в базе
	if (idOfSport == NOT_FOUND)
		puts("ОШИБКА: данного вида спорта нет в базе");
	else {
		student.idOfName = addNameToFile(name);				// запись ФИО в файл
		student.idOfSport = idOfSport;

		addLinkToFile(student);								// запись структуры в файл
		name[strlen(name) - 1] = '\0';
		sport[strlen(sport) - 1] = '\0';
		printf(
			"cтудент %s (%s) успешно добавлен в базу\n",
			name, sport);
	}

	free(name);
	free(sport);
}


// получение всех записи о спорте:
bool getLink(link* l, unsigned long idOfSport) {
	while (fread(l, sizeof(link), 1, flink)) {
		if (l->idOfSport == idOfSport) {			// если есть такой ИД
			return true;
		}
	}

	return false;									// считыванием неудачно
}

// вывод информации о виде спорта:
void getInfoAboutSport() {
	char* sport;
	sport = (char*)malloc(MAX_SPORTSIZE);
	printf("введите название вида спорта ... ");
	getString(MAX_SPORTSIZE, sport);
	puts("");

	unsigned long idOfSport = getIdOfSport(sport);		// поиск вида спорта, полученние его индекса
	sport[strlen(sport) - 1] = '\0';

	if (idOfSport == NOT_FOUND)
		puts("данного вида спорта нет в базе");
	else {												// если такой спорт есть в базе
		link l;											// буфер-индекс
		flink = fopen(FLINK, "rb");						// открытие для чтени
		fname = fopen(FNAME, "rt");

		bool isHere;									// флаг, на случай, если таких записей нет
		char* name = (char*)malloc(MAX_NAMESIZE);		// строка для отображения имени
		while (getLink(&l, idOfSport)) {				// считываем до конца файла [пока происходит чтение]
			fseek(fname, l.idOfName, SEEK_SET);		    /* l.idOfName -- количество байт для смещения указателя в файле от начала файла
														   SEEK_SET -- начало файла */

			fgets(name, MAX_NAMESIZE, fname);

			name[strlen(name) - 1] = '\0';
			printf("студент %s, %s\n", name, sport);
			isHere = true;
		}

		if (!isHere)
			puts("таких студентов нет");

		free(name);
		fclose(flink);
		fclose(fname);
	};

	free(sport);										// освобождение памяти: строка больше не нужна
}


void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char m;
	do
	{
		puts("Лабораторная работа № 3.");
		puts("Основы языка С++. Язык С. Работа с двоичными файлами.");
		puts("Выполнил: студент Андрей Кузнецов, группа 6213.");
		puts("");

		puts("меню");
		puts("---------------------------");
		puts("1 -- добавить вид спорта");
		puts("2 -- добавить студента");
		puts("3 -- вывод списка студентов");
		puts("---------------------------");
		puts("0 -- выход");
		puts("---------------------------");
		printf("выбор ... ");
		m = getch();
		printf("%c", m);
		system("CLS");

		switch (m)
		{
		case 49:
			createNewSport();
			puts("");
			system("pause");
			system("CLS");
			break;
		case 50:
			createNewName();
			puts("");
			system("pause");
			system("CLS");
			break;
		case 51:
			getInfoAboutSport();
			puts("");
			system("pause");
			system("CLS");
			break;
		default:
			system("CLS");
			break;
		};
	} while (m != 48);
}

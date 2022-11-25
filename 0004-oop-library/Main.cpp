#include "stdafx.h"

#include "Library.h"
#include "Author.h"
#include "Book.h"

#include <windows.h>	// содержит system()
#include <sstream>

#include <string>		// работа со строками
#include <iostream>		// для cin, cout, cerr и проч.
#include <cstdlib>
#include <ctime>		// содержит time()


using namespace std;


bool isDigit(const char* s);		// проверка: является ли строка цифрой
void mainMenu();					// главное меню
void addingNewBooksToLibrary();		// добавление книг в библиотеку
void givingBookToPerson();			// выдача книги
void returningBookToLibrary();		// возврат книги
void findBooksInStockByAuthor();


int mainMenuChoice = -1;				// переменная для пункта меню
Library* myLibrary = new Library();		// динамическое создание объекта класса Library


void main() {
	// русификация ввода/вывода:
	SetConsoleCP(1251);				// ввод с консоли в кодировке 1251
	SetConsoleOutputCP(1251);		// Вывод на консоль в кодировке 1251
	setlocale(LC_ALL, "Russian");

	do
	{
		system("cls");	// очистка консоли
		mainMenu();

		switch (mainMenuChoice)
		{
			// 1) Поступление новой книги в библиотеку.
		case 1:
			addingNewBooksToLibrary();
			break;

			// 2) Выдача книги читателю на руки.
		case 2:
			givingBookToPerson();
			break;

			// 3) Возврат книги в библиотеку.
		case 3:
			returningBookToLibrary();
			break;

			// 4) Вывод на экран всех зарегистрированных в библиотеке произведений
			//    (список всех книг с их авторами и количеством экземпляров).
		case 4:
		{
			system("cls");	// очистка консоли
			cout << "Все зарегистрированные в библиотеке произведения." << endl;
			cout << "----------------------------------------------------------------------" << endl;

			myLibrary->printAllRegistratedBooks();

			cout << endl;
			cout << "Нажмите Enter для выхода в главное меню." << endl;
			getchar();
		}
		break;

		//	5)	Вывод на экран авторов всех зарегистрированных в библиотеке книг.
		case 5:
		{
			system("cls"); //очистка консоли
			cout << "Все зарегистрированные в библиотеке авторы." << endl;
			cout << "----------------------------------------------------------------------" << endl;

			myLibrary->printAllRegistratedAuthors();

			cout << endl;
			cout << "Нажмите Enter для выхода в главное меню." << endl;
			getchar();
		}
		break;

		case 6:
			findBooksInStockByAuthor();
			break;
		}
	} while (mainMenuChoice != 0);

	// удаление динамически созданного объекта библиотеки:
	delete myLibrary;
}

bool isDigit(const char* s) {
	const char* temp = "0123456789";	// цифры
	unsigned point_count = 0;

	for (int i = 0; i < strlen(s); i++) {	// по всей строке
		if (s[i] == '.') {
			point_count++;
			if (point_count > 1) return false;
		}
		if (!strchr(temp, s[i])) return false;
	}
	return true;
}

// главное меню:
void mainMenu()
{
	cout << "Библиотека." << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "1) Поступление новой книги в библиотеку." << endl;
	cout << "2) Выдачу книги читателям на руки." << endl;
	cout << "3) Возврат книги в библиотеку." << endl;
	cout << "4) Вывод на экран всех зарегистрированных в библиотеке произведений" << endl;
	cout << "   (список всех книг с их авторами и количеством экземпляров)." << endl;
	cout << "5) Вывод на экран авторов всех зарегистрированных в библиотеке книг." << endl;
	cout << "6) По фамилии автора выводить на экран все его произведения, имеющиеся" << endl;
	cout << "   в библиотеке на в наличии." << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "0) Выход из программы." << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "ваш выбор ... ";

	const int stringSize = 256;
	char s[stringSize];
	double value = 0;				// вводимое число

	do
	{
		// перед вводом числа -- вводить и проверять строку:
		cin.getline(s, stringSize);
		while (!isDigit(s)) {
			cerr << "Некорректное значение. Попробуйте снова.\n";
			cout << "ваш выбор ... ";
			cin.getline(s, stringSize);
		}

		// после ввода числа -- запоминаем:
		mainMenuChoice = atof(s);	// записываем значение в value с помощью функции atof

		if (mainMenuChoice < 0 | mainMenuChoice > 6)
		{
			cerr << "Некорректное значение. Попробуйте снова.\n";
			cout << "ваш выбор ... ";
		}
	} while (mainMenuChoice < 0 | mainMenuChoice > 6);
}

void addingNewBooksToLibrary()
{
	system("cls");	// очистка консоли
	cout << "Поступление новой книги в библиотеку." << endl;
	cout << "----------------------------------------------------------------------" << endl << endl;

	string authorName = "";
	cout << "автор книги .............. ";
	getline(cin, authorName);

	Author* author = new Author(authorName);	// создание объекта

	// проверка: есть ли автор в библиотеке, иначе регистрация его:
	if (myLibrary->IsAuthorRegistrated(author))
	{
		cout << "Книги такого автора уже имеются в библиотеке." << endl;
	}
	else
	{
		myLibrary->RegistrateNewAuthor(author);
		cout << "Новый автор успешно зарегистрирован в библиотеке." << endl;
	}
	cout << endl;

	cout << "название книги ........... ";
	string bookTitle = "";
	getline(cin, bookTitle);

	cout << "количество экземпляров ... ";
	Book* book = new Book();

	// выделяем количество -- число
	string input = "";
	int booksInCount = 0;

	while (true) {
		getline(cin, input);

		// конвертация строки в число:
		stringstream myStream(input);
		if (myStream >> booksInCount) // если строка переводится в int
		{
			try
			{
				book = new Book(-1, bookTitle, myLibrary->GetAuthorIndex(author), booksInCount);
			}
			catch (int i)
			{
				cout << "Некорректное значение. Попробуйте снова." << endl;
				cout << "количество экземпляров ... ";
				continue;
			}

			break;
		}
		cout << "Некорректное значение. Попробуйте снова." << endl;
		cout << "количество экземпляров ... ";
	}
	cout << endl;

	Book* searchedBook = new Book();
	searchedBook = myLibrary->FindBookInLibrary(book);

	if (searchedBook == nullptr)
	{
		srand(time(NULL));
		book->SetCipher(rand());	// шифр -- рандомное число
		myLibrary->RegistrateNewBook(book);

		cout << "Такой книги в библиотеке не было, но теперь она зарегистрирована." << endl;
		cout << "Её шифр: " << book->GetCipher() << endl;
	}
	else
	{
		cout << "Новые экземпляры книги успешно добавлены в библиотеке." << endl;
		searchedBook->IncCurrentCountInLibrary(booksInCount);
	}

	myLibrary->IncCurrentCountOfBooks(booksInCount);
	cout << endl;
	cout << "Книги успешно добавлены в библиотеку." << endl << endl;

	cout << "Нажмите Enter для выхода в главное меню." << endl;
	getchar();
}

void givingBookToPerson()
{
	system("cls");	// очистка консоли
	cout << "Выдача книги читателю на руки." << endl;
	cout << "----------------------------------------------------------------------" << endl << endl;

	string authorName = "";
	cout << "автор книги ...... ";
	getline(cin, authorName);
	Author* author = new Author(authorName);

	if (myLibrary->IsAuthorRegistrated(author))
	{
		cout << "Книги такого автора имеются в библиотеке." << endl << endl;

		cout << "название книги ... ";
		string bookTitle = "";
		getline(cin, bookTitle);
		Book* book = new Book(-1, bookTitle, myLibrary->GetAuthorIndex(author), 1);
		Book* bookSearched = myLibrary->FindBookInLibrary(book);

		if (bookSearched == nullptr)
		{
			cout << "Такой книги нет в библиотеке." << endl;
		}

		if (bookSearched != nullptr)
		{
			int currentCount = bookSearched->GetCurrentCountInLibrary();
			cout << "Текущее количество данных книг в библиотеке: " << currentCount << endl;

			if (currentCount == 0)
			{
				cout << "Ни одного экземпляра нет в наличии, попробуйте зайти попозже." << endl;
			}

			if (currentCount > 0)
			{
				cout << "Вот, возьмите пожалуйста, Вашу книгу. Не забывайте вернуть вовремя." << endl;

				bookSearched->DecCurrentCountInLibrary(1);
				myLibrary->DecCurrentCountOfBooks(1);
			}
		}
	}
	// если нет автора:
	else
	{
		cout << "Такого автора нет в библиотеке." << endl;
	}
	cout << endl;

	cout << "Нажмите Enter для выхода в главное меню." << endl;
	getchar();
}

void returningBookToLibrary()
{
	system("cls");	// очистка консоли
	cout << "Возврат книги в библиотеку." << endl;
	cout << "----------------------------------------------------------------------" << endl << endl;

	string authorName = "";
	cout << "автор книги ...... ";
	getline(cin, authorName);
	Author* author = new Author(authorName);

	if (myLibrary->IsAuthorRegistrated(author))
	{
		cout << "название книги ... ";
		string bookTitle = "";
		getline(cin, bookTitle);
		cout << endl;

		Book* book = new Book(-1, bookTitle, myLibrary->GetAuthorIndex(author), 1);
		Book* bookSearched = myLibrary->FindBookInLibrary(book);

		if (bookSearched == nullptr)
		{
			cout << "Такой книги в библиотеке зарегистрировано не было." << endl;
			cout << "Хотите пожертвовать её библиотеке?" << endl;
			cout << "1 -- да  (регистрация новой книги в библиотеке)" << endl;
			cout << "2 -- нет (выход в главное меню)" << endl << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "ваш выбор ... ";

			string input = "";
			int choice = 0;

			while (true) {
				getline(cin, input);

				stringstream myStream(input);
				if (myStream >> choice)
				{
					if (choice != 1 & choice != 2) {
						cout << "Некорректное значение. Попробуйте снова." << endl;
						cout << "ваш выбор ... ";
						continue;
					}

					break;
				}
				cout << "Некорректное значение. Попробуйте снова." << endl;
				cout << "ваш выбор ... ";
			}

			switch (choice)
			{
				// регистрация новой книги (автор и название уже введены):
			case 1:
			{
				srand(time(NULL));
				book->SetCipher(rand());	// шифр -- случайное число
				myLibrary->RegistrateNewBook(book);

				cout << "Книга теперь зарегистрирована в библиотеке" << endl;
				cout << "Ей был присвoен шифр: " << book->GetCipher() << endl;

				myLibrary->IncCurrentCountOfBooks(1);
				cout << endl;
				cout << "Книга успешно принята в библиотеку." << endl << endl;

				cout << "Нажмите Enter для выхода в главное меню." << endl;
				getchar();
			}
			break;

			case 2:
				break;
			}
		}

		if (bookSearched != nullptr)
		{
			int currentCount = bookSearched->GetCurrentCountInLibrary();
			cout << "Текущее количество данных книг в библиотеке: " << currentCount << endl;

			cout << "Спасибо, что вернули книгу в срок." << endl;
			bookSearched->IncCurrentCountInLibrary(1);
			myLibrary->IncCurrentCountOfBooks(1);
			cout << endl;

			cout << "Нажмите Enter для выхода в главное меню." << endl;
			getchar();
		}

	}

	if (!myLibrary->IsAuthorRegistrated(author))
	{
		cout << endl;
		cout << "Это новый автор в библиотеке, хотите подарить книгу библиотеке?" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "1 -- да (регистрация новой книги в библиотеке)" << endl;
		cout << "2 -- нет (выход в главное меню)" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "ваш выбор ... ";

		string input = "";
		int choice = 0;

		while (true) {
			getline(cin, input);

			stringstream myStream(input);
			if (myStream >> choice)
			{
				if (choice != 1 & choice != 2) {
					cout << "Некорректное значение. Попробуйте снова." << endl;
					cout << "ваш выбор ... ";
					continue;
				}
				break;
			}
			cout << "Некорректное значение. Попробуйте снова." << endl;
			cout << "ваш выбор ... ";
		}

		switch (choice)
		{
			// регистрация новой книги (автор введён, название -- нет)
		case 1:
		{
			// регистрация нового автора:
			myLibrary->RegistrateNewAuthor(author);

			cout << endl;
			cout << "название книги ... ";
			string bookTitle = "";
			getline(cin, bookTitle);
			cout << endl;

			Book* book = new Book(-1, bookTitle, myLibrary->GetAuthorIndex(author), 1);

			srand(time(NULL));
			book->SetCipher(rand()); // шифр - рандомное число
			myLibrary->RegistrateNewBook(book);

			cout << "Книга теперь зарегистрирована в библиотеке" << endl;
			cout << "Ей был присвoен шифр: " << book->GetCipher() << endl;

			myLibrary->IncCurrentCountOfBooks(1);
			cout << endl;
			cout << "Книга была удачно принята в библиотеке." << endl << endl;

			cout << "Нажмите Enter для выхода в главное меню." << endl;
			getchar();
		}
		break;

		case 2:
			break;
		}
	}
	/*cout << endl;
	cout << "Нажмите Enter для выхода в главное меню." << endl;
	getchar();*/
}

void findBooksInStockByAuthor()
{
	system("cls");	// очистка консоли
	cout << "Все произведения автора, имеющиеся в наличии в библиотеке." << endl;
	cout << "----------------------------------------------------------------------" << endl << endl;

	string authorName = "";
	cout << "автор книги ... ";
	getline(cin, authorName);
	Author* author = new Author(authorName);

	if (myLibrary->IsAuthorRegistrated(author))
	{
		myLibrary->printAllBooksByAuthor(author);
	}
	else
	{
		cout << "Такой автор не зарегистрирован в библиотеке." << endl;
	}

	cout << endl;
	cout << "Нажмите Enter для выхода в главное меню." << endl;
	getchar();
}

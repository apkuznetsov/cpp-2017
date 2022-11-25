#pragma once

#include "Author.h"
#include "Library.h"

#include <string>

#include <iostream>
#include <stack>		// для empty(), size(), back(), push_back(), pop_back()

using namespace std;

class Book
{
	int cipher;
	string title;
	int authorIndex;
	int currentCountInLibrary;

public:

	Book()
	{
	}

	Book(int cipher, string title, int authorIndex, int incCount)
	{
		this->cipher = cipher;
		this->title = title;
		this->authorIndex = authorIndex;

		this->currentCountInLibrary = 0;

		if (incCount <= 0)
		{
			throw - 1;	// генерировать целое число -1
		}

		this->currentCountInLibrary += incCount;
	}

	Book(int incCount)
	{
		this->currentCountInLibrary += incCount;
	}

	~Book()
	{
	}

	int GetCipher()
	{
		return this->cipher;
	}
	void SetCipher(int value)
	{
		this->cipher = value;
	}

	string GetTitle()
	{
		return this->title;
	}
	void SetTitle(string value)
	{
		this->title = value;
	}

	int GetAuthorIndex()
	{
		return  this->authorIndex;
	}
	void SetAuthor(int value)
	{
		this->authorIndex = value;
	}

	int GetCurrentCountInLibrary()
	{
		return this->currentCountInLibrary;
	}
	void SetCurrentCountInLibrary(int value)
	{
		this->currentCountInLibrary = value;
	}

	void IncCurrentCountInLibrary(int incCount)
	{
		currentCountInLibrary += incCount;
	}
	void DecCurrentCountInLibrary(int decCount)
	{
		currentCountInLibrary -= decCount;
	}
};

#pragma once

using namespace std;

class Author
{
	string name;

public:

	Author()
	{
	}

	Author(string name)
	{
		this->name = name;
	}

	~Author()
	{
	}

	string GetName()
	{
		return name;
	}
};

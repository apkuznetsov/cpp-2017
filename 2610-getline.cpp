/*
Реализуйте функцию getline, которая считывает поток ввода посимвольно, пока не достигнет конца потока или не встретит символ переноса строки ('\n'), и возвращает C-style строку с прочитанными символами.

Обратите внимание, что так как размер ввода заранее неизвестен, то вам нужно будет перевыделять память в процессе чтения, если в потоке ввода оказалось больше символов, чем вы ожидали.

Память, возвращенная из функции будет освобождена оператором delete[]. Символ переноса строки ('\n') добавлять в строку не нужно, но не забудьте, что в конце C-style строки должен быть завершающий нулевой символ.

Требования к реализации: при выполнении данного задания вы можете определять любые вспомогательные функции, если они вам нужны. Определять функцию main не нужно.
*/

#include <iostream>

char* resize(char* str, unsigned size, unsigned new_size) {
	char* new_str = new char[new_size];
	
    	unsigned to_move = new_size > size ? size : new_size;
    	for (unsigned i = 0; i < to_move; ++i) {
		new_str[i] = str[i];
	}
	
    	delete [] str;
	return new_str;
}

char* getline() {
	char curr_char = '\0';
	unsigned curr_size = 10;
	char* str = new char[curr_size];
	
    	unsigned i;
	for (i = 0; std::cin.get(curr_char) && curr_char != '\n'; ++i) {
		str[i] = curr_char;
        
		if (i == curr_size - 2) {
            		unsigned new_size = curr_size * 1.5;
            		str = resize(str, curr_size, new_size);
            		curr_size = new_size;
        	}
	}
    
	str[i] = '\0';
	return resize(str, curr_size, i + 1);
}

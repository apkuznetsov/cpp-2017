﻿/*
Напишите функцию power, реализующую возведение целого числа в неотрицательную целую степень. 
Функция power должна принимать на вход два целых числа и возвращать целое число.
*/

int power(int x, unsigned p) {
    int answer = 1;
 
    int i;
    for(i = 1; i <= p; ++i) {
        answer *= x;
    }

    return answer;
}

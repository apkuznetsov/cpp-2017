/*
Реализуйте функцию swap_min, которая принимает на вход двумерный массив целых чисел, ищет в этом массиве строку, содержащую наименьшее среди всех элементов массива значение, и меняет эту строку местами с первой строкой массива.

Подумайте, как обменять строки массива, не обменивая элементы строк по-отдельности.
*/

#include <iostream>
using namespace std;

void swap_min(int* m[], unsigned rows, unsigned cols)
{
    int minValue = m[0][0];
    int rowIdxWithMinValue = 0;
    
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; j++)
        {
            if(m[r][c] < minValue)
            {
                minValue = m[r][c];
                rowIdxWithMinValue = r;
            }
        }
    }
    
    swap(m[rowIdxWithMinValue],m[0]);             
}

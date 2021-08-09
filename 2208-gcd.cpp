/*
Напишите рекурсивную функцию вычисления наибольшего общего делителя двух положительных целых чисел (Greatest Common Divisor, GCD).

Для этого воспользуйтесь следующими свойствами:
GCD(a, b) = GCD(b, a bmod b)
GCD(0, a) = a
GCD(a, b) = GCD(b, a)
*/

unsigned gcd(unsigned a, unsigned b)
{
	if(b == 0)
		return a;
    
	return gcd(b, a % b);
}

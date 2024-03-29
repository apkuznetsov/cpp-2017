﻿/*
Вам дан класс Rational, который описывает рациональное число. В нем определены методы add, sub, mul и div, которые прибавляют к нему число, отнимают число, умножают на число и делят на число соответственно. Кроме того в нем определен метод neg, который меняет знак на противоположный.

Вам нужно определить операторы +=, -=, *=, /= для класса Rational так, чтобы они могли принимать в качестве аргументов и объекты типа Rational и целые числа. Кроме того вам необходимо определить операторы унарного минуса и плюса для класса Rational.

Требования к реализации: ваш код не должен вводить или вводить что-либо, реализовывать функцию main не нужно. Кроме того, нельзя (это совершенно не нужно) использовать динамическую память или подключать какие-либо библиотеки.
*/

struct Rational
{
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;
    
private:
    int numerator_;
    int denominator_;
};

Rational& operator+=(Rational &left, const Rational &right) { left.add(right); return left; }
Rational& operator-=(Rational &left, const Rational &right) { left.sub(right); return left; }
Rational& operator*=(Rational &left, const Rational &right) { left.mul(right); return left; }
Rational& operator/=(Rational &left, const Rational &right) { left.div(right); return left; }

Rational operator+(Rational left) { return left; }
Rational operator-(Rational left) { left.neg(); return left; }

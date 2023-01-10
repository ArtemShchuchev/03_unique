#include <iostream>

#include "SecondFunk/SecondaryFunction.h"
#include "Unique/Unique.hpp"

/*
Задача 3*. std::unique_ptr своими руками
Описание
Нужно создать упрощённый аналог std::unique_ptr.

В шаблонном классе должны быть реализованы функции:

1. Конструктор, принимающий сырой указатель.
2. Перегружен оператор * для получения объекта.
3. Запрещены оператор присваивания и конструктор копирования.
4. Метод release, который освобождает владение и возвращает сырой указатель.
5. Деструктор.
*/

struct S
{
    S() : a(0), b(0) {}
    S(int _a, double _b) : a(_a), b(_b) {}
    friend std::ostream& operator<< (std::ostream& out, const S& s)
    {
        return out << "\na = " << s.a << "\nb = " << s.b << "\n\n";
    }

    int a;
    double b;
};

int main()
{
    printHeader("Задача 3*. std::unique_ptr своими руками");   // заголовок

    auto rawPtr = new S(5, 16.58);
    std::cout << "rawPtr: " << *rawPtr << "\n";

    unique_ptr<S>unicPtr(new S(3, 2.3));
    std::cout << "unicPtr: " << *unicPtr << "\n";

    rawPtr = unicPtr.my_release();
    std::cout << "rawPtr: " << *rawPtr << "\n";
    
    try
    {
        // объект unicPtr "пустой"
        std::cout << "unicPtr: " << *unicPtr << "\n";
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "Ошибка! " << err.what() << "\n";
    }

    return 0;
}
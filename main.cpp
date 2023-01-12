#include <iostream>
#include <memory>

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

    S* rawPtr(nullptr);
    S s(5, 16.58);
    rawPtr = &s;
    std::cout << "rawPtr: " << *rawPtr << "\n";

    //unique_ptr<S>unicPtr(rawPtr);         // автоматическая память
    unique_ptr<S>unicPtr(new S(3, 2.3));    // динамическая память
    std::cout << "unicPtr: " << *unicPtr << "\n";

    S* rawPtr2 = unicPtr.release();
    std::cout << "rawPtr2: " << *rawPtr2 << "\n";
    
    delete rawPtr2;

    try
    {
        // объект unicPtr "пустой"
        std::cout << "unicPtr: " << *unicPtr << "\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "\nОшибка типа: " << typeid(err).name() << "\n";
        std::cout << err.what() << "\n";
    }

    return 0;
}
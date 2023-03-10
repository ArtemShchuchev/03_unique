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

    unique_ptr<S>unicPtr(new S(5, 16.58));
    std::cout << "addr unicPtr: " << &unicPtr << " -> obj: " << unicPtr << "\n";

    std::cout << "\nunicPtr: " << *unicPtr;
    *unicPtr = { 6, 18.3 };
    std::cout << "unicPtr: " << *unicPtr;
    
    S* relPtr = unicPtr.release();
    std::cout << "addr  relPtr: " << &relPtr << " -> obj: " << relPtr << "\n";
    std::cout << "Old pointer is                      -> " << unicPtr << "\n";

    delete relPtr;

    try
    {
        // указатель unicPtr = nullptr
        std::cout << "unicPtr: " << *unicPtr;
    }
    catch (const std::exception& err)
    {
        std::cout << "\nОшибка типа: " << typeid(err).name() << "\n";
        std::cout << err.what() << "\n";
    }
    catch (const ExeptNotPtr)
    {
        std::cout << "\nОшибка: Пустой указатель (nullptr)!" << "\n";
    }

    return 0;
}
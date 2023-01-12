#pragma once
#include <stdint.h>
#include <math.h>

template<class T>
class unique_ptr
{
private:
	T* ptr = nullptr;

	bool ptrIsDynamic(T*);	// true если T* указывает на динамическую память
	void deletePtr(T*);		// при необходимости освобождает память

public:
	unique_ptr(T*);	// Конструктор, принимающий сырой указатель
	unique_ptr(const unique_ptr &) = delete;	// конструктор копирования
	~unique_ptr();	// деструктор

	unique_ptr& operator= (const unique_ptr&) = delete;	// оператор присваивания
	T operator* ();	// оператор разименования
	T* release();	// освобождает владение и возвращает сырой указатель.
};



template<class T>
inline bool unique_ptr<T>::ptrIsDynamic(T* _ptr)
{
	// abs - вроде не нужен, ну на всякий случай
	// если между адресом объекта и адресом указателя более 100 int
	// то скорей всего объект расположен в динамической памяти
	// но это не точно ))
	return (abs((__int64*)_ptr - (__int64*)&_ptr) > 100);
}

template<class T>
inline void unique_ptr<T>::deletePtr(T* _ptr)
{
	if (_ptr)
	{
		if (ptrIsDynamic(_ptr))
		{
			std::cout << "release dynamic memory...\n";
			delete _ptr;
		}
		_ptr = nullptr;
	}
}

template<class T>
inline unique_ptr<T>::unique_ptr(T* rawPtr) : ptr( ptrIsDynamic(rawPtr) ? new T : nullptr)
{
	std::cout << "-= Constructor =-\n";
	if (ptrIsDynamic(rawPtr)) *ptr = *rawPtr;
	else ptr = rawPtr;

	deletePtr(rawPtr);
}

template<class T>
inline unique_ptr<T>::~unique_ptr()
{
	std::cout << "-= Destructor =-\n";
	deletePtr(ptr);
}

template<class T>
inline T unique_ptr<T>::operator*()
{
	// почему я не вижу строчки "Объект не существует!"????
	if (!ptr) throw std::runtime_error("Объект не существует!");
	return *ptr;
}

template<class T>
inline T* unique_ptr<T>::release()
{
	std::cout << "-= Release =-\n";
	auto temp = new T;
	*temp = *ptr;
	deletePtr(ptr);
	ptr = nullptr;

	return temp;
}

#pragma once
#include <stdint.h>
#include <math.h>

template<class T>
class unique_ptr
{
private:
	T* ptr = nullptr;
public:
	unique_ptr(T*);		// Конструктор, принимающий сырой указатель
	unique_ptr(const unique_ptr &) = delete;	// конструктор копирования
	~unique_ptr();		// деструктор

	unique_ptr& operator= (const unique_ptr&) = delete;	// оператор присваивания
	T operator* ();		// оператор разименования
	T* release();	// освобождает владение и возвращает сырой указатель.
};



template<class T>
inline unique_ptr<T>::unique_ptr(T* rawPtr) : ptr(new T)
{
	std::cout << "Constructor:\n";
	*ptr = *rawPtr;
	if ( ( reinterpret_cast<std::uintptr_t>(rawPtr) - reinterpret_cast<std::uintptr_t>(&rawPtr) ) > 500)
	{
		std::cout << "delete ptr...\n";
		delete rawPtr;
	}
	rawPtr = nullptr;
}

template<class T>
inline unique_ptr<T>::~unique_ptr()
{
	std::cout << "Destructor:\n";
	if (ptr)
	{
		std::cout << "delete ptr...\n";
		delete ptr;
	}
}

template<class T>
inline T unique_ptr<T>::operator*()
{
	if (!ptr) throw std::runtime_error("Объект не существует!");
	return *ptr;
}

template<class T>
inline T* unique_ptr<T>::release()
{
	auto temp = new T;
	*temp = *ptr;
	std::cout << "Release: delete ptr...\n";
	delete ptr;
	ptr = nullptr;

	return temp;
}

#pragma once

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
	T* my_release();	// освобождает владение и возвращает сырой указатель.
};



template<class T>
inline unique_ptr<T>::unique_ptr(T* rawPtr) : ptr(rawPtr)
{
}

template<class T>
inline unique_ptr<T>::~unique_ptr()
{
	std::cout << "destructor\n";
	if (ptr)
	{
		std::cout << "delete...\n";
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
inline T* unique_ptr<T>::my_release()
{
	auto temp = new T;
	*temp = *ptr;
	delete ptr;
	ptr = nullptr;

	return temp;
}

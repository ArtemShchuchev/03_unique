#pragma once
#include <stdint.h>
#include <math.h>

template<class T>
class unique_ptr
{
private:
	T* ptr = nullptr;

	bool ptrIsDynamic(T*);	// true ���� T* ��������� �� ������������ ������
	void deletePtr(T*);		// ��� ������������� ����������� ������

public:
	unique_ptr(T*);	// �����������, ����������� ����� ���������
	unique_ptr(const unique_ptr &) = delete;	// ����������� �����������
	~unique_ptr();	// ����������

	unique_ptr& operator= (const unique_ptr&) = delete;	// �������� ������������
	T operator* ();	// �������� �������������
	T* release();	// ����������� �������� � ���������� ����� ���������.
};



template<class T>
inline bool unique_ptr<T>::ptrIsDynamic(T* _ptr)
{
	// abs - ����� �� �����, �� �� ������ ������
	// ���� ����� ������� ������� � ������� ��������� ����� 100 int
	// �� ������ ����� ������ ���������� � ������������ ������
	// �� ��� �� ����� ))
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
	// ������ � �� ���� ������� "������ �� ����������!"????
	if (!ptr) throw std::runtime_error("������ �� ����������!");
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

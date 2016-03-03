// MyShare_ptr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//Share_ptr MyShare_ptr 的实现 泛化MyShare_ptr  泛化Share_ptr 泛型编程
template <typename T>
class MyShare_ptr
{
	T* m_instant;
	int* m_pCnt;
public:

	T* getPtr() const
	{
		return m_instant;
	}
	int* getCnt() const{ return m_pCnt; }

	MyShare_ptr():m_instant(NULL), m_pCnt(new int(0)){}
	MyShare_ptr(T* rhsPtr)
	{
		m_instant = rhsPtr;
		m_pCnt = new int(1);
	}

	MyShare_ptr( MyShare_ptr& rhsPtr )
	{		
		m_instant = rhsPtr.m_instant;
		m_pCnt = rhsPtr.m_pCnt;
		int a = ++*m_pCnt;		
	}
	//泛化Copy构造函数
	template <typename Y>
	MyShare_ptr( MyShare_ptr<Y>& rhsPtr )
	{		
		m_instant = rhsPtr.getPtr();
		m_pCnt = rhsPtr.getCnt();
		int a = ++*m_pCnt;		
	}
	

	~MyShare_ptr()
	{
		release();
	}

	void release()
	{
		int a = --*m_pCnt;
		if ( a == 0 )
		{
			delete m_instant;
			m_instant = NULL;
			delete m_pCnt;
			m_pCnt = NULL;
		}
	}

	MyShare_ptr& operator = (MyShare_ptr& rhsPtr)
	{
		if ( this->m_instant == rhsPtr.m_instant )
		{
			return *this;
		}
		release();

		this->m_instant = rhsPtr.m_instant;
		this->m_pCnt = rhsPtr.m_pCnt;
		int a = ++*rhsPtr.m_pCnt;
		return *this;
	}

	//泛化赋值函数
	template <typename Y>
	MyShare_ptr& operator = (MyShare_ptr<Y>& rhsPtr)
	{
		if ( this->m_instant == rhsPtr.getPtr() )
		{
			return *this;
		}
		release();

		this->m_instant = rhsPtr.getPtr();
		this->m_pCnt = rhsPtr.getCnt();
		int a = ++*rhsPtr.getCnt();
		return *this;
	}


	MyShare_ptr& operator = (T* rhsPtr)
	{
		if ( this->m_instant == rhsPtr )
		{
			return *this;
		}
		release();
		m_instant = rhsPtr;
		m_pCnt = new int(1);		
		return *this;
	}

	T& operator * ( )//重载*号操作符
	{
		return *m_instant;
	}

	operator T* ( )//强制类型转换
	{
		return m_instant;
	}

	T* operator -> ( )
	{
		return m_instant;
	}


};



//使用示例
class Person
{
public:
	virtual void show(){printf("Person");}
};

class Student:public Person
{
public:
	virtual void show(){printf("Student");}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Person* pP = new Student;//可以, 正常指针的隐式转换

	//MyShare_ptr的隐式转换 泛化Copy构造函数
	MyShare_ptr<Student> spStu(new Student);
	MyShare_ptr<Person> spPerson(spStu);

	spStu->show();
	spPerson->show();


	//泛化赋值函数
	MyShare_ptr<Person> spPersonB(new Person);
	MyShare_ptr<Student> spStuB(new Student);

	spPersonB = spStuB;
	spStuB->show();
	spPersonB->show();

	


	system("PAUSE");
	return 0;
}


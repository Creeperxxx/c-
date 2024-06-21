#include <iostream>
using namespace std;

class student
{
public:				//自己可以访问类内，别人也可以访问类内
	int id;			
protected:			//自己可以访问类内，别人访问不了，但儿子可以
	int age;
private:			//只有自己类内可以访问
	int name;

public:
	//构造函数，用于初始化
	student()		
	{
		cout << "调用了student类的无参构造函数" << endl;
		age = 12;
	}//可以重载
	student(int a)
	{
		cout << "调用了student类的有参构造函数" << endl;
		age = a;
	}
	student(const student &s)//被拷贝者只读
	{
		cout << "调用了student类的拷贝构造" << endl;
		id = s.id;
		age = s.age;
		name = s.name;
	}
	//析构函数，一般用于处理堆区相关事
	~student()
	{
		cout << "调用了student类的析构函数" << endl;
	}//不可重载

};
//struct和class区别：默认访问权限不同，前者是公共，后者是私有

//浅拷贝和深拷贝
//浅拷贝就是普通拷贝
class example1
{
public:
	int age;
	int* height;
	example1(int age, int height)
	{
		this->age = age;
		this->height = new int(height);	//height数据存放在堆区
	}//原因：当属性中数据存放在堆区时，浅拷贝的直接复制致使复制双方的height指针指向同一区域

	example1(const example1 &e1)//不用系统提供的浅拷贝，自己设计拷贝函数解决问题
	{
		this->age = age;
		this->height = new int(*e1.height);//重新new一块区域存放height数据
	}
};

class example2//两种初始化操作
{
public:
	int a;
	int b;
	int c;
	example2() :a(10), b(20), c(30) {}
	example2(int a1, int b1, int c1) :a(a1), b(b1), c(c1) {}


};
void func1();
void func1(int a, char b);
void func1(char b, int a);
void func2(int& a);
void func2(const int& a);
void test01();
int main()
{
	func2(10);
	return 0;
}

//函数重载
void func1()
{
	cout << "这是无参数func1" << endl;
}

void func1(int a, char b)
{
	cout << "这是有参数func1" << endl;
}

void func1(char b, int a)
{
	cout << "这是有参数但颠倒顺序func1" << endl;
}
//重载条件：同作用域 同函数名 不同函数类型参数个数顺序等不同
//注意：返回值不同不是重载条件

void func2(int &a)
{
	cout << "func2(int a)" << endl;
}
void func2(const int &a)
{
	cout << "这是func2(const int &a)" << endl;
}//const也可以作为重载条件

void test01()//三种构造函数调用
{
	//1.括号调用
	student s1;
	student s2(10);
	student s3(s2);
	//调用默认构造函数时，不要加空括号
	//例如：student s1();   编辑器默认为函数声明

	//2.显示法
	student s4;
	student s5 = student(10);		//student(10)为匿名对象 s5即为其名
	student s6 = student(s5);		//这行执行完匿名对象立马释放

	//3.隐式法
	student s7 = 10;				//相当于s5那行
	student s8 = s7;				//相当于拷贝构造
}


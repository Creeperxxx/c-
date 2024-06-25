#include <iostream>
#include <fstream>

using namespace std;

//template<typename M>	函数模板	typename: 表示后面是数据类型 
template<class T>		//类模板		用class可以表示类或函数模板
//T为通用数据类型		必须紧跟着声明或实现
void test10(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
void test11();

template<class T>	//必须在紧跟的函数中确定T的数据类型
void test12()
{
	cout << "这在说明定义了模板T则必须确定T的数据类型" << endl;
}

template<class T>
void test13(T arr[],int len)
{
	for (int i = 0; i < len; i++)
	{
		int min = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[min] > arr[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			test10(arr[min],arr[i]);
		}
	}
}
template<class T>
void test14(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i];
	}
	cout << endl;
}
void test15()
{
	char arr[5] = { 'e','d','c','b','a'};
	test13(arr, 5);
	test14(arr, 5);
}
//普通函数和函数模板调用规则
//1.两者都可调用，则优先调用普通函数
//2.若要强制调用函数模板，则使用空模板参数(例：test16<>(a,b);)
//3.函数模板可以重载
//4.若模板匹配的更好，则调用函数模板
template<class T>
void test16(T a, T b)
{
	cout << "调用的函数模板" << endl;	
}
void test16(int a, int b)
{
	cout << "调用普通函数" << endl;
}
void test17();

class example14
{
public:
	int a;
	int b;
	example14(int a, int b)
	{
		this->a = a;
		this->b = b;
	}
};
template<typename T>
bool test18(T& a, T& b)//问题：当输入自定义数据类型时，运算符无法正常工作
{
	if (a == b)	//系统无法比较两个自定义类是否相等
	{
		return true;
	}
	else
	{
		return false;
	}
}
void test19();	//解决：如下函数 专门给某个自定义类将函数模板具体化
template<> bool test18(example14& a, example14& b)
{
	cout << "调用具体化模板" << endl;
	if (a.a == b.a && a.b == b.b)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//类模板
template<class atype,class btype>	//可以定义多个参数
class example15
{
public:
	atype a;
	btype b;
	example15(atype a, btype b)
	{
		this->a = a;
		this->b = b;
	}
};
void test20();

//类模板和函数模板区别：
//1.类模板没有自动类型推导，只能用显式指定类型
//2.类模板参数列表可以有默认参数(例：template<class atype=int>)
//	这样利用类创建变量时可以少指定类型 

//类模板和普通类 成员函数创建时机不同：
//类模板在调用时创建 普通类一开始便创建
//原因：类模板中T不明确，只有调用时T才明确
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
		id = 1;
		name = 2;
	}//可以重载
	student(int a)
	{
		cout << "调用了student类的有参构造函数" << endl;
		id = 1;
		name = 2;
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
		this->age = e1.age;
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

class example3		//静态成员变量
{
public:
	static int a;	//所有对象的静态成员变量共享一块空间 例：test02()
					//可以通过类名访问 例：cout<<example3::a;
	int b;
	static void func1()
	{
		a = 100;	//静态成员函数可以访问静态成员变量
		//b = 200;	//不可访问普通成员变量 原因：成员变量必须通过对象访问
	}
};					
int example3::a = 100;	//类外初始化 原因：编译时分配内存

class example4	//this指针和const
{
public:
	int a;
	example4(int a)//1.解决名称冲突
	{
		this->a = a;	 //this指向被调用的成员函数所属的对象
	}
	void func1() //const
	{
		this->a = 10;	//1.函数右边加const 函数不可修改成员变量
	}					//2.常对象不可调用普通函数 只能调用常函数
						//因为普通函数可以修改属性，违背了常
};

class example5		//友元：1.全局函数 2.类 3.成员函数
{
	friend void test03(example5* e);
	friend class example6;
public:
	int a;
	example5();
private:
	int b;
};
class example6
{
public:
	example5* e;
	example6();
	void visit();
};
void test03(example5* e);
void test04();

class example7	//运算符函数重载 1.全局函数重载 2.局部函数重载
{
public:
	int a;
	int b;
	example7(int a1 = 0, int b1 = 0) :a(a1), b(b1) {}
	example7 operator+(example7& e1)
	{
		example7 temp;
		temp.a = this->a + e1.a;
		temp.b = this->b + e1.b;
		return temp;
	}
	void operator()(string e1)	//重载() 伪函数
	{
		cout << e1 << endl;
	}
};
//example7 operator+(example7& e1, example7& e2);//全局重载
void test05();

class example8	//继承：1.public继承 2.protected继承 3.private继承
{				//1.pub继承：保留pub和pro 2.pro继承：转pub为pro 3.pri继承 pub,pro转pri
public:			//父类private可继承，但会隐藏
	int a;
protected:
	int b;
private:
	int c;
};
				
class example9	//动态多态
{				//条件：1.有继承关系 2.子类重写父类虚函数
public:			//使用：父类用指针或引用 执行子类对象
				//若不用，则以父类为形参传子类，调用同名函数时是父类的函数而不是子类重写的函数
	virtual void speak()	//virtual虚函数
	{					
		cout << "example9在调用speak()" << endl;
	}
};//总结：父类接收子类且调用子类重写函数 要在父类被重写函数前加virtual5s

class example10:public example9
{
public:
	void speak()
	{
		cout << "example10调用speak()" << endl;
	}
};
void test06(example9& e1);
void test07();

class example11	//纯虚函数和抽象类 
{
public:
	virtual void func() = 0;	//纯虚函数
};								//一旦有纯虚函数 则1.该类为抽象类 2.子类必须重写纯虚函数
								//若抽象类 则1.无法实例化对象 2.子类若不重写 则同为抽象类

class example12	//虚析构和纯虚析构	作用：必须调用子类析构函数时(数据开辟在堆区)
				//若不加，则只调用父类析构而不调用子类虚构
{
public:
	virtual void speak() = 0;
	example12()
	{
		cout << "example12的构造函数" << endl;
	}
	virtual ~example12()	//虚析构
	{
		cout << "example12的析构函数" << endl;
	}
	//virtual ~example12() = 0;		//纯虚析构	既要声明也要实现	且该类变为抽象类
										
};

class example13 :public example12
{
public:
	string* name;
	void speak()
	{
		cout << *name << "在说话" << endl;
	}
	example13(string name)
	{
		cout << "example13的构造函数" << endl;
		this->name = new string(name);
	}
	~example13()
	{
		if (name != NULL)
		{
			cout << "example13的析构函数" << endl;
			delete name;
			name = NULL;
		}
	}
};
void test08();	//子类开辟在堆区，父类指针接收
				//若直接delete父类，则不会触发子类析构函数
				// 解决办法：在父类析构前加virtual，则析构子，再析构父
//函数重载
void func1();
void func1(int a, char b);
void func1(char b, int a);
void func2(int& a);
void func2(const int& a);
//void 
//函数构造
void test01();
void test02();//不同对象的静态属性占同一片空间
//文件操作
void test09();

int main()
{
	test20();
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

void test02()
{
	example3 e1;
	cout << e1.a << endl;	//输出e1.a，得100
	example3 e2;
	e2.a = 200;				//修改e2.a
	cout << e1.a << endl;	//依旧输出e1.a,得200(e2.a)
	//结论：该类创建的对象，静态成员变量共享同一块空间
}

void test03(example5* e)
{
	cout << e->a << endl;
	cout << e->b << endl;	//因为全局函数友元声明即可访问私有b
}

void test04()
{
	example6 e1;
	e1.visit();
}

example5::example5()
{
	a = 1;
	b = 2;
}
example6::example6()
{
	e = new example5;
}

void example6::visit()
{
	cout << e->a << endl;
	cout << e->b << endl;
}

example7 operator+(example7& e1, example7& e2)
{
	example7 temp;
	temp.a = e1.a + e2.a;
	temp.b = e1.b + e2.b;
	return temp;
}

void test05()
{
	example7 e1(10, 10);
	example7 e2(20, 20);
	example7 e3;
	//e3 = e1 + e2;		
	cout << e3.a << " " << e3.b << endl;
	e3 = e1.operator+(e2);
	cout << e3.a << " " << e3.b << endl;
	e3("hello world");//伪函数 
}

void test06(example9& e1)
{
	e1.speak();
}

void test07()
{
	example9 e1;
	example10 e2;
	test06(e2);
}

void test08()
{
	example12* e12 = new example13("tom");
	e12->speak();
	delete e12;
}

void test09()
{
	ofstream ofs;
	/*ofs.open("test.txt", ios::out);
	ofs << "这是第一行内容" << endl;
	ofs << "这是第二行内容" << endl;*/
	ofs.close();

	ifstream ifs;
	/*ifs.open("test.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "打开失败" << endl;
		return;
	}
	char buff[1024] = { 0 };*/

	/*while (ifs >> buff)
	{
		cout << buff << endl;
	}*/
	
	/*while (ifs.getline(buff, sizeof(buff)))
	{
		cout << buff << endl;
	}*/
	ifs.close();
	//string name = "xiao";
	//ofstream ofs1("xiao.txt", ios::out | ios::binary);
	//ofs1.write((const char*)&name, sizeof(name));//2进制模式用write
	/*ofs1.close();*/

	ifstream ifs1("xiao.txt", ios::in | ios::binary);
	if (!ifs1.is_open())
	{
		cout << "打开失败" << endl;
		return;
	}
	string name1;
	ifs1.read((char*)&name1, sizeof(name1));
	cout << name1 << endl;
	ifs.close();

}

void test11()
{
	int a = 1;
	int b = 2;
	//1.自动推导T为int
	test10(a, b);
	//手动赋值T为int
	test10<int>(a, b);	//可以发生隐式类型转化，也就是即使指定int也可以传char等
}

void test17()
{
	int a = 0;
	int b = 0;
	test16<>(a, b);
}

void test19()
{
	int a = 10;
	int b = 20;
	cout << test18(a, b) << endl;

	example14 a1(1, 1);
	example14 b1(1, 1);
	cout << test18(a1, b1) << endl;
}

void test20()
{
	example15<string,int> e1("xiao", 12);
	cout << e1.a << " " << e1.b << endl;
}
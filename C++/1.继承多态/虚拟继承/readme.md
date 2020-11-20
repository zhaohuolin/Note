## 虚拟继承

多继承下的二义性：在多继承方式下，派生类继承了多个基类的成员，当两个不同基类拥有同名成员时，容易产生名字冲突问题。因此，虚拟继承要解决的就是二义性。

虚拟继承引入的原因：重复基类，派生类间接继承同一基类使得间接基类（Person）在派生类中有多份拷贝，引发二义性。

1、虚拟继承virtual inheritance的定义 语法 class derived_class : virtual […] base_class 虚基类virtual base class 被虚拟继承的基类 在其所有的派生类中，仅出现一次

2、虚拟继承的构造次序 虚基类的初始化与一般的多重继承的初始化在语法上是一样的，但构造函数的调用顺序不同； 若基类由虚基类派生而来，则派生类必须提供对间接基类的构造（即在构造函数初始列表中构造虚基类，无论此虚基类是直接还是间接基类） 调用顺序的规定： 先调用虚基类的构造函数，再调用非虚基类的构造函数 若同一层次中包含多个虚基类,这些虚基类的构造函数按它们的说明的次序调用 若虚基类由非基类派生而来,则仍然先调用基类构造函数,再调用派生类构造函数 3、虚基类由最终派生类初始化 在没有虚拟继承的情况下，每个派生类的构造函数只负责其直接基类的初始化。但在虚拟继承方式下，虚基类则由最终派生类的构造函数负责初始化。 在虚拟继承方式下，若最终派生类的构造函数没有明确调用虚基类的构造函数，编译器就会尝试调用虚基类不需要参数的构造函数（包括缺省、无参和缺省参数的构造函数），如果没找到就会产生编译错误。



```C++
#include<iostream>
using namespace std;
class A { 
    public:	
	    void vf() 
        {
	    	cout<<"I come from class A"<<endl;	
        }
};
class B: virtual public A{};
class C: virtual public A{};
class D: virtual public B, virtual public C{};

int main()
{
	D d;
	d.vf ();	// 删除 virtual 之后不可运行
    system("pause");
    return 0;
}
```



3.派生类的初始化：

```C++
#include <iostream>
using namespace std;
class A {
    int a;
public: 
    A(int x) {
        a=x;
        cout<<"Virtual Bass A..." << " " << a << endl; 
    }
}; 
class B:virtual public A {
public: 
    B(int i):A(i){ cout<<"Virtual Bass B..." << endl; }
};
class C:virtual public A{
    int x;
public:
    C(int i):A(i){
        cout<<"Constructing C..."  << endl;
        x=i; 
    }
};
class ABC:public C, public B {
public: 
    //虚基类由最终派生类初始化 
    ABC(int i,int j,int k):C(i),B(j),A(i) //L1，这里必须对A进行初始化
        { cout << "Constructing ABC..." << endl; }
}; 
int main(){
    ABC obj(1,2,3);
    // system("pause");
    return 0;
}
```

**4. 虚基类调用次序(重要)**

```C++
//ÖØÒª!!!
#include <iostream>
using namespace std;
class A {
    int a;
public: 
    A(){ cout<<"Constructing A"<<endl; }
}; 
class B {
public: 
    B(){ cout<<"Constructing B"<<endl;}
}; 
class B1:virtual public B ,virtual public A{
public: 
    B1(int i){ cout<<"Constructing B1"<<endl; }
}; 
class B2:public A,virtual public B {
public: 
    B2(int j){ cout<<"Constructing B2"<<endl; }
};
class D: public B1, public B2 {
public:
    D(int m,int n): B1(m),B2(n){ cout<<"Constructing D"<<endl; }
    A a;
}; 
    
int main(){
    D d(1,2);
    system("pause");
    return 0;
}

// ？问题：为什么B2前面没有B的构造调用
/*
Constructing B
Constructing A
Constructing B1
Constructing A
Constructing B2
Constructing A  // A 居然在D的前面？
Constructing D
*/
```


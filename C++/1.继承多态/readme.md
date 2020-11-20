## 直接基类与间接基类

一、构造函数和析构函数的构造规则

1. 派生类可以不定义构造函数的情况 当具有下述情况之一时，派生类可以不定义构造函数。 基类没有定义任何构造函数。 基类具有缺省参数的构造函数。 基类具有无参构造函数。 

2. 派生类必须定义构造函数的情况 当基类或成员对象所属类只含有带参数的构造函数时，即使派生类本身没有数据成员要初始化，它也必须定义构造函数，并以构造函数初始化列表的方式向基类和成员对象的构造函数传递参数，以实现基类子对象和成员对象的初始化。 

3. 派生类的构造函数只负责直接基类的初始化

C++语言标准有一条规则：如果派生类的基类同时也是另外一个类的派生类，则每个派生类只负责它的直接基类的构造函数调用。 这条规则表明当派生类的直接基类只有带参数的构造函数，但没有默认构造函数时（包括缺省参数和无参构造函数），它必须在构造函数的初始化列表中调用其直接基类的构造函数，并向基类的构造函数传递参数，以实现派生类对象中的基类子对象的初始化。 这条规则有一个例外情况，当派生类存在虚基类时，所有虚基类都由最后的派生类负责初始化。

总结： 

（1）当有多个基类时，将按照它们在继承方式中的声明次序调用，与它们在构造函数初始化列表中的次序无关。当基类A本身又是另一个类B的派生类时，则先调用基类B的构造函数，再调用基类A的构造函数。

（2）当有多个对象成员时，将按它们在派生类中的声明次序调用，与它们在构造函数初始化列表中的次序无关。

（3）当构造函数初始化列表中的基类和对象成员的构造函数调用完成之后，才执行派生类构造函数体中的程序代码。

```C++
//当同时存在直接基类和间接基类时，每个派生类只负责其直接基类的构造。
#include <iostream>
using namespace std;
class A { 
    int x;
public: 
    A(int aa) {
        x=aa;
        cout<<"Constructing A"<<endl;
    }
    ~A(){ cout<<"Destructing A"<<endl; }
};
class B:public A {
public: 
    B(int x):A(x){ cout<<"Constructing B"<<endl; }
};
class C :public B{
public: 
    C(int y):B(y){ cout<<"Constructing C"<<endl; }
};
int main(){
    C c(1);
    system("pause");
}
```



## 构造函数与析构函数

### 构造函数的调用顺序

1. 基类构造顺序由派生层次决定：**最远的基类最先构造** ，成员构造顺序和定义顺序符合 

2. **析构函数**的析构顺序与构造顺序相反；

3. 没有构造函数的派生类也会调用基类的构造函数；如果基类构造函数需要参数，那么派生类就必须要有构造函数去传参给基类构造函数；

4. 派生类构造函数 派生类可能有多个基类，也可能包括多个成员对象，在创建派生类对象时，派生类的构造函数除了要负责本类成员的初始化外，还要调用基类和成员对象的构造函数，并向它们传递参数，以完成基类子对象和成员对象的建立和初始化。派生类构造函数的参数传递给基类构造初始化  `Son(int a,int b,int l):Father(a,b)`

   

   构造顺序：

   ​	**基类 --> 按定义顺序的成员 --> 自身**

   析构顺序：

   ​	**自身 --> 按定义顺序的成员 --> 基类**

   

   **注**：**派生类只能采用构造函数初始化列表的方式向基类或成员对象的构造函数传递参数**，形式如下：

   派生类构造函数名(参数表):基类构造函数名(参数表),成员对象名1(参数表),…{ //…… }

   即：`D( ) : B(1),a4(4),c2(2),c1(1)`

   ```C++
   //Eg6-12.cpp
   #include <iostream>
   using namespace std;
   class A {
       int x;
   public:
        A(int i=0) {
            x=i;
            cout << "A-----"<<x<<endl;
        }
   };
   class B {
       int y;
   public:
       B(int i) {
           y=i;
           cout << "B-----"<<y<<endl;
       } 
   }; 
   class C {
       int z;
   public:
       C(int i) {
           z=i;
           cout << "C-----"<<z<<endl;
       } 
   };
   class D : public B{
   public: 
       A *a1 = new A(10);
       C c1, c2;
       A a0,a4;
       D( ) : a4(4),c2(2),c1(1),B(1) {
   cout << "D-----5"<<endl;
       }
   };
   int main(){
       D d;
       system("pause");
   }
   
   /*
   B-----1
   A-----10
   C-----1
   C-----2
   A-----0
   A-----4
   D-----5
   */
   ```



## 基类与派生类对象的关系

> 基类对象与派生类对象之间存在赋值相容性。

包括以下几种情况：

*  把派生类对象赋值给基类对象。 
*  把派生类对象的地址赋值给基类指针。
*  用派生类对象初始化基类对象的引用。 

 反之则不行:

* 即不能把基类对象赋值给派生类对象；
* 不能把基类对象的地址赋值给派生类对象的指针；
* 也不能把基类对象作为派生对象的引用。



```c++
#include <iostream>
using namespace std;
class A {
    int a;
public: 
    void setA(int x){ a=x; }
    int getA(){ return a;} 
}; 
class B:public A{
    int b;
public: 
    void setB(int x){ b=x; }
    int getB(){ return b;} 
};
void f1(A a, int x)
{ a.setA(x); }      
void f2(A *pA, int x)
{ pA->setA(x); }
void f3(A &rA, int x)
{ rA.setA(x); }

int main(){
    A a1,*pA;
    B b1,*pB;
    a1.setA(1);
    b1.setA(2);
    //把派生类对象赋值给基类对象。
    a1=b1;                  
    cout<<a1.getA()<<endl;		
    cout<<b1.getA()<<endl; 		
    a1.setA(10);              
    cout<<a1.getA()<<endl;		
    cout<<b1.getA()<<endl;	
    //把派生类对象的地址赋值给基类指针。	 	
    pA=&b1;  
    pA->setA(20);            
    cout<<pA->getA()<<endl;	    
    cout<<b1.getA()<<endl;	
    //用派生类对象初始化基类对象的引用。
    A &ra=b1;                                    
    ra.setA(30);               
    cout<<pA->getA()<<endl;		
    cout<<b1.getA()<<endl;		    
    b1.setA(7);
    cout<<b1.getA()<<endl;		    
    f1(b1,100); 
    cout<<"1111111111"<<endl;
    cout<<b1.getA()<<endl;	//7	    
    f2(&b1,200);
    cout<<b1.getA()<<endl;		    
    f3(b1,300);
    cout<<b1.getA()<<endl;		
    system("pause");
    return 0;
}

/*
2
2 
10
2
20
20
30
30
7
1111111111
7
200
300
*/
```



## 继承访问权限

**一、公有继承 --public**

1. 基类中protected的成员 类内部：可以访问 ; 类对象：不能访问 ; 类的派生类成员：可以访问 

2. 派生类不可访问基类的private成员 

   * 可通过基类的共有成员函数访问:

     ```C++
       
     #include<iostream>
     using namespace std;
     class base{
     	int x;
         public:
     	    void setx(int n){	x=n;	}
     	    int getx(){	return x;  }
     	    void showx(){ cout<<x<<endl; }
             void prt_Num(){ cout << num << endl;}
         private:
             int num = 10000;
     };
     //派生类
     class derived:public base{
     	int y;
         public:
     	    void sety(int n){	y=n;	}
     	    void sety(){	y=getx();    }
     	    void showy(){	cout<<y<<endl;   }
     };
     //派生类不可直接访问基类的private成员，可通过基类的共有成员函数访问
     int main()
     {	
         derived obj;
     	obj.setx(10);	
         obj.sety(20);
     	obj.showx();	
         obj.showy();
     	obj.sety();
     	obj.showx();	
         obj.showy();
         obj.prt_Num();
         system("pause");
     }
     ```

     

3. 派生类可访问基类的protected成员 

4. 派生类可访问基类的public成员

   ```C++
   /*
   基类中protected的成员
   类内部：可以访问
   类的使用者：不能访问
   类的派生类成员：可以访问
   */
   #include<iostream>
   class B
   {	
       private: 
           int i;
   	protected: 
           int j;
   	public: 
           int k;
   };
   class D: public B
   {
   	public:
   		void f() 
           {	
           	i=1;//cannot access 派生类不可访问基类私有成员
   			j=2;//派生类可以访问基类保护成员	
           	k=3;	
           }
   };
   int main()
   {	
       B b; 
   	b.i=1;//cannot access 私有成员，类的使用者不能访问
   	b.j=2; //cannot access 保护成员，类的使用者不能访问
   	b.k=3;
       system("pause");
       return 0;
   }
   ```

   

**二、私有继承 -- private** 

1. 派生类对象不可访问基类的任何成员与函数，但是可以通过给派生类设计一个接口实现访问

   ```C++
   #include <iostream>
   using namespace std;
   class Base{
       
       public:
           int x;
           Base(int x) : x(x) {}
   
           void setx(int n){ x=n; }
           int getx(){ return x; }
           void showx(){ cout<<x<<endl; }
   };
   //私有继承
   //基类的中的public成员在派生类中是private, private成员在派生类对象中不可访问，可以通过派生类方法访问。
   class derived:private Base{
   	int y;
       public:
           derived(int x) : Base(x) { }
   	    void sety(int n){ y=n; }
   	    void sety(){ y=getx(); }
   	    void showy(){ cout<<y<<endl; }
           void pri_Num(){ cout << x << endl; }
   };
   int main(){
   	derived obj(12138);
   	// obj.setx(10);//cannot access
   	obj.sety(20);
       obj.pri_Num();
   	// obj.showx();//cannot access
   	obj.showy();	
   }
   
   ```

   

**三、保护继承 -- protected** 

1. 派生方式为protected的继承称为保护继承，在这种继承方式下， 基类的public成员在派生类中会变成protected成员， 基类的protected和private成员在派生类中保持原来的访问权限 。**注意点：当采用保护继承的时候，由于public成员变为protected成员，因此类的使用者(对象)不可访问！而派生类(类内方法)可访问！**，也就是可以通过派生类的对象调用 public 的方法(也就是接口函数) 实现对 protected 继承于基类的方法或者属性进行操作。 

   ```C++
   /*
   派生方式为protected的继承称为保护继承，在这种继承方式下，
   基类的public成员在派生类中会变成protected成员，
   基类的protected和private成员在派生类中保持原来的访问权限
   */
   #include <iostream>
   using namespace std;
   class Base{
       int x;
   protected:
       int getx(){ return x; }
   public:
       Base(int x):x(x){}
       void setx(int n){ x=n; }
       void showx(){ cout<<x<<endl; }
   };
   class Derived:protected Base{
       int y;
   public:
       Derived(int x):Base(x){}
       void sety(int n){ y=n; }
       void sety()
       { 
           y=getx();
           cout << y << endl;
           
       }   //访问基类的保护成员
       void showy(){ cout<<y<<endl; }
   };
   int main(){
       Derived obj(10);
       // obj.setx(10);    //错误
       obj.sety();
       obj.sety(20);
       // obj.showx();	 //错误， 
       obj.showy(); 
       //system("pause");   
   }
   
   /*
   解释：
   如最上面文字所示：保护继承会将基类的public变为protected，而对于protected成员，
   外部去使用保护成员的时候，会报错，所以setx与showx访问错误，而对于派生类，则可直接访问基类的保护成员，
   在派生类中，y=getx()可正常访问！
   */
   ```

   

**四、派生类对基类成员的访问形式  ** 

1. 通过派生类对象直接访问基类成员 
2. 在派生类成员函数中直接访问基类成员 -- 可以无视继承方式
3. 通过基类名字限定访问被重载的基类成员名



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


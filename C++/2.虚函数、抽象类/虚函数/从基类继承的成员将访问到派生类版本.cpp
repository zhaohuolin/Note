### 从基类继承的成员将访问到派生类版本.cpp

// 代码解析：

// 重载函数调用，无论虚否，在于你的对象类型，基类对象的方法就是基类的方法，派生类就是派生类的。

```C++
#include <iostream>
using namespace std;
class B{
	public: 
    	void f(){ g(); } 
    	virtual void g(){ cout << "B::g"; }
};
class D : public B{
	public: 
    	virtual void g(){ cout << "D::g\n"; }
};
int main(){
	B *b = new D;
	b->f();

	B B1;
	B1.f();
	cout << " " << endl;

    D d;
    d.f();
    // system("pause");
    return 0;
}

/*  
D::g
B::g
D::g
*/
```


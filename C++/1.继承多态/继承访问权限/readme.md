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
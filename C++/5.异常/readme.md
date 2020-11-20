## C++的异常处理

1.catch捕获异常时，不会进行数据类型的默认转换，其基本语法为。 

**异常处理的基本语法**

C++ 通过 throw 语句和 try...catch 语句实现对异常的处理。throw 语句的语法如下：

```C++
throw 表达式;
```

该语句拋出一个异常。异常是一个表达式，其值的类型可以是基本类型，也可以是类。

try...catch 语句的语法如下：

~~~C++
try {
  语句组
  throw 异常类型;  // 不是直接的int，char 。而是具体 1, 1.0, "sting",这样的具体类型值
}
catch(异常类型) {
  异常处理代码
}
...
catch(异常类型) {
  异常处理代码
}
~~~

需要注意的是：`throw 异常类型` 中的异常类型不是直接的 `int，char `。而是具体` 1, 1.0, "sting"`这样的具体类型值。

不妨把 try 和其后`{}`中的内容称作“try块”，把 catch 和其后`{}`中的内容称作“catch块”。

try...catch 语句的执行过程是：

- 执行 try 块中的语句，如果执行的过程中没有异常拋出，那么执行完后就执行最后一个 catch 块后面的语句，所有 catch 块中的语句都不会被执行；
- 如果 try 块执行的过程中拋出了异常，那么拋出异常后立即跳转到第一个“异常类型”和拋出的异常类型匹配的 catch 块中执行（称作异常被该 catch 块“捕获”），执行完后再跳转到最后一个 catch 块后面继续执行。

2.限制异常的方法

* 当一个函数声明中不带任何异常描述时，它可以抛出任何异常。例如：

~~~C++
int f(int,char);                 //函数f可以抛出任何异常

~~~

* 在函数声明的后面添加一个throw参数表，在其中指定函数可以抛出的异常类型。例如：

```C++
try{
    throw(10,"s");  //只允许抛出int和char异常。
}
```

- 指定throw限制表为不包括任何类型的空表，不允许函数抛出任何异常。如：

```C++
try{
	throw;//不允许抛出任何异常
}
```

3.捕获所有异常 在多数情况下，catch都只用于捕获某种特定类型的异常，但它也具有捕获全部异常的能力。其形式如下：

```
catch(…) {
    ……                        //异常处理代码
}
```

4.再次抛出异常 如是catch块无法处理捕获的异常，它可以将该异常再次抛出，使异常能够在恰当的地方被处理。再次抛出的异常不会再被同一个catch块所捕获，它将被传递给外部的catch块处理。要在catch块中再次抛出同一异常，只需在该catch块中添加不带任何参数的throw语句即可。 

5.异常的嵌套调用 try块可以嵌套，即一个try块中可以包括另一个try块，这种嵌套可能形成一个异常处理的调用链。



例子：

```C++
#include<iostream>
using namespace std;
int main(){
    cout<<"1--befroe try block..."<<endl;
    try{
        cout<<"2--Inside try block..."<<endl;
        throw (10, "s"); 
        // throw;  // 不允许抛出任何异常                     
        cout<<"3--After throw ...."<<endl;
    }
    catch(double i) { 		//½ö´ËÓëÀý10.1²»Í¬
        cout<<"4--In catch block1 .. an int type is.."<<i<<endl;
        throw;
    }
    catch(char const *s){
        cout << "char catch" << endl;
    }
    catch(...){
        cout << "char catch block1 .. an char * type  is .." << endl;
    }
    cout<<"5--After Catch...";
    system("pause");
    return 0;
}

/*
1--befroe try block...
2--Inside try block...
char catch
5--After Catch
*/
```


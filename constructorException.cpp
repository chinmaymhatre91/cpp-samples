#include <iostream>

class A 
{
public:
    A():a{5}
    {
        std::cout << "A constructor" << std::endl;
        //throw std::runtime_error("from A");
    }
    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
private:
    int a;
};

class B
{
public:
    B():b{10}
    {
        std::cout << "B constructor" << std::endl;
        //throw std::runtime_error("from B");
    }
    ~B()
    {
        std::cout << "B destructor" << std::endl;
    }
private:
    int b;
};

class C 
{
public:
    C():c{15}
    {
        std::cout << "C constructor" << std::endl;
        //throw std::runtime_error("from C");
    }
    ~C()
    {
        std::cout << "C destructor" << std::endl;
    }
private:
    int c;
};

class X
{
public:
    X()
    {
        std::cout << "X constructor" << std::endl;
        throw std::runtime_error("from X");
    }
    ~X()
    {
        std::cout << "X destructor" << std::endl;
    }

private:
    A oa;
    B ob;
    C oc;
};

int main(int argc, char** argv) 
{
    try
    {
        X ox; 
        
        return 0;
    }
    catch(std::runtime_error e)
    {
        std::cout << "Exception - " << e.what() << std::endl;
        throw;
    }
}

/*
---------------Output---------------
A constructor
B constructor
C constructor
X constructor
C destructor
B destructor
A destructor
Exception - from X
libc++abi: terminating with uncaught exception of type std::runtime_error: from X
Abort trap: 6
*/

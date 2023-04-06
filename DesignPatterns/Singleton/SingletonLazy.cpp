#include <iostream>
#include <mutex>

class SingletonLazy
{
public:
    SingletonLazy(SingletonLazy const&) = delete;
    SingletonLazy& operator=(SingletonLazy const&) = delete;
    
    void setValue(int newValue)
    {
        std::lock_guard<std::mutex> g(m);
        value = newValue;
    }
    int getValue()
    { 
        std::lock_guard<std::mutex> g(m);
        return value; 
    }
    static SingletonLazy* getInstance()
    {
        std::lock_guard<std::mutex> g(m);
        if (!instance)
        {
            instance = new SingletonLazy();
        }
        return instance;
    }

private:
    explicit SingletonLazy() : value{0} {}
    ~SingletonLazy() 
    {
        std::cout << "SigletonLazy destructor" << std::endl; 
    }

    int value;
    static std::mutex m;
    static SingletonLazy* instance;
};

std::mutex SingletonLazy::m;
SingletonLazy* SingletonLazy::instance = nullptr;

int main(int argc, char** argv)
{
    SingletonLazy *s1 = SingletonLazy::getInstance();
    s1->setValue(10);
    SingletonLazy *s2 = SingletonLazy::getInstance();
    std::cout << "Value-" << s2->getValue() << std::endl;

    return 0;
}

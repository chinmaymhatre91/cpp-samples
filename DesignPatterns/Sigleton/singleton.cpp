#include <iostream>
#include <mutex>

class Singleton 
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    
    static Singleton* getInstance() 
    {
        return &instance;
    }

    void setValue(int new_value)
    {
        std::lock_guard<std::mutex> g(m);
        value=new_value;
    }

    int getValue() 
    {
        std::lock_guard<std::mutex> g(m);
        return value;
    }

private:
    explicit Singleton() : value{0}
    {}
    ~Singleton()
    {
        std::cout << "Singleton destructor" << std::endl;
    }

    int value;
    static std::mutex m; 
    static Singleton instance;
};

std::mutex Singleton::m;
Singleton Singleton::instance;

int main() 
{
    Singleton* s1 = Singleton::getInstance();
    s1->setValue(10);
    Singleton* s2 = Singleton::getInstance();
    std::cout << "Value-" << s2->getValue() << std::endl;
    
    return 0;
}

#include <iostream>
#include <mutex>

class SingletonStaticLocal 
{
public:
    SingletonStaticLocal(const SingletonStaticLocal&) = delete;
    SingletonStaticLocal& operator=(const SingletonStaticLocal&) = delete;
    
    static SingletonStaticLocal* getInstance() 
    {
        std::cout << "SingletonStaticLocal getInstance start" << std::endl;
        // Static local variable initialization is thread-safe
        // and will be initialized only once.
        static SingletonStaticLocal instance{};
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
    explicit SingletonStaticLocal() : value{0}
    {
        std::cout << "SingletonStaticLocal destructor" << std::endl;
    }
    ~SingletonStaticLocal()
    {
        std::cout << "SingletonStaticLocal destructor" << std::endl;
    }

    int value;
    static std::mutex m; 
};

std::mutex SingletonStaticLocal::m;

int main() {
    SingletonStaticLocal* s1 = SingletonStaticLocal::getInstance();
    s1->setValue(10);
    SingletonStaticLocal* s2 = SingletonStaticLocal::getInstance();
    std::cout << "Value-" << s2->getValue() << std::endl;

    return 0;
}

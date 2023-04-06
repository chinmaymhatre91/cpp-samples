#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include "utils.h"

void foo(int time, std::promise<std::string> p)
{
    std::cout << "foo start, time - " << utils::getCurrentTime() << std::endl;
    p.set_value_at_thread_exit("return from foo set at time - " + utils::getCurrentTime());
    std::this_thread::sleep_for(std::chrono::seconds(time));
    std::cout << "foo end, time - " << utils::getCurrentTime() << std::endl;
}

void foo_throw(int time, std::promise<int> p)
{
    std::cout << "foo_throw start, time - " << utils::getCurrentTime() << std::endl; 
    try
    {
        //p.set_value(199);
        std::this_thread::sleep_for(std::chrono::seconds(time));
        throw std::runtime_error("from foo_throw at time - " + utils::getCurrentTime());
    }
    catch(...)
    {
        try
        {
            p.set_exception(std::current_exception());
        }
        catch(...)
        {
            std::cout << "exception while set_exception in foo_throw, time - " << utils::getCurrentTime() << std::endl;
        }
    }
    std::cout << "foo_throw end, time - " << utils::getCurrentTime() << std::endl; 
}

int main(int argc, char** argv) 
{
    std::cout << "Start, time - " << utils::getCurrentTime() << std::endl;
    std::promise<std::string> p1;
    std::future<std::string> f1 = p1.get_future();
    std::thread t1(foo, 10, std::move(p1));
    std::cout << "Thread t1 created, time - " << utils::getCurrentTime() << std::endl;
    std::promise<int> p2;
    std::future<int> f2 = p2.get_future();
    std::thread t2(foo_throw, 5, std::move(p2));
    std::cout << "Thread t2 created, time - " << utils::getCurrentTime() << std::endl;
    
    try
    {
        std::cout << "calling f1.get(), time - " << utils::getCurrentTime() << std::endl; 
        auto res1 = f1.get();
        std::cout << "foo return, f1.get() - \"" << res1 << "\", time - " << utils::getCurrentTime() << std::endl;
        std::cout << "calling f2.get(), time - " << utils::getCurrentTime() << std::endl; 
        auto res2 = f2.get();
        std::cout << "foo_throw return, f2.get() - \"" << res2 << "\", time - " << utils::getCurrentTime() << std::endl; 
    }
    catch(const std::runtime_error& e)
    {
        std::cout << "caught exception, e.what() - " << e.what() << ", time - " << utils::getCurrentTime() << std::endl;
    }

    t1.join();
    t2.join();
    
    std::cout << "End, time - " << utils::getCurrentTime() << std::endl;
    
    return 0;
}

#include <iostream>
#include <thread>
#include <chrono>
#include "utils.h"

void foo(int count, bool& running) 
{
    while(running && count>=0)
    {
	    std::cout << "Thread foo running, count - " << count << ", time - " << utils::getCurrentTime() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --count;
    }
}

int main(int argc, char** argv) 
{
    std::cout << "Start, time - " << utils::getCurrentTime() << std::endl;
    bool running = true;
    std::thread t1(foo, 10, std::ref(running));
    std::this_thread::sleep_for(std::chrono::seconds(5));
    running = false;
    t1.join();
    std::cout << "End, time - " << utils::getCurrentTime() << std::endl;
    return 0;
}

/*
---------------Output---------------
Start, time - 04/06/23 01:33:16
Thread foo running, count - 10, time - 04/06/23 01:33:16
Thread foo running, count - 9, time - 04/06/23 01:33:17
Thread foo running, count - 8, time - 04/06/23 01:33:18
Thread foo running, count - 7, time - 04/06/23 01:33:19
Thread foo running, count - 6, time - 04/06/23 01:33:20
End, time - 04/06/23 01:33:21
*/

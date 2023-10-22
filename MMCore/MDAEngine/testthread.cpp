#include <thread>
#include <iostream>

using namespace std;

class MDAEvent
{
    public:
    MDAEvent();
    void test();
    void runner();
};

MDAEvent::MDAEvent()
{
    std::cout << "MDAEvent constructor" << std::endl;
}

void MDAEvent::test()
{
    std::cout << "MDAEvent test" << std::endl;
}

void MDAEvent::runner()
{
    std::thread t1(&MDAEvent::test, this);
    std::cout << "MDAEvent runner" << std::endl;
    t1.join();
}

int main()
{
    MDAEvent event;
    event.runner();
    return 0;
}
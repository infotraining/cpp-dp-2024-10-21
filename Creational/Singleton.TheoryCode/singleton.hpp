#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <iostream>

class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton& instance()
    {        
        static Singleton unique_instance;

        return unique_instance;
    }

    void do_something();

private:    
    Singleton() // disallows creation of new instances outside the class
    {
        std::cout << "Constructor of singleton" << std::endl;
    }

    ~Singleton()
    {
        std::cout << "Singleton has been destroyed!" << std::endl;
    }
};

void Singleton::do_something()
{
    std::cout << "Singleton instance at " << std::hex << &instance() << std::endl;
}

#endif /*SINGLETON_HPP_*/

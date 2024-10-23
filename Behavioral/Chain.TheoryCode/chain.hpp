#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <iostream>
#include <memory>
#include <string>

// "Handler"
class Handler
{
protected:
    std::shared_ptr<Handler> successor_;

public:
    Handler() : successor_{nullptr} {}

    void set_successor(std::shared_ptr<Handler> successor)
    {
        successor_ = successor;
    }

    void handle_request(int request) // Template Method Pattern
    {
        if (can_handle(request))
        {
            if (process_request(request))
                return;
        }
        else if (successor_ != nullptr)
            successor_->handle_request(request);
    }

    virtual ~Handler() = default;
protected:
    virtual bool can_handle(int request) = 0;
    virtual bool process_request(int request) = 0;
};

// "ConcreteHandler1"
class ConcreteHandler1 : public Handler
{
    bool can_handle(int request) override
    {
        return (request >= 0) && (request < 10);
    }

    bool process_request(int request) override
    {
        std::cout << "ConcreteHandler1 handled request " << request << std::endl;

        return false;
    }
};

// "ConcreteHandler2"
class ConcreteHandler2 : public Handler
{
    bool can_handle(int request) override
    {
        return (request >= 10) && (request < 20);
    }

    bool process_request(int request) override
    {
        std::cout << "ConcreteHandler2 handled request " << request << std::endl;

        return true;
    }
};

// "ConcreteHandler3"
class ConcreteHandler3 : public Handler
{
    bool can_handle(int request) override
    {
        return (request >= 20) && (request < 30);
    }

    bool process_request(int request) override
    {
        std::cout << "ConcreteHandler3 handled request " << request << std::endl;

        return true;
    }
};

#endif /*CHAIN_HPP_*/

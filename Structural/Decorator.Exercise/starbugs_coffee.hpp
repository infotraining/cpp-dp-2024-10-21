#ifndef COFFEEHELL_HPP_
#define COFFEEHELL_HPP_

#include <iostream>
#include <memory>
#include <string>

class Coffee
{
public:
    virtual ~Coffee() = default;

    virtual float get_total_price() const = 0;
    virtual std::string get_description() const = 0;
    virtual void prepare() = 0;
};

class CoffeeBase : public Coffee
{
    float price_;
    std::string description_;

public:
    CoffeeBase(float price, const std::string& description)
        : price_{price}
        , description_{description}
    {
    }

    float get_total_price() const override
    {
        return price_;
    }

    std::string get_description() const override
    {
        return description_;
    }
};

class Espresso : public CoffeeBase
{
public:
    Espresso(float price = 4.0, const std::string& description = "Espresso")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect espresso: 7 g, 15 bar and 24 sec.\n";
    }
};

class Cappuccino : public CoffeeBase
{
public:
    Cappuccino(float price = 6.0, const std::string& description = "Cappuccino")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect cappuccino.\n";
    }
};

class Latte : public CoffeeBase
{
public:
    Latte(float price = 8.0, const std::string& description = "Latte")
        : CoffeeBase{price, description}
    {
    }

    void prepare() override
    {
        std::cout << "Making a perfect latte.\n";
    }
};

class CoffeeAddition : public CoffeeBase
{
protected:
    std::shared_ptr<Coffee> coffee_;

public:
    CoffeeAddition(std::shared_ptr<Coffee> coffee, float price, const std::string& description)
        : CoffeeBase(price, description)
        , coffee_(coffee)
    {
    }

    void set_coffe(std::shared_ptr<Coffee> coffee)
    {
        coffee_ = coffee;
    }

    void prepare() override
    {
        coffee_->prepare();
    }

    float get_total_price() const override
    {
        return coffee_->get_total_price() + CoffeeBase::get_total_price();
    }

    std::string get_description() const
    {
        return coffee_->get_description() + " + " + CoffeeBase::get_description();
    }
};

class Whipped : public CoffeeAddition
{
    // float extra_price_ = 2.5;
    // std::string extra_description_ = " with whipped cream";

public:
    Whipped(std::shared_ptr<Coffee> coffee, float price = 2.5, std::string description = "Whipped Cream")
        : CoffeeAddition(coffee, price, std::move(description))
    {
    }

    void prepare() override
    {
        coffee_->prepare();
        std::cout << "Adding whipped cream.\n";
    }    
};

class Whisky : public CoffeeAddition
{    
public:
    Whisky(std::shared_ptr<Coffee> coffee, float price = 6.0, std::string description = "Whisky")
        : CoffeeAddition(coffee, price, std::move(description))
    {
    }

    void prepare() override
    {
        coffee_->prepare();
        std::cout << "Adding some of the good (Irish) stuff.\n";
    }
};

class ExtraEspresso : public CoffeeAddition
{
    float extra_price_ = 4;
    std::string extra_description_ = " with extra espresso";

public:
    ExtraEspresso(std::shared_ptr<Coffee> coffee, float price = 6.0, std::string description = "Whisky")
        : CoffeeAddition(coffee, price, std::move(description))
    {
    }

    void prepare() override
    {
        coffee_->prepare();
        std::cout << "Adding extra espresso.\n";
    }
};
// TO DO: Condiments: Whipped: 2.5$, Whisky: 6.0$, ExtraEspresso: 4.0$

// TO DO: Add CoffeeDecorator and concrete decorators for condiments

#endif /*COFFEEHELL_HPP_*/

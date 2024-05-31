#include <iostream>

// Abstract base class for the beverage making process
class BeverageMaker
{
public:
  // Template method that defines the overall process
  void makeBeverage()
  {
    boilWater();
    brew();
    pourInCup();
    addCondiments();
  }

  // Abstract methods to be implemented by subclasses
  virtual void brew() = 0;
  virtual void addCondiments() = 0;

  // Common methods used by all subclasses
  void boilWater()
  {
    std::cout << "Boiling water..." << std::endl;
  }

  void pourInCup()
  {
    std::cout << "Pouring beverage into cup..." << std::endl;
  }
};

// Concrete subclass for making coffee
class CoffeeMaker : public BeverageMaker
{
public:
  void brew() override
  {
    std::cout << "Brewing coffee..." << std::endl;
  }

  void addCondiments() override
  {
    std::cout << "Adding sugar and milk to coffee..." << std::endl;
  }
};

// Concrete subclass for making tea
class TeaMaker : public BeverageMaker
{
public:
  void brew() override
  {
    std::cout << "Steeping tea leaves..." << std::endl;
  }

  void addCondiments() override
  {
    std::cout << "Adding lemon to tea..." << std::endl;
  }
};

int main()
{
  // Create a coffee maker and make coffee
  CoffeeMaker coffeeMaker;
  coffeeMaker.makeBeverage();

  std::cout << std::endl;

  // Create a tea maker and make tea
  TeaMaker teaMaker;
  teaMaker.makeBeverage();

  return 0;
}

/*
For the Turkish Delight Café ordering system:

• Turkish Delight Café has added tea to the menu:
  – Assume we want to reflect the process of making a beverage: MakeCoffee and MakeTea
  – Draw a class diagram reflecting the Template Method Pattern for the beverage making process.

• Implement the above design within your Turkish Delight Café program.
*/
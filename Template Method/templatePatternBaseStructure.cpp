#include <iostream>

// Abstract base class defining the template method
class AbstractClass
{
public:
  // Template method
  void templateMethod()
  {
    // Call the primitive operations in a specific order
    operation1();
    operation2();
    operation3();
  }

private:
  // Primitive operations to be implemented by subclasses
  virtual void operation1() = 0;
  virtual void operation2() = 0;

  // Default implementation of operation3 // this operation is same for all subclasses that means this operation is template method
  void operation3()
  {
    std::cout << "Default implementation of operation3" << std::endl;
  }
};

// Concrete subclass implementing the primitive operations
class ConcreteClass : public AbstractClass
{
private:
  void operation1() override
  {
    std::cout << "ConcreteClass: operation1" << std::endl;
  }

  void operation2() override
  {
    std::cout << "ConcreteClass: operation2" << std::endl;
  }
};

int main()
{
  // Create an instance of the concrete class
  ConcreteClass concreteObj;

  // Call the template method
  concreteObj.templateMethod();

  return 0;
}
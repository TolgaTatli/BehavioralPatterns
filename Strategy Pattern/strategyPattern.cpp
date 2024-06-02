#include <iostream>

// Abstract base class for strategies
class Strategy {
public:
  virtual void execute() = 0;
};

// Concrete strategy classes
class ConcreteStrategyA : public Strategy {
public:
  void execute() override {
    std::cout << "Executing strategy A" << std::endl;
    // Add your implementation here
  }
};

class ConcreteStrategyB : public Strategy {
public:
  void execute() override {
    std::cout << "Executing strategy B" << std::endl;
    // Add your implementation here
  }
};

// Context class that uses the strategy
class Context {
private:
  Strategy* strategy;

public:
  Context(Strategy* strategy) : strategy(strategy) {}

  void setStrategy(Strategy* strategy) {
    this->strategy = strategy;
  }

  void executeStrategy() {
    strategy->execute();
  }
};

int main() {
  // Create the strategies
  ConcreteStrategyA strategyA;
  ConcreteStrategyB strategyB;

  // Create the context with a default strategy
  Context context(&strategyA);

  // Execute the strategy
  context.executeStrategy();

  // Change the strategy dynamically
  context.setStrategy(&strategyB);
  context.executeStrategy();

  return 0;
}
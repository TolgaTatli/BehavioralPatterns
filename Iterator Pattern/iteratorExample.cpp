#include <iostream>
#include <vector>

// Abstract base class for different strategies
class PaymentStrategy {
public:
  virtual void pay(double amount) = 0;
};

// Concrete strategy classes
class CreditCardStrategy : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Paying $" << amount << " with credit card." << std::endl;
    // Add code to process credit card payment
  }
};

class PayPalStrategy : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Paying $" << amount << " with PayPal." << std::endl;
    // Add code to process PayPal payment
  }
};

class CashStrategy : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Paying $" << amount << " in cash." << std::endl;
    // Add code to process cash payment
  }
};

// Context class that uses the strategy
class ShoppingCart {
private:
  std::vector<double> items;
  PaymentStrategy* paymentStrategy;

public:
  void addItem(double price) {
    items.push_back(price);
  }

  void setPaymentStrategy(PaymentStrategy* strategy) {
    paymentStrategy = strategy;
  }

  void checkout() {
    double total = 0;
    for (double price : items) {
      total += price;
    }

    paymentStrategy->pay(total);
  }
};

int main() {
  ShoppingCart cart;
  cart.addItem(10.99);
  cart.addItem(5.49);
  cart.addItem(7.99);

  // Set the payment strategy dynamically based on user input or other conditions
  PaymentStrategy* strategy = new CreditCardStrategy();
  cart.setPaymentStrategy(strategy);

  cart.checkout();

  delete strategy;

  return 0;
}
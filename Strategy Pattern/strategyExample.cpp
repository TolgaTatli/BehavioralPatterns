#include <iostream>

// Abstract base class for different payment strategies
class PaymentStrategy {
public:
  virtual void pay(double amount) = 0;
};

// Concrete strategy classes
class CreditCardPayment : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Paying $" << amount << " with credit card" << std::endl;
    // Add specific implementation for credit card payment here
  }
};

class PayPalPayment : public PaymentStrategy {
public:
  void pay(double amount) override {
    std::cout << "Paying $" << amount << " with PayPal" << std::endl;
    // Add specific implementation for PayPal payment here
  }
};

// Context class that uses the payment strategy
class ShoppingCart {
private:
  PaymentStrategy* paymentStrategy;

public:
  ShoppingCart(PaymentStrategy* paymentStrategy) : paymentStrategy(paymentStrategy) {}

  void setPaymentStrategy(PaymentStrategy* paymentStrategy) {
    this->paymentStrategy = paymentStrategy;
  }

  void checkout(double amount) {
    paymentStrategy->pay(amount);
  }
};

int main() {
  // Create payment strategies
  CreditCardPayment creditCardPayment;
  PayPalPayment payPalPayment;

  // Create shopping cart with initial payment strategy
  ShoppingCart cart(&creditCardPayment);

  // Checkout with initial payment strategy
  cart.checkout(100.0);

  // Change payment strategy dynamically
  cart.setPaymentStrategy(&payPalPayment);

  // Checkout with new payment strategy
  cart.checkout(50.0);

  return 0;
}
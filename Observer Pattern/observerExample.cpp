#include <iostream>
#include <vector>
#include <algorithm>

// Abstract Observer class
class Observer
{
public:
  virtual void update() = 0;
};

// Concrete Observer classes
class ConcreteObserverA : public Observer
{
public:
  void update() override
  {
    std::cout << "ConcreteObserverA has been notified!" << std::endl;
  }
};

class ConcreteObserverB : public Observer
{
public:
  void update() override
  {
    std::cout << "ConcreteObserverB has been notified!" << std::endl;
  }
};

// Subject class
class Subject
{
private:
  std::vector<Observer *> observers;

public:
  void attach(Observer *observer)
  {
    observers.push_back(observer);
  }

  void detach(Observer *observer)
  {
    // Find and remove the observer from the vector
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
      observers.erase(it);
    }
  }

  void notify()
  {
    // Notify all observers
    for (auto observer : observers)
    {
      observer->update();
    }
  }
};

int main()
{
  // Create subject and observers
  Subject subject;
  ConcreteObserverA observerA;
  ConcreteObserverB observerB;

  // Attach observers to the subject
  subject.attach(&observerA);
  subject.attach(&observerB);

  // Notify observers
  subject.notify();

  // Detach observerA from the subject
  subject.detach(&observerA);

  // Notify observers again
  subject.notify();

  return 0;
}
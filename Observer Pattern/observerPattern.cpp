#include <iostream>
#include <vector>
#include <algorithm>

// Forward declaration of the Observer interface
class Observer;

// Subject interface
class Subject
{
public:
  virtual void attach(Observer *observer) = 0;
  virtual void detach(Observer *observer) = 0;
  virtual void notify() = 0;
};

// Observer interface
class Observer
{
public:
  virtual void update() = 0;
};

// Concrete Subject
class ConcreteSubject : public Subject
{
private:
  std::vector<Observer *> observers;
  int state;

public:
  void attach(Observer *observer) override
  {
    observers.push_back(observer);
  }

  void detach(Observer *observer) override
  {
    // Find and remove the observer from the vector
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
      observers.erase(it);
    }
  }

  void notify() override
  {
    // Notify all observers
    for (auto observer : observers)
    {
      observer->update();
    }
  }

  void setState(int newState)
  {
    state = newState;
    notify(); // Notify observers when the state changes
  }

  int getState() const
  {
    return state;
  }
};

// Concrete Observer
class ConcreteObserver : public Observer
{
private:
  ConcreteSubject *subject;

public:
  ConcreteObserver(ConcreteSubject *subject) : subject(subject) {}

  void update() override
  {
    int state = subject->getState();
    std::cout << "Observer received update. New state: " << state << std::endl;
  }
};

int main()
{
  // Create subject and observers
  ConcreteSubject subject;
  ConcreteObserver observer1(&subject);
  ConcreteObserver observer2(&subject);

  // Attach observers to the subject
  subject.attach(&observer1);
  subject.attach(&observer2);

  // Change the state of the subject
  subject.setState(42);

  // Detach an observer
  subject.detach(&observer2);

  // Change the state again
  subject.setState(99);

  return 0;
}
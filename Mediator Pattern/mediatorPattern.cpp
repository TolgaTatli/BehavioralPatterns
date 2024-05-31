#include <iostream>
#include <string>
#include <vector>

class Colleague;

class Mediator {
public:
  virtual void sendMessage(const std::string& message, Colleague* colleague) = 0;
};

class Colleague {
protected:
  Mediator* mediator;

public:
  Colleague(Mediator* mediator) : mediator(mediator) {}

  virtual void receiveMessage(const std::string& message) = 0;
  virtual void sendMessage(const std::string& message) = 0;
};

class ConcreteColleague : public Colleague {
public:
  ConcreteColleague(Mediator* mediator) : Colleague(mediator) {}

  void receiveMessage(const std::string& message) override {
    std::cout << "Received message: " << message << std::endl;
  }

  void sendMessage(const std::string& message) override {
    mediator->sendMessage(message, this);
  }
};

class ConcreteMediator : public Mediator {
private:
  std::vector<Colleague*> colleagues;

public:
  void addColleague(Colleague* colleague) {
    colleagues.push_back(colleague);
  }

  void sendMessage(const std::string& message, Colleague* colleague) override {
    for (auto c : colleagues) {
      if (c != colleague) {
        c->receiveMessage(message);
      }
    }
  }
};

int main() {
  ConcreteMediator mediator;

  ConcreteColleague colleague1(&mediator);
  ConcreteColleague colleague2(&mediator);

  mediator.addColleague(&colleague1);
  mediator.addColleague(&colleague2);

  colleague1.sendMessage("Hello from colleague 1!");
  colleague2.sendMessage("Hi from colleague 2!");

  return 0;
}
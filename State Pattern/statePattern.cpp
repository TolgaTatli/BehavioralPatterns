#include <iostream>
#include <string>

class Context;

class State {
public:
  virtual void handle(Context& context) = 0;
};

class StateA;
class StateB;

class StateA : public State {
public:
  void handle(Context& context) override;
};

class StateB : public State {
public:
  void handle(Context& context) override;
};

class Context {
private:
  State* currentState;

public:
  Context() : currentState(new StateA) {}

  void setState(State* state) {
    currentState = state;
  }

  void request() {
    if (currentState) {
      currentState->handle(*this);
    }
  }
};

void StateA::handle(Context& context) {
  std::cout << "State A handled." << std::endl;
  context.setState(new StateB);
}

void StateB::handle(Context& context) {
  std::cout << "State B handled." << std::endl;
  context.setState(new StateA);
}

int main() {
  Context context;

  context.request();
  context.request();

  return 0;
}
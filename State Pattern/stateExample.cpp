#include <iostream>

class TrafficLight;

class State {
public:
  virtual void handle(TrafficLight* light) = 0;
};

class GreenLightState : public State {
public:
  void handle(TrafficLight* light) override;
};

class YellowLightState : public State {
public:
  void handle(TrafficLight* light) override;
};

class RedLightState : public State {
public:
  void handle(TrafficLight* light) override;
};

class TrafficLight {
private:
  State* currentState;

public:
  TrafficLight(State* initialState) : currentState(initialState) {}

  void setState(State* newState) {
    currentState = newState;
  }

  void change() {
    currentState->handle(this);
  }
};

void GreenLightState::handle(TrafficLight* light) {
  std::cout << "Green light. Go!" << std::endl;
  light->setState(new YellowLightState());
}

void YellowLightState::handle(TrafficLight* light) {
  std::cout << "Yellow light. Prepare to stop!" << std::endl;
  light->setState(new RedLightState());
}

void RedLightState::handle(TrafficLight* light) {
  std::cout << "Red light. Stop!" << std::endl;
  light->setState(new GreenLightState());
}

int main() {
  TrafficLight light(new GreenLightState());

  for (int i = 0; i < 9; ++i) {
    light.change();
  }

  return 0;
}


// Output of the program:
/*

Green light. Go!
Yellow light. Prepare to stop!
Red light. Stop!
Green light. Go!
Yellow light. Prepare to stop!
Red light. Stop!
Green light. Go!
Yellow light. Prepare to stop!
Red light. Stop!


*/
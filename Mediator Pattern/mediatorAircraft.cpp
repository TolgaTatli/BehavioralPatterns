#include <iostream>
#include <string>

class Aircraft;

// AirTrafficControl is the Mediator class
class AirTrafficControl
{
public:
  virtual void receiveMessage(const std::string &message, Aircraft *aircraft) = 0;
};

// Aircraft is the Colleague class
class Aircraft
{
protected:
  AirTrafficControl *atc;

public:
  Aircraft(AirTrafficControl *atc) : atc(atc) {}

  virtual void sendMessage(const std::string &message) = 0;
  virtual void receiveMessage(const std::string &message) = 0;
};

// Airplane is a concrete Colleague
class Airplane : public Aircraft
{
public:
  Airplane(AirTrafficControl *atc) : Aircraft(atc) {}

  void sendMessage(const std::string &message) override
  {
    atc->receiveMessage(message, this);
  }

  void receiveMessage(const std::string &message) override
  {
    std::cout << "Airplane received message: " << message << std::endl;
  }
};

// ControlTower is a concrete Mediator
class ControlTower : public AirTrafficControl
{
public:
  void receiveMessage(const std::string &message, Aircraft *aircraft) override
  {
    // Here, the ControlTower can decide what to do th the message
    // For simplicity, we'll just print it out
    std::cout << "Control Tower received message: " << message << std::endl;
  }
};

int main()
{
  // Create a new ControlTower
  ControlTower *controlTower = new ControlTower();

  // Create a new Airplane that communicates through the ControlTower
  Airplane *airplane = new Airplane(controlTower);

  // Send a message from the Airplane
  airplane->sendMessage("Requesting permission to land.");

  // Don't forget to delete the dynamically allocated objects
  delete airplane;
  delete controlTower;

  return 0;
}
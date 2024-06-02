#include <iostream>
#include <vector>

// Receiver class
class Light
{
public:
  void turnOn()
  {
    std::cout << "Light is on." << std::endl;
  }

  void turnOff()
  {
    std::cout << "Light is off." << std::endl;
  }
};

// Command interface  // that interface only have one method which is "execute()"
class Command
{
public:
  virtual void execute() = 0;
};

// Concrete command classes
class TurnOnCommand : public Command
{
private:
  Light &light;

public:
  TurnOnCommand(Light &light) : light(light) {}

  void execute() override
  {
    light.turnOn();
  }
};

class TurnOffCommand : public Command
{
private:
  Light &light;

public:
  TurnOffCommand(Light &light) : light(light) {}

  void execute() override
  {
    light.turnOff();
  }
};

// Invoker class // that class has a vector of commands and execute them
class RemoteControl
{ // set command and execute them // there are two methods in this class such as setCommand and executeCommands
private:
  std::vector<Command *> commands;

public:
  void setCommand(Command *command)
  {
    commands.push_back(command);
  }

  void executeCommands()
  {
    for (Command *command : commands)
    {
      command->execute();
    }
    commands.clear();
  }
};

int main()
{
  // Create receiver object
  Light light;

  // Create command objects
  Command *turnOnCommand = new TurnOnCommand(light);
  Command *turnOffCommand = new TurnOffCommand(light);

  // Create invoker object
  RemoteControl remoteControl;

  // Set commands to invoker
  remoteControl.setCommand(turnOnCommand);
  remoteControl.setCommand(turnOffCommand);

  // Execute commands
  remoteControl.executeCommands();

  // Clean up
  delete turnOnCommand;
  delete turnOffCommand;

  return 0;
}
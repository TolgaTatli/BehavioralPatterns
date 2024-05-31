#include <iostream>
#include <vector>

// Command interface
class Command
{
public:
  virtual void execute() = 0;
  virtual void undo() = 0;
};

// Receiver class
class Calculator
{
private:
  int result;

public:
  Calculator() : result(0) {}

  void add(int value)
  {
    result += value;
  }

  void subtract(int value)
  {
    result -= value;
  }

  int getResult() const
  {
    return result;
  }
};

// Concrete command classes
class AddCommand : public Command
{
private:
  Calculator &calculator;
  int value;

public:
  AddCommand(Calculator &calc, int val) : calculator(calc), value(val) {}

  void execute() override
  {
    calculator.add(value);
  }

  void undo() override
  {
    calculator.subtract(value);
  }
};

class SubtractCommand : public Command
{
private:
  Calculator &calculator;
  int value;

public:
  SubtractCommand(Calculator &calc, int val) : calculator(calc), value(val) {}

  void execute() override
  {
    calculator.subtract(value);
  }

  void undo() override
  {
    calculator.add(value);
  }
};

// Invoker class
class Invoker
{
private:
  std::vector<Command *> commands;

public:
  void executeCommand(Command *command)
  {
    command->execute();
    commands.push_back(command);
  }

  void undoLastCommand()
  {
    if (!commands.empty())
    {
      Command *lastCommand = commands.back();
      lastCommand->undo();
      commands.pop_back();
      delete lastCommand;
    }
  }
};

int main()
{
  Calculator calculator;
  Invoker invoker;

  // Create and execute commands
  Command *addCommand = new AddCommand(calculator, 5);
  invoker.executeCommand(addCommand);

  Command *subtractCommand = new SubtractCommand(calculator, 3);
  invoker.executeCommand(subtractCommand);
  
  // Print result
  std::cout << "Result: " << calculator.getResult() << std::endl;


  // Undo last command
  invoker.undoLastCommand();


  // Print result
  std::cout << "Result: " << calculator.getResult() << std::endl;

  // Clean up
  delete addCommand;
  delete subtractCommand;

  return 0;
}
#include <iostream>
#include <string>
#include <vector>

// Memento class
class Memento
{
private:
  std::string text;

public:
  Memento(const std::string &newText) : text(newText) {}

  std::string getText() const
  {
    return text;
  }
};

// Originator class
class TextEditor
{
private:
  std::string text;

public:
  void setText(const std::string &newText)
  {
    text = newText;
  }

  std::string getText() const
  {
    return text;
  }

  // Create a memento object to save the current state
  Memento createMemento() const
  {
    return Memento(text);
  }

  // Restore the state from a memento object
  void restoreFromMemento(const Memento &memento)
  {
    text = memento.getText();
  }
};

// Caretaker class
class TextEditorHistory
{
private:
  std::vector<Memento> history;

public:
  void addMemento(const Memento &memento)
  {
    history.push_back(memento);
  }

  Memento getMemento(int index) const
  {
    return history[index];
  }
};

int main()
{
  TextEditor editor;
  TextEditorHistory history;

  // Set initial text
  editor.setText("Hello, World!");

  // Save the initial state
  history.addMemento(editor.createMemento());

  // Modify the text
  editor.setText("Hello, GitHub Copilot!");

  // Save the modified state
  history.addMemento(editor.createMemento());

  // Restore the initial state
  editor.restoreFromMemento(history.getMemento(0));

  std::cout << "Current text: " << editor.getText() << std::endl;

  return 0;
}
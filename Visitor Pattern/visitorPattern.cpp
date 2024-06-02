#include <iostream>
#include <vector>

// Forward declaration of classes
class ConcreteElementA;
class ConcreteElementB;

// Abstract Visitor class
class Visitor {
public:
  virtual void visit(ConcreteElementA* element) = 0;
  virtual void visit(ConcreteElementB* element) = 0;
};

// Concrete Visitor class
class ConcreteVisitor : public Visitor {
public:
  void visit(ConcreteElementA* element) override {
    std::cout << "Visiting ConcreteElementA" << std::endl;
    // Perform operations specific to ConcreteElementA
  }

  void visit(ConcreteElementB* element) override {
    std::cout << "Visiting ConcreteElementB" << std::endl;
    // Perform operations specific to ConcreteElementB
  }
};

// Abstract Element class
class Element {
public:
  virtual void accept(Visitor* visitor) = 0;
};

// Concrete Element classes
class ConcreteElementA : public Element {
public:
  void accept(Visitor* visitor) override {
    visitor->visit(this);
  }
};

class ConcreteElementB : public Element {
public:
  void accept(Visitor* visitor) override {
    visitor->visit(this);
  }
};

// Client code
int main() {
  std::vector<Element*> elements;
  elements.push_back(new ConcreteElementA());
  elements.push_back(new ConcreteElementB());

  ConcreteVisitor visitor;

  for (Element* element : elements) {
    element->accept(&visitor);
  }

  // Clean up
  for (Element* element : elements) {
    delete element;
  }

  return 0;
}
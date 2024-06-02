#include <iostream>
#include <string>
#include <vector>

// Forward declaration of classes
class Visitor;

// Abstract base class for elements
class Element {
public:
  virtual void accept(Visitor& visitor) = 0;
};

// Concrete element classes
class Book : public Element {
public:
  void accept(Visitor& visitor) override;
  std::string getTitle() const { return "Book Title"; }
};

class Magazine : public Element {
public:
  void accept(Visitor& visitor) override;
  std::string getName() const { return "Magazine Name"; }
};

// Abstract base class for visitors
class Visitor {
public:
  virtual void visit(Book& book) = 0;
  virtual void visit(Magazine& magazine) = 0;
};

// Concrete visitor classes
class DisplayVisitor : public Visitor {
public:
  void visit(Book& book) override {
    std::cout << "Displaying book: " << book.getTitle() << std::endl;
  }

  void visit(Magazine& magazine) override {
    std::cout << "Displaying magazine: " << magazine.getName() << std::endl;
  }
};

class ExportVisitor : public Visitor {
public:
  void visit(Book& book) override {
    std::cout << "Exporting book: " << book.getTitle() << std::endl;
  }

  void visit(Magazine& magazine) override {
    std::cout << "Exporting magazine: " << magazine.getName() << std::endl;
  }
};

// Implement accept() method for each concrete element
void Book::accept(Visitor& visitor) {
  visitor.visit(*this);
}

void Magazine::accept(Visitor& visitor) {
  visitor.visit(*this);
}

int main() {
  // Create a collection of elements
  std::vector<Element*> elements;
  elements.push_back(new Book());
  elements.push_back(new Magazine());

  // Create visitors
  DisplayVisitor displayVisitor;
  ExportVisitor exportVisitor;

  // Apply visitors to elements
  for (Element* element : elements) {
    element->accept(displayVisitor);
    element->accept(exportVisitor);
  }

  // Clean up memory
  for (Element* element : elements) {
    delete element;
  }

  return 0;
}
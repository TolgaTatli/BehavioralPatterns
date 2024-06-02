#include <iostream>
#include <vector>

// Iterator interface
class Iterator {
public:
  virtual int next() = 0;
  virtual bool hasNext() = 0;
};

// Concrete iterator
class ConcreteIterator : public Iterator {
private:
  std::vector<int> collection;
  int position;

public:
  ConcreteIterator(const std::vector<int>& collection) : collection(collection), position(0) {}

  int next() override {
    return collection[position++];
  }

  bool hasNext() override {
    return position < collection.size();
  }
};

// Aggregate interface
class Aggregate {
public:
  virtual Iterator* createIterator() = 0;
};

// Concrete aggregate
class ConcreteAggregate : public Aggregate {
private:
  std::vector<int> collection;

public:
  void add(int item) {
    collection.push_back(item);
  }

  Iterator* createIterator() override {
    return new ConcreteIterator(collection);
  }
};

int main() {
  ConcreteAggregate aggregate;
  aggregate.add(1);
  aggregate.add(2);
  aggregate.add(3);

  Iterator* iterator = aggregate.createIterator();
  while (iterator->hasNext()) {
    std::cout << iterator->next() << " ";
  }
  std::cout << std::endl;

  delete iterator;

  return 0;
}
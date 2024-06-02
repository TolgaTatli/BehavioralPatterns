#include <iostream>
#include <string>

class PurchaseRequest
{
public:
  double amount;  // talep edilen miktar
  std::string purpose; // talebin amacı 
  bool approved;
  std::string approver;

  PurchaseRequest(double amount, std::string purpose)  // constructor
      : amount(amount), purpose(purpose), approved(false), approver("") {}

  void approve(std::string approverName) // onaylama işlemi
  {
    approved = true;
    approver = approverName;
  }
};

class Approver // onaylayıcı sınıfı
{
public:
  Approver *nextApprover;
  std::string name;

  Approver(std::string name) : name(name), nextApprover(nullptr) {}

  void setNext(Approver *approver) // bir sonraki onaylayıcıyı belirlemek için kullanılır 
  {
    nextApprover = approver;
  }

  virtual void processRequest(PurchaseRequest &request) = 0; // talebi işleyen fonksiyon
};

class JuniorAssociate : public Approver
{
public:
  JuniorAssociate(std::string name) : Approver(name) {}

  void processRequest(PurchaseRequest &request) override
  {
    if (request.amount < 500)
    {
      request.approve(name);
      std::cout << "Purchase approved by Junior Associate: " << name << std::endl;
    }
    else if (nextApprover != nullptr)
    {
      nextApprover->processRequest(request);
    }
  }
};

class SeniorAssociate : public Approver
{
public:
  SeniorAssociate(std::string name) : Approver(name) {}

  void processRequest(PurchaseRequest &request) override
  {
    if (request.amount >= 500 && request.amount < 3000)
    {
      request.approve(name);
      std::cout << "Purchase approved by Senior Associate: " << name << std::endl;
    }
    else if (nextApprover != nullptr)
    {
      nextApprover->processRequest(request);
    }
  }
};

class Manager : public Approver
{
public:
  Manager(std::string name) : Approver(name) {}

  void processRequest(PurchaseRequest &request) override
  {
    if (request.amount >= 3000)
    {
      request.approve(name);
      std::cout << "Purchase approved by Manager: " << name << std::endl;
    }
    else
    {
      std::cout << "Purchase amount exceeds Manager's limit." << std::endl;
    }
  }
};

int main()
{
  JuniorAssociate ja("John");
  SeniorAssociate sa("Sarah");
  Manager m("Michael");

  ja.setNext(&sa);
  sa.setNext(&m);

  PurchaseRequest pr1(400, "Office Supplies");
  ja.processRequest(pr1);

  PurchaseRequest pr2(1500, "New Chairs");
  ja.processRequest(pr2);

  PurchaseRequest pr3(5000, "New Computers");
  ja.processRequest(pr3);

  return 0;
}

/*
Bu kod, bir satın alma talebini işleyen bir "sorumluluk zinciri" oluşturur.
Her onaylayıcı, belirli bir miktar aralığındaki talepleri onaylar.
Eğer bir onaylayıcı talebi onaylayamazsa, talebi sonraki onaylayıcıya iletir.
Eğer bir sonraki onaylayıcı yoksa, talep onaylanamaz ve program sonlanır.
*/
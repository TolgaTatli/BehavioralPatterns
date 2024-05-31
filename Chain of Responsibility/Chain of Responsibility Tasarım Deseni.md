# Chain of Responsibility Tasarım Deseni

Chain of Responsibility, bir isteği işlemek için bir dizi nesneyi zincirleme şekilde birleştiren bir davranışsal tasarım desenidir. Bu desen, isteği gönderen nesne ile işleyen nesne arasında sıkı bir bağımlılık oluşturur ve isteği işleyecek olan nesneyi dinamik olarak belirler.

## Nasıl Çalışır?

Chain of Responsibility deseni, bir isteği işlemek için bir dizi işleyici nesnesini bir zincir halinde bağlar. İstek, zincirin başındaki işleyiciye gönderilir ve işleyici, isteği işleyebiliyorsa bunu yapar. İşleyici, isteği işleyemezse, isteği zincirdeki bir sonraki işleyiciye iletir. Bu işlem zincirin sonuna kadar devam eder ve istek işlenecek bir işleyici bulunana kadar devam eder.

## Nerede Kullanılır?

Chain of Responsibility deseni, bir isteği işlemek için birden fazla nesnenin kullanılması gerektiği durumlarda kullanılır. Ayrıca, isteği işleyecek olan nesnenin dinamik olarak belirlenmesi gereken durumlarda da tercih edilir. Örneğin, bir kullanıcı isteği, bir web uygulamasında doğrulama, yetkilendirme ve güvenlik kontrolleri gibi farklı aşamalardan geçmelidir. Her aşama, bir işleyici nesnesi tarafından temsil edilir ve istek zinciri boyunca ilerler.

## Avantajları

- İstekleri işlemek için esnek bir yapı sağlar ve işleyicilerin dinamik olarak değiştirilmesine olanak tanır.
- İstek zinciri boyunca işleyicilerin eklenmesi veya çıkarılması kolaydır.
- İsteklerin hangi işleyici tarafından işleneceği, çalışma zamanında belirlenebilir.

## Dezavantajları

- İstek zinciri çok uzun olduğunda veya işleyicilerin düzgün bir şekilde yapılandırılmadığı durumlarda performans sorunlarına neden olabilir.
- İstek zinciri içindeki işleyicilerin sırası önemlidir ve yanlış bir sıralama, isteklerin doğru bir şekilde işlenmemesine neden olabilir.

## Örnek Kullanım

Aşağıda, bir banka uygulamasında Chain of Responsibility deseninin nasıl kullanılabileceğine dair basit bir örnek bulunmaktadır:

```c++
#include <iostream>
#include <string>

class BankRequest {
public:
std::string requestType;
double amount;

BankRequest(const std::string& type, double amt) : requestType(type), amount(amt) {}
};

class BankHandler {
protected:
BankHandler\* nextHandler;

public:
BankHandler() : nextHandler(nullptr) {}

void setNextHandler(BankHandler\* handler) {
nextHandler = handler;
}

virtual void handleRequest(const BankRequest& request) = 0;
};

class BankTeller : public BankHandler {
public:
void handleRequest(const BankRequest& request) override {
if (request.requestType == "Withdraw" && request.amount <= 1000) {
std::cout << "Bank teller can handle the request." << std::endl;
}
else if (nextHandler != nullptr) {
nextHandler->handleRequest(request);
}
else {
std::cout << "No handler available to handle the request." << std::endl;
}
}
};

class BankManager : public BankHandler {
public:
void handleRequest(const BankRequest& request) override {
if (request.requestType == "Withdraw" && request.amount > 1000 && request.amount <= 5000) {
std::cout << "Bank manager can handle the request." << std::endl;
}
else if (nextHandler != nullptr) {
nextHandler->handleRequest(request);
}
else {
std::cout << "No handler available to handle the request." << std::endl;
}
}
};

class BankExecutive : public BankHandler {
public:
void handleRequest(const BankRequest& request) override {
if (request.requestType == "Withdraw" && request.amount > 5000) {
std::cout << "Bank executive can handle the request." << std::endl;
}
else if (nextHandler != nullptr) {
nextHandler->handleRequest(request);
}
else {
std::cout << "No handler available to handle the request." << std::endl;
}
}
};

int main() {
// Create the chain of responsibility
BankTeller teller;
BankManager manager;
BankExecutive executive;

teller.setNextHandler(&manager);
manager.setNextHandler(&executive);

// Create a bank request
BankRequest request("Withdraw", 2000);

// Process the request
teller.handleRequest(request);

return 0;
}
```

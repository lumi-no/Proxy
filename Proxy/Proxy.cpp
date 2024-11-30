#include <iostream>
#include <string>


class Subject {
public:
    virtual ~Subject() = default;
    virtual void Request() const = 0;
};


class RealSubject : public Subject {
public:
    void Request() const override {
        std::cout << "RealSubject: Обробка запиту.\n";
    }
};


class Proxy : public Subject {
private:
    RealSubject* realSubject_; 

    bool CheckAccess() const {
        
        std::cout << "Proxy: Перевірка доступу перед обробкою запиту.\n";
        return true;
    }

    void LogAccess() const {
      
        std::cout << "Proxy: Логування запиту.\n";
    }

public:
    Proxy(RealSubject* realSubject) : realSubject_(realSubject) {}

    void Request() const override {
        if (CheckAccess()) {
            realSubject_->Request();
            LogAccess();
        }
    }
};


void ClientCode(const Subject& subject) {
    subject.Request();
}

int main() {
    std::cout << "Клієнт: Використання реального об'єкта:\n";
    RealSubject* realSubject = new RealSubject;
    ClientCode(*realSubject);

    std::cout << "\nКлієнт: Використання об'єкта-замісника:\n";
    Proxy* proxy = new Proxy(realSubject);
    ClientCode(*proxy);

    delete proxy;
    delete realSubject;

    return 0;
}

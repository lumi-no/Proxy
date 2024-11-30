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
        std::cout << "RealSubject: ������� ������.\n";
    }
};


class Proxy : public Subject {
private:
    RealSubject* realSubject_; 

    bool CheckAccess() const {
        
        std::cout << "Proxy: �������� ������� ����� �������� ������.\n";
        return true;
    }

    void LogAccess() const {
      
        std::cout << "Proxy: ��������� ������.\n";
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
    std::cout << "�볺��: ������������ ��������� ��'����:\n";
    RealSubject* realSubject = new RealSubject;
    ClientCode(*realSubject);

    std::cout << "\n�볺��: ������������ ��'����-��������:\n";
    Proxy* proxy = new Proxy(realSubject);
    ClientCode(*proxy);

    delete proxy;
    delete realSubject;

    return 0;
}

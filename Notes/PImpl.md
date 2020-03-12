### Идиома PImpl

```c++
#include <iostream>
#include <string>
#include <memory>
 
// где-то в h-файле

class Person
{
public:
    struct impl;
    Person (std::string &name);
    Person (Person &&) = default;
    Person& operator = (Person &&) = default;
    ~Person();
 
    std::string getName();
 
private:
   std::unique_ptr<impl> pimpl;
};
 
// как это используется

int main()
{
    std::string name = "Alexey";
    Person person (name);
    std::cout << "1: " << person.getName() << std::endl;
    Person other (std::move(person));
    std::cout << "2: " << other.getName() << std::endl;
    return 0;
}
 
// где-то в cpp-файле

struct Person::impl
{
    std::string name;
    impl (std::string &name_) : name { name_ } {}
};
 
Person::Person (std::string &name) : pimpl { new impl { name } } 
{
    std::cout << "constructor" << std::endl;
}
 
Person::~Person()
{
    std::cout << "destructor" << std::endl;
}
 
std::string Person::getName()
{
    return this->pimpl->name;
}
```

Пусть у нас есть класс, работающий с удалённым ресурсом. При этом конкретная реализация сокета может различаться от запуска к запуску. В самом классе хранится лишь указатель на реализацию. Такой приём называется [PImpl](https://en.cppreference.com/w/cpp/language/pimpl). Вот как его можно реализовать в C++11.

```c++
#include <iostream>
#include <memory>
 
// некие данные, которыми мы обмениваемся с сервером
struct Data {};
 
// абстрактный сокет (без реализации)
class Socket
{
public:
    Socket() { std::cout << "Socket create\n"; }
    virtual ~Socket() { std::cout << "Socket destroy\n"; }
 
    virtual void send (const Data &data) = 0;
    virtual void receive (Data &data) = 0;
};
 
// TCP-сокет
class TcpSocket final : public Socket
{
public:
    TcpSocket() { std::cout << "TCP create\n"; }
    ~TcpSocket() final { std::cout << "TCP destroy\n"; }
 
    void send (const Data &data) override { std::cout << "TCP send\n"; }
    void receive (Data &data) override { std::cout << "TCP receive\n"; }
};
 
// UDP-сокет
class UdpSocket final : public Socket
{
public:
    UdpSocket() { std::cout << "UDP create\n"; }
    ~UdpSocket() final { std::cout << "UDP destroy\n"; }
 
    void send (const Data &data) override { std::cout << "UDP send\n"; }
    void receive (Data &data) override { std::cout << "UDP receive\n"; }
};
 
// некий коннектор, могущий работать с произвольным сокетом
class Connection
{
public:
 
    // по умолчанию используется TcpSocket
    Connection() : _socket {std::make_unique<TcpSocket>()} {}
 
    // можно подсунуть нестандартный сокет в конструктор
    explicit Connection (Socket *socket_) : _socket {socket_} {}
 
    // запрещаем копирование
    Connection (const Connection &other) = delete;
    Connection &operator = (const Connection &other) = delete;
 
    // поддержка move реализуется компилятором
    Connection (Connection &&other) = default;
    Connection& operator = (Connection &&other) = default;
 
    ~Connection() = default;
 
    void send (const Data &data)
    {
        this->_socket->send (data);
    }
 
    void receive (Data &data)
    {
        this->_socket->receive (data);
    }
 
private:
    std::unique_ptr<Socket> _socket;
};
 
int main()
{
    // с сокетом по умолчанию
    {
        Connection connection;
        Data data;
        connection.send (data);
        connection.receive (data);
    }
 
    std::cout << "========\n";
 
    // с нестандартным сокетом
    {
        Connection connection (new UdpSocket);
        Data data;
        connection.send (data);
        connection.receive (data);
    }
 
    std::cout << "========\n";
 
    // с move-семантикой
    {
        Connection first;
        Data data;
        first.send (data);
        Connection second (std::move (first));
        second.receive (data);
    }
 
    return 0;
}
```

### Curiously Recurring Template Pattern

Wiki: https://ru.wikipedia.org/wiki/Curiously_recurring_template_pattern, https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern.

Curiously Recurring Template Pattern (CRTP) идиома языка C++, название которой можно примерно перевести как Странно рекурсивный шаблон или Странно повторяющийся шаблон, часто просто Рекурсивный Шаблон, состоящая в том, что некоторый класс X наследуется от шаблона класса, использующего X как шаблонный параметр.

Используется и в Java — например, любой `enum X` является наследником от `Enum<X>`.

```c++
#include <iostream>
 
struct Data {};
 
template <class T>
class Socket
{
public:
    void send (const Data &data)
    {
        asDerived()->send_implementation (data);
    }
 
    void receive(Data &data)
    {
        asDerived()->lreceive_implementation (data);
    }    
 
private:
    T* asDerived() { return static_cast<T*> (this); }
};
 
class TcpSocket: public Socket<TcpSocket>
{
public:
    void send_implementation (const Data &data)
    {
        std::cout << "SEND" << std::endl;
    }
 
    void receive_implementation (Data &data)
    {
        std::cout << "RECEIVE" << std::endl;
    }
};
 
int main ()
{
    Data data;
    TcpSocket socket;
    socket.send (data);
    socket.receive (data);
    return 0;
}
```
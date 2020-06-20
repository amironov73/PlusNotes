### systemd

systemd — универсальный всемогутер для Linux. Он может почти всё, но сейчас для нас важнейшим является его умение запускать фоновые процессы (демоны). Оказывается, создавать собственных демонов, запускаемых из-под systemd, довольно просто.

Рассказываю на примере Linux Mint 19.3. В других системах с systemd это должно быть аналогично

```
Linux vmint 5.4.0-37-generic #41~18.04.1-Ubuntu SMP Mon Jun 8 13:37:29 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
```

Для начала сочиняем чрезвычайно полезный TCP-echo server 🙂 следующего содержания (файл `echo-server.cpp`):

```c++
#include <iostream>
#include <string>
#include <csignal>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <future>

void handleSignal (int sig)
{
    if (sig == SIGINT) {
        std::cout << "SIGINT received" << std::endl;
        std::exit (0);
    }
}

void handleClient (int clientHandle)
{
    while (true) {
        char recvBuffer [1024];
        const auto recvSize =
            ::recv (clientHandle, recvBuffer, sizeof (recvBuffer), 0);
        if (recvSize == -1) {
            std::cerr << "recv() failed: " << std::endl;
            break;
        }
        if (recvSize == 0) {
            // end of the message
            break;
        }

        const auto sendSize = ::send (clientHandle, recvBuffer, recvSize, 0);
        if (sendSize != recvSize) {
            std::cerr << "send() failed: " << std::endl;
            std::exit (5);
        }
    }

    ::close (clientHandle);
}

void doServer()
{
    int listenHandle = ::socket (AF_INET, SOCK_STREAM, 0);
    if (listenHandle == -1) {
        std::cerr << "socket() failed" << std::endl;
        std::exit (1);
    }

    struct sockaddr_in localAddress { 0 };
    localAddress.sin_family = AF_INET;
    localAddress.sin_addr.s_addr = htonl (INADDR_ANY);
    localAddress.sin_port = htons (9889);

    auto returnCode = ::bind (listenHandle,
        (struct sockaddr*) &localAddress,
        sizeof (localAddress));
    if (returnCode == -1) {
        std::cerr << "bind() failed" << std::endl;
        ::close (listenHandle);
        std::exit (2);
    }

    returnCode = ::listen (listenHandle, 0);
    if (returnCode == -1) {
        std::cerr << "listen() failed" << std::endl;
        ::close (listenHandle);
        std::exit (3);
    }

    while (true) {
        auto clientHandle = ::accept (listenHandle, nullptr, nullptr);
        if (clientHandle == -1) {
            std::cerr << "accept() failed" << std::endl;
            ::close (listenHandle);
            std::exit (4);
        }

        std::thread workerThread ([=] { handleClient (clientHandle); });
        workerThread.detach();
    }
}

int main()
{
    ::signal (SIGINT, handleSignal);
    doServer();
    return 0;
}
```

Как видим, ничего сложного: прослушиваем TCP-порт 9889 и все полученные данные тут же отправляем обратно, вот и всё, что умеет данный код. Компилируем его с помощью следующего `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 2.8)
project(echo-server)
 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
 
add_executable(echoServer echo-server.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION /var/local)
```

Собираем и устанавливаем:

```
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ cmake --build .
$ sudo cmake --build . --target install
```

Если всё прошло без ошибок, CMake напишет примерно следующее:

```
[100%] Built target echo_server
Install the project...
-- Install configuration: "Release"
-- Installing: /var/local/echo_server
```

Т. е. наш демон успешно скопирован по адресу `/var/local/echo_server` (не обязательно использовать именно такой путь, просто у меня в системе в этой папке оказался минимум посторонних программ, так что я мог не бояться сломать что-нибудь по ходу игрищ с демонами).

Теперь сочиняем файл `echo_server.service` следующего содержания:

```
[Unit]
Description=Example systemd service.
 
[Service]
Type=simple
ExecStart=/var/local/echo_server
 
[Install]
WantedBy=multi-user.target
```

По-моему, текст не нуждается в пояснениях, настолько всё понятно. 🙂

Копируем его в `/etc/systemd/system/`:

```
$ sudo cp echo_server.service /etc/systemd/system/
$ sudo chmod 644 /etc/systemd/system/echo_server.service
```

Собственно, бо́льшая часть работы проделана, наш демон успешно инсталлирован в систему. Можно приступать к проверке:

```
$ sudo systemctl start echo_server
```

Если система не ругается, значит, демон успешно запущен. Убеждаемся в этом:

```
$ sudo systemctl status echo_server
● echo_server.service - Example systemd service.
   Loaded: loaded (/etc/systemd/system/echo_server.service; disabled; vendor preset: enabled)
   Active: active (running) since Wed 2020-06-10 14:44:12 +08; 3min 50s ago
 Main PID: 6607 (echo_server)
    Tasks: 1 (limit: 9434)
   CGroup: /system.slice/echo_server.service
           └─6607 /var/local/echo_server
 
июн 10 14:44:12 vmint systemd[1]: Started Example systemd service..
```

Что говорит `netstat`:

```
$ netstat -nlt
Активные соединения с интернетом (only servers)
Proto Recv-Q Send-Q Local Address Foreign Address State      
tcp        0      0 127.0.0.53:53           0.0.0.0:*               LISTEN     
tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN     
tcp        0      0 0.0.0.0:9889            0.0.0.0:*               LISTEN     
tcp6       0      0 ::1:631                 :::*                    LISTEN  
```

Видим, что наш порт 9889 прослушивается. Можем попробовать соединиться с ним:

```
$ telnet 127.0.0.1 9889
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
Привет, демон!
Привет, демон!
^]
telnet> quit
Connection closed.
```

Наш демон работает! Ура!

Что ещё можно сделать с нашим демоном:

 Действие | Команда
----------|--------
Остановить демона | `systemctl stop echo_server`
Перезапустить демона | `systemctl restart echo_server`
Узнать, активен ли демон | `systemctl is-active echo_server`
Разрешить автоматический запуск демона при старте системы | `systemctl enable echo_server`
Запретить автоматический запуск демона при старте системы | `systemctl disable echo_server`
Проверить, разрешен ли автоматический запуск демона | `systemctl is-enabled echo_server`
 
Поздравим себя: мы только что научились делать несложных демонов для Linux!
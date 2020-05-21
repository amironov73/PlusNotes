#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

/*----------------------------------------------------------------

#include <sys/socket.h>

int socket (int domain, int type, int protocol);

Upon successful completion, socket() shall return a non-negative
integer, the socket file descriptor. Otherwise, a value of -1
shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <sys/socket.h>

int connect (int socket, const struct sockaddr *address,
socklen_t address_len);

Upon successful completion, connect() shall return 0; otherwise,
-1 shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <sys/socket.h>

ssize_t send (int socket, const void *buffer, size_t length, int flags);

Upon successful completion, send() shall return the number of bytes
sent. Otherwise, -1 shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <arpa/inet.h>

int inet_pton (int af, const char *src, void *dst);

This function converts the character string src into a network
address structure in the af address family, then copies the network
address structure to dst. The af argument must be either AF_INET
or AF_INET6.

inet_pton() returns 1 on success (network address was successfully
converted). 0 is returned if src does not contain a character string
representing a valid network address in the specified address family.
If af does not contain a valid address family, -1 is returned and
errno is set to EAFNOSUPPORT.

------------------------------------------------------------------

#include <netdb.h>

struct hostent *gethostbyname (const char *name);

The gethostbyname() function returns a structure of type hostent
for the given host name. Here name is either a hostname,
or an IPv4 address in standard dot notation (as for inet_addr(3)),
or an IPv6 address in colon (and possibly dot) notation.

The gethostbyname() function return the hostent structure or
a NULL pointer if an error occurs. On error, the h_errno variable
holds an error number. When non-NULL, the return value may point
at static data, see the notes below.

------------------------------------------------------------------*/

// если мы подключаемся к локальному хосту
void connectToLocalHost(struct sockaddr_in *serverAddress)
{
    serverAddress->sin_addr.s_addr = htonl (INADDR_LOOPBACK);
}

// если адрес задан четырьмя числами: "123.231.123.231"
void resolveNumbericalAddress (const char *serverName,
    struct sockaddr_in *serverAddress)
{
    auto returnCode = ::inet_pton (AF_INET, serverName,
        &serverAddress->sin_addr);
    if (returnCode != 1) {
        std::cerr << "inet_pton() failed" << std::endl;
        std::exit (2);
    }
}

// если адрес задан именем хоста: "someserver"
void resolveHostname (const char *serverName,
    struct sockaddr_in *serverAddress)
{
    struct hostent *host = gethostbyname (serverName);
    if (host == nullptr) {
        std::cerr << "gethostbyname() failed" << std::endl;
        std::exit (2);
    }
    ((unsigned long*)&serverAddress->sin_addr)[0] =
        ((unsigned long **)host->h_addr_list)[0][0];
}

void doClient(const char *serverName)
{
    auto clientHandle = ::socket (AF_INET, SOCK_STREAM, 0);
    if (clientHandle == -1) {
        std::cerr << "socket() failed" << std::endl;
        std::exit (1);
    }

    struct sockaddr_in serverAddress { 0 };
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons (9889);
    // connectToLocalHost (&serverAddress);
    // resolveNumbericalAddress (serverName, &serverAddress);
    resolveHostname (serverName, &serverAddress);

    auto returnCode = ::connect (clientHandle,
        (struct sockaddr *)& serverAddress,
        sizeof (serverAddress));
    if (returnCode == -1) {
        std::cerr << "connect() failed" << std::endl;
        ::close (clientHandle);
        std::exit (3);
    }

    time_t now = ::time (nullptr);
    std::stringstream ss;
    ss << "Hello, World! Today is " << ::ctime (&now);
    const auto message = ss.str();
    const auto messageSize = message.size();

    returnCode = ::send (clientHandle, message.data(),
        messageSize, 0);
    if (returnCode != static_cast <int> (messageSize)) {
        std::cerr << "send() failed" << std::endl;
        ::close (clientHandle);
        std::exit (4);
    }

    ::close (clientHandle);
}

int main()
{
    std::cout << "Client started" << std::endl;
    //doClient ("127.0.0.1");
    doClient ("localhost");
    std::cout << "Client done" << std::endl;
    return 0;
}

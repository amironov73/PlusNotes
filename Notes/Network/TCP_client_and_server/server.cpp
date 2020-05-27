#include <iostream>
#include <string>
#include <csignal>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>

/*----------------------------------------------------------------

#include <sys/socket.h>

int socket (int domain, int type, int protocol);

Upon successful completion, socket() shall return a non-negative
integer, the socket file descriptor. Otherwise, a value of -1
shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <sys/socket.h>

int bind (int socket, const struct sockaddr *address,
    socklen_t address_len);

Upon successful completion, bind() shall return 0; otherwise,
-1 shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <sys/socket.h>

int listen (int socket, int backlog);

A backlog argument of 0 may allow the socket to accept connections,
in which case the length of the listen queue may be set to
an implementation-defined minimum value.

Upon successful completions, listen() shall return 0;
 otherwise, -1 shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <sys/socket.h>

int accept (int socket, struct sockaddr *restrict address,
    socklen_t *restrict address_len);

Upon successful completion, accept() shall return the non-negative
file descriptor of the accepted socket. Otherwise,
 -1 shall be returned and errno set to indicate the error.

------------------------------------------------------------------

#include <unistd.h>

pid_t fork (void);

Upon successful completion, fork() shall return 0 to the child
process and shall return the process ID of the child process
to the parent process. Both processes shall continue to execute
from the fork() function. Otherwise, -1 shall be returned to the
parent process, no child process shall be created, and errno shall
be set to indicate the error.

------------------------------------------------------------------

#include <sys/types.h>
#include <sys/wait.h>

pid_t wait (int *status);

pid_t waitpid (pid_t pid, int *status, int options);

The value of options is an OR of zero or more of the following constants:
WNOHANG
return immediately if no child has exited.

wait(): on success, returns the process ID of the terminated child;
on error, -1 is returned.

waitpid(): on success, returns the process ID of the child whose state
has changed; if WNOHANG was specified and one or more child(ren) specified
by pid exist, but have not yet changed state, then 0 is returned.
On error, -1 is returned.

------------------------------------------------------------------

#include <signal.h>

typedef void (*sighandler_t) (int);

sighandler_t signal (int signum, sighandler_t handler);

signal() sets the disposition of the signal signum to handler,
which is either SIG_IGN, SIG_DFL, or the address of a programmer-defined
function (a "signal handler").

------------------------------------------------------------------

#include <signal.h>

int sigaction (int signum, const struct sigaction *act,
              struct sigaction *oldact);

------------------------------------------------------------------

#include <sys/socket.h>

ssize_t recv (int socket, void *buffer, size_t length, int flags);

Upon successful completion, recv() shall return the length of the
message in bytes. If no messages are available to be received and
the peer has performed an orderly shutdown, recv() shall return 0.
Otherwise, -1 shall be returned and errno set to indicate the error.

------------------------------------------------------------------*/

void handleSignal (int sig)
{
    std::cout << "Signal: " << sig << std::endl;

    if (sig == SIGINT) {
        std::cout << "SIGINT received" << std::endl;
        std::exit (0);
    }

    if (sig == SIGCHLD) {
        pid_t pid;
        int status;

        /* EEEEXTEERMINAAATE! */
        while ((pid = ::waitpid (-1, &status, WNOHANG)) > 0) {
            std::cout << "Child: " << pid << ", status: " << status << std::endl;
        }
    }
}

void handleClient (int clientHandle)
{
    std::cout << "Client arrived" << std::endl;

    auto returnCode = ::fork();
    if (returnCode == -1) {
        std::cerr << "fork() failed" << std::endl;
        ::close (clientHandle);
    }

    if (returnCode != 0) {
        // in parent process
        ::close (clientHandle);
        return;
    }

    // in child process
    while (true) {
        char recvBuffer [1024];
        const auto recvSize = ::recv (clientHandle, recvBuffer, sizeof (recvBuffer), 0);
        if (recvSize == -1) {
            std::cerr << "recv() failed: " << std::endl;
            break;
        }
        if (recvSize == 0) {
            // end of the message
            break;
        }

        std::string message (recvBuffer, recvSize);
        std::cout << message;
    }

    std::cout << std::endl << std::endl << "Client disconnected" << std::endl;

    ::close (clientHandle);
    std::exit (0);
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

        handleClient (clientHandle);
    }
}

void setupSignalHandlers()
{
    // If the parent simply ignores SIGCHLD, the children
    // are silently reaped and won't turn into zombies.
    ::signal (SIGCHLD, SIG_IGN);

    // New fashion
    // struct sigaction sa { 0 };
    // sigemptyset (&sa.sa_mask);
    // sa.sa_flags = 0;
    // sa.sa_handler = handleSignal;
    // sigaction (SIGCHLD, &sa, nullptr);

    // Old fashion
    // ::signal (SIGCHLD, handleSignal);

    ::signal (SIGINT, handleSignal);

    std::cout << "Signal handler established" << std::endl;
}

int main()
{
    std::cout << "Server started" << std::endl;
    setupSignalHandlers();
    doServer();
    std::cout << "Server done" << std::endl;
    return 0;
}

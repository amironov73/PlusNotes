### POSIX threads

https://ru.wikipedia.org/wiki/POSIX_Threads

POSIX Threads — стандарт POSIX-реализации потоков (нитей) выполнения. Стандарт POSIX.1c, Threads extensions (IEEE Std 1003.1c-1995) определяет API для управления потоками, их синхронизации и планирования.

Реализации данного API существуют для большого числа UNIX-подобных ОС (GNU/Linux, Solaris, FreeBSD, OpenBSD, NetBSD, OS X), а также для Microsoft Windows и других ОС.

Библиотеки, реализующие этот стандарт (и функции этого стандарта), обычно называются Pthreads (функции имеют префикс «pthread_»).

В GCC подключается с помощью ключа `-pthread`.

В C++ имеется собственная обёртка над потоками, включенная в стандарт C++11 (`#include <thread>`). Но может понадобиться взаимодействие с многопоточным кодом на C, который использует POSIX threads.

#### Основные функции стандарта

Pthreads определяет набор типов и функций на языке программирования Си. Заголовочный файл — `pthread.h`.

Типы данных:

* **pthread_t**: дескриптор потока;
* **pthread_attr_t**: перечень атрибутов потока;
* **pthread_barrier_t**: барьер;
* **pthread_barrierattr_t**: атрибуты барьера;
* **pthread_cond_t**: условная переменная;
* **pthread_condattr_t**: атрибуты условной переменной;
* **pthread_key_t**: данные, специфичные для потока;
* **pthread_mutex_t**: мьютекс;
* **pthread_mutexattr_t**: атрибуты мьютекса;
* **pthread_rwlock_t**: мьютекс с возможностью эксклюзивной блокировки;
* **pthread_rwlockattr_t**: атрибуты этого мьютекса;
* **pthread_spinlock_t**: спинлок;

Функции управления потоками:

* **pthread_create()**: создание потока.
* **pthread_exit()**: завершение потока (должна вызываться функцией потока при завершении).
* **pthread_cancel()**: отмена потока.
* **pthread_join()**: подключиться к другому потоку и ожидать его завершения; поток, к которому необходимо подключиться, должен быть создан с возможностью подключения (**PTHREAD_CREATE_JOINABLE**).
* **pthread_detach()**: отключиться от потока, сделав его при этом отдельным (**PTHREAD_CREATE_DETACHED**).
* **pthread_attr_init()**: инициализировать структуру атрибутов потока.
* **pthread_attr_setdetachstate()**: указывает параметр "отделимости" потока (detach state), который говорит о возможности подключения к нему (при помощи `pthread_join`) других потоков (значение **PTHREAD_CREATE_JOINABLE**) для ожидания окончания или о запрете подключения (значение **PTHREAD_CREATE_DETACHED**); ресурсы отдельного потока (**PTHREAD_CREATE_DETACHED**) при завершении автоматически освобождаются и возвращаются системе.
* **pthread_attr_destroy()**: освободить память от структуры атрибутов потока (уничтожить дескриптор).

Функции синхронизации потоков:

* **pthread_mutex_init()**, **pthread_mutex_destroy()**, **pthread_mutex_lock()**, **pthread_mutex_trylock()**, **pthread_mutex_unlock()**: с помощью мьютексов.
* **pthread_cond_init()**, **pthread_cond_signal()**, **pthread_cond_wait()**: с помощью условных переменных.

#### Пример использования

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* sayHello (void *data)
{
    pthread_t thread = pthread_self();
    time_t now;
    printf ("Hello from thread %lu!\n", thread);
    for (int i = 0; i < 10; ++i) {
        now = time (NULL);
        printf ("Now is %s", ctime (&now));
        sleep(1);
    }
    pthread_exit (NULL);
    return NULL; // не выполняется
}

void runThread() {
    pthread_t thread;
    int rc;

    printf ("Running thread\n");

    rc = pthread_create (&thread, NULL, sayHello, NULL);
    if (rc != 0) {
        printf ("Error creating thread: %d\n", rc);
        exit (1);
    }

    rc = pthread_join (thread, NULL);
    if (rc != 0) {
        printf ("Error joining thread: %d\n", rc);
        exit (1);
    }

    printf ("All done!\n");
}

int main (int argc, char **argv)
{
    runThread();
    return 0;
}
```

CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 2.8)
project(helloPthread C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
add_executable(helloPthread main.c)
```

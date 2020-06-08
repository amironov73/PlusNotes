### Услованая переменная

https://ru.wikipedia.org/wiki/%D0%A3%D1%81%D0%BB%D0%BE%D0%B2%D0%BD%D0%B0%D1%8F_%D0%BF%D0%B5%D1%80%D0%B5%D0%BC%D0%B5%D0%BD%D0%BD%D0%B0%D1%8F

Условная переменная — примитив синхронизации, обеспечивающий блокирование одного или нескольких потоков до момента поступления сигнала от другого потока о выполнении некоторого условия или до истечения максимального промежутка времени ожидания. Условные переменные используются вместе с ассоциированным мьютексом и являются элементом некоторых видов мониторов.

Концептуально, условная переменная — это очередь потоков, ассоциированных с разделяемым объектом данных, которые ожидают выполнения некоторого условия, накладываемого на состояние данных. Таким образом, каждая условная переменная {\displaystyle c}c связана с утверждением {\displaystyle P_{c}}P_c. Когда поток находится в состоянии ожидания на условной переменной, он не считается владеющим данными и другой поток может изменить разделяемый объект и просигнализировать ожидающим потокам в случае выполнения утверждения {\displaystyle P_{c}}P_c.

Приведенный пример иллюстрирует применение условных переменных для синхронизации потоков производителя и потребителя. Поток-производитель, постепенно увеличивая значение общей переменной, сигнализирует потоку, ожидающему на условной переменной о выполнении утверждения о превышении максимального значения. Ожидающий поток-потребитель, проверяя значение общей переменной, блокируется в случае невыполнения условия превышения максимума. При получении сигнала об истинности утверждения, поток «потребляет» разделяемый ресурс, уменьшая значение общей переменной так, чтобы оно не стало меньше допустимого минимума.

В библиотеке POSIX Threads для языка C за использование условных переменных отвечают функции и структуры данных с префиксом pthread_cond.

```c
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <pthread.h>

#define STORAGE_MIN 10
#define STORAGE_MAX 20

/* Разделяемый ресурс */
int storage = STORAGE_MIN;

pthread_mutex_t mutex;
pthread_cond_t condition;

/* Функция потока потребителя */
void *consumer(void *args)
{
	puts("[CONSUMER] thread started");
	int toConsume = 0;
	
	while(1)
	{
		pthread_mutex_lock(&mutex);
		/* Если значение общей переменной меньше максимального, 
		 * то поток входит в состояние ожидания сигнала о достижении
		 * максимума */
		while (storage < STORAGE_MAX)
		{
			pthread_cond_wait(&condition, &mutex);
		}
		toConsume = storage-STORAGE_MIN;
		printf("[CONSUMER] storage is maximum, consuming %d\n", \
			toConsume);
		/* "Потребление" допустимого объема из значения общей 
		 * переменной */
		storage -= toConsume;
		printf("[CONSUMER] storage = %d\n", storage);
		pthread_mutex_unlock(&mutex);
	}
	
	return NULL;
}

/* Функция потока производителя */
void *producer(void *args)
{
	puts("[PRODUCER] thread started");
	
	while (1)
	{
		usleep(200000);
		pthread_mutex_lock(&mutex);
		/* Производитель постоянно увеличивает значение общей переменной */
		++storage;
		printf("[PRODUCER] storage = %d\n", storage);
		/* Если значение общей переменной достигло или превысило
		 * максимум, поток потребитель уведомляется об этом */
		if (storage >= STORAGE_MAX)
		{
			puts("[PRODUCER] storage maximum");
			pthread_cond_signal(&condition);
		}
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int res = 0;
	pthread_t thProducer, thConsumer;
	
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&condition, NULL);
	
	res = pthread_create(&thProducer, NULL, producer, NULL);
	if (res != 0)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	
	res = pthread_create(&thConsumer, NULL, consumer, NULL);
	if (res != 0)
	{
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	
	pthread_join(thProducer, NULL);
	pthread_join(thConsumer, NULL);
	
	return EXIT_SUCCESS;
}
```

Стандарт C++11 добавил в язык поддержку многопоточности. Работа с условными переменными обеспечивается средствами, объявленными в заголовочном файле condition_variable

```c++
#include <cstdlib>
#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define STORAGE_MIN 10
#define STORAGE_MAX 20

int storage = STORAGE_MIN;

std::mutex globalMutex;
std::condition_variable condition;

/* Функция потока потребителя */
void consumer()
{
	std::cout << "[CONSUMER] thread started" << std::endl;
	int toConsume = 0;
	
	while(true)
	{
		std::unique_lock<std::mutex> lock(globalMutex);
		/* Если значение общей переменной меньше максимального, 
		 * то поток входит в состояние ожидания сигнала о достижении
		 * максимума */
		if (storage < STORAGE_MAX)
		{
			condition.wait(lock); // Атомарно _отпускает мьютекс_ и сразу же блокирует поток
			toConsume = storage-STORAGE_MIN;
			std::cout << "[CONSUMER] storage is maximum, consuming "
				      << toConsume << std::endl;
		}
		/* "Потребление" допустимого объема из значения общей 
		 * переменной */
		storage -= toConsume;
		std::cout << "[CONSUMER] storage = " << storage << std::endl;
	}
}

/* Функция потока производителя */
void producer()
{
	std::cout << "[PRODUCER] thread started" << std::endl;

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));  
    
		std::unique_lock<std::mutex> lock(globalMutex);
		++storage;
		std::cout << "[PRODUCER] storage = " <<  storage << std::endl;
		/* Если значение общей переменной достигло или превысило
		 * максимум, поток потребитель уведомляется об этом */
		if (storage >= STORAGE_MAX)
		{
			std::cout << "[PRODUCER] storage maximum" << std::endl;
			condition.notify_one();
		}
	}
}

int main(int argc, char *argv[])
{
	std::thread thProducer(producer);
	std::thread thConsumer(consumer);
	
	thProducer.join();
	thConsumer.join();
	
	return 0;
}
```





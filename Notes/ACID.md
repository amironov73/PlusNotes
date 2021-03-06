### ACID

https://habr.com/ru/post/470317/

*Atomicity, Consistency, Isolation, Durability. Атомарность, согласованность, изолированность, долговечность.* Это набор требований к транзакциям в СУБД. ACID обеспечивает надежную и предсказуемую работу СУБД даже в случае ошибок.

* **Атомарность** гарантирует, что транзакция либо завершится полностью, либо ничего не сделает. Промежуточное состояние невозможно, не будет такого, что одна операция транзакции выполнилась успешно, а другая — нет. Все или ничего.
* **Согласованность** гарантирует, что все данные в БД удовлетворяют всем заданным правилам и ограничениям как до начала транзакции, так и после ее завершения. В процессе выполнения транзакции согласованность может нарушаться.
* **Изолированность** гарантирует параллельные транзакции никак не влияют друг на друга. Ни одна транзакция не имеет доступа к несогласованным данным, обрабатываемым другой транзакцией.
* **Долговечность** означает, что результат успешной транзакции сохраняется в БД и не может быть потерян, что бы ни случилось с БД сразу по завершении транзакции.

Все основные реляционные СУБД полностью поддерживают ACID. В мире NoSQL такая полная поддержка скорее исключение.
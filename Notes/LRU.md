### LRU

https://habr.com/ru/post/470317/

*Least Recently Used. Вытеснение давно не используемых.* Это один из алгоритмов кэширования (они же политики вытеснения). В общем случае можно считать кэш быстрым хранилищем пар «ключ-значение», одна из основных характеристик которого — уровень попаданий (hit ratio). Чем выше этот уровень, тем чаще нужное значение находится в быстром кэше и тем реже его надо искать в медленном хранилище. Но поскольку память никогда не бывает резиновой, размер кэша приходится ограничивать. Задача алгоритмов кэширования — определить, какой элемент выкинуть из заполненного кэша в случае необходимости так, чтобы максимизировать уровень попаданий.

LRU вытесняет их кэша элемент, к которому дольше всех никто не обращался. Это, пожалуй, самый известный алгоритм кэширования. Наверное, в силу сочетания эффективности и простоты. Расход памяти у LRU — O(n), среднее время доступа к значению — O(1), среднее время добавления элемента — так же O(1). Для реализации обычно используется хэш-таблица и двусвязный список.

Например, так

```c++
template <class K, class V>
class LRU
{
private:
    using Queue = std::list<std::pair<K, V>>;
    using Iterator = typename Queue::iterator;
    using Hash = std::unordered_map<K, Iterator>;

    Queue queue_;
    Hash hash_;
    const size_t limit_;

public:
    LRU(size_t limit)
        : limit_(limit)
    {
    }

    std::optional<V> get(const K& key)
    {
        const auto it = hash_.find(key);
        if (it == hash_.end())
        {
            return {};
        }
        it->second = reorder(it->second);
        return { it->second->second };
    }

    void add(K&& key, V&& value)
    {
        if (hash_.size() >= limit_)
        {
            pop();
        }
        queue_.emplace_front(std::move(key), std::move(value));
        const auto it = queue_.begin();
        hash_[it->first] = it;
    }

private:
    Iterator reorder(Iterator it)
    {
        queue_.emplace_front(std::move(it->first), std::move(it->second));
        queue_.erase(it);
        return queue_.begin();
    }

    void pop()
    {
        hash_.erase(queue_.back().first);
        queue_.pop_back();
    }
};
```

Очевидным недостатком LRU является большой расход памяти, т. к. он использует две структуры по n элементов. Помимо LRU есть множество других алгоритмов кэширования для самых разных случаев: MRU (Most Recently Used), LFU (Least Frequently Used), Segmented LRU, 2Q и т. д.

### declspec

Это [расширение C/C++ от Microsoft](https://docs.microsoft.com/ru-ru/cpp/cpp/declspec?view=vs-2019), в той или иной степени поддерживаемое многими компиляторами, в т. ч. GCC/G++ из поставки MinGW.

* **align( # )** – задает выравнивание структуры и её элементов:

    ```c++
    __declspec(align(32)) struct Struct1 
    {
       int a, b, c, d, e;
    };
    ```

    Здесь число задаёт выравнивание в байтах и может принимать значения от 1 до 8192.
  
    Начиная с Visual Studio 2015 лучше использовать стандарт C++11:
    
    ```c++
    struct alignas(16) Bar
    {
        int i;       // 4 bytes
        int n;       // 4 bytes
        alignas(4) char arr[3];
        short s;     // 2 bytes
    }; 
    ```

* **allocate(" segname ")** – помещает данные в указанный сегмент. Сегмент должен быть предварительно объявлен с помощью одной из прагм: `code_seg`, `const_seg`, `data_seg`, `init_seg` или `section`:

    ```c++
    #pragma section("mycode", read)
    __declspec(allocate("mycode"))  int i = 0;
    
    int main() {
    }
    ```

* **allocator** – директива предназначена для пользовательских функций, выделяющих память, чтобы сделать выделение памяти видимым через трассировку событий для Windows (ETW).

    ```c++
    __declspec(allocator) void* myMalloc(size_t size)
    ```

* **appdomain** – указывает, что каждый домен управляемого приложения должен иметь свою собственную копию определенной глобальной переменной или статической переменной-члена.

* **code_seg(" segname ")** – помещает функцию в указанный сегмент кода. Сегмент должен быть предварительно объявлен с помощью `#pragma code_seg`:

    ```c++
    template<class T>
    class __declspec(code_seg("Segment_1")) Example
    {
    public:
       virtual void VirtualMemberFunction(T /*arg*/) {}
    };
    ```
  
* **deprecated** – помечает метод, класс или переменную как устаревшую:

    ```c++
    __declspec(deprecated) void func1(int) {}
    __declspec(deprecated("deprecated function")) void func2(int) {}
    ```
  
    Лучше использовать стандарт C++14 `[[deprecated]]`.

* **dllimport** – См. [заметку о DLL](Dll.md). 

* **dllexport** – См. [заметку о DLL](Dll.md).

* **jitintrinsic** – отмечает функцию как значимую для CLR. Директива используется Microsoft, обычным программистам она не нужна.

* **naked** – отменяет генерацию пролога и эпилога для функции:

    ```c++
    __declspec(naked) int func( formal_parameters ) {}
    ```
    Атрибут валиден только для x86 или ARM, а для x64 недоступен.   

* **noalias** – сообщает компилятору, что функция не модифицирует и не ссылается на глобальное состояние, за исключением тех данных, на которые получила указатели/ссылки через свои параметры. Заметьте, что директива ничего не говорит об указателях, возвращенных из функции. 

    ```c++
    __declspec(noalias) void multiply(float * a, float * b, float * c)
    {
        int i, j, k;
    
        for (j=0; j<P; j++)
            for (i=0; i<M; i++)
                for (k=0; k<N; k++)
                    c[i * P + j] =
                              a[i * N + k] *
                              b[k * P + j];
    }
    ```

* **noinline** – запрещает компилятору подставлять тело указанной функции:

    ```c++
    class X {
       __declspec(noinline) int mbrfunc() {
          return 0;
       }   // will not inline
    };
    ```

* **noreturn** – сообщает компилятору, что функция не возвращает управление. Это, например, помогает компилятору выявлять недостижимый код.

    ```c++
    __declspec(noreturn) extern void fatal () {}
    
    int main() {
       if(1)
         return 1;
       else if(0)
         return 0;
       else
         fatal();
    }
    ```

* **nothrow** – сообщает компилятору, что функция не бросает исключения.

    ```c++
    void __declspec(nothrow) __stdcall function2();
    ```
  
    Лучше использовать стандарт C++11 `noexcept`.
    
    В отличие от `noexcept` атрибут `nothrow` позволяет компилятору не генерировать `std::terminate`, что существенно уменьшает код.

* **novtable** – эта директива может быть применена к любому объявлению класса, но должна применяться только к чистым интерфейсным классам, то есть классам, которые никогда не будут созданы сами по себе. Она запрещает компилятору генеровать код для инициализации vfptr в конструкторах и деструкторе класса. Во многих случаях это удаляет единственные ссылки на vtable, которые связаны с классом, и, таким образом, компоновщик удаляет его. Использование этой формы __declspec может привести к значительному уменьшению размера кода.
                 
    Если вы попытаетесь создать экземпляр класса, помеченный как novtable, а затем получить доступ к члену класса, вы получите нарушение доступа (AV).
    
    ```c++
    #include <stdio.h>
    
    struct __declspec(novtable) X {
       virtual void mf();
    };
    
    struct Y : public X {
       void mf() {
          printf_s("In Y\n");
       }
    };
    
    int main() {
       // X *pX = new X();
       // pX->mf();   // Causes a runtime access violation.
    
       Y *pY = new Y();
       pY->mf();
    }
    ```

* **process** – указывает, что процесс управляемого приложения должен иметь одну копию определенной глобальной переменной, статической переменной-члена или статической локальной переменной, совместно используемой всеми доменами приложения в процессе. Это было в первую очередь предназначено для использования при компиляции с `/clr:pure`.

* **property( { get=get_func_name | ,put=put_func_name } )** – задание свойств для COM или просто по приколу:

    ```c++
    struct S {
       int i;
       void putprop(int j) {
          i = j;
       }
    
       int getprop() {
          return i;
       }
    
       __declspec(property(get = getprop, put = putprop)) int the_prop;
    };
    
    int main() {
       S s;
       s.the_prop = 5;
       return s.the_prop;
    }
    ```

* **restrict** – сообщает компилятору, что функция возвращает объект, который не является псевдонимом, то есть на него не ссылаются любые другие указатели. Это позволяет компилятору выполнять дополнительную оптимизацию. Примером функции, к которой применима подобная директива, является `malloc`.

    ```c++
    __declspec(restrict) float * ma (int size)
    {
        float * retval;
        retval = malloc (sizeof(float) * size);
        return retval;
    }
    ```

* **safebuffers** – запрещает компилятору добавлять проверку на переполнение буфера в код данной функции:

    ```c++
    static __declspec(safebuffers) int noCheckBuffers() {
        char buffer[100];
        // Use the buffer...
        return 0;
    }
    ```

* **selectany** – сообщает компилятору, что объявленный глобальный элемент данных (переменная или объект) является произвольным COMDAT (упакованная функция). Во время линковки, если обнаружется несколько определений COMDAT, компоновщик выбирает одно и отбрасывает остальные. Если выбрана опция компоновщика `/OPT:REF`, то произойдет исключение COMDAT для удаления всех элементов данных, на которые нет ссылок, в выходных данных компоновщика.

    ```c++
    //Correct - x1 is initialized and externally visible
    __declspec(selectany) int x1=1;
    
    //Incorrect - const is by default static in C++, so
    //x2 is not visible externally (This is OK in C, since
    //const is not by default static in C)
    const __declspec(selectany) int x2 =2;
    
    //Correct - x3 is extern const, so externally visible
    extern const __declspec(selectany) int x3=3;
    
    //Correct - x4 is extern const, so it is externally visible
    extern const int x4;
    const __declspec(selectany) int x4=4;
    
    //Incorrect - __declspec(selectany) is applied to the uninitialized
    //declaration of x5
    extern __declspec(selectany) int x5;
    
    // OK: dynamic initialization of global object
    class X {
    public:
    X(int i){i++;};
    int i;
    };
    
    __declspec(selectany) X x(1);
    ```

* **spectre(nomitigation)** – запрещает компилятору помещать в функцию инструкции барьера памяти для защиты от первого варианта атаки Spectre:

    ```c++
    static __declspec(spectre(nomitigation))
    int noSpectreIssues() {
        // No Spectre variant 1 vulnerability here
        // ...
        return 0;
    }
    ```

* **thread** – помечает переменную, как локальную для потока (thread-local variable):

    ```c++
    __declspec(thread) int tls_i = 1;
    __declspec(thread) SomeClass SomeObject;
    ```

* **uuid(" ComObjectGUID ")** – задает GUID для COM-объекта.

    ```c++
    struct __declspec(uuid("00000000-0000-0000-c000-000000000046")) IUnknown;
    struct __declspec(uuid("{00020400-0000-0000-c000-000000000046}")) IDispatch;
    ```
 
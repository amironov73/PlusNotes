### Active Template Library

https://ru.wikipedia.org/wiki/Active_Template_Library

https://en.wikipedia.org/wiki/Active_Template_Library

Active Template Library (ATL) — набор шаблонных классов языка C++, разработанных компанией Microsoft для упрощения написания COM-компонентов. Эта библиотека позволяет разработчикам создавать различные объекты COM, серверы автоматизации OLE и управляющие элементы ActiveX. Среда разработки Visual Studio включает мастера и помощники для ATL, позволяющие создать первичную объектную структуру практически без программирования вручную.

Например, управление интернет-магазином может быть реализовано с помощью Microsoft Foundation Classes. Но для передачи по сети размер магазина должен быть небольшим. Приложения, написанные на MFC, отличаются своими размерами и требованием поддержки библиотек. В то же время ATL позволяет создавать небольшие по размеру элементы управления, которые не требуют поддержки библиотек. Таким образом, ATL — это в некоторой степени облегчённая альтернатива MFC в качестве средства управления COM. ATL используется в ASP (Active Server Pages) для создания объектов, которые могут быть вызваны скриптом.

#### Support classes

ATL includes many RAII classes to simplify management of COM types. The most commonly used classes include:

```
CComPtr<T>       general-purpose smart-pointer,
CComBSTR         BSTR wrapper,
CComVariant      VARIANT wrapper, and
CComSafeArray<T> SAFEARRAY wrapper.
```

#### Compiler COM support

Although not formally part of ATL, Microsoft Visual C++ also includes additional C++ RAII classes to simplify management of COM types. These compiler COM support classes can be used as replacement for or in combination with ATL, and includes:

```
_com_ptr_t smart-pointer that decorates the COM interface name with a "Ptr" suffix,
_bstr_t    BSTR wrapper,
_variant_t VARIANT wrapper, and
_com_error HRESULT wrapper.
```

Note that as of Visual Studio 2012, the compiler COM support classes does not include a SAFEARRAY wrapper.
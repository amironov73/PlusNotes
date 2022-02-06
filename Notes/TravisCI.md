### Как собрать программу на чистом C++14 под Travis CI

Qt со своей qmake, безусловно, хороша, но иногда хочется чистого C++. Тогда мы вспоминаем про CMake (тем более, что CLion заточена под неё). И организуем сборку проекта под Travis CI следующим образом:

```yaml
dist: xenial
language: cpp
compiler: gcc
sudo: required

addons:
  apt:
    sources:
      - ubuntu-toolchain-r-test
    packages:
      - gcc-7
      - g++-7
      - cmake

script:
 - export CC=gcc-7
 - export CXX=g++-7
 - sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60
 - sudo update-alternatives --install /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-7 60
 - sudo update-alternatives --install /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-7 60
 - sudo update-alternatives --install /usr/bin/x86_64-linux-gnu-gcc x86_64-linux-gnu-gcc /usr/bin/x86_64-linux-gnu-gcc-7 60
 - cd Source/PlusIrbis
 - cmake .
 - make
```

Вот что рапортует нам CMake:

```
$ cmake .
-- The C compiler identification is GNU 7.4.0
-- The CXX compiler identification is GNU 7.4.0
-- Check for working C compiler: /usr/bin/gcc-7
-- Check for working C compiler: /usr/bin/gcc-7 -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/g++-7
-- Check for working CXX compiler: /usr/bin/g++-7 -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/travis/build/amironov73/PlusIrbis/Source/PlusIrbis
```

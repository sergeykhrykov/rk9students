## Инструкция по сборке

Сборка проекта производится в два этапа:

1. Сборка DCMTK (должна быть произведена вручную).
2. Сборка проекта при помощи Conan и CMake. На этом этапе происходит подключение DCMTK и Boost (последний собирается и подключается автоматически благодаря Conan). 

Необходимые инструменты:

* CMake (https://cmake.org/)
* Conan (https://conan.io/)

Склонировав репозиторий, соберите DCMTK вручную (как любой Cmake-проект) , затем выполните (для Debug-сборки):

     $ mkdir build.debug

     $ cd build.debug

     $ conan install ../src -s compiler="Visual Studio" -s compiler.version=14 -s arch=x86 -s build_type=Debug -s compiler.runtime=MDd

     $ cmake ../src -G "Visual Studio 14"

### Примечание
Проект будет сконфигурирован для Visual Studio 2015, x86, Debug. Для другой конфигурации обратитесь к справке по командам CMake и Conan.

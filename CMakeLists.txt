cmake_minimum_required(VERSION 3.22.1) # Укажите версию CMake

project(Module_26) # Замените "MyProject" на имя вашего проекта

# Укажите исходные файлы вашего проекта
set(SOURCES
    src/main.cpp
    src/array.cpp
)

# Добавьте исполняемый файл
add_executable(main ${SOURCES})
target_compile_options(main PRIVATE -g -O0)


# Укажите дополнительные настройки и библиотеки, если необходимо
# target_link_libraries(my_app your_library)

# Укажите директории для поиска заголовочных файлов, если необходимо
# target_include_directories(my_app PUBLIC include)
# include_directories(${CMAKE_SOURCE_DIR}/json/include)
include_directories(${CMAKE_SOURCE_DIR}/headers)
#include_directories(/usr/include/mysql)

# Установите параметры компиляции, если необходимо
# target_compile_options(my_app PRIVATE -Wall -Wextra)

# Укажите библиотеки MySQL Connector/C++
#target_link_libraries(main /usr/lib/x86_64-linux-gnu/mysqlclient)

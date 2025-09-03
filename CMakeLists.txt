cmake_minimum_required(VERSION 3.5) #установка версии cmake для сборки (данная и новее)

set(PROJECT_NAME InteractiveTimer) #переменная с названием поекта

#создание проекта (пространства проекта) с указанием языка
#определяет глобальные переменные PROJECT_SOURCE_DIR (папка исходников) и PROJECT_BINARY_DIR (папка сборки)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON) #добавляет к списку include-путей папки PROJECT_SOURCE_DIR и PROJECT_BINARY_DIR, для поиска заголовочных файлов

set(CMAKE_AUTOUIC ON) #генерация заголовочного файла для .ui (ui_timerwindow.h) с помощью UIC
set(CMAKE_AUTOMOC ON) #генерация moc_.cpp для каждого заголовочного файла в котором есть макрос Q_OBJECT с помощью MOC и добавляет его в список исходников
set(CMAKE_AUTORCC ON) #генерация .cpp с помощью RCC, который будет вследствии компилироваться вместе с исходниками

set(CMAKE_CXX_STANDARD 11) #указание версии языка для компилятора
set(CMAKE_CXX_STANDARD_REQUIRED ON) #строго указанная версия языка

#проверка на наличие и доступ пакета qt5 и его компонентов, создание целей для линковки
#REQUIRED - пакеты обязательны для сборки, иначе ошибка
find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

#создание объекта цели executable из списка исходников, в котором определяются файлы для дальнейшей работы uic, moc, rcc (которые настраивались выше)
add_executable(${PROJECT_NAME}
    main.cpp
    timerwindow.cpp
    interactivetimer.cpp
    timerwindow.ui
    res.qrc
)

#линковка с qt целями для использования include-пути и defines предпроцессором и линковки после компиляции
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Multimedia)

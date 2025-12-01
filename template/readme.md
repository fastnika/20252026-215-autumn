# Задача 1.4 - Расстояние между многоугольниками

## Описание

Решение задачи 1.4 из курса "Работа на ЭВМ и программирование" (МехМат МГУ, 3 семестр):
**Определить расстояние между двумя многоугольниками общего вида.**

## Структура проекта

```
.
├── build.sh                    # Скрипт сборки (Linux/Mac)
├── build.bat                   # Скрипт сборки (Windows)
├── CMakeLists.txt              # Основной CMake файл
├── readme.md                   # Этот файл
├── env/                        # Директория окружения
│   ├── exception/              # Обработка исключений
│   │   ├── CMakeLists.txt
│   │   ├── inc/base_exception.h
│   │   └── src/base_exception.cpp
│   ├── implement/              # Реализация геометрических классов
│   │   ├── CMakeLists.txt
│   │   ├── inc/polygon.h
│   │   └── src/polygon.cpp
│   ├── interface/              # Интерфейс приложения
│   │   ├── CMakeLists.txt
│   │   ├── inc/interface.h
│   │   ├── inc/interface_stream.h
│   │   ├── src/interface.cpp
│   │   └── src/interface_stream.cpp
│   └── resource/               # Ресурсы и макросы
│       ├── CMakeLists.txt
│       └── inc/resource.h
├── src/                        # Исходный файл приложения
│   └── main.cpp
└── test/                       # Сценарии тестирования
    ├── test_scenario_01.txt
    └── test_scenario_02.txt
```

## Сборка проекта

### Linux/Mac:
```bash
./build.sh
```

### Windows:
```cmd
build.bat
```

## Запуск приложения

### Интерактивный режим:
```bash
./out/bin/Example
```

### Режим самотестирования:
```bash
./out/bin/Example_selftest ./out/bin/test/test_scenario_01.txt
```

## Компоненты системы

### Point (Класс точки)
- Координаты: x, y (приватные)
- Методы: GetX(), GetY(), Distance(), Dot(), Cross(), Length()
- Перегруженные операторы: +, -, *

### Segment (Класс отрезка)
- Состоит из двух Point
- Методы: DistanceToPoint(), DistanceToSegment(), Intersects()

### Polygon (Класс многоугольника)
- Вектор вершин (приватный)
- Методы: Contains(), Intersects(), Distance(), Area()
- Главный метод: `double Distance(const Polygon& other)` - вычисляет расстояние между многоугольниками

### PolygonUtils (Пространство имён)
- Вспомогательные функции: AreCollinear(), IsPointOnSegment()
- Константы: EPSILON, INF

## Формат входных данных (для тестирования)

```
1          # Создать первый многоугольник
3          # Количество вершин
0 0        # Вершина 1
2 0        # Вершина 2
1 2        # Вершина 3
1          # Создать второй многоугольник
3          # Количество вершин
5 0        # Вершина 1
7 0        # Вершина 2
6 2        # Вершина 3
3          # Вычислить расстояние между многоугольниками
4          # Выход
```

## Ошибочные коды

- `0x0` - Успешное завершение
- `0x1` - Ошибка при самотестировании
- `0x1001` - Отсутствует входной файл
- `0x1004` - Некорректные входные данные
- `0x1005` - Ошибочная конфигурация

## Режимы компиляции

### Debug:
Включает отладочные сообщения (DEBUG_LOGGING) и флаги оптимизации -g -O0.

### Release:
Оптимизация -O3, отладочные сообщения отключены.

## Использованные технологии

- C++17
- CMake 3.10+
- Standard Library (iostream, vector, cmath, limits, fstream)
- Макросы логирования (ERR_LOGGING, DEBUG_LOGGING, LOGGING)
- Обработка исключений (try-catch)
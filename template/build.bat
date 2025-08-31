chcp 65001
del /S /Q out
cmake -B out .
cmake --build out
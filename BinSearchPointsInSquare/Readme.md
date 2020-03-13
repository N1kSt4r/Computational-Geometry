# Задача
Найти количество точек в прямоугольной области в реальном времени
# Алгоритм
Выполняется предобработка за ![](https://latex.codecogs.com/svg.latex?O(n^2)), где плоскость разбивается на прямоугольники с координатами ((0, 0), (![](https://latex.codecogs.com/svg.latex?x_i), ![](https://latex.codecogs.com/svg.latex?y_i)), где ![](https://latex.codecogs.com/svg.latex?x_i), ![](https://latex.codecogs.com/svg.latex?y_i)- координаты точки ![](https://latex.codecogs.com/svg.latex?p_{(i)}), в которых мы считаем количество точек. Пусть count(x) - количество точек в прямоугольнике х, тогда count((a, b), (c, d)) = count((0, 0), (c, d)) - count((0, 0), (a, d)) - count((0, 0), (c, b)) + count((0, 0), (a, b)). Местоположение каждой из 4 областей в сетке находится за ![](https://latex.codecogs.com/svg.latex?O(log(n))), где n - количество точек
# Пример работы




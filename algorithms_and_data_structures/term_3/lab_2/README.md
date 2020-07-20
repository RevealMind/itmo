# Графы, кратчайшие пути

## [Задача A](a.cpp). Флойд
<p align="center"><i>ограничение по времени на тест 2 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>

__Условие:__  
Полный ориентированный взвешенный граф задан матрицей смежности. Постройте матрицу кратчайших путей между его вершинами. Гарантируется, что в графе нет циклов отрицательного веса.

__Входные данные:__  
В первой строке вводится единственное число N $(1 ≤ N ≤ 100)$ — количество вершин графа. В следующих N строках по N чисел задается матрица смежности графа (j-ое число в i-ой строке — вес ребра из вершины i в вершину j). Все числа по модулю не превышают 100. На главной диагонали матрицы — всегда нули.

__Выходные данные:__  
Выведите N строк по N чисел — матрицу расстояний между парами вершин, где j-ое число в i-ой строке равно весу кратчайшего пути из вершины i в j.

__Пример__  
>__Входные данные__  
>4<br>
>0 5 9 100<br>
>100 0 2 8<br>
>100 100 0 7<br>
>4 100 100 0<br>
>__Выходные данные__  
>0 5 7 13 <br>
>12 0 2 8 <br>
>11 16 0 7 <br>
>4 9 11 0 <br>

***

## [Задача B](b.cpp). Кратчайший путь-2
<p align="center"><i>ограничение по времени на тест 2 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>

__Условие:__  
Дан неориентированный связный взвешенный граф. Найдите кратчайшее расстояние от первой вершины до всех вершин.

__Входные данные:__  
В первой строке входного файла два числа: n и m $(2 ≤ n ≤ 30\ 000, 1 ≤ m ≤ 400\ 000)$, где n — количество вершин графа, а m — количество ребер. 

__Выходные данные:__  
Выведите n чисел — для каждой вершины кратчашее расстояние до нее.

__Пример__  
>__Входные данные__  
>4 5<br>
>1 2 1<br>
>1 3 5<br>
>2 4 8<br>
>3 4 1<br>
>2 3 3<br>
>__Выходные данные__  
>0 1 4 5 

***

## [Задача C](c.cpp). Цикл отрицательного веса
<p align="center"><i>ограничение по времени на тест 2 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>

__Условие:__  
Дан ориентированный граф. Определите, есть ли в нем цикл отрицательного веса, и если да, то выведите его.

__Входные данные:__  
Во входном файле в первой строке число N $(1 ≤ N ≤ 100)$ — количество вершин графа. В следующих N строках находится по N чисел — матрица смежности графа. Все веса ребер не превышают по модулю $10\ 000$. Если ребра нет, то соответствующее число равно $100\ 000$.

__Выходные данные:__  
В первой строке выходного файла выведите «YES», если цикл существует или «NO» в противном случае. При его наличии выведите во второй строке количество вершин в искомом цикле и в третьей строке — вершины входящие в этот цикл в порядке обхода.

__Пример__  
>__Входные данные__  
>2<br>
>0 -1<br>
>-1 0<br>
>__Выходные данные__  
>YES<br>
>2<br>
>2 1 

***

## [Задача D](d.cpp). Кратчайший путь длины K
<p align="center"><i>ограничение по времени на тест 4 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>

__Условие:__  
Дан ориентированный граф. Найдите кратчайшие пути, состоящие из K рёбер, от S до всех вершин.

__Входные данные:__  
В первой строке дано целых четыре целых числа: $1 ≤ N, M ≤ 10^4$ — количества вершин и рёбер, $0 ≤ K ≤ 100$ — количество рёбер в кратчайших путях, $1 ≤ S ≤ N$ — начальная вершина.

__Выходные данные:__  
Выведите ровно N чисел по одному в строке. i-е число — длина минимального пути из ровно K рёбер из S в i, или  - 1, если пути не существует.

__Пример__  
>__Входные данные__  
>3 3 1 1<br>
>1 2 100<br>
>2 3 300<br>
>1 3 2<br>
>__Выходные данные__  
>-1<br>
>100<br>
>2<br>

>__Входные данные__  
>3 3 2 1<br>
>1 2 100<br>
>2 3 300<br>
>1 3 2<br>
>__Выходные данные__  
>-1<br>
>-1<br>
>400<br>


***

## [Задача E](e.cpp). Кратчайшие пути
<p align="center"><i>ограничение по времени на тест 2 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>

__Условие:__  
Вам дан взвешенный ориентированный граф и вершина s в нём. Для каждой вершины графа u выведите длину кратчайшего пути от вершины s до вершины u.

__Входные данные:__  
Первая строка входного файла содержит три целых числа n, m, s — количество вершин и ребёр в графе и номер начальной вершины соответственно $(2 ≤ n ≤ 2\ 000, 1 ≤ m ≤ 5\ 000)$. 

__Выходные данные:__  
Выведите n строчек — для каждой вершины u выведите длину кратчайшего пути из s в u. Если не существует пути между s и u, выведите «*». Если не существует кратчайшего пути между s и u, выведите «-».

__Пример__  
>__Входные данные__  
>6 7 1<br>
>1 2 10<br>
>2 3 5<br>
>1 3 100<br>
>3 5 7<br>
>5 4 10<br>
>4 3 -18<br>
>6 1 -1<br>
>__Выходные данные__  
>0<br>
>10<br>
>-<br>
>-<br>
>-<br>
>*<br>


***

## [Задача F](f.cpp). В поисках утраченного кефира
<p align="center"><i>ограничение по времени на тест 2 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>
__Условие:__  
Школьник Вася хочет найти запасы спрятанного кефира. По легенде, кефир находится в домиках a, b или c. Вася хочет проверить каждый из этих трёх домиков, потратив на это минимальное количество времени.Местность, в которой находится Вася представляет собой n домиков, пронумерованных числами от 1 до n. Некоторые из домиков соединены дорогами, по которым можно ходить в обе стороны. Время прохождения i-й дороги составляет $w_i$ секунд. Путём в графе называется непустая последовательность вершин, такая что все соседние вершины соединены дорогой. Требуется помочь Васе найти путь, содержащий вершины a, b, c, такой что суммарное время прохождения всех дорог на пути минимально. При этом, если мы прошли по какой-то дороге дважды (или более), то и время её прохождения следует учитывать соответствующее количество раз. Начинать свой путь Вася может из любой вершины.Гарантируется, что a, b, c — попарно различные домики.

__Входные данные:__  
В первой строке ввода записаны два числа n и m $(3 ≤ n ≤ 100\ 000, 0 ≤ m ≤ 200\ 000)$ — количество домиков в ЛКШ и дорог между ними соответственно.

__Выходные данные:__  
Выведите одно целое число — минимальное возможное время, которое нужно затратить на прохождение пути, содержащего домики a, b и c. Если пути, содержащего все три домика не существует, то выведите -1.

__Пример__  
>__Входные данные__  
>4 4<br>
>1 2 3<br>
>2 3 1<br>
>3 4 7<br>
>4 2 10<br>
>1 4 3<br>
>__Выходные данные__  
>11
>__Входные данные__  
>4 2<br>
>1 2 10<br>
>2 3 5<br>
>1 2 4<br>
>__Выходные данные__  
>-1

***

## [Задача H](h.cpp). Dwarf Tower
<p align="center"><i>ограничение по времени на тест 3 секунды<br>
ограничение по памяти на тест 256 мегабайт<br>
вводстандартный ввод<br>
выводстандартный вывод</i></p>

__Условие:__  
Little Vasya is playing a new game named "Dwarf Tower". In this game there are n different items, which you can put on your dwarf character. Items are numbered from 1 to n. Vasya wants to get the item with number 1.

There are two ways to obtain an item:

* You can buy an item. The i-th item costs ci money.
* You can craft an item. This game supports only m types of crafting. To craft an item, you give two particular different items and get another one as a result.

Help Vasya to spend the least amount of money to get the item number 1.

__Входные данные:__  
The first line of input contains two integers n and m $(1 ≤ n ≤ 200 000;0 ≤ m ≤ 500 000)$ — the number of different items and the number of crafting types.

The second line contains n integers ci — values of the items $(0 ≤ c_i ≤ 10^9)$.

The following m lines describe crafting types, each line contains three distinct integers $a_i$, $x_i$, $y_i$ — ai is the item that can be crafted from items $x_i$ and $y_i$ $(1 ≤ ai, xi, yi ≤ n; ai ≠ xi; xi ≠ yi; yi ≠ ai)$.

__Выходные данные:__  
The output should contain a single integer — the least amount of money to spend.

__Пример__  
>__Входные данные__  
>3 3<br>
>1 3 7<br>
>1 2 6<br>
>2 3 5<br>
>11<br>
>__Выходные данные__  
>Possible<br>

>__Входные данные__  
>3 3<br>
>1 3 7<br>
>1 2 6<br>
>2 3 5<br>
>25<br>
>__Выходные данные__  
>Possible<br>

>__Входные данные__  
>2 1<br>
>1 2 1<br>
>9<br>
>__Выходные данные__  
>Possible<br>

>__Входные данные__  
>2 1<br>
>2 1 1<br>
>1000000000000000000<br>
>__Выходные данные__  
>Impossible<br>

>__Входные данные__  
>4 3<br>
>1 3 10<br>
>1 2 10<br>
>2 3 10<br>
>1000<br>
>__Выходные данные__  
>Impossible<br>


***
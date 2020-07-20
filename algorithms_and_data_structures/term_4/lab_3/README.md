# Математика

## [Задача A](a.cpp). Массовая проверка простоты
<p align="center"><i>ограничение по времени на тест:  2 секунды <br>
ограничение по памяти на тест: 256 мегабайт  <br>
ввод: стандартный ввод  <br>
вывод: стандартный вывод</i></p>

__Условие__ 

Целое число p ≥ 2 является простым, если у него нет делителей кроме 1 и p. Необходимо для всех чисел во входном файле проверить простые они или нет.

__Входные данные__

В первой строке задано число n (2 ≤ n ≤ 300000). В следующих n строках заданы числа a<sub>i</sub> (2 ≤ a<sub>i</sub> ≤ 10<sup>6</sup>), которые нужно проверить на простоту

__Выходные данные__

Для каждого числа во входном файле выведите на отдельной строке YES или NO (в зависимости от того, простое оно или нет).

__Пример__

>__Входные данные__
4
60
14
3
55
__Выходные данные__
NO
NO
YES
NO

---

## [Задача B](b.cpp). Массовое разложение на множители
<p align="center"><i>ограничение по времени на тест:  0.5 секунды <br>
ограничение по памяти на тест: 64 мегабайт  <br>
ввод: стандартный ввод  <br>
вывод: стандартный вывод</i></p>

__Условие__ 

Дано много чисел. Требуется разложить их все на простые множители.

__Входные данные__

В первой строке задано число n (2 ≤ n ≤ 300000). В следующих n строках заданы числа a<sub>i</sub> (2 ≤ a<sub>i</sub> ≤ 106), которые нужно разложить на множители.

__Выходные данные__

Для каждого числа выведите в отдельной строке разложение на простые множители в порядке возрастания множителей.

__Пример__

>__Входные данные__
4
60
14
3
55
__Выходные данные__
2 2 3 5
2 7
3
5 11

---

## [Задача C](c.cpp). Большая проверка на простоту
<p align="center"><i>ограничение по времени на тест:  2 секунды <br>
ограничение по памяти на тест: 64 мегабайт  <br>
ввод: стандартный ввод  <br>
вывод: стандартный вывод</i></p>

__Условие__ 

Дано n натуральных чисел a<sub>i</sub>. Определите для каждого числа, является ли оно простым.

__Входные данные__

Программа получает на вход число n, 1 ≤ n ≤ 1000 и далее n чисел a<sub>i</sub>, 1 ≤ a<sub>i</sub> ≤ 10<sup>18</sup>.

__Выходные данные__

Если число a<sub>i</sub> простое, программа должна вывести YES, для составного числа программа должна вывести NO.

__Пример__

>__Входные данные__
4
1
5
10
239
__Выходные данные__
NO
YES
NO
YES

---

## [Задача D](d.cpp). Китайская теорема
<p align="center"><i>ограничение по времени на тест:  2 секунды <br>
ограничение по памяти на тест: 64 мегабайт  <br>
ввод: стандартный ввод  <br>
вывод: стандартный вывод</i></p>

__Условие__ 

Решите в целых числах систему уравнений


x = a (mod n),
x = b (mod m)


где n и m - взаимно простые числа. Среди решений выбрать наименьшее неотрицательное число.

__Входные данные__

Входной файл содержит четыре целых числа a, b, n и m (1 ≤ n, m ≤ 10<sup>6</sup>, 0 ≤ a < n, 0 ≤ b < m).

__Выходные данные__

В выходной файл выведите искомое наименьшее неотрицательное число x.

__Пример__

>__Входные данные__
1 0 2 3
__Выходные данные__
3

>__Входные данные__
3 2 5 9
__Выходные данные__
38

---

## [Задача E](e.cpp). Взлом RSA
<p align="center"><i>ограничение по времени на тест:  2 секунды <br>
ограничение по памяти на тест: 64 мегабайт  <br>
ввод: стандартный ввод  <br>
вывод: стандартный вывод</i></p>

__Условие__ 

В 1977 году Ronald Linn Rivest, Adi Shamir и Leonard Adleman предложили новую криптографическую схему RSA, используемую до сих пор. RSA является криптосистемой с открытым ключом: зашифровать сообщение может кто угодно, знающий общеизвестный открытый ключ, а расшифровать сообщение — только тот, кто знает специальный секретный ключ.

Желающий использовать систему RSA для получения сообщений должен сгенерировать два простых числа p и q, вычислить n = pq и сгенерировать два числа e и d такие, что {ed ≡ 1 ± od{(p - 1)(q - 1)}} (заметим, что {(p - 1)(q - 1) = φ(n)}). Числа n и e составляют открытый ключ и являются общеизвестными. Число d является секретным ключом, также необходимо хранить в тайне и разложение числа n на простые множители, так как это позволяет вычислить секретный ключ d.

Сообщениями в системе RSA являются числа из Z<sub>n</sub>. Пусть M — исходное сообщение. Для его шифрования вычисляется значение C = M<sup>e</sup> mod n (для этого необходимо только знание открытого ключа). Полученное зашифрованное сообщение C передается по каналу связи. Для его расшифровки необходимо вычислить значение M = C<sup>d</sup> mod n, а для этого необходимо знание секретного ключа.

Вы перехватили зашифрованное сообщение C и знаете только открытый ключ: числа n и e. "Взломайте" RSA — расшифруйте сообщение на основе только этих данных.

__Входные данные__

Программа получает на вход три натуральных числа: n, e, C, n ≤ 10<sup>9</sup>, e ≤ 10<sup>9</sup>, C < n. Числа n и e являются частью какой-то реальной схемы RSA, т.е. n является произведением двух простых и e взаимно просто с φ(n). Число C является результатом шифрования некоторого сообщения M.

__Выходные данные__

Выведите одно число M (0 ≤ M < n), которое было зашифровано такой криптосхемой.

__Пример__

>__Входные данные__
143
113
41
__Выходные данные__
123


---

>__Входные данные__
9173503
3
4051753
__Выходные данные__
111111

---

## [Задача F](f.cpp). Задача для второклассника
<p align="center"><i>ограничение по времени на тест:  2 секунды <br>
ограничение по памяти на тест: 256 мегабайт  <br>
ввод: стандартный ввод  <br>
вывод: стандартный вывод</i></p>

__Условие__ 

Вам даны два числа. Необходимо найти их произведение.

__Входные данные__

Входные данные состоят из двух строк, на каждой из которых находится целое одно целое число, длина которого не превосходит двухсот пятидесяти тысяч символов.

__Выходные данные__

Выведите произведение данных чисел.

__Пример__

>__Входные данные__
2
2
__Выходные данные__
4

>__Входные данные__
1
-1
__Выходные данные__
-1
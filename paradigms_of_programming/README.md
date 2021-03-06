# Парадигмы программирования

---

## [Задание 1. Хэширование](task_1)

Модификации
 * *Сложная*
    * Класс должен иметь имя `CalcSHA256` и подсчитывать [SHA-256](https://en.wikipedia.org/wiki/Secure_Hash_Algorithm)
 * *Простая*
    * Напишите простой аналог утилиты [sha256sum](http://linux.die.net/man/1/sha256sum)
    * Класс должен называться `SHA256Sum`
    * Список файлов для хэширования передается в виде аргументов командной строки
    * Если список файлов пуст, то хэшируется стандартный ввод а именем файла считается `-`
    * Вывод хэшей осуществляется в формате `<хэш> *<имя файла>`

## [Задание 2. Бинарный поиск](task_2)

Модификации
 * *Базовая*
    * Класс `BinarySearch` должен находиться в пакете `search`
 * *Простая*
    * Если в массиве `a` отсутствует элемент, равный `x`, то требуется
      вывести индекс вставки в формате, определенном в
      [`Arrays.binarySearch`](http://docs.oracle.com/javase/8/docs/api/java/util/Arrays.html#binarySearch-int:A-int-).
    * Класс должен иметь имя `BinarySearchMissing`
 * *Сложная*
    * Требуется вывести два числа: начало и длину диапазона элементов,
      равных `x`. Если таких элементов нет, то следует вывести
      пустой диапазон, у которого левая граница совпадает с местом
      вставки элемента `x`.
    * Не допускается использование типов `long` и `BigInteger`.
    * Класс должен иметь имя `BinarySearchSpan`

## [Задание 3. Очередь на массиве](task_3)

Модификации
 * *Базовая*
    * Классы должны находиться в пакете `queue`
 * *Простая*
    * Реализовать метод `toArray`, возвращающий массив,
      содержащий элементы, лежащие в очереди в порядке
      от головы к хвосту.
    * Исходная очередь должна остаться неизменной
    * Дублирования кода быть не должно
 * *Сложная*
    * Реализовать методы
        * `push` – добавить элемент в начало очереди
        * `peek` – вернуть последний элемент в очереди
        * `remove` – вернуть и удалить последний элемент из очереди

## [Задание 4. Очередь на связном списке](task_4)

Модификации
 * *Простая*
    * Добавить в интерфейс очереди и реализовать метод
      `toArray`, возвращающий массив,
      содержащий элементы, лежащие в очереди в порядке
      от головы к хвосту
    * Исходная очередь должна оставаться неизменной
    * Дублирования кода быть не должно
 * *Сложная*
    * Добавить в интерфейс очереди и реализовать методы
        * `filter(predicate)` – создать очередь, содержащую элементы, удовлетворяющие
            [предикату](https://docs.oracle.com/javase/8/docs/api/java/util/function/Predicate.html)
        * `map(function)` – создать очередь, содержащую результаты применения
            [функции](https://docs.oracle.com/javase/8/docs/api/java/util/function/Function.html)
    * Исходная очередь должна остаться неизменной
    * Тип возвращаемой очереди должен соответствовать типу исходной очереди
    * Взаимный порядок элементов должен сохраняться
    * Дублирования кода быть не должно

## [Задание 5. Вычисление выражений](task_5-8)

Модификации
 * *Базовая*
    * Реализовать интерфейс `Expression`
 * *Простая*
    * Реализовать интерфейс `DoubleExpression`
 * *Сложная*
    * Реализовать интерфейсы `DoubleExpression` и `TripleExpression`

## [Задание 6. Разбор выражений](task_5-8)

Модификации
 * *Базовая*
    * Класс `ExpressionParser` должен реализовывать интерфейс
        `Parser`
    * Результат разбора должен реализовывать интерфейс
        `TripleExpression`
 * *Простая*
    * Дополнительно реализовать бинарные операции:
        * `&` — побитное И, приоритет меньше чем у `+` (`6 & 1 + 2` равно `6 & (1 + 2)` равно 2);
        * `^` — побитный XOR, приоритет меньше чем у `&` (`6 ^ 1 + 2` равно `6 ^ (1 + 2)` равно 5);
        * `|` — побитное ИЛИ, приоритет меньше чем у `^` (`6 | 1 + 2` равно `6 | (1 + 2)` равно 7);
 * *Сложная*
    * Реализовать операции из простой модификации.
    * Дополнительно реализовать унарные операции (приоритет как у унарного минуса):
        * `~` — побитное отрицание, `~-5` равно 4;
        * `count` — число установленных битов, `count -5` равно 31.

## [Задание 7. Обработка ошибок](task_5-8)

Модификации
 * *Базовая*
    * Класс `ExpressionParser` должен реализовывать интерфейс `Parser`
    * Классы `CheckedAdd`, `CheckedSubtract`, `CheckedMultiply`,
        `CheckedDivide` и `CheckedNegate` должны реализовывать интерфейс `TripleExpression`
    * Нельзя использовать типы `long` и `double`
    * Нельзя использовать методы классов `Math` и `StrictMath`
 * *Простая*
    * Дополнительно реализовать унарные операции:
        * `log10` — логарифм по уснованию 10, `log10 1000` равно 3;
        * `pow10` — 10 в степени, `pow10 4` равно 10000.
 * *Сложная*
    * Реализовать операции простой модификации.
    * Дополнительно реализовать бинарные операции (максимальный приоритет):
        * `**` — возведение в степень, `2 ** 3` равно 8;
        * `//` — логарифм, `10 // 2` равно 3.

## [Задание 8. Вычисление в различных типах](task_5-8)

Модификации
 * *Базовая*
    * Класс `GenericTabulator` должен реализовывать интерфейс `Tabulator` и
      сроить трехмерную таблицу значений заданного выражения.
        * `mode` — режим вычислений:
           * `i` — вычисления в `int` с проверкой на переполнение;
           * `d` — вычисления в `double` без проверки на переполнение;
           * `bi` — вычисления в `BigInteger`.
        * `expression` — выражение, для которого надо построить таблицу;
        * `x1`, `x2` — минимальное и максимальное значения переменной `x` (включительно)
        * `y1`, `y2`, `z1`, `z2` — аналогично для `y` и `z`.
        * Результат: элемент `result[i][j][k]` должен содержать
          значение выражения для `x = x1 + i`, `y = y1 + j`, `z = z1 + k`.
          Если значение не определено (например, по причине переполнения),
          то соответствующий элемент должен быть равен `null`.
 * *Простая*
    * Дополнительно реализовать поддержку режимов:
        * `u` — вычисления в `int` без проверки на переполнение;
        * `l` — вычисления в `long` без проверки на переполнение;
        * `s` — вычисления в `s` без проверки на переполнение.
 * *Сложная*
    * Реализовать операции из простой модификации.
    * Дополнительно реализовать унарные операции:
        * `count` — число установленных битов, `count 5` равно 2.
    * Дополнительно реализовать бинарную операцию (минимальный приоритет):
        * `min` — минимум, `2 min 3` равно 2;
        * `max` — максимум, `2 max 3` равно 3.
    * Дополнительно реализовать поддержку режимов:
        * `u` — вычисления в `int` без проверки на переполнение;
        * `l` — вычисления в `long` без проверки на переполнение;
        * `s` — вычисления в `s` без проверки на переполнение.
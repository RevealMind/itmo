# Java
## Задание 1. Обход файлов

+ Разработайте класс Walk, осуществляющий подсчет хеш-сумм файлов.

    + Формат запуска

       `java Walk <входной файл> <выходной файл>`

    + Входной файл содержит список файлов, которые требуется обойти.
    + Выходной файл должен содержать по одной строке для каждого файла. Формат строки:

        `<шестнадцатеричная хеш-сумма> <путь к файлу>`

    + Для подсчета хеш-суммы используйте алгоритм FNV.
    + Если при чтении файла возникают ошибки, укажите в качестве его хеш-суммы 00000000.
    + Кодировка входного и выходного файлов — UTF-8.
    + Если родительская директория выходного файла не существует, то соответствующий путь надо создать.
    + Размеры файлов могут превышать размер оперативной памяти.
    + Пример

        + Входной файл

            ```
            java/info/kgeorgiy/java/advanced/walk/samples/1
            java/info/kgeorgiy/java/advanced/walk/samples/12
            java/info/kgeorgiy/java/advanced/walk/samples/123
            java/info/kgeorgiy/java/advanced/walk/samples/1234
            java/info/kgeorgiy/java/advanced/walk/samples/1
            java/info/kgeorgiy/java/advanced/walk/samples/binary
            java/info/kgeorgiy/java/advanced/walk/samples/no-such-file
            ```

        + Выходной файл

            ```
            050c5d2e java/info/kgeorgiy/java/advanced/walk/samples/1
            2076af58 java/info/kgeorgiy/java/advanced/walk/samples/12
            72d607bb java/info/kgeorgiy/java/advanced/walk/samples/123
            81ee2b55 java/info/kgeorgiy/java/advanced/walk/samples/1234
            050c5d2e java/info/kgeorgiy/java/advanced/walk/samples/1
            8e8881c5 java/info/kgeorgiy/java/advanced/walk/samples/binary
            00000000 java/info/kgeorgiy/java/advanced/walk/samples/no-such-file
            ```


+ Усложненная версия:

    + Разработайте класс RecursiveWalk, осуществляющий подсчет хеш-сумм файлов в директориях

    + Входной файл содержит список файлов и директорий, которые требуется обойти. Обход директорий осуществляется рекурсивно.

    + Пример

        + Входной файл

        ```
        java/info/kgeorgiy/java/advanced/walk/samples/binary
        java/info/kgeorgiy/java/advanced/walk/samples
        ```

        + Выходной файл

        ```
        8e8881c5 java/info/kgeorgiy/java/advanced/walk/samples/binary
        050c5d2e java/info/kgeorgiy/java/advanced/walk/samples/1
        2076af58 java/info/kgeorgiy/java/advanced/walk/samples/12
        72d607bb java/info/kgeorgiy/java/advanced/walk/samples/123
        81ee2b55 java/info/kgeorgiy/java/advanced/walk/samples/1234
        8e8881c5 java/info/kgeorgiy/java/advanced/walk/samples/binary
        ```


+ При выполнении задания следует обратить внимание на:

    + Дизайн и обработку исключений, диагностику ошибок.
    + Программа должна корректно завершаться даже в случае ошибки.
    + Корректная работа с вводом-выводом.
    + Отсутствие утечки ресурсов.

+ Требования к оформлению задания.

    + Проверяется исходный код задания.
    + Весь код должен находиться в пакете ru.ifmo.rain.фамилия.walk.

## Задание 2. Множество на массиве

+ Разработайте класс ArraySet, реализующие неизменяемое упорядоченное множество.
    + Класс ArraySet должен реализовывать интерфейс SortedSet (упрощенная версия) или NavigableSet (усложненная версия).
    + Все операции над множествами должны производиться с максимально возможной асимптотической эффективностью.

+ При выполнении задания следует обратить внимание на:
    + Применение стандартных коллекций.
    + Избавление от повторяющегося кода.

## Задание 3. Студенты

+ Разработайте класс StudentDB, осуществляющий поиск по базе данных студентов.

+ Класс StudentDB должен реализовывать интерфейс StudentQuery (простая версия) или StudentGroupQuery (сложная версия).

+ Каждый метод должен состоять из ровно одного оператора. При этом длинные операторы надо разбивать на несколько строк.

+ При выполнении задания следует обратить внимание на:
    + Применение лямбда-выражений и потоков.
    + Избавление от повторяющегося кода.

## Задание 4. Implementor

+ Реализуйте класс Implementor, который будет генерировать реализации классов и интерфейсов.

+ Аргументы командной строки: полное имя класса/интерфейса, для которого требуется сгенерировать реализацию.

+ В результате работы должен быть сгенерирован java-код класса с суффиксом Impl, расширяющий (реализующий) указанный класс (интерфейс).

+ Сгенерированный класс должен компилироваться без ошибок.

+ Сгенерированный класс не должен быть абстрактным.

+ Методы сгенерированного класса должны игнорировать свои аргументы и возвращать значения по умолчанию.

+ В задании выделяются три уровня сложности:

    - Простой — Implementor должен уметь реализовывать только интерфейсы (но не классы). Поддержка generics не требуется.
    - Сложный — Implementor должен уметь реализовывать и классы и интерфейсы. Поддержка generics не требуется.
    - Бонусный — Implementor должен уметь реализовывать generic-классы и интерфейсы. Сгенерированный код должен иметь корректные параметры типов и не порождать UncheckedWarning.

## Задание 5. Jar Implementor

+ Создайте .jar-файл, содержащий скомпилированный Implementor и сопутствующие классы.

    + Созданный .jar-файл должен запускаться командой java -jar.
    + Запускаемый .jar-файл должен принимать те же аргументы командной строки, что и класс Implementor.

+ Модифицируйте Implemetor так, что бы при запуске с аргументами -jar имя-класса файл.jar он генерировал .jar-файл с реализацией соответствующего класса (интерфейса).

+ Для проверки, кроме исходного кода так же должны быть предъявлены:
    + скрипт для создания запускаемого .jar-файла, в том числе, исходный код манифеста;
    + запускаемый .jar-файл.

+ Данное домашнее задание сдается только вместе с предыдущим. Предыдущее домашнее задание отдельно сдать будет нельзя.

+ Сложная версия. Решение должно быть модуляризовано.

## Задание 6. Javadoc

+ Документируйте класс Implementor и сопутствующие классы с применением Javadoc.

    + Должны быть документированы все классы и все члены классов, в том числе закрытые (private).
    + Документация должна генерироваться без предупреждений.
    + Сгенерированная документация должна содержать корректные ссылки на классы стандартной библиотеки.

+ Для проверки, кроме исходного кода так же должны быть предъявлены:
    + скрипт для генерации документации;
    + сгенерированная документация.

+ Данное домашнее задание сдается только вместе с предыдущим. Предыдущее домашнее задание отдельно сдать будет нельзя.

## Задание 7. Итеративный параллелизм

+ Реализуйте класс IterativeParallelism, который будет обрабатывать списки в несколько потоков.

+ В простом варианте должны быть реализованы следующие методы:

    + `minimum(threads, list, comparator)` — первый минимум;
    + `maximum(threads, list, comparator)` — первый максимум;
    + `all(threads, list, predicate)` — проверка, что все элементы списка удовлетворяют предикату;
    + `any(threads, list, predicate)` — проверка, что существует элемент списка, удовлетворяющий предикату.

+ В сложном варианте должны быть дополнительно реализованы следующие методы:

    + `filter(threads, list, predicate)` — вернуть список, содержащий элементы удовлетворяющие предикату;
    + `map(threads, list, function)` — вернуть список, содержащий результаты применения функции;
    + `join(threads, list)` — конкатенация строковых представлений элементов списка.

+ Во все функции передается параметр threads — сколько потоков надо использовать при вычислении. Вы можете рассчитывать, что число потоков не велико.

+ Не следует рассчитывать на то, что переданные компараторы, предикаты и функции работают быстро.

+ При выполнении задания нельзя использовать Concurrency Utilities.

+ Рекомендуется подумать, какое отношение к заданию имеют моноиды.

## Задание 8. Параллельный запуск
+ Напишите класс ParallelMapperImpl, реализующий интерфейс ParallelMapper.

    ```java
    public interface ParallelMapper extends AutoCloseable {
        <T, R> List<R> run(
            Function<? super T, ? extends R> f,
            List<? extends T> args
        ) throws InterruptedException;

        @Override
        void close() throws InterruptedException;
    }
    ```

    + Метод run должен параллельно вычислять функцию `f` на каждом из указанных аргументов (`args`).
    + Метод close должен останавливать все рабочие потоки.
    + Конструктор `ParallelMapperImpl(int threads)` создает `threads` рабочих потоков, которые могут быть использованы для распараллеливания.
    + К одному ParallelMapperImpl могут одновременно обращаться несколько клиентов.
    + Задания на исполнение должны накапливаться в очереди и обрабатываться в порядке поступления.
    + В реализации не должно быть активных ожиданий.

+ Модифицируйте касс `IterativeParallelism` так, чтобы он мог использовать `ParallelMapper`.

    + Добавьте конструктор IterativeParallelism(ParallelMapper)
    + Методы класса должны делить работу на `threads` фрагментов и исполнять их при помощи `ParallelMapper`.
    + Должна быть возможность одновременного запуска и работы нескольких клиентов, использующих один `ParallelMapper`.
    + При наличии `ParallelMapper` сам `IterativeParallelism` новые потоки создавать не должен.

## Задание 9. Web Crawler

+ Напишите потокобезопасный класс WebCrawler, который будет рекурсивно обходить сайты.
    + Класс WebCrawler должен иметь конструктор

        ```java
        public WebCrawler(Downloader downloader, int downloaders, int extractors, int perHost)
        ```

        + downloader позволяет скачивать страницы и извлекать из них ссылки;
        + downloaders — максимальное число одновременно загружаемых страниц;
        + extractors — максимальное число страниц, из которых извлекаются ссылки;
        + perHost — максимальное число страниц, одновременно загружаемых c одного хоста. Для опредения хоста следует использовать метод getHost класса URLUtils из тестов.

    + Класс WebCrawler должен реализовывать интерфейс Crawler
        ```java
        public interface Crawler extends AutoCloseable {
            List<String> download(String url, int depth) throws IOException;

            void close();
        }
        ```

        + Метод download должен рекурсивно обходить страницы, начиная с указанного URL на указанную глубину и возвращать список загруженных страниц и файлов. Например, если глубина равна 1, то должна быть загружена только указанная страница. Если глубина равна 2, то указанная страница и те страницы и файлы, на которые она ссылается и так далее. Этот метод может вызываться параллельно в нескольких потоках.
        + Загрузка и обработка страниц (извлечение ссылок) должна выполняться максимально параллельно, с учетом ограничений на число одновременно загружаемых страниц (в том числе с одного хоста) и страниц, с которых загружаются ссылки.
        + Для распараллеливания разрешается создать до downloaders + extractors вспомогательных потоков.
        + Загружать и/или извлекать ссылки из одной и той же страницы в рамках одного обхода (download) запрещается.
        + Метод close должен завершать все вспомогательные потоки.

    + Для загрузки страниц должен применяться Downloader, передаваемый первым аргументом конструктора.
        ```java
        public interface Downloader {
            public Document download(final String url) throws IOException;
        }
        ```

        + Метод download загружает документ по его адресу ([URL](http://tools.ietf.org/html/rfc3986)).
        + Документ позволяет получить ссылки по загруженной странице:
            ```java
            public interface Document {
                List<String> extractLinks() throws IOException;
            }
            ```

        Ссылки, возвращаемые документом являются абсолютными и имеют схему http или https.

    + Должен быть реализован метод main, позволяющий запустить обход из командной строки
        + Командная строка

            `WebCrawler url [depth [downloads [extractors [perHost]]]]`

        + Для загрузки страниц требуется использовать реализацию CachingDownloader из тестов.

+ Версии задания
    - Простая — можно не учитывать ограничения на число одновременных закачек с одного хоста (perHost >= downloaders).
    - Полная — требуется учитывать все ограничения.
    - Бонусная — сделать параллельный обод в ширину.

## Задание 10. HelloUDP

+ Реализуйте клиент и сервер, взаимодействующие по UDP.
+ Класс HelloUDPClient должен отправлять запросы на сервер, принимать результаты и выводить их на консоль.
    - Аргументы командной строки:
        + имя или ip-адрес компьютера, на котором запущен сервер;
        + номер порта, на который отсылать запросы;
        + префикс запросов (строка);
        + число параллельных потоков запросов;
        + число запросов в каждом потоке.
    - Запросы должны одновременно отсылаться в указанном числе потоков. Каждый поток должен ожидать обработки своего запроса и выводить
сам запрос и результат его обработки на консоль. Если запрос не был обработан, требуется послать его заново.
    - Запросы должны формироваться по схеме `<префикс запросов><номер потока>_<номер запроса в потоке>`.
+ Класс HelloUDPServer должен принимать задания, отсылаемые классом HelloUDPClient и отвечать на них.
    - Аргументы командной строки:
        + номер порта, по которому будут приниматься запросы;
        + число рабочих потоков, которые будут обрабатывать запросы.
    - Ответом на запрос должно быть `Hello, <текст запроса>`.
    - Если сервер не успевает обрабатывать запросы, прием запросов может быть временно приостановлен.
+ Бонусный вариант. Реализация должна быть полностью неблокирующей.
    + Клиент не должен создавать потоков.
    + В реализации не должно быть активных ожиданий, в том числе через Selector.
SET dir=out/production

javac -d %dir% info/kgeorgiy/java/advanced/implementor/*.java
javac -d %dir% -cp .;%dir% ru/ifmo/rain/janchenkov/implementor/*.java

jar cfe implementor.jar ru.ifmo.rain.janchenkov.implementor.JarImplementor -C %dir%/ info/kgeorgiy/java/advanced/implementor/*.class %dir%/ru/ifmo/rain/janchenkov/implementor/*.class

SET dir=out/production/

javac -d %dir% info/kgeorgiy/java/advanced/implementor/JarImpler.java
javac -d %dir% -cp .;%dir% ru/ifmo/rain/janchenkov/implementor/JarImplementor.java

java  -Dfile.encoding=UTF-8 -cp  %dir% -p ../lib;../artifacts -m  info.kgeorgiy.java.advanced.implementor jar-class ru.ifmo.rain.janchenkov.implementor.JarImplementor 8v
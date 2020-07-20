SET dir=out/production/

javac -d %dir% -cp ../artifacts/info.kgeorgiy.java.advanced.implementor.jar; ru/ifmo/rain/janchenkov/implementor/*.java
java -p ../artifacts;../lib; -cp %dir% -m info.kgeorgiy.java.advanced.implementor class ru.ifmo.rain.janchenkov.implementor.Implementor

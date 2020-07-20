SET dir=out/production/

javac -d %dir% -cp ../artifacts/info.kgeorgiy.java.advanced.hello.jar; ru/ifmo/rain/janchenkov/hello/*.java
java -p ../artifacts;../lib; -classpath %dir% -m  info.kgeorgiy.java.advanced.hello server-i18n ru.ifmo.rain.janchenkov.hello.HelloUDPServer H9
                                                                                                                                     
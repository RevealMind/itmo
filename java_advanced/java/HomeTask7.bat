SET dir=out/production/

javac -d %dir% -cp ../artifacts/info.kgeorgiy.java.advanced.concurrent.jar ru/ifmo/rain/janchenkov/concurrent/*.java

java  -Dfile.encoding=UTF-8 -cp  %dir% -p ../lib;../artifacts -m  info.kgeorgiy.java.advanced.concurrent list ru.ifmo.rain.janchenkov.concurrent.IterativeParallelism
SET dir=out/production/

javac -d %dir% -cp ../artifacts/info.kgeorgiy.java.advanced.mapper.jar;../artifacts/info.kgeorgiy.java.advanced.concurrent.jar ru/ifmo/rain/janchenkov/mapper/*.java

java  -Dfile.encoding=UTF-8 -cp  %dir% -p ../lib;../artifacts -m  info.kgeorgiy.java.advanced.mapper list ru.ifmo.rain.janchenkov.mapper.ParallelMapperImpl,ru.ifmo.rain.janchenkov.mapper.IterativeParallelism ae
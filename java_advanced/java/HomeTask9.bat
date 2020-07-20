SET dir=out/production/

javac -d %dir% -cp ../artifacts/info.kgeorgiy.java.advanced.crawler.jar; ru/ifmo/rain/janchenkov/crawler/*.java
java -p ../artifacts;../lib; -classpath %dir% -m  info.kgeorgiy.java.advanced.crawler hard ru.ifmo.rain.janchenkov.crawler.WebCrawler Mu
                                                                                                                                     
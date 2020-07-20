SET dir=out/production/

javac -d %dir% -cp ../artifacts/info.kgeorgiy.java.advanced.student.jar; ru/ifmo/rain/janchenkov/student/*.java
java -p ../artifacts;../lib; -classpath %dir% -m  info.kgeorgiy.java.advanced.student AdvancedStudentGroupQuery ru.ifmo.rain.janchenkov.student.StudentDB

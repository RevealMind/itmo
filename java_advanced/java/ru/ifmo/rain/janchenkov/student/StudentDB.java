package ru.ifmo.rain.janchenkov.student;

import info.kgeorgiy.java.advanced.student.AdvancedStudentGroupQuery;
import info.kgeorgiy.java.advanced.student.Group;
import info.kgeorgiy.java.advanced.student.Student;

import java.util.*;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collector;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.Map.Entry;

public class StudentDB implements AdvancedStudentGroupQuery {
    private static final Comparator<Student> NAME_ORDER = Comparator
            .comparing(Student::getLastName)
            .thenComparing(Student::getFirstName)
            .thenComparing(Student::compareTo);

    @Override
    public List<String> getFirstNames(List<Student> students) {
        return getField(students, Student::getFirstName, Collectors.toList());
    }

    @Override
    public List<String> getLastNames(List<Student> students) {
        return getField(students, Student::getLastName, Collectors.toList());
    }

    @Override
    public List<String> getGroups(List<Student> students) {
        return getField(students, Student::getGroup, Collectors.toList());
    }

    @Override
    public List<String> getFullNames(List<Student> students) {
        return getField(students, StudentDB::getFullName, Collectors.toList());
    }

    @Override
    public Set<String> getDistinctFirstNames(List<Student> students) {
        return getField(students, Student::getFirstName, Collectors.toCollection(TreeSet::new));
    }

    @Override
    public String getMinStudentFirstName(List<Student> students) {
        return students.stream()
                .min(Student::compareTo)
                .map(Student::getFirstName)
                .orElse("");
    }

    @Override
    public List<Student> sortStudentsById(Collection<Student> students) {
        return sorted(students.stream(), Student::compareTo);
    }

    @Override
    public List<Student> sortStudentsByName(Collection<Student> students) {
        return sorted(students.stream(), NAME_ORDER);
    }

    @Override
    public List<Student> findStudentsByFirstName(Collection<Student> students, String firstName) {
        return filtered(students.stream(), student -> firstName.equals(student.getFirstName()), Collectors.toList());
    }

    @Override
    public List<Student> findStudentsByLastName(Collection<Student> students, String lastName) {
        return filtered(students.stream(), student -> lastName.equals(student.getLastName()), Collectors.toList());
    }

    @Override
    public List<Student> findStudentsByGroup(Collection<Student> students, String group) {
        return filtered(students.stream(), student -> group.equals(student.getGroup()), Collectors.toList());
    }

    @Override
    public Map<String, String> findStudentNamesByGroup(Collection<Student> students, String group) {
        return filtered(students.stream(), student -> group.equals(student.getGroup()),
                Collectors.toMap(
                        Student::getLastName,
                        Student::getFirstName,
                        BinaryOperator.minBy(String::compareTo)));
    }

    @Override
    public List<Group> getGroupsByName(Collection<Student> students) {
        return getGroupsByImpl(students, this::sortStudentsByName);
    }

    @Override
    public List<Group> getGroupsById(Collection<Student> students) {
        return getGroupsByImpl(students, this::sortStudentsById);
    }

    @Override
    public String getLargestGroup(Collection<Student> students) {
        return getLargest(getGroupEntryStream(students.stream()), Collections.reverseOrder(String::compareTo));
    }

    @Override
    public String getLargestGroupFirstName(Collection<Student> students) {
        return getLargest(getGroupEntryStream(students.stream(), Collectors.mapping(Student::getFirstName, Collectors.toSet())), Collections.reverseOrder(String::compareTo));
    }

    @Override
    public String getMostPopularName(Collection<Student> students) {
        return getLargest(getGroupEntryStream(students.stream(), StudentDB::getFullName, Collectors.mapping(Student::getGroup, Collectors.toSet())), String::compareTo);

    }

    private static String getFullName(final Student student) {
        return String.format("%s %s", student.getFirstName(), student.getLastName());
    }

    private static <R> R getField(final List<Student> students,
                                  final Function<Student, String> fieldGetter,
                                  final Collector<String, ?, R> collector) {
        return students.stream().map(fieldGetter).collect(collector);
    }

    private static <R> List<R> sorted(final Stream<R> stream,
                                      final Comparator<R> comparator) {
        return stream
                .sorted(comparator)
                .collect(Collectors.toList());
    }

    private static <R> R filtered(final Stream<Student> stream,
                                  final Predicate<Student> fieldGetter,
                                  final Collector<Student, ?, R> collector) {
        return stream
                .filter(fieldGetter)
                .sorted(NAME_ORDER)
                .collect(collector);
    }


    private static Stream<Entry<String, List<Student>>> getGroupEntryStream(final Stream<Student> stream) {
        return getGroupEntryStream(stream, Collectors.toList());
    }

    private static <V> Stream<Entry<String, V>> getGroupEntryStream(final Stream<Student> stream,
                                                                    final Collector<Student, ?, V> valueCollector) {
        return getGroupEntryStream(stream, Student::getGroup, valueCollector);
    }

    private static <T> Stream<Entry<String, T>> getGroupEntryStream(final Stream<Student> stream,
                                                                    final Function<Student, String> keyGetter,
                                                                    final Collector<Student, ?, T> collector) {
        return stream
                .collect(Collectors.groupingBy(keyGetter, collector))
                .entrySet()
                .stream();
    }

    private static List<Group> getGroupsByImpl(final Collection<Student> students,
                                               final Function<Collection<Student>, List<Student>> function) {
        return sorted(getGroupEntryStream(students.stream()).map(s -> new Group(s.getKey(), function.apply(s.getValue()))),
                Comparator.comparing(Group::getName));
    }

    private static <T extends Collection> String getLargest(final Stream<Entry<String, T>> stream,
                                                            final Comparator<String> comparator) {
        return stream
                .max(Comparator.
                        comparingInt((Entry<String, T> cur) -> cur.getValue().size())
                        .thenComparing((Entry::getKey), comparator))
                .map(Entry::getKey)
                .orElse("");
    }

}

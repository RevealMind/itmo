package generator;

import lombok.*;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.CommonTokenStream;
import util.Pair;
import util.grammar.GrammarParserLexer;
import util.grammar.GrammarParserParser;
import util.grammar.GrammarParserParser.*;
import util.tokens.Terminal;
import util.tokens.action.*;
import util.tokens.node.Node;
import util.tokens.node.NumeratedNode;
import util.tokens.node.TypedNode;
import util.tokens.rule.ExtendedRule;
import util.tokens.rule.Rule;

import javax.print.attribute.HashAttributeSet;
import java.time.Year;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

@Data
public class TableGenerator {
    public static final Node EPS = new Node("EPS");
    public static final Node END = new Node("END");

    public static Result generate(CharStream inputStream, String name, String pack) {
        GrammarParserParser parserParser = new GrammarParserParser(new CommonTokenStream(new GrammarParserLexer(inputStream)));

        List<Terminal> terminals = getTerminals(parserParser.terminals());

        LexerGenerator.generateLexer(name, terminals, pack);

        List<Rule> rules = getRules(parserParser.nonterminals());

        List<Node> terminalsNode = terminals.stream()
                .map(Terminal::getName)
                .map(Node::new)
                .collect(Collectors.toList());
        terminalsNode.add(EPS);

        List<Node> nonterminalsNode = rules.stream()
                .map(Rule::getLeft)
                .collect(Collectors.toList());

        Set<Node> allNodes = Stream.of(terminalsNode, nonterminalsNode)
                .flatMap(Collection::stream)
                .collect(Collectors.toSet());

        Map<Node, List<Rule>> rulesFromStartingNode = rules
                .stream()
                .collect(Collectors.toMap(
                        Rule::getLeft,
                        rule -> new ArrayList<>(List.of(rule)),
                        (l, r) -> {
                            l.addAll(r);
                            return l;
                        }));

        Map<Pair<ItemSet, Node>, ItemSet> itemSetsEdges = new HashMap<>();
        Set<ItemSet> itemSets = getItemSets(rules.get(0), allNodes, rulesFromStartingNode, itemSetsEdges);

        Set<Rule> numeratedRules = extendedGrammars(rules.get(0), itemSets, itemSetsEdges);

        Map<Node, Set<Node>> firstSet = getFirstSet(numeratedRules, new HashSet<>(terminalsNode));

        Map<Node, Set<Node>> followSet = getFollowSet(firstSet, numeratedRules, new HashSet<>(terminalsNode));

        return createTable(numeratedRules, itemSetsEdges, followSet, new HashSet<>(terminalsNode), rules);
    }

    private static Result createTable(Set<Rule> numeratedRules,
                                                                Map<Pair<ItemSet, Node>, ItemSet> edges,
                                                                Map<Node, Set<Node>> followSet,
                                                                HashSet<Node> terminals,
                                                                List<Rule> rules) {

        Map<Pair<Integer, Node>, Action> table = new HashMap<>();

        edges.forEach((k, v) -> {
            if (terminals.contains(k.getSecond())) {
                table.put(new Pair<>(k.getFirst().id, k.getSecond()), new Shift(v.id));
            } else {
                table.put(new Pair<>(k.getFirst().id, k.getSecond()), new GoTo(v.id));
            }
        });

        Map<Rule, Set<Node>> mergedRules = getMergeRules(numeratedRules, followSet);

        mergedRules.forEach((rule, follow) -> {
            for (Node node : follow) {
                if (rule.left.name.equals("start")) {
                    table.put(new Pair<>(rule.ind, node), new Accept());
                } else {
                    table.put(new Pair<>(rule.ind, node), new Reduce(rule.code, mapToInit(rule, new HashSet<>(rules))));
                }
            }
        });

        Set<TypedNode> typedNode = new HashSet<>();
        mergedRules.forEach((rule, follow) -> {
            typedNode.add(new TypedNode(rule.left.name, "", rule.type));
        });

        return new Result(table, typedNode, new HashSet<>(rules));
    }

    private static Rule mapToInit(Rule rule, HashSet<Rule> rules) {
        return rules.stream().filter(r -> {
            if (r.right.size() != rule.right.size())
                return false;

            for (int i = 0; i < rule.right.size(); i++) {
                if (!rule.right.get(i).name.equals(r.right.get(i).name))
                    return false;
            }

            return rule.left.name.equals(r.left.name);
        }).findFirst().get();
    }

    private static Map<Rule, Set<Node>> getMergeRules(Set<Rule> rules, Map<Node, Set<Node>> followSet) {
        List<List<Rule>> preMerge = new ArrayList<>();
        for (Rule rule : rules) {
            boolean changed = false;

            outer: for (List<Rule> group : preMerge) {
                Rule tmp = group.get(0);

                if (tmp.left.name.equals(rule.left.name)) {
                    if (tmp.right.size() == (rule.right.size())) {
                        for (int i = 0; i < rule.right.size(); i++) {
                            if (!rule.right.get(i).name.equals(tmp.right.get(i).name)) {
                                break outer;

                            }
                        }

                        if (((NumeratedNode) tmp.right.get(tmp.right.size() - 1)).to
                                == ((NumeratedNode) rule.right.get(rule.right.size() - 1)).to) {
                            changed = true;
                            group.add(rule);
                            break;
                        }
                    }
                }
            }

            if (!changed)
                preMerge.add(new ArrayList<>(List.of(rule)));
        }

        Map<Rule, Set<Node>> mergedRulesAndFollow = new HashMap<>();
        preMerge.forEach(ruleList -> {
            Set<Node> mergedFollow = new HashSet<>();

            ruleList.get(0).ind = ((NumeratedNode) ruleList.get(0).right.get(ruleList.get(0).right.size() - 1)).to;
            ruleList.forEach(r -> mergedFollow.addAll(followSet.get(r.left)));
            mergedRulesAndFollow.put(ruleList.get(0), mergedFollow);
        });

        return mergedRulesAndFollow;
    }

    private static Map<Node, Set<Node>> getFollowSet( Map<Node, Set<Node>> firstSet, Set<Rule> rules, HashSet<Node> terminals) {
        // -----------------------------------------
        System.out.println("----------------------------------------------------");
        System.out.println("Generate Follow Set: ");
        // -----------------------------------------

        Map<Node, Set<Node>> followSet = new HashMap<>();
        for (Rule rule : rules) {
            if (rule.left.name.equals("start")) {
                followSet.put(rule.left, new HashSet<>(Set.of(END)));
                continue;
            }
            followSet.put(rule.left, new HashSet<>());
        }

        boolean changed = true;
        while (changed) {
            changed = false;
            for (Rule rule : rules) {
                for (int i = 0; i < rule.right.size(); i++) {
                    if (!terminals.contains(new Node(rule.right.get(i).name))) {
                        Set<Node> cur = followSet.get(rule.right.get(i));
                        Set<Node> prev = new HashSet<>(cur);

                        if (i + 1 == rule.right.size()) {
                            cur.addAll(followSet.get(rule.left));
                        } else {
                            cur.addAll(firstSet.get(rule.right.get(i + 1)));
                            cur = cur.stream().filter(n -> !n.name.equals(EPS.name)).collect(Collectors.toSet());

                            if (firstSet.get(rule.right.get(i + 1)).contains(EPS)) {
                                cur.addAll(followSet.get(rule.left));
                            }
                        }
                        if (!cur.equals(prev)) {
                            changed = true;
                        }
                    }
                }
            }
        }

        // -----------------------------------------
        followSet.forEach((k, v) -> System.out.println(k + " : " + v));
        System.out.println("---------------------COMPLETED!---------------------\n");
        // -----------------------------------------

        return followSet;
    }

    private static Map<Node, Set<Node>> getFirstSet(Set<Rule> rules, HashSet<Node> terminals) {
        // -----------------------------------------
        System.out.println("----------------------------------------------------");
        System.out.println("Generate First Set: ");
        // -----------------------------------------
        Map<Node, Set<Node>> firstSet = new HashMap<>();
        for (Rule rule : rules) {
            firstSet.put(rule.left, new HashSet<>());
            for (Node node : rule.right) {
                if (terminals.contains(new Node(node.name))) {
                    firstSet.put(node, new HashSet<>(Set.of(new Node(node.name))));
                } else {
                    firstSet.put(node, new HashSet<>());
                }
            }
        }

        boolean changed = true;
        while (changed) {
            changed = false;
            for (Rule rule : rules) {
                Set<Node> cur = firstSet.get(rule.left);
                Set<Node> prev = new HashSet<>(cur);
                cur.addAll(first(rule.right, firstSet));
                if (!cur.equals(prev))
                    changed = true;
            }
        }
        // -----------------------------------------
        firstSet.forEach((k, v) -> System.out.println(k + " : " + v));
        System.out.println("---------------------COMPLETED!---------------------\n");
        // -----------------------------------------
        return firstSet;
    }

    private static Set<Node> first(List<Node> nodes, Map<Node, Set<Node>> firstSet) {
        if (nodes.isEmpty()) {
            return Set.of(EPS);
        }
        Set<Node> result = new HashSet<>();
        for (Node node : nodes) {
            if (firstSet.get(node).stream().noneMatch(n -> n.name.equals(EPS.name))) {
                result = result.stream()
                        .filter(n -> !n.name.equals(EPS.name))
                        .collect(Collectors.toSet());
                result.addAll(firstSet.get(node));
                break;
            } else {
                result.addAll(firstSet.get(node));
            }
        }
        return result;
    }

    private static Set<Rule> extendedGrammars(Rule startRule, Set<ItemSet> itemSets, Map<Pair<ItemSet, Node>, ItemSet> edges) {
        // -----------------------------------------
        System.out.println("----------------------------------------------------");
        System.out.println("Generate extended Grammar: ");
        // -----------------------------------------

        List<ItemSet> sortedItemSets = itemSets.stream()
                .sorted(Comparator.comparing(ItemSet::getId))
                .collect(Collectors.toList());

        Node rightOfStart = startRule.right.get(0);
        int to = edges.get(new Pair<>(sortedItemSets.get(0), rightOfStart)).id;

        int currentRuleId = 0;

        Rule extendedStartRule = new Rule(
                currentRuleId++,
                new NumeratedNode(startRule.left.name, 0, -1),
                List.of(new NumeratedNode(rightOfStart.name, 0, to)),
                startRule.type, startRule.code);


        Set<Rule> extendedGrammar = new HashSet<>(Set.of(extendedStartRule));

        for (ItemSet itemSet : itemSets) {
            List<ExtendedRule> rules = itemSet.rules.stream().filter(rule -> rule.dotPos == 0 && rule.ind != 0).collect(Collectors.toList());
            for (ExtendedRule rule : rules) {
                Node extendedLeftPart = new NumeratedNode(rule.left.name, itemSet.id, edges.get(new Pair<>(itemSet, rule.left)).id);
                List<Node> extendedRightPart = new ArrayList<>();

                ItemSet curSet = itemSet;
                for (int i = 0; i < rule.right.size(); i++) {
                    Node curNode = rule.right.get(i);
                    ItemSet nextSet = edges.get(new Pair<>(curSet, curNode));
                    extendedRightPart.add(new NumeratedNode(curNode.name, curSet.id, nextSet.id));
                    curSet = nextSet;
                }

                extendedGrammar.add(new Rule(currentRuleId++, extendedLeftPart, extendedRightPart, rule.type, rule.code));
            }
        }

        // -----------------------------------------
        extendedGrammar.stream().sorted(Comparator.comparing(Rule::getInd)).forEach(System.out::println);
        System.out.println("---------------------COMPLETED!---------------------\n");
        // -----------------------------------------


        return extendedGrammar;

    }

    private static Set<ItemSet> getItemSets(Rule start, Set<Node> nodes, Map<Node, List<Rule>> rulesFromStartingNode, Map<Pair<ItemSet, Node>, ItemSet> edges) {
        // -----------------------------------------
        System.out.println("----------------------------------------------------");
        System.out.println("Generate item sets");
        // -----------------------------------------

        ItemSet itemSet0 = initItemSet(start, rulesFromStartingNode);

        Set<ItemSet> itemSets = new HashSet<>(Set.of(itemSet0));
        Set<ItemSet> queue = new HashSet<>(Set.of(itemSet0));

        int currentItemSetId = 1;

        while (!queue.isEmpty()) {
            Set<ItemSet> next = new HashSet<>();
            for (ItemSet itemSet : queue) {
                for (Node node : nodes) {
                    ItemSet newItemSet = itemSet.createNewBy(node, rulesFromStartingNode);
                    if (newItemSet.rules.isEmpty()) {
                        continue;
                    }
                    if (itemSets.contains(newItemSet)) {
                        if (!edges.containsKey(new Pair<>(itemSet, node))) {
                            ItemSet to = itemSets.stream().filter(i -> i.equals(newItemSet)).findFirst().get();
                            edges.put(new Pair<>(itemSet, node), to);
                        }
                    } else {
                        next.add(newItemSet);
                        itemSets.add(newItemSet);
                        newItemSet.id = currentItemSetId++;
                        edges.put(new Pair<>(itemSet, node), newItemSet);
                    }
                }
            }
            queue = next;
        }

        // -----------------------------------------
        itemSets.stream().sorted(Comparator.comparing(ItemSet::getId)).forEach(System.out::println);
        System.out.println("---------------------COMPLETED!---------------------\n");
        // -----------------------------------------

        return itemSets;
    }

    private static ItemSet initItemSet(Rule start, Map<Node, List<Rule>> rulesFromStartingNode) {
        ItemSet i0 = new ItemSet();
        i0.add(new ExtendedRule(start));

        ItemSet prev = null;

        while (!i0.equals(prev)) {
            prev = i0.copy();

            for (ExtendedRule extendedRule : i0.getRules()) {
                List<Rule> rules = rulesFromStartingNode.get(extendedRule.right.get(0));
                if (rules != null) {
                    rules.forEach(r -> i0.add(new ExtendedRule(r)));
                }
            }
        }

        return i0;
    }

    private static List<Rule> getRules(NonterminalsContext nonterminals) {
        // -----------------------------------------
        System.out.println("----------------------------------------------------");
        System.out.println("Take rules from your grammar: ");
        // -----------------------------------------

        List<Rule> rules = new ArrayList<>();
        int ind = 0;

        // start nonterminal
        {
            FirstContext startRule = nonterminals.first();
            Node left = new Node("start");
            List<Node> right = List.of(new Node(startRule.NONTERM_NAME().getText()));
            String type = startRule.TYPE().getText();
            String code = startRule.CODE().getText();

            rules.add(new Rule(ind++, left, right, type.substring(1, type.length() - 1), code.substring(1, code.length() - 1)));
        }

        // other nonterminals
        for (NonterminalContext nonterminal : nonterminals.nonterminal()) {
            Node left = new Node(nonterminal.NONTERM_NAME(0).getText());

            List<Node> right = new ArrayList<>();
            for (int i = 3; i < nonterminal.children.size() - 2; i++) {
                String name = nonterminal.children.get(i).getText();
                right.add(new Node(name));
            }

            String type = nonterminal.TYPE().getText();
            String code = nonterminal.CODE().getText();

            rules.add(new Rule(ind++, left, right, type.substring(1, type.length() - 1), code.substring(1, code.length() - 1)));
        }

        // -----------------------------------------
        for (Rule rule : rules) {
            System.out.println(rule);
        }
        System.out.println("---------------------COMPLETED!---------------------\n");
        // -----------------------------------------

        return rules;
    }

    private static List<Terminal> getTerminals(TerminalsContext ctx) {
        // -----------------------------------------
        System.out.println("----------------------------------------------------");
        System.out.println("Take terminals from your grammar: ");
        // -----------------------------------------

        List<Terminal> terminals = new ArrayList<>();

        for (TerminalContext terminal : ctx.terminal()) {
            String terminalName = terminal.TERM_NAME().getText();

            String regex = terminal.REGEX().getText();
            regex = regex.substring(1, regex.length() - 1);

            terminals.add(new Terminal(terminalName, regex));
        }

        // -----------------------------------------
        terminals.forEach(System.out::println);
        System.out.println("---------------------COMPLETED!---------------------\n");
        // -----------------------------------------

        return terminals;
    }

    @Value
    public static class Result {
        public Map<Pair<Integer, Node>, Action> table;
        public Set<TypedNode> nodes;
        public Set<Rule> rules;
    }

    @Data
    @RequiredArgsConstructor
    @AllArgsConstructor
    private static class ItemSet {
        @EqualsAndHashCode.Exclude
        public int id;
        public Set<ExtendedRule> rules = new HashSet<>();

        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append("i").append(id).append(" : ").append(rules);
            return sb.toString();
        }

        public void add(ExtendedRule extendedRule) {
            rules.add(extendedRule);
        }

        public ItemSet copy() {
            return new ItemSet(id, new HashSet<>(rules));
        }

        public List<ExtendedRule> getRules() {
            return new ArrayList<>(rules);
        }

        public ItemSet createNewBy(Node node, Map<Node, List<Rule>> rulesFromStartingNode) {
            ItemSet newItemSet = new ItemSet();

            newItemSet.rules = rules
                    .stream()
                    .filter(rule -> rule.dotPos < rule.right.size() && rule.right.get(rule.dotPos).equals(node))
                    .map(rule -> new ExtendedRule(rule, rule.dotPos + 1))
                    .collect(Collectors.toSet());

            ItemSet prev = null;
            while (!newItemSet.equals(prev)) {
                prev = newItemSet.copy();

                for (ExtendedRule extendedRule : newItemSet.getRules()) {
                    if (extendedRule.dotPos < extendedRule.right.size()) {
                        List<Rule> rules = rulesFromStartingNode.get(extendedRule.right.get(extendedRule.dotPos));

                        if (rules != null) {
                            rules.forEach(r -> newItemSet.add(new ExtendedRule(r)));
                        }
                    }
                }
            }

            return newItemSet;
        }
    }
}

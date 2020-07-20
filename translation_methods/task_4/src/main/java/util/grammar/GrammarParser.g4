grammar GrammarParser;

start : file;
file : terminals nonterminals;
terminals : terminal*;
terminal : TERM_NAME ':' REGEX ';';

nonterminals : first nonterminal*;
first: 'start' TYPE ':' NONTERM_NAME CODE ';';
nonterminal : NONTERM_NAME TYPE ':' (NONTERM_NAME | TERM_NAME)* CODE ';';

TERM_NAME:[A-Z]([A-Z0-9]*);
NONTERM_NAME:[a-z]([a-z0-9]*);

CODE: '{'.*?'}';
TYPE: '['.*?']';
REGEX: '"' (~[\\"] | '\\' [\\"])* '"';

WS: [ \t\r\n]+ -> skip;

grammar Program;

start: expression EOF;

expression: PRINT arg | ASGN VAR arg | IF condition expression elseif? expression?;

elseif: ELSEIF condition expression elseif?;

arg: condition | number;

condition: VAR | BOOL_CONST | BINARY_BOOL_OP condition condition | NOT condition | CMP_OP number number;

number: NUM | VAR | BINARY_OP number number;

// LEXER

BINARY_OP: '+'|'-'|'*'|'/';

BOOL_CONST     : 'true'|'false';
BINARY_BOOL_OP : '&&' | '||' | '^';
NOT            : '!';

CMP_OP: '<'|'>'|'<='|'>='|'=='|'!==';

ASGN : '=';

IF    : 'if';
ELSEIF    : 'elseif';
PRINT : 'print';

NUM : '0' | ('-')? ('1'..'9') ('0'..'9')*;
VAR : ('a'..'z' | 'A'..'Z') ('a'..'z' | 'A'..'Z' | '0'..'9' | '_' )*;

WS : [ \t\r\n] -> skip;

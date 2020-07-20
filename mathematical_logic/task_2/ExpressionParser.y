{

module ExpressionParser(parseExpression) where

import Lexer 
import Expression

}

%name      parseExpression
%tokentype { Token }
%error     { parseError }

%token 
	VARIABLE    { TVariable $$ }
	AND         { TAnd }
	OR          { TOr }
	NOT         { TNot }
	IMPLICATION { TImplication }
	OPEN        { TOpen }
	CLOSE       { TClose }

%%

Expr 
	: Disj                  { $1 }
	| Disj IMPLICATION Expr { Binary Implication $1 $3 }

Disj
	: Conj         { $1 }
	| Disj OR Conj { Binary Or $1 $3 }

Conj
	: Term          { $1 }
	| Conj AND Term { Binary And $1 $3 }

Term 
	: NOT Term        { Not $2 }
	| OPEN Expr CLOSE { $2 }
	| VARIABLE        { Variable $1 }

{

parseError = fail "Parse error"

}

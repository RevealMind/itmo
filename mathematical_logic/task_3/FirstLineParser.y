{
module FirstLineParser(parseFirstLine) where

import Lexer
import Expression
}

%name       parseFirstLine
%tokentype  { Token }
%error      { parseError }

%token 
    VARIABLE            { TVariable $$ }
    AND                 { TAnd }
    OR                  { TOr }
    NOT                 { TNot }
    IMPLICATION         { TImplication }
    OPEN                { TOpen }
    CLOSE               { TClose }
    TOURNIQUET          { TTourniquet }
    COMMA               { TComma }

%%

Start 
    : LeftPart TOURNIQUET Expr      { FirstLine $1 $3 }
    | TOURNIQUET Expr               { FirstLine [] $2 }

LeftPart
    : Expr COMMA LeftPart           { $1 : $3 }
    | Expr                          { [$1] }

Expr 
    : Disj                          { $1 }
    | Disj IMPLICATION Expr         { BinaryOperator Implication $1 $3 }

Disj 
    : Conj                          { $1 }
    | Disj OR Conj                  { BinaryOperator Or $1 $3 }
    
Conj 
    : Term                          { $1 }
    | Conj AND Term                 { BinaryOperator And $1 $3 }

Term 
    : NOT Term                      { Not $2 }
    | OPEN Expr CLOSE               { $2 }
    | VARIABLE                           { Variable $1 }
    
{
parseError = fail "Parse error"
}
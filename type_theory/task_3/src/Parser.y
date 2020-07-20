{
module Parser where

import Grammar
import Lexer
}

%name      parseExpr
%tokentype { Token }
%error     { parseError }

%token VAR    { TokenVar $$ }
%token DOT    { TokenDot }
%token SLASH  { TokenSlash }
%token OPEN   { TokenOpen }
%token CLOSE  { TokenClose }

%%

Expr
  : Apl                    { $1 }
  | Apl SLASH VAR DOT Expr { Aplication $1 (Lambda $3 $5)}
  | SLASH VAR DOT Expr     { Lambda $2 $4 }

Apl
  : Atom           { $1 }
  | Apl Atom       { Aplication $1 $2 }

Atom
  : OPEN Expr CLOSE    { $2 }
  | VAR                { Var $1 }

{
parseError = fail "Parse error"
}

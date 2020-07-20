{
module Parser where

import Grammar
import Lexer
}

%name      parseExpr
%tokentype { Token }
%error     { parseError }
%monad     { Either String }{ >>= }{ return }

%token VAR    { TokenVar $$ }
%token NOT    { TokenNot }
%token IMPL   { TokenImpl }
%token AND    { TokenAnd }
%token OR     { TokenOr }
%token OPEN   { TokenOpen }
%token CLOSE  { TokenClose }

%%

Expr
  : Disj               { $1 }
  | Disj IMPL Expr     { Binary Impl $1 $3 }

Disj
  : Conj               { $1 }
  | Disj OR Conj       { Binary Or $1 $3 }

Conj
  : Term               { $1 }
  | Conj AND Term      { Binary And $1 $3 }

Term
  : NOT Term           { Not $2 }
  | VAR                { Var $1 }
  | OPEN Expr CLOSE    { $2 }

{
parseError = fail "Parse error"
}

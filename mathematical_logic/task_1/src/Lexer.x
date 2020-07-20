{
module Lexer where
}

%wrapper "basic"


$alpha = [A-Z]
$ls_ds = [A-Z0-9]

tokens :-

  $white+                    ;
  "#".*                      ;
  \(                         { \_ -> TokenOpen }
  \)                         { \_ -> TokenClose }
  \|                         { \_ -> TokenOr }
  &                          { \_ -> TokenAnd }
  "->"                       { \_ -> TokenImpl }
  !                          { \_ -> TokenNot }
  $alpha [$ls_ds \']*        { \s -> TokenVar s }

{

data Token = TokenNot
           | TokenVar String
           | TokenImpl
           | TokenAnd
           | TokenOr
           | TokenOpen
           | TokenClose
           deriving (Show, Eq)

}

{
module Lexer where
}

%wrapper "basic"


$alpha = [a-z]
$ls_ds = [a-z0-9]

tokens :-

  $white+                    ;
  "#".*                      ;
  \(                         { \_ -> TokenOpen }
  \)                         { \_ -> TokenClose }
  \.                         { \_ -> TokenDot }
  \\                         { \_ -> TokenSlash }
  $alpha [$ls_ds \']*        { \s -> TokenVar s }

{

data Token = TokenVar String
           | TokenDot
           | TokenSlash
           | TokenOpen
           | TokenClose
           deriving (Show, Eq)

}

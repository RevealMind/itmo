{
module Lexer where
}

%wrapper "basic"

$letter = [A-Z]
$sybols = [$letter 0-9 \']
$spaces = [\ \r \t]

tokens :-
    $spaces+                    ;
    $letter[$sybols]*           {\x -> TVariable x}
    &                           {\_ -> TAnd}
    \|                          {\_ -> TOr}
    !                           {\_ -> TNot}
    "->"                        {\_ -> TImplication}
    \(                          {\_ -> TOpen}
    \)                          {\_ -> TClose}
    "|-"                        {\_ -> TTourniquet}
    \,                          {\_ -> TComma}

{
data Token =
    TVariable String
    | TAnd
    | TOr
    | TNot
    | TImplication
    | TOpen
    | TClose
    | TTourniquet
    | TComma
    deriving (Eq,Show)
}
{
module Lexer where
}

%wrapper "basic"

$letter = [A-Z]
$symbols = [$letter 0-9 \' \’]
$spaces = [\ \r \t]

tokens :- 
    $spaces+                             ;
    $letter[$symbols]*                   {\x -> TVariable x}
    &                                    {\_ -> TAnd}
    \|                                   {\_ -> TOr}
    "->"                                 {\_ -> TImplication}
    !                                    {\_ -> TNot}
    \(            			             {\_ -> TOpen}
    \)                                   {\_ -> TClose}
    "|-"                                 {\_ -> TTourniquet}
    \,                                   {\_ -> TComma}

{
data Token =
    TVariable String
    | TAnd
    | TOr
    | TImplication
    | TNot
    | TOpen
    | TClose
    | TTourniquet
    | TComma
    deriving (Eq, Show)
}

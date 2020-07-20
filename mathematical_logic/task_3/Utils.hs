module Utils where

import ExpressionParser
import FirstLineParser
import Lexer
import Expression
import qualified Data.Set as Set (Set, empty, fromList, insert, member)
import qualified Data.Map.Strict as Map (Map, empty, singleton, fromList, insert, update, lookup, member, (!), foldlWithKey')

data Storage = Storage { _hypothesis  ::  Set.Set Expression
                       , _parts       ::  Map.Map Expression [Expression]
                       , _expressions ::  Set.Set Expression 
                       }

parse :: String -> Expression
parse = parseExpression . alexScanTokens

classicalAxiomList = map parse [ "A -> B -> A"
                               , "(A -> B) -> (A -> B -> C) -> (A -> C)"
                               , "A -> B -> A & B"
                               , "A & B -> A"
                               , "A & B -> B"
                               , "A -> A | B"
                               , "B -> A | B"
                               , "(A -> C) -> (B -> C) -> (A | B -> C)"
                               , "(A -> B) -> (A -> !B) -> !A"
                               ]

brokenAxiom = parse "!!A -> A"

doubleNegation = [ "A"
                 , "(A -> (!A -> A))"
                 , "(!A -> A)"
                 , "(!A -> (!A -> !A))"
                 , "((!A -> (!A -> !A)) -> ((!A -> ((!A -> !A) -> !A)) -> (!A -> !A)))"
                 , "((!A -> ((!A -> !A) -> !A)) -> (!A -> !A))"
                 , "(!A -> ((!A -> !A) -> !A))"
                 , "(!A -> !A)"
                 , "((!A -> A) -> ((!A -> !A) -> !!A))"
                 , "((!A -> !A) -> !!A)"
                 , "!!A"
                 ]


doubleNegationBrokenAxiom = [ "(A -> (!!A -> A))"
                            , "(((A -> (!!A -> A)) -> ((A -> !(!!A -> A)) -> !A)) -> (!(!!A -> A) -> ((A -> (!!A -> A)) -> ((A -> !(!!A -> A)) -> !A))))"
                            , "((A -> (!!A -> A)) -> ((A -> !(!!A -> A)) -> !A))"
                            , "(!(!!A -> A) -> ((A -> (!!A -> A)) -> ((A -> !(!!A -> A)) -> !A)))"
                            , "((A -> (!!A -> A)) -> (!(!!A -> A) -> (A -> (!!A -> A))))"
                            , "(!(!!A -> A) -> (A -> (!!A -> A)))"
                            , "((!(!!A -> A) -> (A -> (!!A -> A))) -> ((!(!!A -> A) -> ((A -> (!!A -> A)) -> ((A -> !(!!A -> A)) -> !A))) -> (!(!!A -> A) -> ((A -> !(!!A -> A)) -> !A))))"
                            , "((!(!!A -> A) -> ((A -> (!!A -> A)) -> ((A -> !(!!A -> A)) -> !A))) -> (!(!!A -> A) -> ((A -> !(!!A -> A)) -> !A)))"
                            , "(!(!!A -> A) -> ((A -> !(!!A -> A)) -> !A))"
                            , "(!(!!A -> A) -> (A -> !(!!A -> A)))"
                            , "((!(!!A -> A) -> (A -> !(!!A -> A))) -> ((!(!!A -> A) -> ((A -> !(!!A -> A)) -> !A)) -> (!(!!A -> A) -> !A)))"
                            , "((!(!!A -> A) -> ((A -> !(!!A -> A)) -> !A)) -> (!(!!A -> A) -> !A))"
                            , "(!(!!A -> A) -> !A)"
                            , "(!A -> (!!A -> A))"
                            , "(((!A -> (!!A -> A)) -> ((!A -> !(!!A -> A)) -> !!A)) -> (!(!!A -> A) -> ((!A -> (!!A -> A)) -> ((!A -> !(!!A -> A)) -> !!A))))"
                            , "((!A -> (!!A -> A)) -> ((!A -> !(!!A -> A)) -> !!A))"
                            , "(!(!!A -> A) -> ((!A -> (!!A -> A)) -> ((!A -> !(!!A -> A)) -> !!A)))"
                            , "((!A -> (!!A -> A)) -> (!(!!A -> A) -> (!A -> (!!A -> A))))"
                            , "(!(!!A -> A) -> (!A -> (!!A -> A)))"
                            , "((!(!!A -> A) -> (!A -> (!!A -> A))) -> ((!(!!A -> A) -> ((!A -> (!!A -> A)) -> ((!A -> !(!!A -> A)) -> !!A))) -> (!(!!A -> A) -> ((!A -> !(!!A -> A)) -> !!A))))"
                            , "((!(!!A -> A) -> ((!A -> (!!A -> A)) -> ((!A -> !(!!A -> A)) -> !!A))) -> (!(!!A -> A) -> ((!A -> !(!!A -> A)) -> !!A)))"
                            , "(!(!!A -> A) -> ((!A -> !(!!A -> A)) -> !!A))"
                            , "(!(!!A -> A) -> (!A -> !(!!A -> A)))"
                            , "((!(!!A -> A) -> (!A -> !(!!A -> A))) -> ((!(!!A -> A) -> ((!A -> !(!!A -> A)) -> !!A)) -> (!(!!A -> A) -> !!A)))"
                            , "((!(!!A -> A) -> ((!A -> !(!!A -> A)) -> !!A)) -> (!(!!A -> A) -> !!A))"
                            , "(!(!!A -> A) -> !!A)"
                            , "((!(!!A -> A) -> !A) -> ((!(!!A -> A) -> !!A) -> !!(!!A -> A)))"
                            , "((!(!!A -> A) -> !!A) -> !!(!!A -> A))"
                            , "!!(!!A -> A)"
                            ]

doubleNegationModusPonens = [ "(((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))) -> (!B -> ((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))))"
                            , "((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "(!B -> ((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))))"
                            , "((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (!B -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "(((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))"
                            , "(!B -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))"
                            , "((!B -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((!B -> ((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))) -> (!B -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))))"
                            , "((!B -> ((((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))) -> (!B -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))))"
                            , "(!B -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "((((A -> B) -> ((A -> !B) -> !A)) -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A)))) -> (!B -> (((A -> B) -> ((A -> !B) -> !A)) -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "(((A -> B) -> ((A -> !B) -> !A)) -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))))"
                            , "(!B -> (((A -> B) -> ((A -> !B) -> !A)) -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A)))))"
                            , "((A -> B) -> ((A -> !B) -> !A))"
                            , "(!B -> ((A -> B) -> ((A -> !B) -> !A)))"
                            , "((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> ((!B -> (((A -> B) -> ((A -> !B) -> !A)) -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))))) -> (!B -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "((!B -> (((A -> B) -> ((A -> !B) -> !A)) -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))))) -> (!B -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A)))))"
                            , "(!B -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))))"
                            , "((((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))) -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))) -> (!B -> (((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))) -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))))"
                            , "(((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))) -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "(!B -> (((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))) -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))))"
                            , "((!B -> ((A -> B) -> ((A -> B) -> ((A -> !B) -> !A)))) -> ((!B -> (((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))) -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))) -> (!B -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))))"
                            , "((!B -> (((A -> B) -> ((A -> B) -> ((A -> !B) -> !A))) -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))) -> (!B -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))))"
                            , "(!B -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "((!B -> ((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))) -> ((!B -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))) -> (!B -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))))"
                            , "((!B -> (((A -> B) -> (((A -> B) -> ((A -> !B) -> !A)) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))) -> (!B -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))))"
                            , "(!B -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))))"
                            , "(((A -> B) -> (!B -> (A -> B))) -> (!B -> ((A -> B) -> (!B -> (A -> B)))))"
                            , "((A -> B) -> (!B -> (A -> B)))"
                            , "(!B -> ((A -> B) -> (!B -> (A -> B))))"
                            , "((((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))) -> (!B -> (((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))))"
                            , "(((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))"
                            , "(!B -> (((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "(((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> (!B -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))"
                            , "((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))"
                            , "(!B -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))"
                            , "((!B -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((!B -> (((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))) -> (!B -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))))"
                            , "((!B -> (((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))) -> (!B -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "(!B -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))"
                            , "((((A -> B) -> (!B -> (A -> B))) -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))) -> (!B -> (((A -> B) -> (!B -> (A -> B))) -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))))"
                            , "(((A -> B) -> (!B -> (A -> B))) -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))"
                            , "(!B -> (((A -> B) -> (!B -> (A -> B))) -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "((!B -> ((A -> B) -> (!B -> (A -> B)))) -> ((!B -> (((A -> B) -> (!B -> (A -> B))) -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))) -> (!B -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))))"
                            , "((!B -> (((A -> B) -> (!B -> (A -> B))) -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))) -> (!B -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "(!B -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))"
                            , "((!B -> ((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))) -> ((!B -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))) -> (!B -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "((!B -> (((A -> B) -> ((!B -> (A -> B)) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))) -> (!B -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))))"
                            , "(!B -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))))"
                            , "((((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))) -> (!B -> (((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "(((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))"
                            , "(!B -> (((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))))"
                            , "((!B -> ((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A))))) -> ((!B -> (((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))) -> (!B -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))))"
                            , "((!B -> (((A -> B) -> (!B -> ((A -> B) -> ((A -> !B) -> !A)))) -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))) -> (!B -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))))"
                            , "(!B -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))"
                            , "((!B -> ((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A))))) -> ((!B -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))) -> (!B -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))))"
                            , "((!B -> (((A -> B) -> ((!B -> ((A -> B) -> ((A -> !B) -> !A))) -> (!B -> ((A -> !B) -> !A)))) -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))) -> (!B -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))))"
                            , "(!B -> ((A -> B) -> (!B -> ((A -> !B) -> !A))))"
                            , "((!B -> (A -> !B)) -> (!B -> (!B -> (A -> !B))))"
                            , "(((!B -> (A -> !B)) -> ((A -> B) -> (!B -> (A -> !B)))) -> (!B -> ((!B -> (A -> !B)) -> ((A -> B) -> (!B -> (A -> !B))))))"
                            , "((!B -> (A -> !B)) -> ((A -> B) -> (!B -> (A -> !B))))"
                            , "(!B -> ((!B -> (A -> !B)) -> ((A -> B) -> (!B -> (A -> !B)))))"
                            , "(!B -> (A -> !B))"
                            , "(!B -> (!B -> (A -> !B)))"
                            , "((!B -> (!B -> (A -> !B))) -> ((!B -> ((!B -> (A -> !B)) -> ((A -> B) -> (!B -> (A -> !B))))) -> (!B -> ((A -> B) -> (!B -> (A -> !B))))))"
                            , "((!B -> ((!B -> (A -> !B)) -> ((A -> B) -> (!B -> (A -> !B))))) -> (!B -> ((A -> B) -> (!B -> (A -> !B)))))"
                            , "(!B -> ((A -> B) -> (!B -> (A -> !B))))"
                            , "((((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))) -> (!B -> (((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))))"
                            , "(((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))"
                            , "(!B -> (((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))))"
                            , "(((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> (!B -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))"
                            , "((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))"
                            , "(!B -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))"
                            , "((!B -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((!B -> (((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))) -> (!B -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))))"
                            , "((!B -> (((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))) -> (!B -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))))"
                            , "(!B -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))"
                            , "((((A -> B) -> (!B -> (A -> !B))) -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))) -> (!B -> (((A -> B) -> (!B -> (A -> !B))) -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))))"
                            , "(((A -> B) -> (!B -> (A -> !B))) -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))"
                            , "(!B -> (((A -> B) -> (!B -> (A -> !B))) -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))))"
                            , "((!B -> ((A -> B) -> (!B -> (A -> !B)))) -> ((!B -> (((A -> B) -> (!B -> (A -> !B))) -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))) -> (!B -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))))"
                            , "((!B -> (((A -> B) -> (!B -> (A -> !B))) -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))) -> (!B -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))))"
                            , "(!B -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))"
                            , "((!B -> ((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))) -> ((!B -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))) -> (!B -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))))"
                            , "((!B -> (((A -> B) -> ((!B -> (A -> !B)) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))) -> (!B -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))))"
                            , "(!B -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))))"
                            , "((((A -> B) -> (!B -> ((A -> !B) -> !A))) -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A)))) -> (!B -> (((A -> B) -> (!B -> ((A -> !B) -> !A))) -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A))))))"
                            , "(((A -> B) -> (!B -> ((A -> !B) -> !A))) -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A))))"
                            , "(!B -> (((A -> B) -> (!B -> ((A -> !B) -> !A))) -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A)))))"
                            , "((!B -> ((A -> B) -> (!B -> ((A -> !B) -> !A)))) -> ((!B -> (((A -> B) -> (!B -> ((A -> !B) -> !A))) -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A))))) -> (!B -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A))))))"
                            , "((!B -> (((A -> B) -> (!B -> ((A -> !B) -> !A))) -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A))))) -> (!B -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A)))))"
                            , "(!B -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A))))"
                            , "((!B -> ((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A)))) -> ((!B -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A)))) -> (!B -> ((A -> B) -> (!B -> !A)))))"
                            , "((!B -> (((A -> B) -> ((!B -> ((A -> !B) -> !A)) -> (!B -> !A))) -> ((A -> B) -> (!B -> !A)))) -> (!B -> ((A -> B) -> (!B -> !A))))"
                            , "(!B -> ((A -> B) -> (!B -> !A)))"
                            , "(!B -> ((A -> B) -> !B))"
                            , "((((A -> B) -> !B) -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A))) -> (!B -> (((A -> B) -> !B) -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A)))))"
                            , "(((A -> B) -> !B) -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A)))"
                            , "(!B -> (((A -> B) -> !B) -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A))))"
                            , "((!B -> ((A -> B) -> !B)) -> ((!B -> (((A -> B) -> !B) -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A)))) -> (!B -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A)))))"
                            , "((!B -> (((A -> B) -> !B) -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A)))) -> (!B -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A))))"
                            , "(!B -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A)))"
                            , "((!B -> ((A -> B) -> (!B -> !A))) -> ((!B -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A))) -> (!B -> ((A -> B) -> !A))))"
                            , "((!B -> (((A -> B) -> (!B -> !A)) -> ((A -> B) -> !A))) -> (!B -> ((A -> B) -> !A)))"
                            , "(!B -> ((A -> B) -> !A))"
                            , "(((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))))) -> (!B -> ((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))))"
                            , "((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))"
                            , "(!B -> ((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))))))"
                            , "((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!B -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))"
                            , "(((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))"
                            , "(!B -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))))"
                            , "((!B -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> ((!B -> ((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))) -> (!B -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))))"
                            , "((!B -> ((((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))) -> (!B -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))))))"
                            , "(!B -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))))"
                            , "((((A -> B) -> !A) -> (!!A -> ((A -> B) -> !A))) -> (!B -> (((A -> B) -> !A) -> (!!A -> ((A -> B) -> !A)))))"
                            , "(((A -> B) -> !A) -> (!!A -> ((A -> B) -> !A)))"
                            , "(!B -> (((A -> B) -> !A) -> (!!A -> ((A -> B) -> !A))))"
                            , "((!B -> ((A -> B) -> !A)) -> ((!B -> (((A -> B) -> !A) -> (!!A -> ((A -> B) -> !A)))) -> (!B -> (!!A -> ((A -> B) -> !A)))))"
                            , "((!B -> (((A -> B) -> !A) -> (!!A -> ((A -> B) -> !A)))) -> (!B -> (!!A -> ((A -> B) -> !A))))"
                            , "(!B -> (!!A -> ((A -> B) -> !A)))"
                            , "(((!!A -> ((A -> B) -> !A)) -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))) -> (!B -> ((!!A -> ((A -> B) -> !A)) -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))))"
                            , "((!!A -> ((A -> B) -> !A)) -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))"
                            , "(!B -> ((!!A -> ((A -> B) -> !A)) -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))))"
                            , "((!B -> (!!A -> ((A -> B) -> !A))) -> ((!B -> ((!!A -> ((A -> B) -> !A)) -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))) -> (!B -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))))"
                            , "((!B -> ((!!A -> ((A -> B) -> !A)) -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))) -> (!B -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))))"
                            , "(!B -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))"
                            , "((!B -> (!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B))))) -> ((!B -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))) -> (!B -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))))"
                            , "((!B -> ((!!A -> (((A -> B) -> !A) -> (((A -> B) -> !!A) -> !(A -> B)))) -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))) -> (!B -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))))"
                            , "(!B -> (!!A -> (((A -> B) -> !!A) -> !(A -> B))))"
                            , "((!!A -> ((A -> B) -> !!A)) -> (!B -> (!!A -> ((A -> B) -> !!A))))"
                            , "(!!A -> ((A -> B) -> !!A))"
                            , "(!B -> (!!A -> ((A -> B) -> !!A)))"
                            , "(((!!A -> ((A -> B) -> !!A)) -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B)))) -> (!B -> ((!!A -> ((A -> B) -> !!A)) -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B))))))"
                            , "((!!A -> ((A -> B) -> !!A)) -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B))))"
                            , "(!B -> ((!!A -> ((A -> B) -> !!A)) -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B)))))"
                            , "((!B -> (!!A -> ((A -> B) -> !!A))) -> ((!B -> ((!!A -> ((A -> B) -> !!A)) -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B))))) -> (!B -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B))))))"
                            , "((!B -> ((!!A -> ((A -> B) -> !!A)) -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B))))) -> (!B -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B)))))"
                            , "(!B -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B))))"
                            , "((!B -> (!!A -> (((A -> B) -> !!A) -> !(A -> B)))) -> ((!B -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B)))) -> (!B -> (!!A -> !(A -> B)))))"
                            , "((!B -> ((!!A -> (((A -> B) -> !!A) -> !(A -> B))) -> (!!A -> !(A -> B)))) -> (!B -> (!!A -> !(A -> B))))"
                            , "(!B -> (!!A -> !(A -> B)))"
                            , "(!!A -> (!B -> !!A))"
                            , "!!A"
                            , "(!B -> !!A)"
                            , "((!B -> !!A) -> ((!B -> (!!A -> !(A -> B))) -> (!B -> !(A -> B))))"
                            , "((!B -> (!!A -> !(A -> B))) -> (!B -> !(A -> B)))"
                            , "(!B -> !(A -> B))"
                            , "(((!B -> !(A -> B)) -> ((!B -> !!(A -> B)) -> !!B)) -> (!!(A -> B) -> ((!B -> !(A -> B)) -> ((!B -> !!(A -> B)) -> !!B))))"
                            , "((!B -> !(A -> B)) -> ((!B -> !!(A -> B)) -> !!B))"
                            , "(!!(A -> B) -> ((!B -> !(A -> B)) -> ((!B -> !!(A -> B)) -> !!B)))"
                            , "((!B -> !(A -> B)) -> (!!(A -> B) -> (!B -> !(A -> B))))"
                            , "(!!(A -> B) -> (!B -> !(A -> B)))"
                            , "((!!(A -> B) -> (!B -> !(A -> B))) -> ((!!(A -> B) -> ((!B -> !(A -> B)) -> ((!B -> !!(A -> B)) -> !!B))) -> (!!(A -> B) -> ((!B -> !!(A -> B)) -> !!B))))"
                            , "((!!(A -> B) -> ((!B -> !(A -> B)) -> ((!B -> !!(A -> B)) -> !!B))) -> (!!(A -> B) -> ((!B -> !!(A -> B)) -> !!B)))"
                            , "(!!(A -> B) -> ((!B -> !!(A -> B)) -> !!B))"
                            , "(!!(A -> B) -> (!B -> !!(A -> B)))"
                            , "((!!(A -> B) -> (!B -> !!(A -> B))) -> ((!!(A -> B) -> ((!B -> !!(A -> B)) -> !!B)) -> (!!(A -> B) -> !!B)))"
                            , "((!!(A -> B) -> ((!B -> !!(A -> B)) -> !!B)) -> (!!(A -> B) -> !!B))"
                            , "(!!(A -> B) -> !!B)"
                            , "!!(A -> B)"
                            , "!!B"
                            ]
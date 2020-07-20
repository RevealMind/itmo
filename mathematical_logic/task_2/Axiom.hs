module Axiom where

import Expression

determineAxiomOf :: Expression -> Int
determineAxiomOf expression = case expression of
    (Binary Implication a (Binary Implication _ a1))
     | a == a1                                   -> 1 
    (Binary Implication (Binary Implication a b) (Binary Implication (Binary Implication a1 (Binary Implication b1 c)) (Binary Implication a2 c1)))
     | a == a1 && a1 == a2 && b == b1 && c == c1 -> 2
    (Binary Implication a (Binary Implication b (Binary And a1 b1)))
     | a == a1 && b == b1                        -> 3
    (Binary Implication (Binary And a b) ab1)
     | a == ab1                                  -> 4
     | b == ab1                                  -> 5
    (Binary Implication ab (Binary Or a b))
     | ab == a                                   -> 6
     | ab == b                                   -> 7
    (Binary Implication (Binary Implication a c) (Binary Implication (Binary Implication b c1) (Binary Implication (Binary Or a1 b1) c2)))
     | a == a1 && b == b1 && c == c1 && c1 == c2 -> 8
    (Binary Implication (Binary Implication a b) (Binary Implication (Binary Implication a1 (Not b1)) (Not a2)))
     | a == a1 && a1 == a2 && b == b1            -> 9
    (Binary Implication (Not (Not a)) a1)
     | a == a1                                   -> 10
    _                                            -> -1

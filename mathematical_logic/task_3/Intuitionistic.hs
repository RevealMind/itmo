module Intuitionistic(initStorage, translate) where 
import Utils
import Expression
import qualified Data.Set as Set (Set, empty, fromList, insert, member)
import qualified Data.Map.Strict as Map (Map, empty, singleton, fromList, insert, update, lookup, member, (!), foldlWithKey')
import Data.Maybe


initStorage :: [Expression] -> Storage
initStorage h = Storage (Set.fromList h) (Map.empty) (Set.empty)

translate :: Storage -> Expression -> (Storage, [Expression])
translate store expression = (newStrorage, out) 
    where 
        newStrorage = store { _parts = addParts expression 
                            , _expressions = Set.insert expression expressions 
                            }
            where
                addParts (BinaryOperator Implication left right ) = 
                    if Map.member right parts
                        then Map.update (\x -> Just (left:x)) right parts
                        else Map.insert right [left] parts
                addParts _ = parts
        out :: [Expression]
        out  
            | isHypothesis || isClassicalAxiom = translateDoubleNegation
            | isBrokenAxiom                    = translateBrokenAxiom
            | otherwise                        = translateModusPonens
                where
                    isHypothesis = Set.member expression hypothesis
                    isClassicalAxiom = loop classicalAxiomList
                    isBrokenAxiom = checker expression brokenAxiom

                    loop :: [Expression] -> Bool
                    loop []                        = False
                    loop (begin : rest) 
                        | checker expression begin = True
                        | otherwise                = loop rest

                    checker :: Expression -> Expression -> Bool
                    checker _expression _pattern =  helper _expression _pattern /= Nothing 
                        where 
                            helper (BinaryOperator op1 left1 right1) (BinaryOperator op2 left2 right2) =
                                    if op1 /= op2               
                                        then Nothing
                                        else _helper (helper left1 left2) (helper right1 right2)
                                            where
                                                _helper _ Nothing                = Nothing
                                                _helper Nothing _                = Nothing
                                                _helper left (Just right) = Map.foldlWithKey' f left right
                                                    where
                                                        f Nothing _ _ = Nothing
                                                        f (Just result) key value  
                                                            | Map.lookup key result == Nothing     = Just (Map.insert key value result)
                                                            | Map.lookup key result == Just value  = Just result
                                                            | otherwise                            = Nothing
                            helper (Not expr) (Not pattern) =  helper expr pattern 
                            helper expr (Variable var)      =  Just (Map.singleton var expr)
                            helper _ _                      =  Nothing
                    
                    translateDoubleNegation = apply doubleNegation (Map.fromList[("A", expression)])
                    translateBrokenAxiom    = helper expression
                        where 
                            helper (BinaryOperator Implication _ right) = apply doubleNegationBrokenAxiom (Map.fromList [("A", right)])
                            helper _ = undefined
                    translateModusPonens    = apply doubleNegationModusPonens (Map.fromList [("A", leftPartMP), ("B", expression)])
                        where 
                            leftPartMP = fromJust (foldr f Nothing (parts Map.! expression))
                                where f _ res@(Just a) = res
                                      f expr _ =
                                        if Set.member expr expressions
                                            then Just expr
                                            else Nothing
                    apply:: [String] -> Map.Map String Expression -> [Expression]
                    apply template values =  map (mapExpression values . parse) template    
                        where
                            mapExpression :: Map.Map String Expression -> Expression -> Expression
                            mapExpression values (BinaryOperator op left right)  = BinaryOperator op (mapExpression values left) (mapExpression values right)
                            mapExpression values (Variable var)                  = values Map.! var
                            mapExpression values (Not expression)                = Not (mapExpression values expression)
        parts = _parts store
        hypothesis = _hypothesis store
        expressions = _expressions store
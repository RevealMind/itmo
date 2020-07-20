module Main where

import Expression
import System.IO
import Axiom
import Type
import Utils

import Data.Set as Set (member, singleton, insert)
import Data.Map.Strict as M ((!), lookup, insert, fromList, insertWith, member, update)
import Data.List(foldl', elemIndex)
import Data.Maybe(isJust, fromJust)

main :: IO ()
main = do
    line <- getLine
    let fl = getFirstLine line
    let storage = initStorage fl
    readByLine storage

readByLine :: Storage -> IO()
readByLine storage = do
        iseof <- isEOF
        if iseof then
            if (check storage) then do
                print . firstLine $ storage
                let lines = minimized . initProof $ storage
                mapM_ print lines 
            else 
                putStrLn incorrect
        else do
            line <- getLine
            case addExpression (getExpression line) storage of
                Nothing         -> putStrLn incorrect
                Just newStorage -> readByLine newStorage
             
             
check storage  = (ammount storage /= 1) && ((lastExpr storage) == (res . firstLine $ storage))  


addExpression :: Expression -> Storage -> Maybe Storage
addExpression expression storage@(Storage n (FirstLine _hyp _res) m1 m2 last) 
    | M.member expression m1 && expression /= _res = Just storage { lastExpr = expression }
    | otherwise                                    = newStorage $! determineTypeOf expression storage
    where 
        newStorage :: Type -> Maybe Storage
        newStorage Uncertain      = Nothing
        newStorage expressionType = Just $ storage {
              ammount  = n + 1
            , exprTN   = updTN
            , exprMP   = updMP expression
            , lastExpr = expression 
            } where 
                updTN 
                    | expression == _res && M.member expression m1 = M.update (\(t, _) -> Just (t, n)) expression m1 
                    | otherwise                                    = M.insert expression (expressionType, n) m1
                updMP (Binary Implication a b) = M.insertWith (++) b [(a, n)] m2 
                updMP _                        = m2 
                 
minimized :: [Line] -> [Line]
minimized proof = newProof
    where
        used = getUsed (Set.singleton $ init . head . reverse $  proof) (reverse proof) 
            where 
                init (Line _ _ p) = p
                getUsed set []                  = set
                getUsed set ((Line e t p) : xs) = 
                    case t of 
                        ModusPonens (a, b) -> if Set.member p set then 
                                                  getUsed ((Set.insert a) . (Set.insert b) $ set) xs 
                                              else 
                                                  getUsed set xs   
                        _         -> getUsed set xs
        prepare = Prelude.filter (\(Line _ _ p) -> Set.member p used) proof
        oldToNew = M.fromList (Prelude.map (\(newNum, Line _ _ oldNum) -> (oldNum, newNum)) (zip [1 ..] prepare)) 
        newProof = Prelude.map (helper oldToNew) prepare
            where
                helper m (Line e (ModusPonens (a, b)) p) = Line e (ModusPonens (m M.! a, m M.! b)) (m M.! p)
                helper m (Line e t p)                    = Line e t (m M.! p)   
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
       
        

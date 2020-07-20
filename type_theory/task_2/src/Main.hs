module Main where

import           Data.List                     as List
                                                ( )
import           Data.Map.Strict               as Map
                                                ( Map
                                                , empty
                                                , insert
                                                , member
                                                , size
                                                , (!)
                                                )
import           Data.Maybe
import           Data.Set                      as Set
                                                ( Set
                                                , delete
                                                , disjoint
                                                , empty
                                                , fromList
                                                , insert
                                                , member
                                                , singleton
                                                , union
                                                )
import           Grammar
import           Lexer                          ( alexScanTokens )
import           Parser                         ( parseExpr )

--- Вспомогательные функции и типы
type Ref = Map.Map Int Expression

parse :: String -> Expression
parse = parseExpr . alexScanTokens

freeVars :: Expression -> Ref -> Set.Set String
freeVars (Var x         ) ref = Set.singleton x
freeVars (Aplication l r) ref = freeVars l ref `Set.union` freeVars r ref
freeVars (Lambda     x e) ref = Set.delete x (freeVars e ref)
freeVars (Wrapper x     ) ref = freeVars (ref ! x) ref

newVar :: Int -> String
newVar ind = "v" ++ show ind

--- Обертка выражения
openWrapper :: Expression -> Ref -> Expression
openWrapper (Wrapper x) ref = ref ! x
openWrapper e           _   = e

doWrapper :: Expression -> Ref -> (Expression, Ref)
doWrapper expr@(Wrapper x) ref = (expr, ref')
 where
  e    = openWrapper (ref ! x) ref
  ref' = Map.insert x e ref
doWrapper e ref = (Wrapper x, ref')
 where
  x    = Map.size ref
  ref' = Map.insert x e ref

--- Подстановка
substitute
  :: String
  -> Expression
  -> Expression
  -> Ref
  -> Set.Set String
  -> Map.Map String String
  -> Int
  -> (Expression, Int)
substitute x b cur@(Var y) ref varsOfb m ind
  | Map.member y m = (Var (m ! y), ind)
  | x == y         = (b, ind)
  | otherwise      = (cur, ind)
substitute x b (Aplication l r) ref varsOfb m ind = (Aplication l' r', ind'')
 where
  (l', ind' ) = substitute x b l ref varsOfb m ind
  (r', ind'') = substitute x b r ref varsOfb m ind'
substitute x b (Wrapper y) ref varsOfb m ind =
  substitute x b (ref ! y) ref varsOfb m ind
substitute x b (Lambda y expr) ref varsOfb m ind
  | Set.member y varsOfb = (Lambda y' expr1, ind1)
  | otherwise            = (Lambda y expr2, ind2)
 where
  y'            = newVar ind
  (expr1, ind1) = substitute x b expr ref varsOfb (Map.insert y y' m) (ind + 1)
  (expr2, ind2) = substitute x b expr ref varsOfb m ind

--- Основной алгоритм
reduce :: Expression -> Ref -> Int -> (Expression, Ref, Int, Bool)
reduce expr@(Var x           ) ref ind = (expr, ref, ind, False)

reduce (     Lambda name expr) ref ind = (Lambda name expr', ref', ind', flag)
  where (expr', ref', ind', flag) = reduce expr ref ind

reduce (Aplication (Lambda name a) b) ref ind = (expr, ref', ind', True)
 where
  (wrappB, ref') = doWrapper b ref
  (expr  , ind') = substitute name
                              wrappB
                              a
                              ref'
                              (Set.insert name (freeVars b ref'))
                              Map.empty
                              ind

reduce (Aplication l@(Wrapper x) b) ref ind = case ref ! x of
  Lambda name a -> (expr, ref', ind', True)
   where
    (wrappB, ref') = doWrapper b ref
    (expr  , ind') = substitute name
                                wrappB
                                a
                                ref'
                                (Set.insert name (freeVars b ref'))
                                Map.empty
                                ind
  _ -> if flagL
    then (Aplication l' b, ref', ind', flagL)
    else (Aplication l b', ref'', ind'', flagR)
   where
    (l', ref' , ind' , flagL) = reduce l ref ind
    (b', ref'', ind'', flagR) = reduce b ref ind

reduce (Aplication l r) ref ind = if flagL
  then (Aplication l' r, ref', ind', flagL)
  else (Aplication l r', ref'', ind'', flagR)
 where
  (l', ref' , ind' , flagL) = reduce l ref ind
  (r', ref'', ind'', flagR) = reduce r ref ind

reduce expr@(Wrapper x) ref ind | flag      = (expr, ref'', ind', flag)
                                | otherwise = (expr, ref, ind, flag)
 where
  (expr', ref', ind', flag) = reduce (ref ! x) ref ind
  ref''                     = Map.insert x (openWrapper expr' ref') ref'

--- Вывод
printEachK :: Expression -> Ref -> Int -> Int -> Int -> Int -> IO ()
printEachK expr ref m k step ind
  | step > m = return ()
  | isNormalized && step `rem` k == 0 = do
    print (Storage (expr, ref))
    printEachK expr' ref' m k (step + 1) ind'
  | not isNormalized = print (Storage (expr, ref))
  | otherwise = printEachK expr' ref' m k (step + 1) ind'
  where (expr', ref', ind', isNormalized) = reduce expr ref ind

-- Main sextion
main :: IO ()
main = do
  line       <- getLine
  m          <- readIO (takeWhile (/= ' ') line) :: IO Int
  k          <- readIO (drop 1 (dropWhile (/= ' ') line)) :: IO Int
  expression <- getLine
  printEachK (parse expression) Map.empty m k 0 1

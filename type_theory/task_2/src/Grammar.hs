module Grammar where

import Data.Map.Strict as Map (Map, (!))

--- Expression section
data Expression = Aplication Expression Expression | Lambda String Expression | Var String | Wrapper Int deriving (Eq, Ord)

instance Show Expression where
    show (Aplication e1 e2) = "(" ++ show e1 ++ " " ++ show e2 ++ ")"
    show (Lambda e1 e2)     = "(\\" ++ e1 ++ "." ++ show e2 ++ ")"
    show (Var variabel)     = variabel
    show (Wrapper x)        = show x

--- Storage for memoization section
newtype Storage = Storage (Expression, Map.Map Int Expression)

instance Show Storage where 
    show (Storage (Wrapper ind, ref)) = show (Storage (ref ! ind, ref))
    show (Storage (Aplication e1 e2, ref)) = "(" ++ show (Storage (e1, ref)) ++ " " ++ show (Storage (e2, ref)) ++ ")"
    show (Storage (Lambda x e2, ref)) = "(\\" ++ x ++ "." ++ show (Storage (e2, ref)) ++ ")"
    show (Storage (Var var, ref)) = var 
    
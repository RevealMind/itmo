module Grammar where

import Data.Set as Set (Set, union, singleton)
import Data.List (intercalate)

newtype ETPair = ETPair (Expression, Type) deriving (Eq, Ord)

data ExpressionType = App ExpressionType ExpressionType ETPair | Lam (String, Type) ExpressionType ETPair | V ETPair deriving (Eq, Ord)

data Expression = Aplication Expression Expression | Lambda String Expression | Var String deriving (Eq, Ord)

instance Show Expression where
    show (Aplication e1 e2) = "(" ++ show e1 ++ " " ++ show e2 ++ ")"
    show (Lambda e1 e2)     = "(\\" ++ e1 ++ "." ++ show e2 ++ ")"
    show (Var variabel)     = variabel

-- Type section

data Type = TVar String | Arrow Type Type deriving (Eq, Ord)

instance Show Type where
    show (TVar var)    = var
    show (Arrow t1 t2) = "(" ++ show t1 ++ " -> " ++ show t2 ++ ")"

typeVars :: Type -> Set.Set String
typeVars (TVar x)    = singleton x
typeVars (Arrow l r) = typeVars l `Set.union` typeVars r

-- Context section

newtype Context = Context [(Type, Type)] deriving (Show, Eq)

emptyContext :: Context
emptyContext = Context []

extend :: (Type, Type) -> Context -> Context
extend x (Context xs) = Context (x: xs)

union :: Context -> Context -> Context
union (Context xs) (Context ys) = Context (xs ++ ys)
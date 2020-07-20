module Expression where 

import Data.List (intercalate)

data Expression = 
    Binary Operator Expression Expression
    | Not Expression
    | Variable String
    deriving (Eq, Ord)

data Operator = And | Or | Implication deriving (Eq, Ord)

instance Show Operator where
    show And         = "&"
    show Or          = "|"
    show Implication = "->"

instance Show Expression where
    show (Binary op el er) = "(" ++ intercalate " " [show el, show op, show er] ++ ")"
    show (Not e)           = "!" ++ show e 
    show (Variable var)    = var 

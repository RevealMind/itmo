module Expression where

import Data.List (intercalate)

data Operator = And 
              | Or 
              | Implication 
              deriving (Eq, Ord)

data Expression = BinaryOperator Operator Expression Expression
                | Not            Expression
                | Variable       String
                deriving (Eq, Ord)

data FirstLine = FirstLine { leftPart  :: [Expression]
                           , rightPart :: Expression
                           }

instance Show Operator where
    show Or          = "|"
    show And         = "&"
    show Implication = "->"

instance Show Expression where
    show (BinaryOperator operator eLeft eRight) = "(" ++ intercalate " " [show eLeft, show operator, show eRight] ++ ")"
    show (Not expression)                       = "!" ++ show expression
    show (Variable var)                         = var

instance Show FirstLine where
    show fl = intercalate "|- " [left, right]
        where 
            left = case intercalate ", " $ map show $ leftPart fl of 
                ""       -> ""
                nonEmpty -> nonEmpty ++ " "
            right = show $ rightPart fl
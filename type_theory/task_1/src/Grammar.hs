module Grammar where

data Expression = Aplication Expression Expression | Lambda String Expression | Var String
instance Show Expression where
	show (Aplication e1 e2) = "(" ++ show e1 ++ " " ++ show e2 ++ ")"
	show (Lambda e1 e2) = "(\\" ++ e1 ++ "." ++ show e2 ++ ")"
	show (Var variabel) = variabel

module Grammar where

data Binoperation = And | Or |Impl
data Expression = Binary Binoperation Expression Expression | Not Expression | Var String

instance Show Binoperation where
	show And  = "&"
	show Or   = "|"
	show Impl = "->"

instance Show Expression where
	show (Binary operation e1 e2) = "(" ++ show operation ++ "," ++ show e1 ++ "," ++ show e2 ++ ")"
	show (Not e) = "(!" ++ show e ++ ")"
	show (Var variabel) = variabel

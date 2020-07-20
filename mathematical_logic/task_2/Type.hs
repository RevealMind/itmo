module Type where 
import Expression
import Axiom
import Data.List              (intercalate, elemIndex)
import Data.Map.Strict as Map (Map, lookup)

data Type = Axiom Int | Hypothesis Int | ModusPonens (Int, Int) | Uncertain

data FirstLine = FirstLine { 
      hyp :: [Expression]
    , res :: Expression
    }

data Storage = Storage { 
      ammount   :: Int
    , firstLine :: FirstLine
    , exprTN    :: Map Expression (Type, Int)
    , exprMP    :: Map Expression [(Expression, Int)]
    , lastExpr  :: Expression
    }

data Line = Line Expression Type Int

instance Show Type where
    show (Axiom num)          = "Ax. sch. " ++ show num
    show (Hypothesis num)     = "Hypothesis " ++ show num 
    show (ModusPonens (a, b)) = "M.P. " ++ show a ++ ", " ++ show b

instance Show FirstLine where
    show (FirstLine h r) = hyp ++ spliter ++ res
        where 
              spliter = if Prelude.null h then "|- " else " |- "
              hyp     = intercalate ", " list
              list    = Prelude.map show h  
              res     = show r

instance Show Line where 
    show (Line e t p) = "[" ++ show p ++ ". " ++ show t ++ "] " ++ show e

determineTypeOf :: Expression -> Storage -> Type 
determineTypeOf expression storage 
    | isAxiom       = Axiom numOfAxiom
    | isHypotesis   = Hypothesis numOfHypothesis
    | isModusPonens = ModusPonens numsOfModusPonens
    | otherwise     = Uncertain
    where
        -- Check AXIOM
        isAxiom = numOfAxiom /= -1
        numOfAxiom = determineAxiomOf expression
        -- Check HYPOTESIS
        isHypotesis = numOfHypothesis /= -1
        numOfHypothesis = 
            case elemIndex expression (hyp . firstLine $ storage) of 
                Nothing  -> -1
                Just num -> num + 1
        -- Check MODUS PONENS
        isModusPonens = numsOfModusPonens /= (-1, -1)  
        numsOfModusPonens = 
            case Map.lookup expression (exprMP storage) of
                Nothing   -> (-1, -1) 
                Just list -> findAny $ Prelude.map findHelper list
                where
                    findHelper (exprA, posAB) = 
                        case Map.lookup exprA (exprTN storage) of  
                            Nothing -> (-1, -1) 
                            Just (_, posA) -> (posAB, posA)
                    
                    findAny [x]          = x
                    findAny ((_, -1):xs) = findAny xs
                    findAny (x : xs)     = x

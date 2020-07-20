module Utils where

import Lexer
import Expression
import ExpressionParser
import FirstLineParser
import Type
import Data.Map.Strict as M (empty, toList)
import Data.List            (sortOn)

getFirstLine :: String -> FirstLine
getFirstLine = parseFirstLine . alexScanTokens

getExpression :: String -> Expression
getExpression = parseExpression . alexScanTokens

incorrect :: String
incorrect = "Proof is incorrect"


initStorage :: FirstLine -> Storage
initStorage fl = Storage { 
      ammount   = 1
    , firstLine = fl
    , exprTN    = M.empty
    , exprMP    = M.empty
    , lastExpr  = Variable "KARTON"
    }

initProof :: Storage -> [Line]
initProof storage = Prelude.map (\(e, (t,p)) -> Line e t p) (sortOn (snd . snd) (M.toList $ exprTN storage))

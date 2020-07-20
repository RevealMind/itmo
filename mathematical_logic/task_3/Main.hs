module Main where

import ExpressionParser
import FirstLineParser
import Expression
import Lexer
import Utils
import System.IO
import Intuitionistic
import Data.List(intercalate)

main :: IO ()
main = do 
    task <- getLine
    let parsed = parseFirstLine . alexScanTokens $ task
        left  = leftPart parsed
        right = Not . Not . rightPart $ parsed
    print $ FirstLine left right
    readByLine $ initStorage left 
    

readByLine :: Storage -> IO ()
readByLine storage = do
    iseof <- isEOF
    if iseof 
        then return ()
        else do
            task <- getLine
            let (newStore, out) = translate storage $ parse task
            mapM_ print out
            readByLine newStore
            
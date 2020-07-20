module Main where

import Grammar (Expression (..))
import Lexer (alexScanTokens)
import Parser (parseExpr)

main :: IO ()
main = do 
  input <- getContents
  putStrLn (show (parseExpr (alexScanTokens input)))

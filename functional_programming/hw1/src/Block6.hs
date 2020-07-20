{-# LANGUAGE LambdaCase #-}

-----------------------------------------------------------------------------
-- |
-- Module      : Block6
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Block6: a module for sixth block of homework №1.
--
-----------------------------------------------------------------------------

module Block6
  ( Parser(..)
  , element
  , eof
  , ok
  , parseRBS
  , parseListiOfNumList
  , parseNum
  , satisfy
  , stream
  ) where

import Control.Applicative (Alternative, empty, liftA2, many, some, (<|>))
import Control.Monad (replicateM, (>=>))
import Data.Char (isDigit, isSpace)

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 1 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of parser-combinator
newtype Parser s a = Parser { runParser :: [s] -> Maybe (a, [s]) }

instance Functor (Parser s) where
  fmap f pa = Parser $ runParser pa >=> \(a, next) -> return (f a, next)

instance Applicative (Parser s) where
  pure a = Parser $ return . (,) a

  pf <*> pa = Parser $ runParser pf      >=> \(f, rest) ->
                       runParser pa rest >>= \(a, rest') ->
                       return (f a, rest')

instance Monad (Parser s) where
  pa >>= f = Parser $ runParser pa >=> \(a, rest) -> runParser (f a) rest

instance Alternative (Parser s) where
  empty = Parser $ \_ -> Nothing

  pa <|> pb = Parser $ \s -> runParser pa s <|> runParser pb s

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 2 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Always succeeds without consuming any input
ok :: Parser s ()
ok = return ()

-- | Succeeds only at the end of input stream
eof :: Parser s ()
eof = Parser $ \s -> case s of
  [] -> return ((), s)
  _  -> Nothing

-- | Consumes only single character and returns it if predicate is true
satisfy :: (s -> Bool) -> Parser s s
satisfy p = Parser $ \case
  [] -> Nothing
  x:xs -> if p x
    then return (x, xs)
    else Nothing

-- | Consumes given character and returns it
element :: Eq s => s -> Parser s s
element e = satisfy (== e)

-- | Consumes given list of character and returns their
stream :: Eq s => [s] -> Parser s [s]
stream = traverse element

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 3 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Parser for regular bracket sequences
parseRBS :: Parser Char ()
parseRBS = many parseRuleCBS *> eof
  where
    parseRuleCBS = element '(' *> many parseRuleCBS *> element ')'

-- | Parser for Number
parseNum :: (Num a, Read a) => Parser Char a
parseNum = read <$> (parseWithSign <|> parseInt)
  where parseWithSign = parseMinus <|> parsePlus
        parsePlus = element '+' *> parseInt
        parseMinus = (:) <$> element '-' <*> parseInt
        parseInt = some $ satisfy isDigit

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 4 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Parser for List of list of number
parseListiOfNumList :: (Num a, Read a) => Parser Char [[a]]
parseListiOfNumList = parseStart <* eof
  where
    parseStart = liftA2 (:) parseNumList (many $ element ',' *> parseNumList)

    parseNumList = trim parseNum >>= flip replicateM (element ',' *> trim parseNum)

    trim parse = skip *> parse <* skip
    spaces = satisfy isSpace
    skip = many spaces


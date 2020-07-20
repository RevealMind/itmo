-----------------------------------------------------------------------------
-- |
-- Module      : Task4
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task4: a module for fourth task of homework №0.
--
-----------------------------------------------------------------------------

module Task4
  ( -- Функции, выраженные с помощью fix
    factorial
  , fibonacci
  , iterateElement
  , mapFix
  ) where

import Data.Function (fix)

-- | @'iterateElement' x@ - список, т.ч
--
--  @iterateElement x == [x, x..]@
iterateElement :: a -> [a]
iterateElement x = fix (x :)

-- | 'factorial' функция факториала числа
factorial :: Integer -> Integer
factorial = fix (\rec n -> if n <= 0 then 1 else n * rec (n - 1))

-- | @'fibonacci' x@ - x-ое число фибоначи
fibonacci :: Integer -> Integer
fibonacci = fix (\rec n -> if n <= 1 then 1 else rec (n - 1) + rec (n - 2))

-- | @'mapFix' f xs@ - это список, полученный путем применения f к каждому элементу xs, т.е.
--
-- @mapFix f [x1, x2, ..., xn] == [f x1, f x2, ..., f xn]@
mapFix :: (a -> b) -> [a] -> [b]
mapFix = fix handler
  where
    handler :: ((a -> b) -> [a] -> [b]) -> (a -> b) -> [a] -> [b]
    handler _ _ [] = []
    handler rec f (x : xs) = f x : rec f xs

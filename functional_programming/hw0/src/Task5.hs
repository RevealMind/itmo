-----------------------------------------------------------------------------
-- |
-- Module      : Task5
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task5: a module for fifth task of homework №0.
--
-----------------------------------------------------------------------------

module Task5
  ( -- * Функции для черчевских нумералов
    churchMult
  , churchPlus
  , churchToInt
  , succChurch
  , zero
  ) where

type Nat a = (a -> a) -> a -> a

-- | 'zero' - определения нуля для черчевских нумералов, т.е
--
-- @churchToInt zero = 0@
zero :: Nat a
zero _ x = x

-- | @'succChurch' x@ - черчевский нумерал равный
-- инкременту черчевского нумерала x, т.е
--
-- @churchToInt (succChurch number) = 1 + churchToInt number@
succChurch :: Nat a -> Nat a
succChurch n f x = f (n f x)

-- | @'churchPlus' x y@ - черчевский нумерал равный
-- сумме черчевский нумералов x и y, т.е
--
-- @churchToInt (churchPlus m n) = churchToInt m + churchToInt n@
churchPlus :: Nat a -> Nat a -> Nat a
churchPlus a b f x = a f (b f x)

-- | @'churchMult' x y@ - черчевский нумерал равный произведению
-- черчевских нумералов x и y, т.е
--
-- @churchToInt (churchMult m n) = churchToInt m * churchToInt n@
churchMult :: Nat a -> Nat a -> Nat a
churchMult a b f x = a (b f) x

-- | @'churchToInt' x@ - число, которое соответсвует черчевскому нумералу x
churchToInt :: Nat Integer -> Integer
churchToInt n = n (1 +) 0

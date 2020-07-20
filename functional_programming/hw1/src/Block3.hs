-----------------------------------------------------------------------------
-- |
-- Module      : Block3
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Block1: a module for third block of homework №1.
--
-----------------------------------------------------------------------------

module Block3
  ( Endo (..)
  , Name (..)
  , NonEmpty (..)
  , ThisOrThat (..)
  , eitherConcat
  , maybeConcat
  ) where

import Data.Foldable (fold)
import Data.Maybe (fromMaybe)

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 1(Base) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Concat list of Maybe list and then unwrapp
maybeConcat :: [Maybe [a]] -> [a]
maybeConcat = fromMaybe [] . fold

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 1(Hard) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Concat list of Either and then unwrapp to pair
eitherConcat :: (Monoid a, Monoid b) => [Either a b] -> (a, b)
eitherConcat = foldMap func
  where
    func (Left a)  = (a, mempty)
    func (Right b) = (mempty, b)

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 2(Base) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of non-empty list
data NonEmpty a = a :| [a]
  deriving (Show, Eq)

instance Semigroup (NonEmpty a) where
  (x:|xs) <> (y:|ys) = x :| (xs ++ y:ys)

-- | This type is used for my homework
data ThisOrThat a b = This a | That b | Both a b
  deriving (Show, Eq)

instance Semigroup (ThisOrThat a b) where
  This _ <> This a     = This a
  That _ <> That b     = That b
  That b <> This a     = Both a b
  This a <> That b     = Both a b
  Both _ _ <> Both a b = Both a b
  This _ <> Both a b   = Both a b
  That _ <> Both a b   = Both a b
  Both _ b <> This a   = Both a b
  Both a _ <> That b   = Both a b

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 2(Hard) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of 'String' united by dot
data Name = Name String
  deriving (Show, Eq)

instance Semigroup Name where
  Name a  <> Name "" = Name a
  Name "" <> Name b  = Name b
  Name a  <> Name b  = Name (a ++ '.' : b)

instance Monoid Name where
  mempty = Name ""

-- | Type of func wrapper
newtype Endo a = Endo { getEndo :: a -> a }

instance Semigroup (Endo a) where
  Endo f <> Endo g = Endo (f . g)

instance Monoid (Endo a) where
  mempty = Endo id

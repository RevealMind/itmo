{-# LANGUAGE InstanceSigs #-}

-----------------------------------------------------------------------------
-- |
-- Module      : Block1
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Block1: a module for first block of homework №1.
--
-----------------------------------------------------------------------------

module Block1
  ( -- * Day
    Day (..)
  , afterDays
  , daysToParty
  , nextDay
  , isWeekend
    -- * Nat
  , Nat (..)
    -- * Tree
  , Tree (..)
  , contains
  , empty
  , even
  , fromList
  , insert
  , remove
  , size
  ) where

import Data.List.NonEmpty as NE (NonEmpty (..), length, (<|))
import Prelude hiding (even, length)

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 1 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of days of the week
data Day
  = Monday
  | Tuesday
  | Wednesday
  | Thursday
  | Friday
  | Saturday
  | Sunday
  deriving Show

instance Eq Day where
  a == b = show a == show b

instance Enum Day where
  fromEnum Monday    = 0
  fromEnum Tuesday   = 1
  fromEnum Wednesday = 2
  fromEnum Thursday  = 3
  fromEnum Friday    = 4
  fromEnum Saturday  = 5
  fromEnum Sunday    = 6

  toEnum 0 = Monday
  toEnum 1 = Tuesday
  toEnum 2 = Wednesday
  toEnum 3 = Thursday
  toEnum 4 = Friday
  toEnum 5 = Saturday
  toEnum 6 = Sunday
  toEnum n
    | n >= 0    = toEnum $ Prelude.mod n 7
    | otherwise = error "Incorect input"

instance Ord Day where
  a <= b = fromEnum a <= fromEnum b

-- | Return next day
nextDay :: Day -> Day
nextDay = flip afterDays 1

-- | Return day after n days
afterDays :: Day -> Int -> Day
afterDays day count = toEnum $ count + fromEnum day

-- | Return 'True' if day is weekend
isWeekend :: Day -> Bool
isWeekend Saturday = True
isWeekend Sunday   = True
isWeekend _        = False

-- | Return count of days before Friday
daysToParty :: Day -> Int
daysToParty day = Prelude.mod (4 - fromEnum day) 7

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 2 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of natural number
data Nat
  = Z
  | S Nat

instance Show Nat where
  show = show . toInteger

instance Eq Nat where
  Z == Z         = True
  (S x) == (S y) = x == y
  _ == _         = False

instance Ord Nat where
  Z <= _         = True
  _ <= Z         = False
  (S x) <= (S y) = x <= y

instance Enum Nat where
  fromEnum Z     = 0
  fromEnum (S x) = 1 + fromEnum x

  toEnum 0 = Z
  toEnum n = S $ toEnum $! n - 1

instance Num Nat where
  abs = id

  signum Z = 0
  signum _ = 1

  (S x) + (S y) = S . S $ x + y
  x     + (S y) = S $ x + y
  x     + Z     = x

  Z     * _ = Z
  (S x) * y = y + (x * y)

  a     - Z     = a
  Z     - _     = Z
  (S a) - (S b) = a - b

  fromInteger n
    | n <= 0    = Z
    | otherwise = S $ fromInteger $! n - 1

instance Real Nat where
  toRational Z     = 0
  toRational (S x) = 1 + toRational x

instance Integral Nat where
  quotRem _ Z = error "Dividing by Z"
  quotRem x y
    | x < y     = (Z, x)
    | otherwise = let (x', y') = quotRem (x - y) y in (S x', y')

  divMod = quotRem

  div a = fst . quotRem a

  mod a = snd . quotRem a

  toInteger Z     = 0
  toInteger (S x) = 1 + toInteger x

-- | Fast impl 'even' for 'Nat'
even :: Nat -> Bool
even Z         = True
even (S Z)     = False
even (S (S x)) = even x

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 3 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of tree with 'NonEmpty' List
data Tree a
  = Leaf
  | Node (NonEmpty a) (Tree a) (Tree a)
  deriving Show

instance Eq a => Eq (Tree a) where
  Leaf == Leaf = True
  (Node a l r) == (Node b lb rb) = a == b && l == lb && r == rb
  _ == _ = False

-- | Return 'True' if 'Tree' is empty
empty :: Tree a -> Bool
empty Leaf = True
empty _    = False

-- | Return size of tree
size :: Ord a => Tree a -> Int
size Leaf             = 0
size (Node elems l r) = length elems + size l + size r

-- | Return 'True' if elem contains in 'Tree'
contains :: Ord a => a -> Tree a -> Bool
contains _ Leaf = False
contains x (Node (k :| _) l r)
  | x == k    = True
  | x < k     = contains x l
  | otherwise = contains x r

-- | 'insert' elem in 'Tree'
insert :: Ord a => a -> Tree a -> Tree a
insert x Leaf = Node (x :| []) Leaf Leaf
insert x (Node elems@(k :| _) l r)
  | x == k    = Node (x <| elems) l r
  | x < k     = Node elems (insert x l) r
  | otherwise = Node elems l (insert x r)

-- | Create 'Tree' from list
fromList :: Ord a => [a] -> Tree a
fromList list = foldr insert Leaf (reverse list)

-- | 'remove' elem in 'Tree'
remove :: Ord a => a -> Tree a -> Tree a
remove _ Leaf = Leaf
remove x (Node elems@(k :| xs) l r)
  | x < k         = Node elems (remove x l) r
  | x > k         = Node elems l (remove x r)
  | not (null xs) = Node (x :| tail xs) l r
  | otherwise =
      case (l, r) of
        (_, Leaf) -> l
        (Leaf, _) -> r
        _         -> let (e, r') = getRemoveMin r in Node e l r'

getRemoveMin :: Ord a => Tree a -> (NE.NonEmpty a, Tree a)
getRemoveMin Leaf                = error "empty tree"
getRemoveMin (Node elems Leaf r) = (elems, r)
getRemoveMin (Node elems l r)    = (elems', Node elems l' r)
  where (elems', l') = getRemoveMin l


----------------------------------------------- Block2 ---------------------------------------------
----------------------------------------------- Task 1 ---------------------------------------------
----------------------------------------------------------------------------------------------------

instance Foldable Tree where
  foldr :: (a -> b -> b) -> b -> Tree a -> b
  foldr _ z Leaf          = z
  foldr f z (Node xs l r) = foldr f (foldr f (foldr f z r) xs) l

  foldMap :: Monoid m => (a -> m) -> Tree a -> m
  foldMap _ Leaf          = mempty
  foldMap f (Node xs l r) = foldMap f l <> foldMap f xs <> foldMap f r

-----------------------------------------------------------------------------
-- |
-- Module      : Block4
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Block4: a module for fourth block of homework №1.
--
-----------------------------------------------------------------------------

module Block4
  ( NonEmpty(..)
  , Tree (..)
  , stringSum
  ) where

import Text.Read (readMaybe)

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 1(Base) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Safyt sting sum. Will return 'Nothing' if an error
stringSum :: String -> Maybe Int
stringSum str = sum <$> traverse readMaybe (words str)

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 2 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of tree with elem in list
data Tree a
  = Branch (Tree a) (Tree a)
  | Leaf a
  deriving Show

instance Functor Tree where
  fmap f (Leaf a)     = Leaf (f a)
  fmap f (Branch l r) = Branch (fmap f l) (fmap f r)

instance Applicative Tree where
  pure = Leaf

  Leaf f     <*> el = fmap f el
  Branch l r <*> el = Branch (l <*> el) (r <*> el)

instance Foldable Tree where
  foldr f el (Leaf a)     = f a el
  foldr f el (Branch l r) = foldr f (foldr f el r) l

instance Traversable Tree where
  traverse f (Leaf a)     = pure <$> f a
  traverse f (Branch l r) = Branch <$> traverse f l <*> traverse f r

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 3 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of non-empty list
data NonEmpty a = a :| [a]

instance Functor NonEmpty where
  fmap f (a :| as) = f a :| fmap f as

instance Applicative NonEmpty where
  pure a = a :| []

  f :| fs <*> (a :| as) = x :| xs
    where x:xs = f:fs <*> a:as

instance Monad NonEmpty where
  a :| as >>= f = x :| xs
    where
      x:xs = a:as >>= toList . f
      toList (t:|ts) = t:ts

instance Foldable NonEmpty where
  foldr f b (a :| as) = foldr f b $ a:as

instance Traversable NonEmpty where
  traverse f (a :| as) = (:|) <$> f a <*> traverse f as

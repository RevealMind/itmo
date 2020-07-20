{-# LANGUAGE TypeOperators #-}

-----------------------------------------------------------------------------
-- |
-- Module      : Task1
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task1: a module for first task of homework №0.
--
-----------------------------------------------------------------------------

module Task1
  ( -- * Inhabitant terms
    associator
  , distributivity
  , eitherAssoc
  ) where

-- | The `distributivity` function demonstrates the distribution law
--
-- >>> distributivity (Left 1)
-- (Left 1, Left 1)
--
-- >>> distributivity (Right (2 , 3))
-- (Right 2, Right 3)
distributivity :: Either a (b, c) -> (Either a b, Either a c)
distributivity (Left  a)      = (Left a, Left a)
distributivity (Right (b, c)) = (Right b, Right c)

-- | The `associator` function demonstrates the law of associativity
--
-- >>> associator (1, (2, 3))
-- ((1, 2), 3)
associator :: (a, (b, c)) -> ((a, b), c)
associator (a, (b, c)) = ((a, b), c)

type (<->) a b = (a -> b, b -> a)

-- | The `eitherAssoc` function generate pair of function that implement
--  the law of associativity
--
-- >>> fst eitherAssoc (left 1)
-- Left (left 1)
eitherAssoc :: Either a (Either b c) <-> Either (Either a b) c
eitherAssoc = (eitherAssociatorL, eitherAssociatorR)
  where
    eitherAssociatorL :: Either a (Either b c) -> Either (Either a b) c
    eitherAssociatorL (Left  a)         = Left (Left a)
    eitherAssociatorL (Right (Left  b)) = Left (Right b)
    eitherAssociatorL (Right (Right c)) = Right c

    eitherAssociatorR :: Either (Either a b) c -> Either a (Either b c)
    eitherAssociatorR (Left  (Left  a)) = Left a
    eitherAssociatorR (Left  (Right b)) = Right (Left b)
    eitherAssociatorR (Right c)         = Right (Right c)

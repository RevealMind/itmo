-----------------------------------------------------------------------------
-- |
-- Module      : Block2
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Block2: a module for second block of homework №1.
--
-----------------------------------------------------------------------------

module Block2
  ( splitOn
  , joinWith
  ) where

import Data.List.NonEmpty (NonEmpty (..), (<|))

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 2(Base) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | split list on elem
splitOn :: Eq a => a -> [a] -> NonEmpty [a]
splitOn el = foldr func ([] :| [])
  where
    func x acc@(y :| ys)
      | x == el   = [] <| acc
      | otherwise = (x : y) :| ys

----------------------------------------------------------------------------------------------------
-------------------------------------------- Task 2(Hard) ------------------------------------------
----------------------------------------------------------------------------------------------------

-- | join list with elem
joinWith :: a -> NonEmpty [a] -> [a]
joinWith el (y :| ys) = foldl func y ys
  where
    func acc x = acc ++ el : x

-----------------------------------------------------------------------------
-- |
-- Module      : Task3
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task3: a module for third task of homework №0.
--
-----------------------------------------------------------------------------

module Task3
  ( -- * Комбинаторы в SK-базисе
    composition
  , contraction
  , identity
  , s
  , permutation
  ) where

-- | 's' - один из комбинаторов SK-базиса
s :: (a -> b -> c) -> (a -> b) -> a -> c
s f g x = f x (g x)

-- | 'identity' - комбинатор вида λx.x
identity :: a -> a
identity = s const const

-- | 'composition' - комбинатор вида λf.λg.λx.f (g x)
composition :: (b -> c) -> (a -> b) -> a -> c
composition = s (const s) const

-- | 'contraction' - комбинатор вида λf.λx.f x x
contraction :: (a -> a -> b) -> a -> b
contraction = s s (s const)

-- | 'permutation' - комбинатор вида λf.λy.λx.f x y
permutation :: (a -> b -> c) -> b -> a -> c
permutation = s (s (const (s (const s) const)) s) (const const)

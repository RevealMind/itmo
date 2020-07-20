-----------------------------------------------------------------------------
-- |
-- Module      : Task2
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task2: a module for second task of homework №0.
--
-----------------------------------------------------------------------------

module Task2
  ( -- * Заселенные
    doubleNeg
  , excludedNeg
  , thirdNegElim
   -- * Незаселенные
  , doubleNegElim
  , pierce
  ) where

import Data.Void (Void)

-- Отрицание в BHK интерпритации
type Neg a = a -> Void

-- | 'doubleNeg' населяет тип a -> ¬¬a
doubleNeg :: a -> Neg (Neg a) -- (a -> ((a -> Void) -> Void))
doubleNeg a f = f a

-- | 'excludedNeg' населяет тип ¬¬(a ∨ ¬a)
excludedNeg :: Neg (Neg (Either a (Neg a))) -- (((Either a (a -> Void)) -> Void) -> Void)
excludedNeg f = (f . Right) (f . Left)

-- | 'pierce' не доказуема в ИИВ =>
-- По изоморфизму К-Х, не существует терма, населяющего данный тип
pierce :: ((a -> b) -> a) -> a
pierce = undefined

-- | 10я аксиома не доказуема в ИИВ =>
-- По изоморфизму К-Х, не существует терма, населяющего данный тип
doubleNegElim :: Neg (Neg a) -> a
doubleNegElim = undefined

-- | 'thirdNegElim' населяет тип ¬¬¬a -> ¬a
thirdNegElim :: Neg (Neg (Neg a)) -> Neg a -- ([(a -> Void) -> Void] -> Void) -> a -> Void
thirdNegElim f = f . doubleNeg

-----------------------------------------------------------------------------
-- |
-- Module      : Task6
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task6: a module for sixth task of homework №0.
--
-----------------------------------------------------------------------------

module Task6
    ( -- WHNF
      first
    , second
    ) where

import Data.Maybe (mapMaybe)
import Task1 (distributivity)

-- | Шаги редукции, которые приводят 'first' к WHNF:
--
-- @ distributivity (Left ("harold" ++ " hide " ++ "the " ++ "pain")) ~>
-- (Left ("harold" ++ " hide " ++ "the " ++ "pain"), Left ("harold" ++ " hide " ++ "the " ++ "pain"))@
--
-- WHNF: @(Left ("harold" ++ " hide " ++ "the " ++ "pain"), Left ("harold" ++ " hide " ++ "the " ++ "pain"))@
first :: (Either [Char] b, Either [Char] c)
first = distributivity (Left ("harold" ++ " hide " ++ "the " ++ "pain"))

-- | Шаги редукции, которые приводят 'second' к WHNF:
--
-- @ null $ mapMaybe foo "pole chudes ochen' chudesno" ~>
-- null (mapMaybe foo "pole chudes ochen' chudesno") ~>
-- ... ~>
-- null ((exp pi) : (mapMaybe foo "le chudes ochen' chudesno")) ~>
-- False@
--
-- WHNF: @False@
second :: Bool
second = null $ mapMaybe foo "pole chudes ochen' chudesno"

foo :: Char -> Maybe Double
foo char =
    case char == 'o' of
      True -> Just $ exp pi
      False -> Nothing

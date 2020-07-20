-----------------------------------------------------------------------------
-- |
-- Module      : Block5
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Block5: a module for fifth block of homework №1.
--
-----------------------------------------------------------------------------

module Block5
  ( -- * Eval
    ArithmeticError (..)
  , Expr (..)
  , Operation (..)
  , eval
    -- * SMA algo
  , moving
  ) where

import Control.Monad.State.Lazy (State, evalState, get, modify, replicateM)
import Numeric.Natural (Natural)

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 1 ---------------------------------------------
----------------------------------------------------------------------------------------------------

-- | Type of base arithmetic operation
data Operation
  = Sum
  | Minus
  | Mul
  | Div
  | Pow
  deriving Eq

-- | Type of 'Int' expresstions
data Expr
  = Const Int
  | BinOp Operation Expr Expr
  deriving Eq

-- | Type of common arithmetic error
data ArithmeticError
  = DivByNull
  | NegatePow
  deriving (Eq, Show)

-- | Evaluate expresstion and return answer or 'ArithmeticError' if an error
eval :: Expr -> Either ArithmeticError Int
eval (BinOp op l r) = eval l >>= \a -> eval r >>=  applyOp op a
eval (Const x)      = return x

applyOp :: Operation -> Int -> Int -> Either ArithmeticError Int
applyOp Sum   a b = return $ a + b
applyOp Minus a b = return $ a - b
applyOp Mul   a b = return $ a * b
applyOp Div a b
  | b == 0    = Left DivByNull
  | otherwise = return $ a `div` b
applyOp Pow a b
  | b < 0     = Left NegatePow
  | otherwise = return $ a ^ b

----------------------------------------------------------------------------------------------------
----------------------------------------------- Task 2 ---------------------------------------------
----------------------------------------------------------------------------------------------------

data Step
  = Induction
  | Base

data StepInfo a = StepInfo
  { siSum      :: a
  , siFrame    :: Natural
  , siFromList :: [a]
  , siToList   :: [a]
  , siType     :: Step
  }

-- | Implementation  Simple Moving Average algorithm
moving :: Fractional a => Natural -> [a] -> [a]
moving n xs = evalState (replicateM (length xs) step) initStep
  where initStep = StepInfo 0 n xs xs Base

step :: Fractional a => State (StepInfo a) a
step = do
  stepInfo <- get
  case siType stepInfo of
    Base -> baseStep
    _    -> inductionStep

baseStep :: Fractional a => State (StepInfo a) a
baseStep = do
  StepInfo s frame as bs _ <- get
  let curFrame = fromIntegral . succ $ length as - length bs
  stepHandler s curFrame (changeType $ frame == curFrame)

inductionStep :: Fractional a => State (StepInfo a) a
inductionStep = do
  stepInfo <- get
  let val:restList = siFromList stepInfo
  stepHandler val (siFrame stepInfo) (changeFromList restList)

stepHandler :: Fractional a => a -> Natural -> (StepInfo a -> StepInfo a) -> State (StepInfo a) a
stepHandler leftVal frame modifier = do
  stepInfo <- get
  let rightVal:restList = siToList stepInfo
  let prevSum = siSum stepInfo
  let curSum = prevSum + (rightVal - leftVal) / fromIntegral frame
  modify $ modifier . changeSum curSum . changeToList restList
  return curSum

changeSum :: Fractional a => a -> StepInfo a -> StepInfo a
changeSum curSum s = s {siSum = curSum}

changeToList :: Fractional a => [a] -> StepInfo a -> StepInfo a
changeToList newList s = s {siToList = newList}

changeFromList :: Fractional a => [a] -> StepInfo a -> StepInfo a
changeFromList newList s = s {siFromList = newList}

changeType :: Bool -> StepInfo a -> StepInfo a
changeType cond s
  | cond      = s {siType = Induction}
  | otherwise = s

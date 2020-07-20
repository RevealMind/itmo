{-# LANGUAGE MultiWayIf #-}

module SpecBlock5 where

import Block5
import Utils

import Hedgehog (Property, forAll, property, (===))
import Test.Hspec (SpecWith, describe, it, shouldBe)
import Test.Tasty (TestTree, testGroup)
import Test.Tasty.Hedgehog (testProperty)
import Test.Tasty.Hspec (testSpec)

import System.IO.Unsafe (unsafePerformIO)

testBlock5 :: TestTree
testBlock5 = testGroup "Block5" [task1Tests, task2Test]

task1Tests :: TestTree
task1Tests = testGroup "Task1" [task1]
  where
    task1 = testGroup propTests [testProperty "safeOp" task1SafeOp
                               , testProperty "unsafeOp" task1UnsafeOp]

task1SafeOp :: Property
task1SafeOp = property $ do
  a <- forAll $ genInt leftBound rightBound
  b <- forAll $ genInt leftBound rightBound
  c <- forAll $ genInt leftBound rightBound
  d <- forAll $ genInt leftBound rightBound

  let expr = BinOp Minus (BinOp Mul (BinOp Sum (Const a) (Const b)) (Const c)) (Const d)
  Block5.eval expr === Right (((a + b) * c) - d)

task1UnsafeOp :: Property
task1UnsafeOp = property $ do
  a <- forAll $ genInt leftBound rightBound
  b <- forAll $ genInt leftBound rightBound
  c <- forAll $ genInt leftBound rightBound

  let expr = BinOp Pow (BinOp Div (Const a) (Const b)) (Const c)
  if | (b == 0)  -> Block5.eval expr === Left DivByNull
     | (c < 0)   -> Block5.eval expr === Left NegatePow
     | otherwise -> Block5.eval expr === Right ((a `div` b) ^ c)


task2Test :: TestTree
task2Test = testGroup "Task2" [unsafePerformIO $ testSpec unitTests task2Spec]

task2Spec :: SpecWith ()
task2Spec =
  describe "moving" $ do
    it "first example (moving 4 [1, 5, 3, 8, 7, 9, 6])" $
      moving 4 [1, 5, 3, 8, 7, 9, 6] `shouldBe` ([1.0, 3.0, 3.0, 4.25, 5.75, 6.75, 7.5] :: [Double])
    it "second example (moving 2 [1, 5, 3, 8, 7, 9, 6])" $
      moving 2 [1, 5, 3, 8, 7, 9, 6] `shouldBe` ([1.0, 3.0, 4.0, 5.5, 7.5, 8.0, 7.5] :: [Double])

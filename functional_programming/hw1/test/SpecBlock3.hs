{-# LANGUAGE ScopedTypeVariables #-}
{-# LANGUAGE TypeApplications    #-}

module SpecBlock3 where

import Block3
import Utils

import Hedgehog (Gen, Property, forAll, property, (===))
import Hedgehog.Function (Arg, Vary, fn, forAllFn)
import qualified Hedgehog.Gen as Gen (bool)
import Test.Hspec (SpecWith, describe, it, shouldBe)
import Test.Tasty (TestTree, testGroup)
import Test.Tasty.Hedgehog (testProperty)
import Test.Tasty.Hspec (testSpec)

import System.IO.Unsafe (unsafePerformIO)

testBlock3 :: TestTree
testBlock3 = testGroup "Block3" [task1Test, task2Test]

task1Test :: TestTree
task1Test = testGroup "Task1" [unsafePerformIO (testSpec unitTests task1Spec)]

task1Spec :: SpecWith ()
task1Spec = do
  describe "maybeConcat" $ do
    it "maybeConcat empty list" $
      maybeConcat [] `shouldBe` ([] :: [Int])
    it "maybeConcat list of Nothing" $
      maybeConcat (replicate 100 Nothing) `shouldBe` ([] :: [Int])
    it "maybeConcat list of Just" $
      maybeConcat [Just [1,2,3], Just [4,5]] `shouldBe` ([1,2,3,4,5] :: [Int])
    it "maybeConcat list" $
      maybeConcat [Just [1,2,3], Nothing, Just [4,5]] `shouldBe` ([1,2,3,4,5] :: [Int])

  describe "eitherConcat" $ do
    it "eitherConcat empty list" $
      eitherConcat [] `shouldBe` ("", "")
    it "eitherConcat list of Left" $
      eitherConcat [Left "a", Left "b", Left "c"] `shouldBe` ("abc", "")
    it "eitherConcat list of Right" $
      eitherConcat [Right "a", Right "b", Right "c"] `shouldBe` ("", "abc")
    it "eitherConcat list" $
      eitherConcat [Left "a", Right [1, 2, 3], Left "b", Right [4, 5]] `shouldBe` ("ab", [1,2,3,4,5] :: [Int])

task2Test :: TestTree
task2Test = testGroup "Task2" $ [testGroup propTests [testProperty "Semigroup NonEmpty" (task2Semi genNonEmpty)
                                                    , testProperty "Semigroup ThisOrThat" (task2Semi genThisOrThat)
                                                    , testProperty "Semigroup Name" (task2Semi genName)
                                                    , testProperty "Monad Name" (task2SemiMon genName)
                                                    , testProperty "Monad Endo Bool" (task2Monoid Gen.bool)
                                                    , testProperty "Monad Endo Integer" (task2Monoid (genInteger leftBound rightBound))]]

task2Semi :: (Show a, Eq a, Semigroup a) => Gen a -> Property
task2Semi gen = property $ do
  xs <- forAll gen
  ys <- forAll gen
  zs <- forAll gen
  (xs <> ys) <> zs === xs <> (ys <> zs)

task2SemiMon :: (Show a, Eq a, Monoid a) => Gen a -> Property
task2SemiMon gen = property $ do
  x <- forAll gen
  mempty <> x === x <> mempty
  mempty <> x === x

task2Monoid :: forall a . (Show a, Eq a, Arg a, Vary a) => Gen a -> Property
task2Monoid gen = property $ do
    g' <- forAllFn $ fn @a gen
    f' <- forAllFn $ fn @a gen
    k' <- forAllFn $ fn @a gen
    let g = Endo g'
    let f = Endo f'
    let k = Endo k'
    x <- forAll gen
    getEndo ((g <> f) <> k) x === getEndo (g <> (f <> k)) x
    getEndo (mempty <> f) x === getEndo (f <> mempty) x
    getEndo (mempty <> f) x === getEndo f x

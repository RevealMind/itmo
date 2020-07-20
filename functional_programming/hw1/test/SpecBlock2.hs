module SpecBlock2 where

import Block1 (fromList)
import Block2
import Utils

import Hedgehog (Property, forAll, property, (===))
import qualified Hedgehog.Gen as Gen (string, alpha)
import qualified Hedgehog.Range as Range (linear)
import Test.Hspec (SpecWith, describe, it, shouldBe)
import Test.Tasty (TestTree, testGroup)
import Test.Tasty.Hedgehog (testProperty)
import Test.Tasty.Hspec (testSpec)

import Data.Foldable (toList)
import Data.List (sort)
import Data.List.NonEmpty (NonEmpty (..))
import System.IO.Unsafe (unsafePerformIO)

testBlock2 :: TestTree
testBlock2 = testGroup "Block2" [task1Test, task2Test]

task1Test :: TestTree
task1Test = testGroup "Task1" [testProperty propTests task1Prop]

task1Prop :: Property
task1Prop = property $ do
  xs <- forAll $ Gen.string (Range.linear 0 100000) Gen.alpha
  toList (Block1.fromList xs) === sort xs

task2Test :: TestTree
task2Test = testGroup "Task2" [unsafePerformIO (testSpec unitTests task2Spec)
                             , testProperty "Property-based test" task2Prop]

task2Spec :: SpecWith ()
task2Spec = do
  describe "splitOn" $ do
    it "split empty string" $
      splitOn ' ' "" `shouldBe` ([]:|[])
    it "non-empty string split on space" $
      splitOn ' ' "path to file" `shouldBe` ("path":|["to", "file"])
    it "non-empty string split on slash" $
      splitOn '/' "path/to/file" `shouldBe` ("path":|["to", "file"])

  describe "joinWith" $ do
    it "join empty string" $
      joinWith ' ' ([]:|[]) `shouldBe` ""
    it "non-empty string split on space" $
      joinWith ' ' ("path":|["to", "file"]) `shouldBe` "path to file"
    it "non-empty string split on slash" $
      joinWith '/' ("path":|["to", "file"]) `shouldBe` "path/to/file"

task2Prop :: Property
task2Prop = property $ do
  xs <- forAll $ Gen.string (Range.linear 0 100000) Gen.alpha
  x <- forAll Gen.alpha
  joinWith x (splitOn x xs) === xs

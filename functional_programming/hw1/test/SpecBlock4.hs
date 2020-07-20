module SpecBlock4 where

import Block4
import Utils

import Hedgehog (Property, forAll, property, (===))
import qualified Hedgehog.Gen as Gen (list)
import qualified Hedgehog.Range as Range (linear)
import Test.Hspec (SpecWith, describe, it, shouldBe)
import Test.Tasty (TestTree, testGroup)
import Test.Tasty.Hedgehog (testProperty)
import Test.Tasty.Hspec (testSpec)

import Data.List (intercalate)
import System.IO.Unsafe (unsafePerformIO)

testBlock4 :: TestTree
testBlock4 = testGroup "Block4" [task1Test]

task1Test :: TestTree
task1Test = testGroup "Task1" [unsafePerformIO (testSpec unitTests task1Spec)
                             , testProperty propTests task1Prop]

task1Spec :: SpecWith ()
task1Spec =
  describe "stringSum" $ do
    it "sum empty string" $
      stringSum "" `shouldBe` pure 0
    it "sum string with 1 number" $
      stringSum "1" `shouldBe` pure 1
    it "sum string with 1 number with spaces" $
      stringSum "         123          " `shouldBe` (pure 123 :: Maybe Int)
    it "sum string with 1 large number" $
      stringSum "9223372036854775807" `shouldBe` pure 9223372036854775807
    it "sum wrong string" $
      stringSum "123456789OI23Z5678" `shouldBe` Nothing

task1Prop :: Property
task1Prop = property $ do
  xs <- forAll $ Gen.list (Range.linear 1 10000) (genInteger leftBound rightBound)
  spliter <- forAll genSpaces
  let str = intercalate spliter (map show xs)
  let s = sum xs
  stringSum str === pure (fromIntegral s)



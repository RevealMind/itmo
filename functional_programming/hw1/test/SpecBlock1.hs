module SpecBlock1 where

import Block1
import Utils

import Hedgehog (Property, diff, forAll, property, (/==), (===))
import Test.Hspec (SpecWith, describe, it, shouldBe)
import Test.Tasty (TestTree, testGroup)
import Test.Tasty.Hedgehog (testProperty)
import Test.Tasty.Hspec (testSpec)

import Data.List.NonEmpty (NonEmpty (..))
import System.IO.Unsafe (unsafePerformIO)

testBlock1 :: TestTree
testBlock1 = testGroup "Block1" [task1Test, task2Test, task3Test]

task1Test :: TestTree
task1Test = testGroup "Task1" [unsafePerformIO (testSpec unitTests task1Spec)]

task1Spec :: SpecWith ()
task1Spec = do
  describe "nextDay" $ do
    it "Monday: next day is Tuesday" $
      nextDay Monday `shouldBe` Tuesday
    it "Tuesday: next day is Wednesday" $
      nextDay Tuesday `shouldBe` Wednesday
    it "Wednesday: next day is Thursday" $
      nextDay Wednesday `shouldBe` Thursday
    it "Thursday: next day is Friday" $
      nextDay Thursday `shouldBe` Friday
    it "Friday: next day is Saturday" $
      nextDay Friday `shouldBe` Saturday
    it "Saturday: next day is Sunday" $
      nextDay Saturday `shouldBe` Sunday
    it "Sunday: next day is Monday" $
      nextDay Sunday `shouldBe` Monday

  describe "afterDays" $ do
    it "7 days after Sunday is Sunday" $
      afterDays Sunday 7 `shouldBe` Sunday
    it "10 days after Monday is Thursday" $
      afterDays Monday 10 `shouldBe` Thursday
    it "365 days after Monday is Tuesday" $
      afterDays Monday 365 `shouldBe` Tuesday
    it "30 days after Monday is Wednesday" $
      afterDays Monday 30 `shouldBe` Wednesday

  describe "isWeekend" $ do
    it "Monday isn't Weekend" $
      isWeekend Monday `shouldBe` False
    it "Tuesday isn't Weekend" $
      isWeekend Tuesday `shouldBe` False
    it "Wednesday isn't Weekend" $
      isWeekend Wednesday `shouldBe` False
    it "Thursday isn't Weekend" $
      isWeekend Thursday `shouldBe` False
    it "Friday isn't Weekend" $
      isWeekend Friday `shouldBe` False
    it "Saturday is Weekend" $
      isWeekend Saturday `shouldBe` True
    it "Sunday is Weekend" $
      isWeekend Sunday `shouldBe` True

  describe "daysToParty" $ do
      it "Monday: 4 days to party" $
        daysToParty Monday `shouldBe` 4
      it "Tuesday: 3 days to party" $
        daysToParty Tuesday `shouldBe` 3
      it "Wednesday: 2 days to party" $
        daysToParty Wednesday `shouldBe` 2
      it "Thursday: 1 days to party" $
        daysToParty Thursday `shouldBe` 1
      it "Friday: party is today" $
        daysToParty Friday `shouldBe` 0
      it "Saturday: 6 days to party" $
        daysToParty Saturday `shouldBe` 6
      it "Sunday: 7 days to party" $
        daysToParty Sunday `shouldBe` 5

task2Test :: TestTree
task2Test = testGroup "Task2" $ [testGroup propTests [testProperty "add" $ propTestOpDef (+) (+)
                                                    , testProperty "minus" $ propTestOpDef (-) (-)
                                                    , testProperty "mul" $ propTestOp 1000 (*) (*)
                                                    , testProperty "div" $ propTestOpDef div div
                                                    , testProperty "mod" $ propTestOpDef mod mod
                                                    , testProperty "toInt . fromInt" propTestFromTo
                                                    , testProperty "GT" propTestGT
                                                    , testProperty "not EQ" propTestNEQ
                                                    , testProperty "even" propTestEven]]

propTestOp :: Integer -> (Integer -> Integer -> Integer) -> (Nat -> Nat -> Nat) -> Property
propTestOp maxRight opI opN = property $ do
  b <- forAll $ genInteger 1 maxRight
  a <- forAll $ genInteger 1 maxRight
  let a' = fromInteger a :: Nat
  let b' = fromInteger b :: Nat
  let res = fromInteger (a `opI` b) :: Nat
  a' `opN` b' === res

propTestOpDef :: (Integer -> Integer -> Integer) -> (Nat -> Nat -> Nat) -> Property
propTestOpDef = propTestOp 1000000

propTestFromTo :: Property
propTestFromTo = property $ do
  a <- forAll $ genInteger 0 1000000
  let a' = fromInteger a :: Nat
  toInteger a' === a

propTestGT :: Property
propTestGT = property $ do
  a <- forAll $ genInteger 0 1000000
  b <- forAll $ genInteger a 1000000
  let a' = fromInteger a :: Nat
  let b' = fromInteger b :: Nat
  diff a' (<=) b'

propTestNEQ :: Property
propTestNEQ = property $ do
  a <- forAll $ genInteger 0 1000000
  b <- forAll $ genInteger (a + 1) 1000000
  let a' = fromInteger a :: Nat
  let b' = fromInteger b :: Nat
  a' /== b'

propTestEven :: Property
propTestEven = property $ do
  a <- forAll $ genInteger 0 1000000
  let a' = fromInteger a :: Nat
  Block1.even a' === Prelude.even a

task3Test :: TestTree
task3Test = testGroup "Task3" [unsafePerformIO (testSpec unitTests task3Spec)]

task3Spec :: SpecWith ()
task3Spec = do
  describe "empty" $ do
    it "Leaf: it's empty tree" $
      empty Leaf `shouldBe` True
    it "Node: isn't empty tree" $
      empty (Block1.fromList ['a']) `shouldBe` False

  describe "size" $ do
    it "Leaf" $
      Block1.size (Leaf :: Tree Int) `shouldBe` 0
    it "Node with 1 elem" $
      Block1.size (Block1.fromList ['a']) `shouldBe` 1
    it "Node with 5 elem" $
      Block1.size (Block1.fromList ['a','a','a','b','c']) `shouldBe` 5

  describe "contains" $ do
    it "Empty tree doesn't contain any element" $
      Block1.contains 1 (Leaf :: Tree Int) `shouldBe` False
    it "Tree that contains elem" $
      Block1.contains 'a' (Block1.fromList ['a','a','a','b','c']) `shouldBe` True
    it "Tree that doesn't contain elem" $
      Block1.contains 'f' (Block1.fromList ['d','b','e','a','c']) `shouldBe` False

  describe "insert" $ do
    it "Insert in empty tree" $
      Block1.insert 'a' Leaf `shouldBe` Node ('a':|[]) Leaf Leaf
    it "Tree that contains elem" $
      Block1.insert 'a' (Block1.fromList ['b','a','c']) `shouldBe` Node ('b':|[]) (Node ('a':|"a") Leaf Leaf) (Node ('c':|[]) Leaf Leaf)
    it "Tree that doesn't contain elem" $
      Block1.insert 'f' (Block1.fromList ['b','a','c']) `shouldBe` Node ('b':|[]) (Node ('a':|[]) Leaf Leaf) (Node ('c':|[]) Leaf (Node ('f':|[]) Leaf Leaf))

  describe "fromList" $ do
    it "From empty list - Leaf" $
      Block1.fromList ([] :: [Int])`shouldBe` Leaf
    it "Tree that contains elem" $
      Block1.fromList ['b','a','c'] `shouldBe` Node ('b':|[]) (Node ('a':|[]) Leaf Leaf) (Node ('c':|[]) Leaf Leaf)

  describe "remove" $ do
    it "Remove empty tree" $
      Block1.remove 'a' Leaf `shouldBe` Leaf
    it "Tree that contains list of elem" $
      Block1.remove 'a' (Block1.fromList ['b','a','a','c']) `shouldBe` Node ('b':|[]) (Node ('a':|[]) Leaf Leaf) (Node ('c':|[]) Leaf Leaf)
    it "Tree that contains elem" $
      Block1.remove 'b' (Block1.fromList ['b','a','c']) `shouldBe` Node ('c':|[]) (Node ('a':|[]) Leaf Leaf) Leaf

module SpecBlock6 where

import Block6
import Utils

import Hedgehog (Property, forAll, property, (===))
import qualified Hedgehog.Gen as Gen (list)
import qualified Hedgehog.Range as Range (linear)
import Test.Hspec (SpecWith, describe, it, shouldBe)
import Test.Tasty (TestTree, testGroup)
import Test.Tasty.Hedgehog (testProperty)
import Test.Tasty.Hspec (testSpec)

import Control.Applicative (many, some, (<|>))
import Data.List (intercalate)
import System.IO.Unsafe (unsafePerformIO)

testBlock6 :: TestTree
testBlock6 = testGroup "Block6" [task1Tests, task2Tests, task3Tests, task4Tests]

task1Tests :: TestTree
task1Tests = testGroup "Task1" [unsafePerformIO $ testSpec unitTests task1Sepc]

task1Sepc :: SpecWith ()
task1Sepc =
  describe "Instance" $ do
    it "Functor" $
      runParser (pure <$> element 'a') "a" `shouldBe` Just (Just 'a', "")
    it "Applicative" $
      runParser ((:) <$> element 'a' <*> many (element 'a')) "a" `shouldBe` Just ("a", "")
    it "Monad" $
      runParser (element 'a' >>= some . element) "aa" `shouldBe` Just ("a", "")
    it "Alternative" $ do
      runParser (element 'a' <|> element 'b') "ab" `shouldBe` Just ('a', "b")
      runParser (element 'a' <|> element 'b') "ba" `shouldBe` Just ('b', "a")

task2Tests :: TestTree
task2Tests = testGroup "Task2" [unsafePerformIO $ testSpec unitTests task2Sepc]

task2Sepc :: SpecWith ()
task2Sepc =
  describe "Combinators" $ do
    it "ok" $
      runParser ok "ab" `shouldBe` Just ((), "ab")
    it "eof" $ do
      runParser eof "ab" `shouldBe` Nothing
      runParser eof "" `shouldBe` Just ((), "")
    it "satisfy" $
      runParser (satisfy (== 'a')) "ab" `shouldBe` Just ('a', "b")
    it "element" $
      runParser (element 'a') "aa" `shouldBe` Just ('a', "a")
    it "stream" $
      runParser (stream "Hello! ") "Hello! Its me" `shouldBe` Just ("Hello! ", "Its me")

task3Tests :: TestTree
task3Tests = testGroup "Task3" [unsafePerformIO $ testSpec unitTests task3Sepc]

task3Sepc :: SpecWith ()
task3Sepc = do
  describe "CBS" $ do
    it "correct tests" $ do
      runParser parseRBS "" `shouldBe` Just ((), "")
      runParser parseRBS "()" `shouldBe` Just ((), "")
      runParser parseRBS "()()" `shouldBe` Just ((), "")
      runParser parseRBS "(())()" `shouldBe` Just ((), "")
      runParser parseRBS "(()())()" `shouldBe` Just ((), "")
    it "incorrect tests" $ do
      runParser parseRBS "(" `shouldBe` Nothing
      runParser parseRBS "(a)" `shouldBe` Nothing
      runParser parseRBS "()(()" `shouldBe` Nothing
      runParser parseRBS "(())()  (" `shouldBe` Nothing
      runParser parseRBS "(()())())))" `shouldBe` Nothing

  describe "Number" $ do
    it "correct tests" $ do
      runParser parseNum "1" `shouldBe` Just (1:: Int, "")
      runParser parseNum "+1" `shouldBe` Just (1 :: Int, "")
      runParser parseNum "-1" `shouldBe` Just (-1 :: Int, "")
      runParser parseNum "1234567890Z" `shouldBe` Just (1234567890 :: Int, "Z")
    it "incorrect tests" $ do
      runParser parseNum "fgh1" `shouldBe` (Nothing :: Maybe (Int, String))
      runParser parseNum "+-1" `shouldBe` (Nothing :: Maybe (Int, String))
      runParser parseNum "-   1" `shouldBe` (Nothing :: Maybe (Int, String))

task4Tests :: TestTree
task4Tests = testGroup "Task4" [unsafePerformIO $ testSpec unitTests task4Sepc
                              , testProperty propTests task4Prop]

task4Sepc :: SpecWith ()
task4Sepc =
  describe "ListiOfNumList" $ do
    it "correct tests" $ do
      runParser parseListiOfNumList "1, 1" `shouldBe` Just ([[1:: Int]], "")
      runParser parseListiOfNumList "1, 1, 2, 1, 1" `shouldBe` Just ([[1:: Int], [1,1]], "")
      runParser parseListiOfNumList "2, 1,+10  , 3,5,-7, 2" `shouldBe` Just ([[1:: Int, 10], [5,-7,2]], "")
    it "incorrect tests" $ do
      runParser parseListiOfNumList "1, fgh1" `shouldBe` (Nothing :: Maybe ([[Int]], String))
      runParser parseListiOfNumList "2, 1 3" `shouldBe` (Nothing :: Maybe ([[Int]], String))

task4Prop :: Property
task4Prop = property $ do
  let genList = Gen.list (Range.linear 1 1000) (genInteger leftBound rightBound)
  let genListOfList = Gen.list (Range.linear 1 100) genList

  xs <- forAll genListOfList

  let listOfList = map (\t -> toInteger (length t) : t) xs
  let listOfStr = map (intercalate ", ". map show) listOfList
  let str = intercalate ", " listOfStr

  runParser parseListiOfNumList str === Just (xs, "")

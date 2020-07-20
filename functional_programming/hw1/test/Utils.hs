module Utils where

import Block3 (NonEmpty(..), ThisOrThat(..), Name(..))
import Block5 (Operation(..))

import Hedgehog
import qualified Hedgehog.Gen as Gen
import qualified Hedgehog.Range as Range

unitTests :: String
unitTests = "Unit-Test"

propTests :: String
propTests = "Property test"

leftBound :: (Num a) => a
leftBound = -1000000

rightBound ::(Num a) => a
rightBound = -1000000

genInt :: Int -> Int -> Gen Int
genInt lB rB = Gen.int (Range.linear lB rB)

genInteger :: Integer -> Integer -> Gen Integer
genInteger lB rB = Gen.integral (Range.linear lB rB)

genNonEmpty :: Gen (NonEmpty Char)
genNonEmpty = (:|) <$> Gen.unicodeAll <*> Gen.string size Gen.unicodeAll
  where size = Range.linear 0 10000

genThisOrThat :: Gen (ThisOrThat Char Char)
genThisOrThat = Gen.choice [genThis, genThat, genBoth]
  where genThis = This <$> Gen.unicodeAll
        genThat = That <$> Gen.unicodeAll
        genBoth = Both <$> Gen.unicodeAll <*> Gen.unicodeAll

genName :: Gen Name
genName = Name <$> Gen.string (Range.linear 0 10000) Gen.unicodeAll

genSpaces :: Gen String
genSpaces = Gen.string (Range.linear 1 100) (Gen.constant ' ')

genOperator :: Gen Operation
genOperator = Gen.element [Sum, Minus, Mul, Div, Pow]


module Main where

import SpecBlock1 (testBlock1)
import SpecBlock2 (testBlock2)
import SpecBlock3 (testBlock3)
import SpecBlock4 (testBlock4)
import SpecBlock5 (testBlock5)
import SpecBlock6 (testBlock6)

import Test.Tasty (TestTree, defaultMain, testGroup)

main :: IO ()
main = defaultMain allTests

allTests :: TestTree
allTests = testGroup "All Tests" [testBlock1
                                , testBlock2
                                , testBlock3
                                , testBlock4
                                , testBlock5
                                , testBlock6]

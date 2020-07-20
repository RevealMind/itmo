-----------------------------------------------------------------------------
-- |
-- Module      : Task7
-- Copyright   : (c) 2020 Dmitry Janchenkov
-- License     : MIT
--
-- Maintainer  : 99_dimas@mail.ru
-- Stability   : experimental
--
-- The Task7: a module for seventh task of homework №0.
--
-----------------------------------------------------------------------------

module Task7
  ( -- * Термы
    term1
  , term2
  , term3
  ) where

import Data.Either (lefts, rights)

-- | @ term3 = let impl = \x y -> not x || y in
--             let isMod2 = \x -> x `mod` 2 == 0 in
--             let isMod4 = \x -> x `mod` 4 == 0 in
--             \x -> (isMod4 x) `impl` (isMod2 x)@
term3 :: Integer -> Bool
term3 =
  let
    impl :: Bool -> Bool -> Bool
    impl = \x y ->
      (((||) :: Bool -> Bool -> Bool)
      ((not :: Bool -> Bool) (x :: Bool) :: Bool) :: Bool -> Bool)
      (y :: Bool) :: Bool in
    let
      isMod2 :: Integer -> Bool
      isMod2 = \x ->
        (((==) :: Integer -> Integer -> Bool)
        (((mod :: Integer -> Integer -> Integer) (x :: Integer) :: Integer -> Integer)
        (2 :: Integer) :: Integer) :: Integer -> Bool)
        (0 :: Integer) :: Bool in
      let
        isMod4 :: Integer -> Bool
        isMod4 = \x ->
          (((==) :: Integer -> Integer -> Bool)
          (((mod :: Integer -> Integer -> Integer) (x :: Integer) :: Integer -> Integer)
          (4 :: Integer) :: Integer) :: Integer -> Bool)
          (0 :: Integer) :: Bool in \x ->
            (impl :: Bool -> Bool -> Bool)
            (isMod4 (x :: Integer) :: Bool)
            (isMod2 (x :: Integer) :: Bool)

-- | @term2 = (\x -> zip (lefts x) (rights x)) [Left (1 + 2), Right (2 ^ 6)]@
term2 :: [(Integer, Integer)]
term2 = f1 ([el1, el2] :: [Either Integer Integer])
  where
    el1 :: Either Integer Integer
    el1 = left n1PlusN2

    el2 :: Either Integer Integer
    el2 = right n3PowN4

    left :: Integer -> Either Integer Integer
    left = Left

    right :: Integer -> Either Integer Integer
    right = Right

    f1 :: [Either Integer Integer] -> [(Integer, Integer)]
    f1 = \x ->
      (zip'
      (lefts' (x :: [Either Integer Integer]) :: [Integer]) :: [Integer] -> [(Integer, Integer)])
      (rights' (x :: [Either Integer Integer]) :: [Integer])   :: [(Integer, Integer)]

    zip' :: [Integer] -> [Integer] -> [(Integer, Integer)]
    zip' = zip

    lefts' :: [Either Integer Integer] -> [Integer]
    lefts' = lefts

    rights' :: [Either Integer Integer] -> [Integer]
    rights' = rights

    n1PlusN2 :: Integer
    n1PlusN2 = n1Plus n2

    n1Plus :: Integer -> Integer
    n1Plus = plus n1

    plus :: Integer -> Integer -> Integer
    plus = (+)

    n1 :: Integer
    n1 = 1

    n2 :: Integer
    n2 = 2

    n3PowN4 :: Integer
    n3PowN4 = n3Pow n4

    n3Pow :: Integer -> Integer
    n3Pow = pow n3

    pow :: Integer -> Integer -> Integer
    pow = (^)

    n3 :: Integer
    n3 = 2

    n4 :: Integer
    n4 = 6

-- | @term1 = null . head $ map (uncurry id) [((++) "Dorian ", " Grey")]@
term1 :: Bool
term1 = nullComposHeadApplyUpdList
  where
    nullComposHeadApplyUpdList :: Bool
    nullComposHeadApplyUpdList = nullComposHeadApply updList

    nullComposHeadApply :: [[Char]] -> Bool
    nullComposHeadApply = apply nullComposHead

    apply ::  ([[Char]] -> Bool) -> [[Char]] -> Bool
    apply = ($)

    nullComposHead :: [[Char]] -> Bool
    nullComposHead = nullCompos head'

    nullCompos :: ([[Char]] -> [Char]) -> [[Char]] -> Bool
    nullCompos = compos null'

    compos :: ([Char] -> Bool) -> ([[Char]] -> [Char]) -> [[Char]] -> Bool
    compos = (.)

    null' :: [Char] -> Bool
    null' = null

    head' :: [[Char]] -> [Char]
    head' = head

    updList :: [[Char]]
    updList = mapUncurryId listPairs

    mapUncurryId :: [([Char] -> [Char], [Char])] -> [[Char]]
    mapUncurryId = map' uncurryId

    map' :: (([Char] -> [Char], [Char]) -> [Char]) -> [([Char] -> [Char], [Char])] -> [[Char]]
    map' = map

    uncurryId :: ([Char] -> [Char], [Char]) -> [Char]
    uncurryId = uncurry' id'

    uncurry' :: (([Char] -> [Char]) -> [Char] -> [Char]) -> ([Char] -> [Char], [Char]) -> [Char]
    uncurry' = uncurry

    id' :: ([Char] -> [Char]) -> [Char] -> [Char]
    id' = id

    listPairs :: [([Char] -> [Char], [Char])]
    listPairs = [pair]

    pair :: ([Char] -> [Char], [Char])
    pair = halfPair str2

    str2 :: [Char]
    str2 = " Grey"

    halfPair :: [Char] -> ([Char] -> [Char], [Char])
    halfPair = constrPair f1

    constrPair :: ([Char] -> [Char]) -> [Char] -> ([Char] -> [Char], [Char])
    constrPair = (,)

    f1 :: [Char] -> [Char]
    f1 = conc str1

    conc :: [Char] -> [Char] -> [Char]
    conc = (++)

    str1 :: [Char]
    str1 = "Dorian "

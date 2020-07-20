{-# LANGUAGE BangPatterns #-}

module Task1 where

data Point = Point !Int !Int

plus :: Point -> Point -> Point
plus (Point x1 y1) (Point x2 y2) = Point (x1 + x2) (y1 + y2)

minus :: Point -> Point -> Point
minus (Point x1 y1) (Point x2 y2) = Point (x1 - x2) (y1 - y2)

scalarProduct :: Point -> Point -> Int
scalarProduct (Point x1 y1) (Point x2 y2) = x1 * x2 + y1 * y2

crossProduct :: Point -> Point -> Int
crossProduct (Point x1 y1) (Point x2 y2) = x1 * y2 - x2 * y1

distance :: Point -> Point -> Double
distance a b = sqrt . fromIntegral $! scalarProduct point point
  where point = minus b a

perimeter :: [Point] -> Double
perimeter xs@(x:_) = snd $ foldr helper (x, 0) xs
  where helper b (a, !acc) = (b, acc + distance a b)
perimeter _ = 0

doubleArea :: [Point] -> Int
doubleArea xs@(x:_) = abs . snd $ foldr helper (x, 0) xs
  where helper b (a, !acc) = (b, acc + crossProduct a b)
doubleArea _ = 0

perimeterLazy :: [Point] -> Double
perimeterLazy xs@(x:_) = snd $ foldr helper (x, 0) xs
  where helper b (a, acc) = (b, acc + distance a b)
perimeterLazy _ = 0

doubleAreaLazy :: [Point] -> Int
doubleAreaLazy xs@(x:_) = abs . snd $ foldr helper (x, 0) xs
  where helper b (a, acc) = (b, acc + crossProduct a b)
doubleAreaLazy _ = 0

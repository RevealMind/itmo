module Main where

import           Data.List       as List (intercalate)
import           Data.Map.Strict as Map (Map, alter, empty, fromList, insert,
                                         member, toList, (!))
import           Data.Maybe
import           Data.Set        as Set (Set, empty, insert, member, union)
import           Grammar         
import           Lexer           (alexScanTokens)
import           Parser          (parseExpr)

--- Решение конекста

-- Разрешимость контекста

isDecidable :: Context -> Bool
isDecidable (Context xs) = handler xs $ foldl (\acc (_, r) -> acc `Set.union` typeVars r) Set.empty xs
  where
    handler [] _                         = True
    handler ((TVar var, _) : xs) usedVar = not (Set.member var usedVar) && handler xs (Set.insert var usedVar)
    handler _ _                          = False

-- Совместность контекста

isJoint :: Context -> Bool
isJoint (Context xs) = handler xs
  where
    handler []                               = True
    handler ((TVar var, r@(Arrow _ _)) : xs) = not (Set.member var $ typeVars r) && handler xs
    handler (_ : xs)                         = handler xs

-- Алгоритм унификации

unification :: Context -> Maybe Context
unification context@(Context eq)
  | not . isJoint $ context     = Nothing
  | not . isDecidable $ context = unification newContext
  | otherwise                   = Just context
  where newContext = Context $ handler (head eq) (tail eq)

        handler (a@(Arrow _ _), v@(TVar _)) xs          = xs ++ [(v, a)]
        handler cur@(alpha@(TVar _), teta@(TVar _)) xs  = if alpha == teta then xs else substitute alpha teta xs ++ [cur]
        handler (Arrow l1 r1, Arrow l2 r2) xs           = xs ++ [(l1, l2), (r1, r2)]
        handler cur@(alpha@(TVar _), teta) xs           = substitute alpha teta xs ++ [cur]

        substitute alpha teta = map substituteHandler
          where substituteHandler (l, r) = (handler l, handler r)
                handler (Arrow l r) = Arrow (handler l) (handler r)
                handler var         = if alpha == var then teta else var

---- Основоной алгос

--- Обход

type Depth = Int
type Ind = Int
type СTPair = (Context, Type)
type ExprTypeMap = Map.Map String Type
type TypeTypeMap = Map.Map Type Type

inference :: Expression -> Ind -> ExprTypeMap -> (СTPair, Ind, ExprTypeMap, ExpressionType)
inference expr@(Var x) n m = ((emptyContext, t), n', m', newTree)
  where (t, n', m') = if Map.member x m
                        then (m ! x, n, m)
                        else (TVar ("t" ++ show n), n + 1, Map.insert x (TVar ("t" ++ show n)) m)
        newTree = V (ETPair (expr, t))

inference expr@(Lambda x p) n m = ((contextP, Arrow typeX typeP), n'', m''', newTree)
  where m''' = alter (const Nothing) x m''
        newTree = Lam (x, typeX) treeP (ETPair (expr, Arrow typeX typeP))
        typeX = m'' ! x
        ((contextP, typeP), n'', m'', treeP) = inference p n' m'
        (n', m') = (n + 1, Map.insert x (TVar ("t" ++ show n)) m)

inference expr@(Aplication p q) n m = ((newContext, newType), n''', mq, newTree)
  where newContext = (typeP, Arrow typeQ newType) `extend` (contextP `Grammar.union` contextQ)
        newTree = App treeP treeQ (ETPair (expr, newType))
        (newType, n''') = (TVar ("t" ++ show n''), n'' + 1)
        ((contextQ, typeQ), n'', mq, treeQ) = inference q n' mp
        ((contextP, typeP), n', mp, treeP)  = inference p n m

--- Вывод типа

showLine :: ETPair -> ExprTypeMap -> TypeTypeMap -> Depth -> Int -> String
showLine (ETPair (e, t)) etm ttm depth n = shiftShow ++ hypShow ++ "|- " ++ show e ++ " : " ++ show (substituteFromMap t ttm) ++ " [rule #" ++ show n ++ "]"
  where shiftShow = concat $ replicate depth "*   "

        hypShow' = intercalate ", " (map (\(e, t) -> e ++ " : " ++ show (substituteFromMap t ttm)) (toList etm))
        hypShow = if null hypShow' then hypShow' else hypShow' ++ " "

        substituteFromMap t@(TVar _) ttm
          | Map.member t ttm = ttm ! t
          | otherwise      = t
        substituteFromMap (Arrow l r) ttm = Arrow (substituteFromMap l ttm) (substituteFromMap r ttm)

showInferenceType :: ExpressionType -> ExprTypeMap -> TypeTypeMap -> Depth -> [String]
showInferenceType (V pair) etm ttm depth                   = [showLine pair etm ttm depth 1]
showInferenceType (App treeP treeQ pair) etm ttm depth     = showLine pair etm ttm depth 2 : showInferenceType treeP etm ttm (depth + 1) ++ showInferenceType treeQ etm ttm (depth + 1)
showInferenceType (Lam (x, typeX) tree pair) etm ttm depth = showLine pair etm ttm depth 3 : showInferenceType tree (Map.insert x typeX etm) ttm (depth + 1)

inferenceType :: Expression -> Maybe [String]
inferenceType expr
  | isJust solvedContext = Just (showInferenceType tree etm ttm 0)
  | otherwise = Nothing
  where ((context, t), _, etm, tree) = inference expr 1 Map.empty
        solvedContext = unification context
        (Context tt) = fromJust solvedContext
        ttm = Map.fromList tt

-- Main sextion

main :: IO ()
main = do
  input <- getContents
  case inferenceType . parseExpr . alexScanTokens $ input of
    Just proof -> putStr . unlines $ proof
    Nothing    -> putStr "Expression has no type"
 
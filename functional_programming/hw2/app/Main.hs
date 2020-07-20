{-# LANGUAGE ScopedTypeVariables #-}
module Main
  ( main
  )
where

import Changer (save)
import Control.Exception (IOException, catch)
import Control.Monad.IO.Class (liftIO)
import Control.Monad.Trans.Except (runExceptT)
import Control.Monad.Trans.Reader (runReaderT)
import Control.Monad.Trans.State (StateT, execStateT, get, put, runState)
import Control.Monad.Trans.Writer (runWriterT)
import Data.Time.Clock (UTCTime, getCurrentTime)
import Invoker (invoke)
import Options.Applicative (ParserFailure (..), ParserResult (..), defaultPrefs, execParserPure,
                            fullDesc, helper, info)
import Parser (programOptions)
import Scaner (scan)
import System.Environment (getArgs)
import System.IO (hFlush, stdout)
import Types (FSZipper, Opts (..), fsGoRoot, getDirPath)


main :: IO ()
main = do
  args <- getArgs
  case args of
    [file] -> do
      fs' <-
        scan file `catch` (\(ex :: IOException) -> print ex >> pure Nothing)
      case fs' of
        Nothing -> return ()
        Just fs -> do
          fz <- execStateT process (fs, [])
          let (fs'', _) = fsGoRoot fz
          save fs'' `catch` (\(ex :: IOException) -> print ex >> pure ())
    _ -> putStrLn "Wrong number of arguments"


parseCommand :: String -> ParserResult Opts
parseCommand =
  execParserPure defaultPrefs (info (helper <*> programOptions) fullDesc)
    . words

process :: StateT FSZipper IO ()
process = do
  fsZipper <- get
  liftIO . putStr $ (getDirPath fsZipper) ++ " > "
  liftIO $ hFlush stdout
  cmd     <- liftIO getLine
  curTime <- liftIO getCurrentTime
  case parseCommand cmd of
    Success opt -> do
      let (i, newSt) = runInvoke opt curTime fsZipper
      case i of
        (Left i') -> do
          liftIO (putStrLn i')
          process
        (Right (_, "exit")) -> pure ()
        (Right (_, res   )) -> put newSt >> liftIO (putStrLn res) >> process
    Failure (ParserFailure err) -> do
      let (h, _, _) = err ""
      liftIO $ print h
      process
    CompletionInvoked _ -> do
      liftIO
        $ putStrLn "Sorry, this programm does not support completion invoked"
      process

runInvoke
  :: Opts -> UTCTime -> FSZipper -> (Either String ((), String), FSZipper)
runInvoke cmd time = runState
  (runExceptT . runWriterT $ runReaderT (invoke . optCommand $ cmd) time)


module Invoker
  ( invoke
  )
where

import Control.Monad (foldM, when)
import Control.Monad.Trans.Class (lift)
import Control.Monad.Trans.Except (ExceptT, throwE)
import Control.Monad.Trans.Reader (ReaderT, ask)
import Control.Monad.Trans.State (State, get, modify, put)
import Control.Monad.Trans.Writer (WriterT, tell)
import Data.Time.Clock (UTCTime)
import System.Directory.Internal (Permissions (..))
import System.FilePath.Posix (splitDirectories, takeFileName, (</>))
import Types (Command (..), DirInfo (..), FSFilePath (..), FSZipper, FileInfo (..), FileName (..),
              FileSystem (..), InfoFS (..), Name, fsDelFile, fsNewFile, fsTo, fsUp, getDirPath,
              nameIs)



invoke
  :: Command
  -> ReaderT UTCTime (WriterT String (ExceptT String (State FSZipper))) ()
invoke Exit = lift $ tell "exit" >> pure ()

invoke Dir  = do
  (item, _) <- lift . lift . lift $ get
  case item of
    (Folder _ xs) -> lift . tell . unlines' . map (show . FileName) $ xs
    _             -> do
      lift . lift . lift $ toDir
      invoke Dir

invoke (Cd path) = do
  lift . lift . lift $ toDir

  fz@(item, _) <- lift . lift . lift $ get

  case item of
    (Folder _ _) -> do
      let res = foldM (flip fsTo) fz (splitDirectories path)
      case res of
        Just (File fi, _) ->
          lift . lift . throwE $ "Неверный путь. " ++ fiName fi ++ ": файл"
        Just newFZ -> lift . lift . lift $ put newFZ
        Nothing    -> lift . lift . throwE $ "Неверный путь."
    _ -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (Ls path) = do
  lift . lift . lift $ toDir

  fz@(item, _) <- lift . lift . lift $ get
  case item of
    (Folder _ _) -> do
      let res = foldM (flip fsTo) fz (splitDirectories path)
      case res of
        Just (File fi, _) ->
          lift . lift . throwE $ "Неверный путь. " ++ fiName fi ++ ": файл"
        Just (Folder _ xs, _) ->
          lift . tell . unlines . map (show . FileName) $ xs
        Nothing -> lift . lift . throwE $ "Неверный путь."
    _ -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (Cat path) = do
  lift . lift . lift $ toDir

  fz@(item, _) <- lift . lift . lift $ get
  case item of
    (Folder _ _) -> do
      let res = foldM (flip fsTo) fz (splitDirectories path)
      case res of
        Just (File fi, _) -> lift . tell $ fiContent fi
        Just (Folder di _, _) ->
          lift . lift . throwE $ "Неверный путь. " ++ diName di ++ ": папка"
        Nothing -> lift . lift . throwE $ "Неверный путь."
    _ -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (Information path) = do
  lift . lift . lift $ toDir
  fz@(item, _) <- lift . lift . lift $ get
  case item of
    (Folder _ _) -> do
      let res = foldM (flip fsTo) fz (splitDirectories path)
      case res of
        Just (f, _) -> lift . tell $ show $ InfoFS f
        Nothing     -> lift . lift . throwE $ "Неверный путь."
    _ -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (WriteFile path content) = do
  lift . lift . lift $ toDir
  fz@(item, _) <- lift . lift . lift $ get
  case item of
    (Folder _ _) -> case fsTo (takeFileName path) fz of
      Just (File fi, bs) ->
        lift . lift . lift $ put (File fi { fiContent = unwords content }, bs)
      Just (Folder di _, _) ->
        lift . lift . throwE $ "Неверный путь. " ++ diName di ++ ": папка"
      Nothing ->
        lift . lift . throwE $ "В текущей директории нет такого файла."
    _ -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (CreateFile name) = do
  when
    ('/' `elem` name)
    ( lift
    . lift
    . throwE
    $ "Некоректное имя файла. Файл не должен содержать '/'"
    )
  lift . lift . lift $ toDir
  curTime <- ask
  fz      <- lift . lift . lift $ get
  let newFile = File FileInfo
        { fiName        = name
        , fiPath        = getDirPath fz </> name
        , fiContent     = ""
        , fiPermissions = Permissions True True False False
        , fiSize        = 0
        , fiModTime     = curTime
        }
  case fsTo name fz of
    Just _  -> lift . lift . throwE $ "Файл с данным именем уже существует"
    Nothing -> case fsNewFile newFile fz of
      Just fz' -> lift . lift . lift $ put fz'
      Nothing  -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (CreateDir name) = do
  when
    ('/' `elem` name)
    ( lift
    . lift
    . throwE
    $ "Некоректное имя файла. Файл не должен содержать '/'"
    )
  lift . lift . lift $ toDir
  fz <- lift . lift . lift $ get
  let dirInfo = DirInfo { diName        = name
                        , diPath        = getDirPath fz </> name
                        , diPermissions = Permissions True True False True
                        }
  case fsTo name fz of
    Just _  -> lift . lift . throwE $ "Файл с данным именем уже существует"
    Nothing -> case fsNewFile (Folder dirInfo []) fz of
      Just fz' -> lift . lift . lift $ put fz'
      Nothing  -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

invoke (Delete name) = do
  when
    ('/' `elem` name)
    ( lift
    . lift
    . throwE
    $ "Некоректное имя файла. Файл не должен содержать '/'"
    )
  lift . lift . lift $ toDir
  fz <- lift . lift . lift $ get

  case fsDelFile name fz of
    Just fz' -> lift . lift . lift $ put fz'
    Nothing ->
      lift
        . lift
        . throwE
        $ "В текущей директории не существует файла с таким именем"

invoke (FindFile name) = do
  when
    ('/' `elem` name)
    ( lift
    . lift
    . throwE
    $ "Некоректное имя файла. Файл не должен содержать '/'"
    )
  lift . lift . lift $ toDir
  (item, _) <- lift . lift . lift $ get
  case item of
    (Folder _ xs) -> do
      let files = walker name xs
      lift $ tell (unlines' (map (show . FSFilePath) files))
    _ -> lift . lift . throwE $ "Произошла непредвиденная ошибка"

toDir :: State FSZipper ()
toDir = do
  (item, _) <- get
  case item of
    (File _) -> modify fsUp
    _        -> pure ()

walker :: Name -> [FileSystem] -> [FileSystem]
walker _    []                = []
walker name (f@(File _) : []) = if nameIs name f then [f] else []
walker name (f@(File _) : bs) =
  (if nameIs name f then [f] else []) ++ walker name bs
walker name (f@(Folder _ xs) : []) =
  (if nameIs name f then [f] else []) ++ walker name xs
walker name (f@(Folder _ xs) : bs) =
  (if nameIs name f then [f] else []) ++ walker name (bs ++ xs)

unlines' :: [String] -> String
unlines' []       = []
unlines' [x     ] = x
unlines' (l : ls) = l ++ '\n' : unlines' ls

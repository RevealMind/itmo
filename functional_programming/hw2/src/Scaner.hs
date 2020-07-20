module Scaner(scan) where

import Data.Maybe (catMaybes)
import System.Directory (doesDirectoryExist, doesFileExist, getFileSize, getModificationTime,
                         getPermissions, listDirectory, makeAbsolute)
import System.FilePath.Posix (takeBaseName, takeFileName, (</>))
import System.IO (hPutStrLn, stderr)
import System.IO.Strict (readFile)
import Types (DirInfo (..), FileInfo (..), FileSystem (..))

scan :: FilePath -> IO (Maybe FileSystem)
scan path = do
  permissions <- getPermissions path
  absPath <- makeAbsolute path
  dir <- doesDirectoryExist path
  file <- doesFileExist path
  if dir
  then do
    files <- listDirectory path
    filedInCurrentDir <- mapM (scan . (path </>)) files
    let fileList = catMaybes filedInCurrentDir
    let di = DirInfo {
        diName = takeBaseName path,
        diPath = absPath,
        diPermissions = permissions
      }
    pure . pure $ Folder di fileList
  else if file
  then do
    size <- getFileSize path
    content <- System.IO.Strict.readFile path
    modTime <- getModificationTime path
    let fi = FileInfo {
      fiName = takeFileName path,
      fiPath = absPath, fiContent = content,
      fiPermissions = permissions,
      fiSize = size,
      fiModTime = modTime
    }
    pure . pure $ File fi
  else
    hPutStrLn stderr ("Пропущен файл: " ++ absPath) >> pure Nothing

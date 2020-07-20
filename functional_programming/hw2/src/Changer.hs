module Changer
  ( save
  )
where

import Control.Monad (when)
import Data.List ((\\))
import System.Directory (createDirectoryIfMissing, doesDirectoryExist, doesFileExist, listDirectory,
                         removeDirectory, removeFile, removePathForcibly)
import System.FilePath.Posix (normalise, (</>))
import Types (DirInfo (..), FileInfo (..), FileName (..), FileSystem (..))


save :: FileSystem -> IO ()
save (File fi) = do
  dirExist <- doesDirectoryExist $ fiPath fi
  when dirExist (removeDirectory $ fiPath fi)
  writeFile (fiPath fi) (fiContent fi)
save (Folder di xs) = do
  dirExist  <- doesDirectoryExist $ diPath di
  fileExist <- doesFileExist $ diPath di
  when fileExist (removeFile $ diPath di)

  if dirExist
    then do
      listDir <- listDirectory $ diPath di
      let remList = listDir \\ map (show . FileName) xs
      mapM_ (removePathForcibly . (normalise . (</>) (diPath di))) remList
    else createDirectoryIfMissing True $ diPath di

  mapM_ save xs


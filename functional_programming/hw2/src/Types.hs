module Types where

import Data.List (break)
import Data.Time.Clock (UTCTime)
import System.Directory.Internal (Permissions (..))
import System.FilePath.Posix (takeExtension)

type Name = String

data FileInfo = FileInfo
  { fiName        :: Name
  , fiPath        :: FilePath
  , fiContent     :: !String
  , fiSize        :: Integer
  , fiPermissions :: Permissions
  , fiModTime     :: UTCTime
  } deriving Show

data DirInfo = DirInfo
  { diName        :: Name
  , diPath        :: FilePath
  , diPermissions :: Permissions
  } deriving Show


data FileSystem
  = File FileInfo
  | Folder DirInfo [FileSystem]
  deriving (Show)

newtype FileName = FileName FileSystem

instance Show FileName where
  show (FileName (File fi))     = fiName fi
  show (FileName (Folder di _)) = diName di

newtype FSFilePath = FSFilePath FileSystem

instance Show FSFilePath where
  show (FSFilePath (File fi))     = fiPath fi
  show (FSFilePath (Folder di _)) = diPath di

newtype InfoFS = InfoFS FileSystem

instance Show InfoFS where
  show (InfoFS (File fi)) = unlines
    [
    "Путь: " ++ show (fiPath fi),
    "Права доступа: _" ++ show (PermissionsInfo $ fiPermissions fi),
    "Тип: файл (" ++ takeExtension (fiPath fi) ++ ")",
    "Время изменения: " ++ show (fiModTime fi),
    "Размер: " ++ show (fiSize fi)
    ]
  show (InfoFS (Folder di _)) = unlines
    [
    "Путь: " ++ show (diPath di),
    "Права доступа: d" ++ show (PermissionsInfo $ diPermissions di),
    "Тип: папка"
    ]

newtype PermissionsInfo = PermissionsInfo Permissions

instance Show PermissionsInfo where
  show (PermissionsInfo (Permissions r w _ x)) = concat [
    if r then "r" else "_",
    if w then "w" else "_",
    if x then "x" else "_"
    ]

isFile :: FileSystem -> Bool
isFile (File _) = True
isFile _        = False

isDir :: FileSystem -> Bool
isDir = not . isFile

data FSCrumb = FSCrumb DirInfo [FileSystem] [FileSystem] deriving (Show)

type FSZipper  = (FileSystem, [FSCrumb])


fsGoRoot :: FSZipper -> FSZipper
fsGoRoot cur@(_, []) = cur
fsGoRoot fz          = fsUp fz

fsUp :: FSZipper -> FSZipper
fsUp cur@(_, [])                        = cur
fsUp (item, FSCrumb dirInfo ls rs : bs) = (Folder dirInfo (ls ++ [item] ++ rs), bs)

fsTo :: Name -> FSZipper -> Maybe FSZipper
fsTo name fz@(Folder folderInfo items, bs)
 | name == ".." = Just $ fsUp fz
 | name == "."  = Just fz
 | otherwise    = case break (nameIs name) items of
     (_ , []     ) -> Nothing
     (ls, item:rs) -> Just (item, FSCrumb folderInfo ls rs:bs)

fsTo _ _ = Nothing

nameIs :: Name -> FileSystem -> Bool
nameIs name (Folder DirInfo  { diName = folderName } _) = name == folderName
nameIs name (File   FileInfo { fiName = fileName })     = name == fileName

fsNewFile :: FileSystem -> FSZipper -> Maybe FSZipper
fsNewFile item (Folder di items, bs) = Just (Folder di (item:items), bs)
fsNewFile _ _                        = Nothing

fsDelFile :: Name -> FSZipper -> Maybe FSZipper
fsDelFile name (Folder di items, bs) = case break (nameIs name) items of
     (_ , []  ) -> Nothing
     (ls, _:rs) -> Just (Folder di (ls ++ rs), bs)

fsDelFile _ _ = Nothing

getDirPath :: FSZipper -> FilePath
getDirPath (Folder di _, _)      = diPath di
getDirPath (_, FSCrumb di _ _:_) = diPath di
getDirPath (_, _)                = error "Imposible state"

newtype Opts = Opts { optCommand :: Command } deriving (Show)

data Command
    = Cd String
    | Dir
    | Ls String
    | CreateDir String
    | Cat String
    | CreateFile String
    | Delete String
    | WriteFile String [String]
    | FindFile String
    | Information String
    | Exit
    deriving (Show)

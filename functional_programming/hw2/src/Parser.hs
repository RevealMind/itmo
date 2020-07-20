module Parser(programOptions) where

import Options.Applicative (CommandFields, Mod, Parser, command, help, hsubparser, info, metavar,
                            progDesc, strArgument)

import Control.Applicative (many)
import Data.Semigroup ((<>))
import Types (Command (..), Opts (..))


programOptions :: Parser Opts
programOptions =
        Opts <$>
        hsubparser ( cdCommand
                  <> dirCommand
                  <> lsCommand
                  <> createDirCommand
                  <> catCommand
                  <> createFileCommand
                  <> deleteCommand
                  <> writeFileCommand
                  <> findFileCommand
                  <> informationCommand
                  <> exitCommand)


cdCommand :: Mod CommandFields Command
cdCommand = command "cd" (info cdOptions (progDesc "Переходит в директорию"))

cdOptions :: Parser Command
cdOptions = Cd <$> strArgument (metavar "FOLDER" <> help "Имя папки, в которую надо перейти")


dirCommand :: Mod CommandFields Command
dirCommand = command "dir" (info (pure Dir) (progDesc "Показывает содержимое текущей директории"))


exitCommand :: Mod CommandFields Command
exitCommand = command "exit" (info (pure Exit) (progDesc "Выходит из интерактивной консоли"))


lsCommand :: Mod CommandFields Command
lsCommand = command "ls" (info lsOptions (progDesc "Показывает содержимое переданной директории"))

lsOptions :: Parser Command
lsOptions = Ls <$> strArgument (metavar "FOLDER" <> help "Имя папки, которую надо отобразить")


createDirCommand :: Mod CommandFields Command
createDirCommand = command "create-folder" (info createDirOptions (progDesc "Создает папку в текущей директории"))

createDirOptions :: Parser Command
createDirOptions = CreateDir <$> strArgument (metavar "FOLDERNAME" <> help "Имя папки, в которую надо создать")


catCommand :: Mod CommandFields Command
catCommand = command "cat" (info catOptions (progDesc "Показывает содержимое файла"))

catOptions :: Parser Command
catOptions = Cat <$> strArgument (metavar "FILE" <> help "Имя файла, который необходимо отобразить")


createFileCommand :: Mod CommandFields Command
createFileCommand = command "create-file" (info createFileOptions (progDesc "Создает файл"))

createFileOptions :: Parser Command
createFileOptions = CreateFile <$> strArgument (metavar "FILENAME" <> help "Имя файла, который необходимо создать")


deleteCommand :: Mod CommandFields Command
deleteCommand = command "remove" (info deleteOptions (progDesc "Удаляет файл/директорию"))

deleteOptions :: Parser Command
deleteOptions = Delete <$> strArgument (metavar "NAME" <> help "Имя файла/директории, который(ую) надо удлаить")


writeFileCommand :: Mod CommandFields Command
writeFileCommand = command "write-file" (info writeFileOptions (progDesc "Записывает текст в файл"))

writeFileOptions :: Parser Command
writeFileOptions = WriteFile
                   <$> strArgument (metavar "FILENAME" <> help "Имя файла, в который надо записать")
                   <*> many (strArgument (metavar "TEXT" <> help "Текс, который надо записать в файл"))


findFileCommand :: Mod CommandFields Command
findFileCommand = command "find-file" (info findFileOptions (progDesc "Поиск файла в текущией директории и поддиректориях"))

findFileOptions :: Parser Command
findFileOptions = FindFile <$> strArgument (metavar "FILENAME" <> help "Имя файла/директории, который(ую) надо удлаить")


informationCommand :: Mod CommandFields Command
informationCommand = command "information" (info informationOptions (progDesc "Показывает информацию о файле/директории"))

informationOptions :: Parser Command
informationOptions = Information <$> strArgument (metavar "NAME" <> help "Имя файла/директории, информацию которого(ой) надо отобразить")

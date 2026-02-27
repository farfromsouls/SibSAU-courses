module Main where
import System.Environment (getArgs)
import System.IO (readFile)

main :: IO ()
main = do
    args <- getArgs
    case args of
        [fileName] -> do
            content <- readFile fileName
            putStr content
        _ -> putStrLn "Использование: cat <имя_файла>"
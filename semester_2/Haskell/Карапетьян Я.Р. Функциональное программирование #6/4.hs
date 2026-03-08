module Main where
import System.Environment (getArgs)

main :: IO ()
main = do
    args <- getArgs
    case args of
        [nStr, fileName] -> do
            let n = read nStr :: Int
            content <- readFile fileName
            let linesList = lines content
                firstNLines = take n linesList
            putStrLn $ unlines firstNLines
        _ -> putStrLn "Использование: head n имя_файла"
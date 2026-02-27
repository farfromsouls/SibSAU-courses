module Main where

main :: IO ()
main = do
    putStr "Введите первое число: "
    num1Str <- getLine
    putStr "Введите второе число: "
    num2Str <- getLine
    
    let num1 = read num1Str :: Double
        num2 = read num2Str :: Double
        sum = num1 + num2
    
    putStrLn $ "Сумма: " ++ show sum
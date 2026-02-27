import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))
import Data.Fixed (mod')

side :: Floating a => a -> a -> a
side h l = sqrt (h^2 + (l / 2)^2)

angles :: Floating a => a -> a -> (a, a)
angles h l = (alpha, beta)
  where
    alpha = atan (2 * h / l) * (180 / pi) 
    beta  = 180 - 2 * alpha   

main :: IO ()
main = do
    hSetBuffering stdout NoBuffering
    
    putStr "Введите высоту треугольника (h): "
    hStr <- getLine
    putStr "Введите длину основания (l): "
    lStr <- getLine
    
    let h = read hStr :: Double
        l = read lStr :: Double
        
        lengthOfSide = side h l
        (alpha, beta) = angles h l
    
    putStrLn $ "\nРезультаты вычислений:"
    putStrLn $ "Длина боковой стороны: " ++ show lengthOfSide ++ " метров"
    putStrLn $ "Угол при основании: " ++ show alpha ++ " градусов"
    putStrLn $ "Угол при вершине: " ++ show beta ++ " градусов"
    
    -- Проверка корректности
    putStrLn $ "\nПроверка (сумма углов): " ++ show (2*alpha + beta) ++ " градусов"
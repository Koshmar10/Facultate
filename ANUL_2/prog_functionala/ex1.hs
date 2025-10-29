import Data.List
myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x = x+x

maxim :: Integer -> Integer -> Integer
maxim x y = 
    if (x > y) 
        then x 
        else y

max3 x y z = 
    let
        u = maxim x y
    in 
        (maxim  u z)

maxim4 x y z w =
    let 
        u = maxim x y
        v = maxim z w 
    in 
        maxim u v
test_maxim4 x y z w =
    let
        max = maxim4 x y z w
    in
        max >= x && max >= y && max >= z && max>=w
    
maxim3 x y z  = 
    if (x > y)
        then if(x > z)
            then x
            else z
        else if(y > z)
            then y
            else z

eeny :: Integer -> String
eeny a = 
    if (even a)
        then "eeny"
        else "meeny"



fizzbuzz :: Integer -> String
fizzbuzz = undefined

fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)
    
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)
    
tribonacci :: Integer -> Integer
tribonacci 1 =1
tribonacci 2 =1
tribonacci 3 =2
tribonacci n = 
    tribonacci (n-1) - tribonacci ( n-2 ) + tribonacci(n-3)

tribonacci n 
    | n  == 1 = 1
    | n == 2 = 1
    | n == 3 = 2
    | otherwise = tribonacci (n-1) - tribonacci (n-2) + tribonacci(n-3)

binomial :: Integer -> Integer -> Integer
binomial n k 
    | k == 0 = 1
    | n == 0 = 0
    | otherwise = binomial(n-1, k) + binomial(n-1, k-1)

square_sum :: Integer ->Integer -> Integer
square_sum a b = a*a + b*b

odd_or_even :: Integer -> [Char]
odd_or_even a = 
    if (a `mod` 2 == 0)
        then "par"
        else "impar"
fact :: Integer -> Integer
fact 0 = 1
fact a = a * fact (a-1)

btd :: Integer -> Integer -> Bool
btd a b = 
    if (a > 2*b)
        then True
        else False
max_lista :: [Integer] -> Integer
max_lista x = maximum x

poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a*x*x + b*x + c

fizzbuzz :: Integer -> String
fizzbuzz x = 
    if ( mod x 3 &&  x `mod` 5 )
        then "FizzBuzz"
        else 
            if (x `mod` 3)
                then "Fizz"
                else 
                    if (x `mod` 5)
                        then "Buzz"

fizzbuzz :: Integer -> String
fizzbuzz x
    | x `mod` 15 == 0 = "FizzBuzz" 
    | x `mod` 3  == 0 = "Fizz"     
    | x `mod` 5  == 0 = "Buzz"     
    | otherwise       = show x     

    

    
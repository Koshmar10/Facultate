import Data.List
import Data.Char
verifL :: [Int] -> Bool
verifL  x =  
    if (even (length x))
        then True
        else False


takefinal :: [Int] -> Int -> [Int]

takefinal xs n = reverse (take n (reverse xs))

remove :: [Int] -> Int -> [Int]
remove [] _ = []
remove (h:t) n
    | n == 0    = t
    | otherwise = h : remove t (n-1)



-- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)   
    | even h    = h `div` 2 : t'
    | otherwise = t'
    where t' = semiPareRec t

myreplicate :: Int -> Int -> [Int]
myreplicate _ 0 = []
myreplicate v n = v : myreplicate v (n-1)

sumImp :: [Int] -> Int
sumImp [] = 0
sumImp (h:t) 
    | even h  = 0 + sumImp t
    | otherwise = h + sumImp t

totalLen :: [String] -> Int
totalLen [] = 0
totalLen (h : t)
    | head h == 'A' = length h + totalLen t
    | otherwise = 0 + totalLen t

countv :: String -> Int
countv [] = 0
countv (h:t)
    | h  `elem` "aeiou" = 1 + countv t
    | otherwise = 0 + countv t


nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale (h : t)
    | h == reverse h = countv h + nrVocale t
    | otherwise = 0 + nrVocale t 
-- nrVocale ["sos", "civic", "palton", "desen", "aerisirea"] == 9

-- f 3 [1,2,3,4,5,6] = [1,2,3,3,4,3,5,6,3]
f :: Int -> [Int] -> [Int]
f _ [] = []
f n (h: t)
    | even h = h : n : f n t
    | otherwise = h :f n t

semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]

-- divizori 4 == [1,2,4]
divi :: Int -> [Int]
divi n = [x | x <- [2..n `div` 2], n `mod` x == 0]


listadiv :: [Int] -> [[Int]]
listadiv [] = []
listadiv (h:t) = divi h : listadiv t
-- listadiv [1,4,6,8] == [[1],[1,2,4],[1,2,3,6],[1,2,4,8]]

-- inInterval 5 10 [1..15] == [5,6,7,8,9,10]
-- inInterval 5 10 [1,3,5,2,8,-1] == [5,8]
inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec _ _ [] =[]
inIntervalRec a b (h:t)
    | h >=a && h<=b = h : inIntervalRec a b t
    | otherwise = inIntervalRec a b t 

inIntervalComp a b l = [x | x <- l, x <= b && x >= a]
-- pozitive [0,1,-3,-2,8,-1,6] == 3
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t)
    | h > 0 = 1+ pozitiveRec t
    | otherwise = 0+ pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp l =  length [x | x <- l, x > 0]
-- pozitiiImpare [0,1,-3,-2,8,-1,6,1] == [1,2,5,7]
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = pozAux l 0

pozAux :: [Int] -> Int -> [Int]
pozAux [] _ = []
pozAux (h:t) i
    | odd h     = i : pozAux t (i+1)
    | otherwise = pozAux t (i+1)

pozitiiImpareComp l = [i | (x, i) <- zip l [0..], even x == False]
-- multDigits "The time is 4:25" == 40
-- multDigits "No digits here!" == 1
multDigitsRec [] =0
multDigitsRec (h:t)
    | isDigit h = digitToInt h + multDigitsRec t
    | otherwise = multDigitsRec t
multDigitsComp  l= sum [digitToInt x | x<-l, isDigit x]
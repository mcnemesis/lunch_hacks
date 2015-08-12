#!/usr/bin/env runhaskell
-- FILE: gematria.hs
-- Purpose: given a user provided string as a commandline parameter or prompted value, will output its reduced numericl value
-- How: each letter of the alphabet is assigned a numeric value with A=1,B=2,...Z=26 and all other letters assigned 0
-- How: then, given a string, each letter is mapped to its numeric value, and these are then summed up, and this final figure
-- How: output modulo 9
import Data.List
ai x = elemIndex x ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
main = do putStrLn "What: "
          x <- getLine
          putStrLn (map (read $ show) (map ai x))

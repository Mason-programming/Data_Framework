#!/bin/bash 

# Test if the enviroment varibles are there
echo "Checking usdview" 
if command -v usdview &> /dev/null; then 
    echo "usdview avaible" 
else
    echo "path to usdview has not been found" 

fi 

if command -v usdcat &> /dev/null; then 
    echo "usdcat path is found" 
else 
    echo "Path to usdcaat cot found" 

fi 


if command -v doblender &> /dev/null; then 
    echo "The path to doblender has been found" 
else 
    echo "Path to doblender was not found"
fi 

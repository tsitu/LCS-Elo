# LCS Elo

This program calculates and sorts the ELO rankings of League of Legends LCS teams against each other. Data is separated by region, split, and year. Base ELO is set at 1200, and k-factor is set at 32.

How to compile:
`g++ -g -Wall -o main main.cpp`

Usage:
`./main data/<data.txt> tests/<output.txt>`

## To-do list
* USCF staggered k-factors: ELO < 2100 = 32, 2100 < ELO < 2400 = 24, ELO > 2400 = 16
* FIDE range: Total games < 30 && ELO < 2300 = 40, ELO < 2400 = 20, Total games > 30 && ELO > 2400 = 10
* Add a counter for the number of total games a team has played
* Copy data over to Chart.js

*Disclaimer: Information is accurate as of March 5th, 2015*
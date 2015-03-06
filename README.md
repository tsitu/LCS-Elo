# LCS Elo

This program calculates and sorts the ELO rankings of League of Legends LCS teams with respect to each other. Data is separated by year, region, and split. Base ELO is set at 1200, and k-factor is set at 32. For more information about the ELO rating system visit [Wikipedia](http://en.wikipedia.org/wiki/Elo_rating_system#Mathematical_details)

How to compile:
`g++ -g -Wall -o main main.cpp`

Usage:
`./main data/<data.txt> tests/<output.txt>`

## To-do list
* USCF staggered k-factors: ELO < 2100 = 32, 2100 < ELO < 2400 = 24, ELO > 2400 = 16
* FIDE range: Total games < 30 && ELO < 2300 = 40, ELO < 2400 = 20, Total games > 30 && ELO > 2400 = 10
* Copy data over to Chart.js

*Disclaimer: Information is accurate as of March 6th, 2015*
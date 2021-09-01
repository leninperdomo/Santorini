# Santorini
Implementation of the Santorini game written in C.

Video Demonstration URL: https://youtu.be/zMOTJMYtzV4

Santorini is a 2-4 player game in which the players take turns moving one of their builders into an octagonal neighbor space, then construct a building level adjacent to the builder. The building levels are from 2 to 4 and the objective of the game is to become the first player who moves a builder into a level 3 building to win the game.

In Santorini, a 6 x 6 integer array is used to represent the game board. The array is passed to various methods such as
printGameboard, which prints the elements in the array, and changeAdjacentValues, which alters the number values stored in the rows adjacent
to a given builder. A scanf call is utilized in main to take in user input for the player's builder. The isValidMove method serves the purpose
of checking whether the user input is a valid move and is in the format "row collumn". Amongst the functions made for the game there are 
printGameboard, isValidMove, changeAdjacentValues, abs, getBestMove, AIMove, getPotentialPoints, and gameOver. Nested for loops were used repeatedly 
to traverse the gameboard. For instance, iteration is utlized to print the gameboard values in printGameboard. After each turn,
the gameOver method checks whether the conditions for the game to end have been met. If the conditions are met, the game immediately ends and
a printf statement announces the winner accordingly. The AI checks what move has the potential to reduce the largest number of total
values from the gameboard array and moves accordingly. This ensures that the AI always moves its builder to the most beneficial position.
At each stage of the game, the game state is displayed showing both the player's and the AI's gameboard.

Enjoy the game!

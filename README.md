# Santorini
Implementation of the Santorini game written in C.

Video Demonstration URL: https://youtu.be/zMOTJMYtzV4

My Santorini implementation utilizes a 6 x 6 integer array to represent the game board. The array is passed to various methods such as
printGameboard, which prints the elements in the array, and changeAdjacentValues, which alters the number values stored in the rows adjacent
to a given builder. I use a scanf call in main to take in user input for the player's builder. I also use the isValidMove method to check whether
the user input is a valid move and is in the format "row collumn". I created a variety of different functions for my game implementation. These 
functions include printGameboard, isValidMove, changeAdjacentValues, abs, getBestMove, AIMove, getPotentialPoints, and gameOver. I repeatedly use 
nested for loops to traverse the gameboard. For instance, I applied iteration to print the gameboard values in printGameboard. After each turn, I use
the gameOver method to check whether the conditions for the game to end have been met. If the conditions are met, the game immediately ends and
a printf statement announces the winner accordingly. The AI checks what move has the potential to reduce the largest number of total
values from the gameboard array and moves accordingly. This ensures that the AI always moves its builder to the most beneficial position.
There are no global variables of any kind in my code. At each stage of the game, the state of the game is printed clearly showing the player's
gameboard and the AI's gameboard. All the relevant information to the state of the game is properly aligned and seprated by newlines to improve
readability.

Enjoy the game!

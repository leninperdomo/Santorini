#include <stdio.h>

/*
Helper method for isValidMove, returns absolute value of parameter n
*/
int abs(int n) {
	if (n < 0) {
		n *= -1;
	}
	return n;
}

/*
Checks whether the player's move is valid.
Returns 1 if valid, 0 if invalid.
*/
int isValidMove(int prevRow, int prevCol, int nRow, int nCol, int eRow, int eCol) {
	int isValidMove = 1;

	//Distance between builder's previous and current row and collumn
	int rowDistance = abs(nRow - prevRow);
	int colDistance = abs(nCol - prevCol);

	//Check if move is within matrix value range
	if ((nRow > 6) || (nCol > 6) || (nRow < 1) || (nCol < 1)) {
		isValidMove = 0;
		printf("\nWARNING: Invalid Move\nRow and/or collumn out of bounds.\n\n");
	}

	//Check if another builder occupies the move position
	if ((nRow == eRow) && (nCol == eCol)) {
		isValidMove = 0;
		printf("\nWARNING: Invalid Move\nSpot occupied by another builder.\n\n");
	}

	//Check if the current position is the same as the previous one
	if ((nRow == prevRow) && (nCol == prevCol)) {
		isValidMove = 0;
		printf("\nWARNING: Invalid Move\nMust move builder to a different position.\n\n");
	}

	//Check whether new builder position is adjacent to previous one
	if (((rowDistance > 1) || (colDistance > 1)) && ((prevRow != 0) && prevCol != 0)) {
		isValidMove = 0;
		printf("\nWARNING: Invalid Move\nMust move builder to an adjacent position.\n\n");
	}

	return isValidMove;
}

/*
Returns 1 if game is over, 0 otherwise.
*/
int gameOver(int array[6][6]) {
	int gameOver = 0;
	int fourCount = 0;
	int zeroCount = 0;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (array[i][j] == 4) {
				fourCount++;
			}
			if (array[i][j] == 0) {
				zeroCount++;
			}
		}
	}

	//Player wins if number of array values of four exceeds ten
	//AI wins if number of array values of zero exceeds ten
	if (fourCount >= 10) {
		gameOver = 1;
		printf("\nPlayer Wins!\n");
	} else if (zeroCount >= 10) {
		gameOver = 1;
		printf("\nThe machines have risen... (AI Wins)\n");
	}

	return gameOver;
}

/*
Changes all values in the rows adjacent to the given builder (nRow and nCol).
Stops changing values if it reaches an enemy builder (eRow and eCol).
If turnCount is even (player turn), increase gameboard values.
If turnCount is odd (AI turn), decrease gameboard values.
*/
void changeAdjacentValues(int arr[6][6], int turnCount, int nRow, int nCol, int eRow, int eCol) {

	//Changes all collumns to the right
	for (int i = nCol; i < 6; i++) {
		if ((i == eCol - 1) && (nRow == eRow)) {
                	break;
		}
		if ((turnCount % 2 != 0) && (arr[nRow - 1][i] < 4)) {
			arr[nRow - 1][i] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[nRow - 1][i] > 0)) {
                        arr[nRow - 1][i] -= 1;
		}
	}

	//Changes all collumns to the left
	for (int i = nCol - 2; i >= 0; i--) {
		if ((i == eCol - 1) && (nRow == eRow)) {
			break;
		}
		if ((turnCount % 2 != 0) && (arr[nRow - 1][i] < 4)) {
			arr[nRow - 1][i] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[nRow - 1][i] > 0)) {
                        arr[nRow - 1][i] -= 1;
		}
	}

	//Changes all rows down
	for (int i = nRow; i < 6; i++) {
		if ((i == eRow - 1) && (nCol == eCol)) {
			break;
		}
		if ((turnCount % 2 != 0) && (arr[i][nCol - 1] < 4)) {
			arr[i][nCol - 1] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[i][nCol - 1] > 0)) {
                        arr[i][nCol - 1] -= 1;
		}
	}

	//Changes all rows up
	for (int i = 0; i < nRow - 1; i++) {
		if ((i == eRow - 1) && (nCol == eCol)) {
			break;
		}
		if ((turnCount % 2 != 0) && (arr[i][nCol - 1] < 4)) {
			arr[i][nCol - 1] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[i][nCol - 1] > 0)) {
                        arr[i][nCol - 1] -= 1;
		}
	}

	//Changes all diagonal octagons right and down
	for (int i = nRow, j = nCol; i < 6 && j < 6; i++, j++) {
		if ((i == eRow - 1) && (j == eCol - 1)) {
			break;
		}
		if ((turnCount % 2 != 0) && (arr[i][j] < 4)) {
			arr[i][j] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[i][j] > 0)) {
                        arr[i][j] -= 1;
		}
	}

	//Changes all diagonal octagons left and up
	for (int i = nRow - 2, j = nCol - 2; i >= 0 && j >= 0; i--, j--) {
		if ((i == eRow - 1) && (j == eCol - 1)) {
                        break;
		}
                if ((turnCount % 2 != 0) && (arr[i][j] < 4)) {
                        arr[i][j] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[i][j] > 0)) {
                        arr[i][j] -= 1;
		}
	}

	//Changes all diagonal octagons right and up
	for (int i = nRow, j = nCol - 2; i < 6 && j >= 0; i++, j--) {
		if ((i == eRow - 1) && (j == eCol - 1)) {
                        break;
		}
                if ((turnCount % 2 != 0) && (arr[i][j] < 4)) {
                        arr[i][j] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[i][j] > 0)) {
                        arr[i][j] -= 1;
		}
	}


	//Change all diagonal octagons left and down
	for (int i = nRow - 2, j = nCol; i >= 0 && j < 6; i--, j++) {
		if ((i == eRow - 1) && (j == eCol - 1)) {
                        break;
                }
		if ((turnCount % 2 != 0) && (arr[i][j] < 4)) {
                        arr[i][j] += 1;
		}
		if ((turnCount % 2 == 0) && (arr[i][j] > 0)) {
                        arr[i][j] -= 1;
		}
	}
}

/*
Helper method for getBestMove.
Returns the amount of points each potential move could yield for the AI builder.
*/
int calculatePotentialPoints(int array[6][6], int nRow, int nCol, int eRow, int eCol) {
	int pointTotal = 0;

	int arrayCopy[6][6];
        for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                        arrayCopy[i][j] = array[i][j];
                }
        }

	changeAdjacentValues(arrayCopy, 2, nRow, nCol, eRow, eCol);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			pointTotal += arrayCopy[i][j];
		}
	}

	return pointTotal;
}

/*
Helper method for AImove.
Uses calculatePotentialPoints to find the AI move that would reduce the most points.
bestMove[0] = row of best move.
bestMove[1] = column of best move.
*/
void getBestMove(int array[6][6], int bestMove[2], int pRow, int pCol, int aRow, int aCol) {
	int mostPointsReduced = 1000;

	//Potential Move 1: 1 up and 1 left
	if ((aRow > 0) && (aCol > 0)) {
		int potentialPoints;
		potentialPoints = calculatePotentialPoints(array, aRow - 1, aCol - 1, pRow, pCol);
		if ((potentialPoints < mostPointsReduced) && ((aRow - 1 != pRow) && (aCol - 1 != pCol))) {
			bestMove[0] = aRow - 2;
			bestMove[1] = aCol - 2;
			mostPointsReduced = potentialPoints;
		}
	}

	//Potential Move 2: 1 up
        if (aRow > 0) {
                int potentialPoints;
                potentialPoints = calculatePotentialPoints(array, aRow - 1, aCol, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow - 1 != pRow) && (aCol != pCol))) {
                        bestMove[0] = aRow - 2;
                        bestMove[1] = aCol - 1;
                        mostPointsReduced = potentialPoints;
                }
        }

	//Potential Move 3: 1 up and 1 right
        if ((aRow > 0) && (aCol < 7)) {
                int potentialPoints;
                potentialPoints = calculatePotentialPoints(array, aRow - 1, aCol + 1, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow - 1 != pRow) && (aCol + 1 != pCol))) {
                        bestMove[0] = aRow - 2;
                        bestMove[1] = aCol;
                        mostPointsReduced = potentialPoints;
                }
        }

	//Potential Move 4: 1 right
        if (aCol < 7) {
                int potentialPoints;
                potentialPoints = calculatePotentialPoints(array, aRow, aCol + 1, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow != pRow) && (aCol + 1 != pCol))) {
                        bestMove[0] = aRow - 1;
                        bestMove[1] = aCol;
                        mostPointsReduced = potentialPoints;
                }
        }

	//Potential Move 5: 1 down and 1 right
        if ((aRow < 6) && (aCol < 7)) {
                int potentialPoints;
		//BINGO: The problem is somewhere here
                potentialPoints = calculatePotentialPoints(array, aRow + 1, aCol + 1, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow + 1 != pRow) && (aCol + 1 != pCol))) {
			bestMove[0] = aRow;
                        bestMove[1] = aCol;
                        mostPointsReduced = potentialPoints;
                }
        }

	//Potential Move 6: 1 down
        if (aRow < 6) {
                int potentialPoints;
                potentialPoints = calculatePotentialPoints(array, aRow + 1, aCol, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow + 1 != pRow) && (aCol != pCol))) {
                        bestMove[0] = aRow;
                        bestMove[1] = aCol - 1;
                        mostPointsReduced = potentialPoints;
                }
        }

	//Potential Move 7: 1 down and 1 left
        if ((aRow < 6) && (aCol > 0)) {
                int potentialPoints;
                potentialPoints = calculatePotentialPoints(array, aRow + 1, aCol - 1, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow + 1 != pRow) && (aCol - 1 != pCol))) {
                        bestMove[0] = aRow;
			bestMove[1] = aCol - 2;
                        mostPointsReduced = potentialPoints;
                }
        }


	//Potential Move 8: 1 left
        if (aCol > 0) {
                int potentialPoints;
                potentialPoints = calculatePotentialPoints(array, aRow, aCol - 1, pRow, pCol);
                if ((potentialPoints < mostPointsReduced) && ((aRow != pRow) && (aCol - 1 != pCol))) {
                        bestMove[0] = aRow - 1;
                        bestMove[1] = aCol - 2;
			mostPointsReduced = potentialPoints;
                }
        }
}

/*
Algorithmn for AI's moves
Moves AI's builder to postion that will reduce the most numbers from the gameboard.
*/
void AImove(int array[6][6], int AIoctagon[2], int turnCount, int pRow, int pCol) {
	// AIoctagon[0] = aRow - 1
	// AIoctagon[1] = aCol - 1
	if (turnCount == 2) {
		if (pCol < 6) {
			AIoctagon[0] = pRow - 1;
			AIoctagon[1] = pCol;
		} else {
			AIoctagon[0] = pRow - 1;
			AIoctagon[1] = pCol - 2;
		}
		return;
	}

	int bestMove[2];
	getBestMove(array, bestMove, pRow, pCol, AIoctagon[0] + 1, AIoctagon[1] + 1);
	AIoctagon[0] = bestMove[0];
	AIoctagon[1] = bestMove[1];

}

/*
Prints the game board.
Converts the array parameter to a character array.
Prints 'P' for player's builder and 'A' for AI's builder.
*/
void printGameboard(int array[6][6], int turnCount, int pRow, int pCol, int aRow, int aCol) {
	char gameboard_copy[6][6];

	printf("  1 2 3 4 5 6\n");
	for (int i = 0; i < 6; i++) {
		printf("%i ", i + 1);
		for (int j = 0; j < 6; j++) {
			gameboard_copy[i][j] = array[i][j] + '0';

			if ((i + 1 == pRow) && (j + 1 == pCol)) {
				gameboard_copy[i][j] = 'P';
			}

			if ((i + 1 == aRow) && (j + 1) == aCol) {
				gameboard_copy[i][j] = 'A';
			}

			printf("%c ", gameboard_copy[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void main(void)
{
	int gameboard[6][6];
	int turnCount = 0;
	int pRow;
	int pCol;
	int aRow;
	int aCol;
	int AIoctagon[2];

	//Create and Show Empty Gameboard
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			gameboard[i][j] = 2;
		}
	}
	printf("\nSantorini\n");
	printGameboard(gameboard, turnCount, 0, 0, 0, 0);
	turnCount++;

	//Round 1
	int moveValidity = 1;
	printf("Please type two numbers between 1-6 in the format 'a b': ");
	scanf("%i %i", &pRow, &pCol);
	moveValidity = isValidMove(0, 0, pRow, pCol, 0, 0);
	while (moveValidity != 1) {
		printf("Please type two numbers between 1-6 in the format 'a b': ");
        	scanf("%i %i", &pRow, &pCol);
		moveValidity = isValidMove(0, 0, pRow, pCol, 0, 0);
	}
	changeAdjacentValues(gameboard, turnCount, pRow, pCol, 7, 7);
	printf("\nPlayer Move:\n");
	printGameboard(gameboard, turnCount, pRow, pCol, 0, 0);
	turnCount++;

	printf("\nAI Move:\n");
	AImove(gameboard, AIoctagon, turnCount, pRow, pCol);
	aRow = AIoctagon[0] + 1;
	aCol = AIoctagon[1] + 1;
	printGameboard(gameboard, turnCount, pRow, pCol, aRow, aCol);
	turnCount++;

	//All Subsequent Rounds
	int gameFinished = 0;
	while (gameFinished != 1) {
		int prevRow = pRow;
		int prevCol = pCol;
		printf("Please type two numbers between 1-6 in the format 'a b': ");
        	scanf("%i %i", &pRow, &pCol);
		moveValidity = isValidMove(prevRow, prevCol, pRow, pCol, aRow, aCol);
        	while (moveValidity != 1) {
                	printf("Please type two numbers between 1-6 in the format 'a b': ");
                	scanf("%i %i", &pRow, &pCol);
                	moveValidity = isValidMove(prevRow, prevCol, pRow, pCol, aRow, aCol);
        	}

        	changeAdjacentValues(gameboard, turnCount, pRow, pCol, aRow, aCol);
        	printf("\nPlayer Move:\n");
        	printGameboard(gameboard, turnCount, pRow, pCol, aRow, aCol);
        	turnCount++;

        	printf("\nAI Move:\n");
        	AImove(gameboard, AIoctagon, turnCount, pRow, pCol);
        	aRow = AIoctagon[0] + 1;
        	aCol = AIoctagon[1] + 1;
        	changeAdjacentValues(gameboard, turnCount, aRow, aCol, pRow, pCol);
        	printGameboard(gameboard, turnCount, pRow, pCol, aRow, aCol);
        	turnCount++;

		gameFinished = gameOver(gameboard);
	}
}

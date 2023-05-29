#include <stdio.h>
#include <stdlib.h>

#define SIDE 8
#define VISITED 1
#define NOT_VISITED 0

#define GOAL_X 0
#define GOAL_Y 7

#define FALSE 0
#define TRUE !FALSE

#define GOAL_FIRST_CORNER_X 0
#define GOAL_FIRST_CORNER_Y 7

#define GOAL_SECOND_CORNER_X 7
#define GOAL_SECOND_CORNER_Y 7


#define GOAL_THIRD_CORNER_X  7
#define GOAL_THIRD_CORNER_Y 0


void printBoard(int board[][SIDE]);

int goHorsie(int board[][SIDE], int x, int y, int step, int* foundFirst, int* foundSecond, int* foundThird);

int main(void)
{
	int board[SIDE][SIDE] = { NOT_VISITED };

	
	int* foundFirstCorner = (int*)malloc(sizeof(int) * 1);
	int* foundSecondCorner = (int*)malloc(sizeof(int) * 1);
	int* foundThirdCorner = (int*)malloc(sizeof(int) * 1);

	*foundFirstCorner = FALSE;
	*foundSecondCorner = FALSE;
	*foundThirdCorner = FALSE;

	if (goHorsie(board, 0, 0, 1, foundFirstCorner, foundSecondCorner, foundThirdCorner))
	{
		printf("Yes, there is a path passing through all the 3 corners without repeating\n");
		printBoard(board);
	}
	else
	{
		printf("No path passing through all corners without repating");
	}

	free(foundFirstCorner);
	free(foundSecondCorner);
	free(foundThirdCorner);
	getchar();
	return 0;
}

/*
Function checks if knight can travel from top left corner and travel through all corners
input: the board, the current x and y, the current step and pointers to ints representing if alredy found the first, second and third corners
output: whether a path was found
*/
int goHorsie(int board[][SIDE], int x, int y, int step, int* foundFirst, int* foundSecond, int* foundThird)
{
	int res = FALSE;

	if (*foundFirst && *foundSecond && *foundThird) // checks if has been to all the corners
	{
		res = TRUE;
	}
	else if (x >= SIDE || y >= SIDE || x < 0 || y < 0 || // out of the board
		board[x][y] != NOT_VISITED) // we were here already!
	{
		res = FALSE;
	}
	else if (x == GOAL_FIRST_CORNER_X && y == GOAL_FIRST_CORNER_Y) // checks if it is in the first corner
	{
		*foundFirst = TRUE;
		board[x][y] = step;
	}
	else if (x == GOAL_SECOND_CORNER_X && y == GOAL_SECOND_CORNER_Y) // checks if is in the second corner
	{

		*foundSecond = TRUE;
		board[x][y] = step;
	}
	else if (x == GOAL_THIRD_CORNER_X && y == GOAL_THIRD_CORNER_Y) // checks if it is in the third corner
	{

		*foundThird = TRUE;
		board[x][y] = step;
	}
	else
	{
		board[x][y] = step;
		step++;
		// changing order here will change the path, because once a condition is verified (TRUE) the rest aren't checked
		res = goHorsie(board, x + 2, y + 1, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x + 2, y - 1, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x + 1, y + 2, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x + 1, y - 2, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x - 2, y + 1, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x - 2, y - 1, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x - 1, y + 2, step, foundFirst, foundSecond, foundThird) ||
			goHorsie(board, x - 1, y - 2, step, foundFirst, foundSecond, foundThird);
		if (!res)
		{
			board[x][y] = NOT_VISITED;
		}
	}

	return res;
}


/*
Function prints the board
input: board to print
output: none
*/
void printBoard(int board[][SIDE])
{
	int i = 0, j = 0;
	for (i = 0; i < SIDE; i++)
	{
		for (j = 0; j < SIDE; j++)
		{
			printf("%3d", board[i][j]);
		}
		printf("\n");
	}
}

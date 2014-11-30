#include <stdio.h>
#include <stdlib.h>

int find_path(int r, int pond[r][r], int x, int y, int i, int prevKind);
void print_pond(int r, int pond[r][r]);
int valid_pad(int r, int pond[r][r], int x, int y);

//Set of all possible moves.
const int possibleMoves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

#define ROWS atoi(argv[1])

int main(int argc, char *argv[])
{
	//Test for three arguments.
	if (argc != 4)
	{
		printf("Usage: requires three arguments.\n");
		exit(0);
	}
	int pond[ROWS][ROWS], i, j, iniX, iniY;
	iniX = atoi(argv[2]);
	iniY = atoi(argv[3]);
	//Test to make sure matrix is a valid size.
	if (ROWS < 0 || ROWS > 9)
	{
		printf("Usage: first argument must be greater than 0 and smaller than 9.\n");
		exit(0);
	}
	//Test to make sure all arguments are within bounds.
	if (iniX > 8 ||iniX < 0 || iniY < 0|| iniY > 8 || (iniX - 1) > ROWS || (iniY - 1) > ROWS)
	{
		printf("Usage: second and third argument must be within bounds.\n");
		exit(0);
	}
	//Initializes matrix to all zeros.
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < ROWS; j++)
		{
			pond[i][j] = 0;
		}
	}
	pond[iniX][iniY] = 1;
	find_path(ROWS, pond, iniX, iniY, 2, -1);
	printf("No path possible\n");
}

/*Function that prints the matrix.
  @param r, amount of rows or columns in matrix.
  @param pond[r][r], matrix to print.
*/
void print_pond(int r, int pond[r][r])
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			printf(" %2d ", pond[i][j]);
		}
		putchar('\n');
	}
}

/*Function that checks whether or not a move is valid.
  @param r, amount of rows or columns in matrix.
  @param pond[r]][r], matrix that the move is being done in.
  @param x, x coordinate of move to be checked.
  @param y, y coordinate of move to be checked.
  @return int, returns a 1 if valid 0 if invalid.
*/
int valid_pad(int r, int pond[r][r], int x, int y)
{
	if (x >= 0 && y >= 0 && x < r && y < r && pond[x][y] ==  0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*Function that recursively finds a path for the frog.
  @param r, amount of rows or columns in matrix.
  @param pond[r][r], matrix that the path is being found for.
  @param x, x coordinate of frogs current location.
  @param y, y coordinate of frogs current location.
  @param i, current number of move being done.
  @param prevKind, previous kind of move that was done.
  @return int, returns 1 if on the right path 0 if no possible path was found.
*/ 
int find_path(int r, int pond[r][r], int x, int y, int i, int prevKind)
{
	int j, newX, newY;
	if ((i - 1) == r * r)
	{
		print_pond(r, pond);
		exit(0);
	}
	
	//Iterates through all possible moves.
	for (j = 0; j < 8; j++)
	{
		newX = x + possibleMoves[j][0];
		newY = y + possibleMoves[j][1];
		//Tests if valid pad also making sure to do a different move.
		if (valid_pad(r, pond, newX, newY) == 1 && prevKind != j)
		{
			pond[newX][newY] = i;
			//Recursively continues.
			if (find_path(r, pond, newX, newY, i+1, j) == 1)
			{
				return 1;
			}
			else
			{
				pond[newX][newY] = 0; //Backtrack.
			}
		}
	}
	return 0;
}



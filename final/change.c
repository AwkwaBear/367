//FINAL EXAM EE 367

//Completed by: Anthony Gasbarro

/*
 * Computate f(n) = the number of ways to represent n cents
 * with quarters, dimes, nickels and pennies
 */

#include <stdio.h>
#include <stdlib.h>

int change(int coins[],int amount);



void main(int argc, char *argv[])
{

if (argc != 2) {
	printf("Usage:  ./a.out <integer n>\n");
	return;
}

int coins[4] = {25, 10, 5, 1};
int n = atoi(argv[1]);
printf("Number of ways to represent %d cents = %d\n",n,change(coins,n));
return;
}

/*
 * Returns the number of representations of n cents.
 * It currently doesn't work.
 * Implement it using top-down dynamic programming with memoization
 */

int change(int coins[],int amount)
{
//index is set to 4 because there are 4 denominations of coin
	int index = 4;

	//initialize a 2d array for the solutions for each amount vs coin denomination
		int combos[amount+1][index+1];
//initialize the array to store all amounts of zero with 1 solution
	for(int i = 0; i <= 4; i++){
		combos[0][i] = 1;
	}
//update array to show 1 solution for all amounts when using pennies
	for(int i = 0; i <= amount; i++){
		combos[i][0] = 0;
	}

//double for loop will iterate through and find all solutions by
//subtracting current denomination being checked from amount and solving
//the subsequent subproblems
for(int i = 1; i <= index; i++){
	for(int j = 1; j <= amount; j++){

		//if the amount is less than or equal to the previous coins amounts
		//a possible new solution to add exists which will then be computed
		if (coins[i-1] <= j){
			combos[j][i] = combos[j][i-1] + combos[j-coins[i-1]][i];
		}

		//if coin value is greter than the current amount being solved for
		//pass the previous solution to the current memo cell
		else{
			combos[j][i] = combos[j][i-1];
		}
	}
}

//finally return the value solved for at the end of the sequence
return combos[amount][4];
}

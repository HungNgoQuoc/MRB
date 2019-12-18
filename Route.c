/*
 ============================================================================
 Name        : Route.c
 Author      : NGO QUOC HUNG
 Version     : 1.0.0
 Copyright   : Copyright
 Description : Route
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int input[9][6] = { { 1, 1, 1, 1 }, { 0, 0, 0, 0, 1 }, { 0, 1, 1, 0 }, { 0, 1,
		0, 1, 1 }, { 0, 0, 1, 0 }, { 0, 1, 1, 1, 1 }, { 0, 0, 1, 0 }, { 0, 1, 0,
		0, 1 }, { 0, 1, 1, 1 } };

int output[11][10];

int main(void) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			if (i % 2 == 0) {
				output[i + 1][j * 2 + 1] = input[i][j];
				output[i + 1][j * 2] =
						output[i + 1][j * 2] == 0 ?
								input[i][j] : output[i + 1][j * 2];
				output[i + 1][j * 2 + 2] =
						output[i + 1][j * 2 + 2] == 0 ?
								input[i][j] : output[i + 1][j * 2 + 2];
			} else {
				output[i + 1][j * 2] = input[i][j];
				output[i][j * 2] =
						output[i][j * 2] == 0 ? input[i][j] : output[i][j * 2];
				output[i + 2][j * 2] =
						output[i + 2][j * 2] == 0 ?
								input[i][j] : output[i + 2][j * 2];
			}
		}
	}

	int iX = 0, iY = 0;
	bool end = false;

	printf("Ma tran:\n");
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%3d", output[i][j]);
			fflush(stdout);
		}
		printf("\n");
		fflush(stdout);
	}

	printf("Dang tim duong...\n");
//	while (!end) {
//		printf("iX = %3d, iY = %3d\n", iX, iY);
//		fflush(stdout);
//		if (output[iX][iY] == 0) {
//			output[iX][iY] = 3;
//		}
//
//		if (iX >= 0) {
//			iX++;
//		}
//
//		if (iY >= 0) {
//			iY++;
//		}
//
//		if (iX >= 11) {
//			iX--;
//		}
//
//		if (iY >= 10) {
//			iY--;
//		}
//
//		if(iX == 0 && iY == 0){
//			end = true;
//		}
//	}
//
//	printf("Ma tran sau khi tim duong:\n");
//	for (int i = 0; i < 11; i++) {
//		for (int j = 0; j < 10; j++) {
//			printf("%3d", output[i][j]);
//			fflush(stdout);
//		}
//		printf("\n");
//		fflush(stdout);
//	}

	return EXIT_SUCCESS;
}

#include <stdio.h>

int dice[4] = { 0, 0, 0, 0 };
int diceLR[2] = { 0, 0 };

int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };

int N;
int M;
int x;
int y;
int K;

int commend[1000] = { 0, };

int map[21][21];


void roll(int d) {
	if (d == 1) {
		int temp = diceLR[0];
		diceLR[0] = dice[3];
		dice[3] = diceLR[1];
		diceLR[1] = dice[1];
		dice[1] = temp;
	}
	if (d == 2) {
		int temp = diceLR[1];
		diceLR[1] = dice[3];
		dice[3] = diceLR[0];
		diceLR[0] = dice[1];
		dice[1] = temp;
	}

	if (d == 3) {
		int temp = dice[0];
		dice[0] = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[3];
		dice[3] = temp;
	}

	if (d == 4) {
		int temp = dice[0];
		dice[0] = dice[3];
		dice[3] = dice[2];
		dice[2] = dice[1];
		dice[1] = temp;
	}

}

int main() {

	scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	int n;
	for (int k = 0; k < K; k++) {
		scanf("%d", &n);
		int cx = x + dx[n - 1];
		int cy = y + dy[n - 1];

		if (cx >= 0 && cy >= 0 && cx < N && cy < M) {

			roll(n);
			x = cx;
			y = cy;

			if (map[x][y] == 0) {
				map[x][y] = dice[3];
			}
			else  if (map[x][y] != 0) {
				dice[3] = map[x][y];
				map[x][y] = 0;
			}

			printf("%d\n", dice[1]);
		}


	}

	return 0;
}
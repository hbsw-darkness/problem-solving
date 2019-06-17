/*
처음에 큰 좌표를 따고 시작했는데... 시간초과 난다.
경량화를 진행했지만... 답이 틀렸다고 한다.
그냥 dfs로 구현해보자
*/

#include <stdio.h>

int N;
int T;

int maps[20][20];
bool chNum[101];
int dx[4] = { 1, 1, -1, -1 };
int dy[4] = { -1, 1, 1, -1 };
int oldx = 0;
int oldy = 0;
int maxN = -1;

void dfs(int x, int y, int d, int cnt, int result) {

	if (cnt >= 4) {
		//종료 조건. 사각형을 넘어가면 종료
		return;
	}
	//현재 값 중복 체크 저장.
	chNum[maps[x][y]] = true;
	//방향 회전 시작.
	for (int i = 0; i < 4; i++) {
		int cx = x + dx[i];
		int cy = y + dy[i];

		if (oldx == cx && oldy == cy && cnt == 3 && result >= 4) {
			//처음 위치 도달하면 종료

			if (maxN < result) {
				maxN = result;
			}
			chNum[maps[x][y]] = false;
			return;
		}

		if (cx >= 0 && cy >= 0 && cx < N && cy < N && chNum[maps[cx][cy]] == false) {
			//방향 전환을 한다? 안한다?
			//현재 진행 방향이 같으면 .cnt를 증가시키지 않는다.
			//진행 방향이 회전되면 cnt를 증가시킨다.
			if (d == i) {
				dfs(cx, cy, i, cnt, result + 1);
			}
			else {
				dfs(cx, cy, i, cnt + 1, result + 1);
			}
		}
	}
	chNum[maps[x][y]] = false;

}

void dfsAll() {

	for (int i = 0; i < N - 2; i++) {
		for (int j = 1; j < N - 1; j++) {
			oldx = i;
			oldy = j;
			dfs(i, j, 0, 0, 1);
		}
	}
}

int main() {


	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		scanf("%d", &N);
		maxN = -1;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &maps[i][j]);
			}
		}

		dfsAll();

		setbuf(stdout, NULL);
		printf("#%d %d\n", t + 1, maxN);
	}
	return 0;
}
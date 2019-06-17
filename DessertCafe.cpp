/*
ó���� ū ��ǥ�� ���� �����ߴµ�... �ð��ʰ� ����.
�淮ȭ�� ����������... ���� Ʋ�ȴٰ� �Ѵ�.
�׳� dfs�� �����غ���
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
		//���� ����. �簢���� �Ѿ�� ����
		return;
	}
	//���� �� �ߺ� üũ ����.
	chNum[maps[x][y]] = true;
	//���� ȸ�� ����.
	for (int i = 0; i < 4; i++) {
		int cx = x + dx[i];
		int cy = y + dy[i];

		if (oldx == cx && oldy == cy && cnt == 3 && result >= 4) {
			//ó�� ��ġ �����ϸ� ����

			if (maxN < result) {
				maxN = result;
			}
			chNum[maps[x][y]] = false;
			return;
		}

		if (cx >= 0 && cy >= 0 && cx < N && cy < N && chNum[maps[cx][cy]] == false) {
			//���� ��ȯ�� �Ѵ�? ���Ѵ�?
			//���� ���� ������ ������ .cnt�� ������Ű�� �ʴ´�.
			//���� ������ ȸ���Ǹ� cnt�� ������Ų��.
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
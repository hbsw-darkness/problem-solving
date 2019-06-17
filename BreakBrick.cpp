#include <stdio.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class pt {
public:
	int x;
	int y;
	int num;

	pt(int x, int y, int num) {
		this->x = x;
		this->y = y;
		this->num = num;
	}
};

const int maxH = 15;
const int maxW = 12;
int N = 0;
int W = 0;
int H = 0;
int map[maxH][maxW];

int minCnt = 99999999;

int moveX = 1;
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };
vector<pt> v;


void copyOldMap(int oldMap[][12], int thisMap[][12]) {

	for (int i = 0; i < maxH; i++) {
		for (int j = 0; j < maxW; j++) {
			thisMap[i][j] = oldMap[i][j];
		}
	}
}

int checkBlockCnt(int checkMap[][12]) {
	int cnt = 0;
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (checkMap[i][j] > 0) {
				cnt++;
			}
		}
	}
	return cnt;
}

void mapBlockSet(int destroyMap[][12]) {
	for (int i = H - 2; i >= 0; i--) {
		for (int j = 0; j < W; j++) {
			//제일 아래 두번째 줄부터 검사해서 현재 블록이 0이 아니고 아래쪽이 0이면
			//위에 블록을 땡겨서 내린다.
			//printf("%d %d\n", i, j);
			if (destroyMap[i][j] > 0) {
				int x = i + 1;
				int y = j;
				int num = destroyMap[i][j];
				destroyMap[i][j] = 0;
				while (x >= 0 && y >= 0 && x < H && y < W && destroyMap[x][y] == 0) {
					x += 1;
				}
				x -= 1;
				destroyMap[x][y] = num;
			}
		}
	}
}

void bfs(int checkMap[][12]) {
	for (int i = 0; i < v.size(); i++) {
		//printf("in bfs\n");
		queue<pt> q;
		bool chut = false;
		q.push(v[i]);

		while (!q.empty()) {
			int x = q.front().x;
			int y = q.front().y;
			int num = q.front().num;

			q.pop();

			//현재 구슬 발사되었고 현재 위치가 0이면 내리기.
			if (chut == false) {
				while (x >= 0 && y >= 0 && x < H && y < W && checkMap[x][y] == 0) {
					//printf("in chut check\n");
					x += 1;
				}
				if (checkMap[x][y] > 0) {
					chut = true;
					num = checkMap[x][y];
				}
			}

			if (x >= 0 && y >= 0 && x < H && y < W) {
				if (num > 1) {
					checkMap[x][y] = 0;
					//블록이 1보다 크면 n-1사이즈의 주변 십자가로 파괴한다.
					for (int i = 0; i < 4; i++) {
						int cx = x;
						int cy = y;
						int cnt = num - 1;

						while (cx + dx[i] >= 0 && cy + dy[i] >= 0 && cx + dx[i] < H && cy + dy[i] < W && cnt > 0) {
							cx += dx[i];
							cy += dy[i];
							if (checkMap[cx][cy] > 0) {
								q.push(pt(cx, cy, checkMap[cx][cy]));
								checkMap[cx][cy] = 0;

							}
							cnt -= 1;
							/*
							printf("-------------%d \n", cnt);
							for (int i = 0; i < H; i++) {
							for (int j = 0; j < W; j++) {
							printf("%d ", map[i][j]);
							}
							printf("---------------\n");
							}
							*/
						}
					}
				}
				else if (num == 1) {
					//블록이 0이면 자기만 파괴.
					checkMap[x][y] = 0;
				}
			}
		}

		mapBlockSet(checkMap);
		/*
		printf("\n");
		for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
		printf("%d ", map[i][j]);
		}
		printf("\n");
		}
		*/

	}
}

void dfs(int depth) {
	if (depth == N) {

		int thisMap[maxH][maxW];
		copyOldMap(map, thisMap);
		bfs(thisMap);
		int cnt = checkBlockCnt(thisMap);
		if (minCnt > cnt) {
			minCnt = cnt;
		}
		return;
	}

	for (int i = 0; i < W; i++) {
		v.push_back(pt(0, i, 0));
		dfs(depth + 1);
		v.pop_back();
	}
}


int main() {

	int T = 0;
	scanf("%d", &T);
	for (int t = 0; t < T; t++) {
		minCnt = 99999999;
		scanf("%d %d %d", &N, &W, &H);

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		//v.push_back(pt(0, 2, 0));
		//v.push_back(pt(0, 2, 0));
		//v.push_back(pt(0, 6, 0));
		//bfs(map);
		dfs(0);
		v.clear();
		printf("#%d %d\n", t + 1, minCnt);

	}

	return 0;
}
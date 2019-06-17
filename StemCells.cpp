#include <iostream>
#include <stdio.h>
#include <list>
#include <queue>

using namespace std;

class cell {
public:
	int x;
	int y;
	int life;
	int inTime;
	int time;

	cell(int _x, int _y, int _life, int _inTime, int _time) {
		x = _x;
		y = _y;
		life = _life;
		inTime = _inTime;
		time = _time;
	}
};

int T;
int N, M;
int K;
int times = 0;

list<cell> lifeCell;
list<cell> inCell;
list<cell> dieCell;

const int CenterStart = 450;

int Maps[1000][1000];
bool ChMaps[1000][1000];

int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };


void resetAll() {
	lifeCell.clear();
	inCell.clear();
	dieCell.clear();

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			Maps[i][j] = 0;
			ChMaps[i][j] = false;
		}
	}

}

void bfs() {

	int lifeCnt = lifeCell.size();
	int inCnt = inCell.size();
	//printf("%d %d\n", lifeCnt, inCnt);
	//ó���� �� Ȱ��ȭ �ֵ鸸 ã�Ƽ� �ð��� ������Ŵ.
	while (lifeCnt != 0) {
		lifeCnt--;

		int x = lifeCell.front().x;
		int y = lifeCell.front().y;
		int life = lifeCell.front().life;
		int inTime = lifeCell.front().inTime;
		int time = lifeCell.front().time;

		//�ð� ����.
		time += 1;

		lifeCell.pop_front();

		if (inTime != time) {
			//Ÿ�Ӱ� ��Ÿ���� �ٸ��� ������ ����Ʈ�� �ִ´�.
			lifeCell.push_back(cell(x, y, life, inTime, time));
			ChMaps[x][y] = true;
			continue;
		}
		else if (inTime == time) {
			//inTime�� time�� ������ Ȱ��ȭ��. Ȱ��ȭ ����Ʈ�� �ִ´�.
			inCell.push_back(cell(x, y, life, inTime, time));
			ChMaps[x][y] = true;
		}
	}

	//Ȱ��ȭ �� �ֵ��� ������ ����.

	while (inCnt != 0) {
		inCnt--;

		int x = inCell.front().x;
		int y = inCell.front().y;
		int life = inCell.front().life;
		int inTime = inCell.front().inTime;
		int time = inCell.front().time;

		inCell.pop_front();
		time++;
		//�ð��� ������Ų��. �׷��� �״´�.

		//���� Ȱ��ȭ ���¶�� ���Ľ�Ű�� ť�� �ִ´�.
		for (int i = 0; i < 4; i++) {
			int cx = x + dx[i];
			int cy = y + dy[i];

			if (Maps[cx][cy] < life && ChMaps[cx][cy] == false) {
				//printf("create in?\n");
				Maps[cx][cy] = life;
				lifeCell.push_back(cell(cx, cy, life, inTime, 0));
			}
		}

		if ((life + inTime) == time) {
			//�״´�.
			dieCell.push_back(cell(x, y, life, inTime, time));
			//printf("die %d\n", dieCell.size());
		}
		else {
			inCell.push_back(cell(x, y, life, inTime, time));
		}
	}
}

void print(int k) {
	printf("%d------------\n", k);
	for (int i = 440; i < 460; i++) {
		for (int j = 440; j < 460; j++) {
			printf("%d ", Maps[i][j]);
		}
		printf("\n");
	}
}

void bfsAll() {

	for (int i = 0; i < K; i++) {
		bfs();
		//print(i);
	}

}

int main() {
	scanf("%d", &T);

	for (int t = 0; t < T; t++) {

		//�ʱ�ȭ
		resetAll();


		scanf("%d %d %d", &N, &M, &K);
		N += CenterStart;
		M += CenterStart;

		for (int i = CenterStart; i < N; i++) {
			for (int j = CenterStart; j < M; j++) {
				scanf("%d", &Maps[i][j]);
				if (Maps[i][j] != 0) {
					lifeCell.push_back(cell(i, j, Maps[i][j], Maps[i][j], 0));
					ChMaps[i][j] = false;
				}
			}
		}

		bfsAll();

		printf("#%d %d\n", t + 1, inCell.size() + lifeCell.size());

	}

}
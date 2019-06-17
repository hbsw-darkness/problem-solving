#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <list>

using namespace std;

class person {
public:
	int x;
	int y;
	int index;

public:
	person() {
		x = y = index = 0;
	}

	person(int x, int y, int index) {
		this->x = x;
		this->y = y;
		this->index = index;
	}
};


class InPerson {
public:
	int person;
	int mc;
	int index;
	InPerson() {};
	InPerson(int p, int m, int index) {
		person = p;
		mc = m;
		this->index = index;
	}
};

class MC {
public:
	int x;
	int y;
	int size;
	int index;
	int p;
	MC() {};
	MC(int x, int y, int size, int index, int p) {
		this->x = x;
		this->y = y;
		this->size = size;
		this->index = index;
		this->p = p;
	}
};

int T;
int M;
int A;
int sumE = 0;

//�� �� �� ��
int dx[5] = { 0, 0, 1, 0, -1 };
int dy[5] = { 0, -1, 0, 1, 0 };

person Aps;
person Bps;

vector<MC> McList;

list<int> ad;

list<int> bd;

vector<InPerson> AMc;
vector<InPerson> BMc;


void bfsDia(int _x, int _y, int _size, int _index, int _p) {
	queue<MC> q;
	q.push(MC(_x, _y, _size, _index, _p));
	int oldSize = _size;
	bool chMap[11][11];
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			chMap[i][j] = false;
		}
	}
	McList.push_back(MC(_x, _y, oldSize, _index, _p));
	chMap[_x][_y] = true;
	while (!q.empty()) {

		int x = q.front().x;
		int y = q.front().y;
		int size = q.front().size;
		int index = q.front().index;
		int p = q.front().p;

		q.pop();

		for (int i = 1; i < 5; i++) {

			int cx = x + dx[i];
			int cy = y + dy[i];

			if (cx >= 0 && cy >= 0 && cx < 11 && cy < 11 && chMap[cx][cy] == false && size != 0) {
				q.push(MC(cx, cy, size - 1, index, p));
				McList.push_back(MC(cx, cy, oldSize, index, p));
				chMap[cx][cy] = true;

			}
		}
	}
	/*
	for (int i = 1; i < 11; i++) {
	for (int j = 1; j < 11; j++) {
	printf("%d", chMap[j][i]);
	}
	printf("\n");
	}
	*/
}

void moveCheck() {
	int mss = 0;
	list<int>::iterator iterA = ad.begin();
	list<int>::iterator iterB = bd.begin();
	//printf("%d %d %d %d\n", m, Ap.x, Ap.y, sumE);

	while (mss != M + 1) {
		//m�� 0�϶����� üũ ����.
		int MaxAnum = 0;
		int MaxBnum = 0;

		AMc.clear();
		BMc.clear();

		//printf("vector size %d\n", AMc.size(), BMc.size());

		//üũ ���� �ȿ� ���� ��ǥ�� ������ �� ����� �迭���� ����.
		for (int i = 0; i < McList.size(); i++) {
			if (McList[i].x == Aps.x && McList[i].y == Aps.y) {
				AMc.push_back(InPerson(Aps.index, i, McList[i].index));
			}
			if (McList[i].x == Bps.x && McList[i].y == Bps.y) {
				BMc.push_back(InPerson(Bps.index, i, McList[i].index));
				//printf("sss %d %d %d %d\n", mss, BMc.size(), McList[i].p, McList[i].index);
			}
		}



		//���� �Ϸ� �� �� ����� �迭 ũ�⿡ ���� ���� ó��.
		if ((AMc.size() >= 1 && BMc.size() >= 1)) {
			//���⼱ ���� Ž������ ���� ū ���� ã�Ƽ� ��ȯ�Ѵ�.
			//printf("111 %d %d %d\n", mss, AMc.size(), BMc.size());
			for (int i = 0; i < AMc.size(); i++) {
				for (int j = 0; j < BMc.size(); j++) {

					int a;
					int b;
					//printf("---%d %d %d\n", mss, AMc[i].mc, BMc[j].mc);

					//amc�� bmc �� mc index ���� ���� ������
					if (AMc[i].index == BMc[j].index) {
						int mcn = AMc[i].mc;

						a = McList[mcn].p / 2;
						b = McList[mcn].p / 2;
						if (MaxAnum + MaxBnum < a + b) {
							MaxAnum = a;
							MaxBnum = b;
						}
					}
					//mc���� ���� �ٸ���.
					else {
						//printf("---%d %d %d\n", mss, AMc[i].index, BMc[j].index);
						a = McList[AMc[i].mc].p;
						b = McList[BMc[j].mc].p;
						if (MaxAnum + MaxBnum < a + b) {
							MaxAnum = a;
							MaxBnum = b;
						}
					}
				}
			}
		}
		else {
			//printf("222 %d %d %d\n", mss, AMc.size(), BMc.size());
			if (BMc.size() == 0 && AMc.size() > 0) {
				for (int i = 0; i < AMc.size(); i++) {
					if (MaxAnum < McList[AMc[i].mc].p) {
						MaxAnum = McList[AMc[i].mc].p;
					}
				}
			}

			else if (AMc.size() == 0 && BMc.size() > 0) {
				for (int i = 0; i < BMc.size(); i++) {
					if (MaxBnum < McList[BMc[i].mc].p) {
						MaxBnum = McList[BMc[i].mc].p;
					}
				}
			}
		}

		sumE = sumE + (MaxAnum + MaxBnum);

		//printf("%d      %d      %d     %d     %d    x%d    y%d\n", mss, MaxAnum, MaxBnum, aMax, bMax, Aps.x, Aps.y);



		//���⼭ 1ƽ ������ ��ŭ �÷��̾� �̵�.

		if (mss < M) {
			// printf("%d %d %d\n", mss, ad.size(), bd.size());

			Aps.x = Aps.x + dx[*iterA];
			Aps.y = Aps.y + dy[*iterA];

			Bps.x = Bps.x + dx[*iterB];
			Bps.y = Bps.y + dy[*iterB];
			iterA++;
			iterB++;
		}
		mss++;
	}



}

int main() {

	scanf("%d", &T);
	for (int t = 0; t < T; t++) {

		//�ʱ�ȭ
		Aps.x = 1;
		Aps.y = 1;
		Aps.index = 1;
		ad.clear();

		Bps.x = 10;
		Bps.y = 10;
		Bps.index = 2;
		bd.clear();

		McList.clear();
		AMc.clear();
		BMc.clear();

		sumE = 0;
		//�ʱ�ȭ ��



		scanf("%d %d", &M, &A);
		//����� �̵���ǥ �ޱ�

		for (int i = 0; i < 2; i++) {
			for (int ms = 0; ms < M; ms++) {
				int inputN = 0;
				scanf("%d", &inputN);
				if (i == 0) {
					ad.push_back(inputN);
				}
				else {
					bd.push_back(inputN);
				}
			}
		}

		//MC ��ǥ �ޱ�
		for (int i = 0; i < A; i++) {
			int x, y, size, p;
			scanf("%d %d %d %d", &x, &y, &size, &p);
			//�Է¹����� �ٷ� bfs�� ���̾Ƹ�� ���� �����ϱ�.
			bfsDia(x, y, size, i + 1, p);
			//printf("v size %d\n", McList.size());
		}

		/*
		for (int i = 0; i < McList.size(); i++) {
		printf("%d %d\n", McList[i].x, McList[i].y);
		}
		printf("-----------------------\n");
		*/
		// ����Ǿ����� �̵��ϸ鼭 ���� üũ�ϱ�.
		moveCheck();
		printf("#%d %d\n", t + 1, sumE);
	}
	return 0;
}
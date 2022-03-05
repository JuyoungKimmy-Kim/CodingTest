#include <iostream>
#include <vector>

using namespace std;

int dy[4] = { 0,0,1,-1 };
int dx[4] = { 1,-1,0,0 };

int R, C, T;
int upCleaner, downCleaner;
int totalDust = 0;

vector<vector<int>> room, tmp;

void circuitAir() {
	totalDust -= room[upCleaner - 1][0];
	totalDust -= room[downCleaner + 1][0];

	//CCW 
	for (int y = upCleaner - 1; y > 0; y--) //L
		room[y][0] = room[y - 1][0];
	for (int x = 0; x < C - 1; x++) // U
		room[0][x] = room[0][x + 1];
	for (int y = 0; y <= upCleaner - 1; y++) //R
		room[y][C - 1] = room[y + 1][C - 1];
	for (int x = C - 1; x > 1; x--) //D
		room[upCleaner][x] = room[upCleaner][x - 1];
	room[upCleaner][1] = 0;

	//CW
	for (int y = downCleaner + 1; y < R - 1; y++) //L
		room[y][0] = room[y + 1][0];
	for (int x = 0; x <C-1; x++) //D
		room[R-1][x] = room[R-1][x + 1];
	for (int y = R-1; y>downCleaner; y--) //R
		room[y][C - 1] = room[y - 1][C - 1];
	for (int x = C-1; x >1; x--) // U
		room[downCleaner][x] = room[downCleaner][x-1];

	room[downCleaner][1] = 0;
}

void spreadDust() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (room[i][j] == 0 || room[i][j]==-1) continue;

			int microDust = room[i][j]/5;
			int cnt = 0;

			for (int dir = 0; dir < 4; dir++) {
				int ny = i + dy[dir];
				int nx = j + dx[dir];

				if (ny < 0 || nx < 0 || ny >= R || nx >= C) continue;
				if (room[ny][nx] == -1) continue;

				tmp[ny][nx] += microDust;
				cnt++;
			}
			tmp[i][j] -= (cnt*microDust);
		}
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			room[i][j] += tmp[i][j];
			tmp[i][j] = 0;
		}
	}
}

void input() {
	cin >> R >> C >> T;
	room = vector<vector<int>>(R, vector<int>(C));
	tmp= vector<vector<int>>(R, vector<int>(C));

	bool up = true;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> room[i][j];
			if (room[i][j] == -1) {
				if (up) {
					upCleaner = i;
					up = false;
				}
				else downCleaner = i;
			}
			else totalDust += room[i][j];
		}
	}
}

int main() {
	input();
	while (T--) {
		spreadDust();
		circuitAir();
		//printf("%d\n", totalDust);
	}
	cout << totalDust << endl;

	return 0;
}
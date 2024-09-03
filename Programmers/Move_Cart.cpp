// 2024 PCCP 기출문제 4번 수레 움직이기(Lv.3) 문제이며
// 퍼즐판 위에 있는 빨간색 수레와 파란색 수레를 최대한 적은 횟수로 정해진 위치로 움직이는 문제이다.
// 문제의 조건으로 
// 1. 수레는 벽이나 격자 판 밖으로 움직일 수 없습니다.
// 2. 수레는 자신이 방문했던 칸으로 움직일 수 없습니다.
// 3. 자신의 도착 칸에 위치한 수레는 움직이지 않습니다. 계속 해당 칸에 고정해 놓아야 합니다.
// 4. 동시에 두 수레를 같은 칸으로 움직일 수 없습니다.
// 5. 수레끼리 자리를 바꾸며 움직일 수 없습니다.
// 가 주어지며 퍼즐판의 최대 크기는 4*4이다.
// 최대한 적은 횟수를 출력해야하기 때문에 BFS 또는 DFS로 완전탐색을 하여 최솟값을 구해야한다.
// 조건에 맞추기 위해선 빨간색 수레를 먼저 이동시킨 후 파란색 수레를 움직이는 것이 쉽게 풀이 가능하므로
// 2중 for문과 DFS로 문제를 풀이하였다.

#include <vector>
#include <stack>
#include <climits> // 최솟값 비교를 위한 INT_MAX를 사용하기 위한 헤더

using namespace std;

typedef pair<int,int> point; //좌표값을 보다 쉽게 구분하기 위한 자료형 선언

// 매개변수 전달을 최소화 하기 위한 전역변수들
int N; // 퍼즐판 세로
int M; // 퍼즐판 가로
int ans = INT_MAX; // 최솟값
vector<vector<int>> MAZE; // 퍼즐판
vector<vector<int>> Red_visit; // 빨간색 수레의 이동경로
vector<vector<int>> Blue_visit; // 파란색 수레의 이동경로

point Red_Start; // 빨간색 수레의 시작지점
point Blue_Start; // 파란색 수레의 시작지점
point Red_End; // 빨간색 수레의 끝지점
point Blue_End; // 파란색 수레의 끝지점

vector<int> dx = {-1,0,1,0}; // X값의 변화량
vector<int> dy = {0,-1,0,1}; // Y값의 변화량

void Find_Point() // 각 수레의 시작&끝지점 찾는 함수
{
	for(int i = 0;i<MAZE.size();i++)
	{
		for(int j = 0;j<MAZE[0].size();j++)
		{
			if(MAZE[i][j] == 1)
				Red_Start = {j,i};
			else if(MAZE[i][j] == 2)
				Blue_Start = {j,i};
			else if(MAZE[i][j] == 3)
				Red_End = {j,i};
			else if(MAZE[i][j] == 4)
				Blue_End = {j,i};
		}
	}
}

// DFS 들어가기 앞서 비방문 = 0, 방문 = 1, 현재위치 = 2로 나타내었다.
void DFS(point RC, point BC, int count) // Depth First Search
{
	if(count > ans) // 깊이가 현재 최솟값보다 크면 더 이상 탐색할 필요가 없기때문에
		return; // 탐색을 그만한다.
	else if(RC == Red_End && BC == Blue_End && count < ans) // 빨간색 수레와 파란색 수레 모두 끝지점에 도착했고 깊이가 최솟값보다 작으면
	{
		ans = count; // 최솟값을 바꾸고
		return; // 탐색을 그만한다.
	}
	Red_visit[RC.second][RC.first] = 1; // 빨간색 수레가 방문했기 때문에 1
	Blue_visit[BC.second][BC.first] = 1; // 파란색 수레가 방문했기 때문에 1
	for(int i = 0;i<dx.size();i++) // 빨간색 수레의 좌표를 상하좌우로 이동한다.
	{
		int next_RX, next_RY, next_BX, next_BY; // 이동할 빨간색 수레와 파란색 수레의 좌표
		if(RC != Red_End) // 빨간색 수레가 끝지점에 도착하지 못했다면 빨간색 수레를 움직인다.
		{
			next_RX = RC.first + dx[i];
			next_RY = RC.second + dy[i];
			if(next_RX < 0 || next_RX >= M || next_RY < 0 || next_RY >= N || MAZE[next_RY][next_RX] == 5 || Red_visit[next_RY][next_RX] == 1)
			// 움직일 좌표가 퍼즐판을 벗어나거나 이동할 좌표에 장애물이 있거나 방문했던 곳이라면
				continue; // 다른 좌표로 이동한다.
		}
        else // 만약 도착했다면 현재 위치로 고정한다.
        {
            next_RX = RC.first;
			next_RY = RC.second;
		}
		Red_visit[next_RY][next_RX] = 2; // 현재위치이므로 2
		for(int j = 0;j<dx.size();j++) // 파란색 수레의 좌표를 상하좌우로 이동한다.
		{
			if(BC != Blue_End) // 빨간색 수레가 끝지점에 도착하지 못했다면 빨간색 수레를 움직인다.
			{
				next_BX = BC.first + dx[j];
				next_BY = BC.second + dy[j];
				if(next_BX < 0 || next_BX >= M || next_BY < 0 || next_BY >= N || MAZE[next_BY][next_BX] == 5 || Blue_visit[next_BY][next_BX] == 1)
				// 움직일 좌표가 퍼즐판을 벗어나거나 이동할 좌표에 장애물이 있거나 방문했던 곳이라면
					continue;
			}
			else // 만약 도착했다면 현재 위치로 고정한다.
			{
				next_BX = BC.first;
				next_BY = BC.second;
			}
			if(next_RX == next_BX && next_RY == next_BY) // 파란색 수레가 이동할 자리가 빨간색 수레가 있다면
				continue; // 다른 좌표로 이동한다.
			if(next_RX == BC.first && next_RY == BC.second && next_BX == RC.first && next_BY == RC.second)
			// 빨간색 수레와 파란색 수레가 교차하며 이동한다면
				continue; // 다른 좌표로 이동한다.
			Blue_visit[next_BY][next_BX] = 2; // 현재위치이므로 2
            DFS({next_RX,next_RY},{next_BX,next_BY},count+1); // 이동한 좌표로 DFS
            Blue_visit[next_BY][next_BX] = 0; // 백트랙킹 했기때문에 움직였던 좌표는 미방문으로 변경
		}
		Red_visit[next_RY][next_RX] = 0; // 백트랙킹 했기때문에 움직였던 좌표는 미방문으로 변경
	}
}

int solution(vector<vector<int>> maze) {
	N = maze.size();
	M = maze[0].size();
	MAZE = maze;
	Red_visit = vector<vector<int>>(N,vector<int>(M,0));
	Blue_visit = vector<vector<int>>(N,vector<int>(M,0));
	Find_Point();
	DFS(Red_Start,Blue_Start,0);
    if(ans == INT_MAX) // 최솟값이 바뀌지 않았기때문에 해결할 수 있는 방법이 없다라고 판단하여
        return 0; // 0 리턴
	return ans;
}
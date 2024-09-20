#include <vector>
#include <queue>
#include <set>

// 2024 PCCP 기출문제 2번 석유시추(Lv.2) 문제이며 (https://school.programmers.co.kr/learn/courses/30/lessons/250136)
// 1번부터 m번까지의 땅에서 단 하나의 시추관으로 석유를 시추할 때 최대량을 출력하는 문제이다.
// 매개변수로 석유가 매장되어있는 땅을 2차원배열(이하 land)이며
// 연결되어있는 석유를 찾은 후 해당 번호의 땅에 합산 후 최대량을 출력해야하므로
// 연결되어있는 석유를 찾기위한 탐색으로 DFS 또는 BFS을 사용해야하고 필자는 BFS를 사용하여 풀이하였다.
// 하지만 문제 효율성조건으로 땅의 넓이의 최대치는 500*500 이므로 중복탐색을 지양해야함.
// set과 visit을 이용하여 m번까지의 중복탐색을 지양하였다.


using namespace std;

vector<vector<int>> LAND;
vector<int> dx = {-1,0,1,0}; // X 변화량 배열
vector<int> dy = {0,-1,0,1}; // Y 변화량 배열
vector<int> ans; // 1번부터 M번까지의 석유시추량을 기록하는 배열

int max(int n1, int n2) // n1와 n2를 비교해서 큰 값을 리턴 하는 함수
{
	return (n1<n2) ? n2 : n1;
}

int n, m; // n은 깊이, m은 가로

void BFS(int start) // 너비 우선 탐색
{
	for(int i = 0;i<n;i++) // start번 땅을 n 깊이까지 탐색하는 for문
	{
		if(LAND[i][start] == 0) // 해당 땅에 석유가 없다면
			continue; // 다음 깊이로 이동한다.
		queue<pair<int,int>> Q; // BFS를 사용하기 위한 큐
		Q.push({start,i}); // 해당 땅 좌표를 큐에 삽입
		set<int> temp; // 땅 번호를 저장할 set, set을 사용하는 이유는 중복 X 값을 배제하기위함
		temp.insert(start); // 좌표가 가르키는 땅 번호를 삽입
		LAND[i][start] = 0; // 해당 땅을 방문하였기때문에 0 대입
		int oil = 1; // 기름을 하나 시추하였기때문에 시작값 1
		while(!Q.empty()) // BFS가 끝날때까지 반복
		{
			pair<int,int> cur = Q.front();
			Q.pop();
			for(int j = 0;j<dx.size();j++) // 좌표값을 바꾸기 위한 for
			{
				int X = cur.first + dx[j];
				int Y = cur.second + dy[j];
				if(X < 0 || X >= m || Y < 0 || Y>=n  || LAND[Y][X] == 0) // 좌표값이 좌표범위를 벗어나거나 해당 땅에 기름이 없으면
					continue; // 다음 방문지로 이동
				temp.insert(X); // 해당 땅 번호를 삽입
				LAND[Y][X] = 0; // 해당 땅에 있는 석유를 시추하였기떄문에 0 대입
				oil++; // 시추한 기름 1추가
				Q.push({X,Y}); // 이동한 좌표값 큐에 삽입
			}
		}
		for(auto X : temp) // set에 들어가있는 땅 번호에 시추한 기름만큼 추가
			ans[X] += oil;
	}
}

int solution(vector<vector<int>> land) {
    int answer = 0;
	n = land.size();
	m = land[0].size();
	LAND = land;
	ans.resize(m);
	for(int i = 0;i<m;i++)
		BFS(i);
	for(int N : ans)
		answer = max(answer,N);
    return answer;
}
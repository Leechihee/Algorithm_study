// 프로그래머스 연습문제 무인도 여행(Lv.2) 문제이며
// 지도는 격자로 그려져있으며 각 칸에 적힌 X 문자는 바다를 나타내고 숫자는 무인도, 숫자의 값은 해당 섬의 식량을 나타낸다.
// 이때 상하좌우로 연결된 무인도는 연결된 무인도로 이루어진다.
// 이때 섬의 위치가 그려진 지도에서 각 섬에서 최대 몇일까지 머무를 수 있는지 배열에 오름차순으로 정렬하여 리턴하는 문제이다.
// 문제의 조건으로
// 1. 3 ≤ maps의 길이 ≤ 100
// 2. 3 ≤ maps[i]의 길이 ≤ 100
// 3. maps[i]는 'X' 또는 1 과 9 사이의 자연수로 이루어진 문자열입니다.
// 4. 지도는 직사각형 형태입니다.
// 가 주어지며 지도의 최대 크기는 100*100이다.
// 문제에서 지도에 그려진 모든 섬에서의 머무를 수 있는 기간을 배열에 담아 리턴해야하므로
// BFS 또는 DFS를 이용하여 섬들을 탐색하여 식량 값들을 총합하여 배열에 담고
// 정렬로 오름차순으로 정렬 후 리턴하는 방식으로 풀이하였다.
// 이때 주의점이 문제조건에 직사각형 형태로 주어지는 것을 유의하여 문제 풀이해야한다.

#include <string>
#include <vector>
#include <algorithm> // 정렬 알고리즘을 이용하기 위한 헤더

using namespace std;

// DFS 매개변수를 줄이기 위한 전역변수, 배열 선언
vector<string> Graph;
vector<vector<int>> visit;
vector<int> ans_arr; // 결과값을 저장하는 배열
int ans = 0;

vector<int> dx = {-1,0,1,0}; // X값 변화량
vector<int> dy = {0,-1,0,1}; // Y값 변화량

//DFS 들어가기 앞서 미방문 = 0, 방문 = 1로 표현하였음.
void DFS(int X, int Y, int count)
{
	visit[X][Y] = 1; // 해당 좌표를 방문했기때문에 1
	if(Graph[X][Y] == 'X') // 해당 좌표가 바다라면
		return; // 이전 좌표로 이동한다.
    ans += Graph[X][Y] - '0'; // 해당 좌표가 섬이므로 식량값을 더한다.
	for(int i = 0;i<dx.size();i++) // 좌표이동을 위한 for문
	{
		int next_X = X+dx[i];
		int next_Y = Y+dy[i];
		if(next_X < 0 || next_X >= Graph.size() || next_Y < 0 || next_Y >= Graph[next_X].size() || visit[next_X][next_Y] != 0)
		// 이동할 좌표가 지도 좌표를 넘어섰거나 해당 좌표를 방문했다면
			continue; // 다른 좌표로 이동한다
		DFS(next_X,next_Y,count+1);
	}
	if(count == 0 && ans != 0) // 최초 탐색으로 돌아왔고 식량값이 0이 아니라면
	{
		ans_arr.push_back(ans); // 결과배열에 삽입하고
		ans = 0; // 새로운 탐색을 위해 전역변수를 0으로 초기화
	}
}

vector<int> solution(vector<string> maps) {
	visit = vector<vector<int>>(maps.size()); // 방문배열 X축 초기화
	for(int i = 0;i<visit.size();i++) // 방문배열 Y축 초기화
		visit[i] = vector<int>(maps[i].size(),0);
	Graph = maps; // 지역변수를 전역변수로 초기화
	
	for(int x = 0;x<maps.size();x++)
	{
		for(int y = 0;y<maps[x].size();y++)
		{
			if(visit[x][y] != 0) // 방문한 좌표라면
				continue; // 다른 좌표로 이동한다.
            DFS(x,y,0);
		}
	}
	
	if(ans_arr.size() == 0) // 만약 결과배열이 비어있다면
		ans_arr.push_back(-1); // 결과배열에 -1 삽입
	sort(ans_arr.begin(),ans_arr.end()); // 오름차순으로 졍렬 후
    return ans_arr; // 리턴
}
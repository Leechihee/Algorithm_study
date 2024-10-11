// 프로그래머스 연습문제 DFS/BFS 네트워크(Lv.3) 문제이며 (https://school.programmers.co.kr/learn/courses/30/lessons/43162)
// 네트워크란 컴퓨터 상호 간에 정보를 교환할 수 있도록 연결된 형태를 의미한다.
// 예를 들어, 컴퓨터 A와 컴퓨터 B가 직접적으로 연결되어있고,
// 컴퓨터 B와 컴퓨터 C가 직접적으로 연결되어 있을 때
// 컴퓨터 A와 컴퓨터 C도 간접적으로 연결되어 정보를 교환할 수 있다.
// 따라서 컴퓨터 A, B, C는 모두 같은 네트워크 상에 있다고 할 수 있다.
// 이때, 컴퓨터의 개수와 연결에 대한 정보가 담긴 2차원 배열이 매개변수로 주어질 때,
// 네트워크의 개수를 출력하는 문제이다.

// 문제를 해석하면
// 컴퓨터 개수와 연결에 대한 정보를 이용하여 컴퓨터를 연결시키고
// 연결된 컴퓨터들의 집합체의 개수를 구하는 문제이다.
// 따라서 연결에 대한 정보를 완전탐색을 이용하여 컴퓨터를 연결시킨 내용을 Graph에 담고
// DFS/BFS를 이용하여 만들어진 네트워크를 개수를 세는 방법으로 풀이하면 된다.


#include <string>
#include <vector>
#include <queue> // BFS를 위한 큐 헤더 선언

using namespace std;

// 매개변수 전달을 줄이기 위한 전역배열 선언
vector<vector<int>> Network; // 네트워크를 저장하기 위한 배열
vector<bool> visit; // 중복탐색을 지양하기 위한 배열

// 연결에 대한 정보가 담긴 2차원 배열을 통해 graph에 네트워크 삽입
void make_network(vector<vector<int>> c)
{
	for(int i = 0;i<c.size();i++)
	{
		for(int j = 0;j<c[i].size();j++)
		{
			if(c[i][j])
				Network[i].push_back(j);
		}
	}
}

int BFS(int start)
{
	// solution에서 0부터 n-1까지 탐색을 시도하므로 중복탐색 방지용 조건문
	if(visit[start]) // 시작 컴퓨터가 방문한 컴퓨터라면
		return 0; // 0을 출력하여 네트워크 형성을 방지
	
	queue<int> Q; // BFS를 위한 큐
	Q.push(start); // 처음부분 큐에 삽입
	visit[start] = true; // 방문했기때문에 ture
	// 모든 컴퓨터를 탐색할때까지 반복해야하므로 반복문 사용
	while(!Q.empty())
	{
		int cur = Q.front(); // 현재 방문해야할 컴퓨터로 초기화
		Q.pop(); // 그리고 큐에서 정보를 지운다
		// 해당 컴퓨터와 직접적으로 연결된 컴퓨터들을 탐색한다.
		for(int i = 0;i<Network[cur].size();i++)
		{
			int next = Network[cur][i]; // 나중에 탐색할 컴퓨터 번호
			if(visit[next]) // 근데 탐색을 했다면
				continue; // 다른 컴퓨터를 탐색한다.
			// 탐색하지 않았다면
			visit[next] = true; // 탐색했기때문에 true
			Q.push(next); // 그리고 나중에 이 컴퓨터에 연결된 컴퓨터를 탐색하기 위해 큐 삽입
		}
	}
	// 네트워크가 형성되었기 때문에 1을 리턴하여 개수 추가
	return 1;
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
	Network.resize(n);
	visit = vector<bool>(n,false);
	make_network(computers);
	for(int i = 0;i<n;i++)
		answer += BFS(i);
    return answer;
}
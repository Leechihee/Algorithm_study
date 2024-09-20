// 프로그래머스 문제 전력망을 둘로 나누기(Lv.2) 문제이며 (https://school.programmers.co.kr/learn/courses/30/lessons/86971)
// 주어진 송전탑의 전선을 끊어 전력망를 2개로 분할 후
// 두 전력망의 송전탑 개수의 차이를 최소화 시키는 문제이다.
// 문제의 제한사항으론
// 1. n은 2 이상 100 이하인 자연수입니다.
// 2. wires는 길이가 n-1인 정수형 2차원 배열입니다.
// 2-1. wires의 각 원소는 [v1, v2] 2개의 자연수로 이루어져 있으며, 이는 전력망의 v1번 송전탑과 v2번 송전탑이 전선으로 연결되어 있다는 것을 의미합니다.
// 2-2. ≤ v1 < v2 ≤ n 입니다.
// 2-3. 전력망 네트워크가 하나의 트리 형태가 아닌 경우는 입력으로 주어지지 않습니다.
// 가 주어지며
// 전력망을 탐색해야하므로 BFS 또는 DFS를 사용해야하며 전선을 끊는 모든 경우의 수를 탐색하여 최소값을 찾아야하므로 완전탐색 또한 이용해야한다.

#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> Wires; // 매개변수 전달을 줄이기위한 전역변수 선언
int N; // 송전탑 개수

int abs(int n) // 절대값 산출
{
	return (n<0) ? -n : n;
}

//BFS를 들어가기 앞서 비방문 = 0, 방문 = 1로 나타내었다.
int BFS(vector<vector<int>> Graph, int deleteDir) //Breadth First Search
{
	queue<int> Q; // BFS를 하기 위한 큐 선언
	vector<int> visit(N+1, 0); // 중복방문 방지를 위한 배열 선언
    
	Graph[Wires[deleteDir][0]].erase(find(Graph[Wires[deleteDir][0]].begin(),Graph[Wires[deleteDir][0]].end(),Wires[deleteDir][1]));
	Graph[Wires[deleteDir][1]].erase(find(Graph[Wires[deleteDir][1]].begin(),Graph[Wires[deleteDir][1]].end(),Wires[deleteDir][0]));
	// deleteDir에 의한 전선 끊기
	Q.push(1); // 기점은 어디서 시작해도 상관없기 떄문에 1로 고정
	
	int cur, result = 0;
	while(!Q.empty())
	{
		cur = Q.front(); // 현재 위치
        Q.pop();
        visit[cur] = 1; 
        result++;
		for(int i = 0;i<Graph[cur].size();i++)
		{
			int next = Graph[cur][i]; // 다음 위치
			if(visit[next] != 0) // 다음 위치가 방문 했던 곳이라면
				continue; // 다른 곳으로 이동한다.
			Q.push(next);
		}
	}
	return abs(N-2*result); // (N-result)-result = N-2*result이고 문제조건에서 절대값으로 리턴해야하므로
}

int solution(int n, vector<vector<int>> wires) {
	int answer = 101; // 문제의 최대값은 100이므로 101
	Wires = wires;
	N = n;
	vector<vector<int>> graph(n+1); // 전력망을 그래프로 선언하여 탐색
	for(vector<int> V : wires)
	{
		int from = V[0];
		int to = V[1];
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	
	for(int i = 0;i<wires.size();i++)
		answer = min(answer,BFS(graph,i));
	
    return answer;
}
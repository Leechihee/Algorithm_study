// 프로그래머스 그래프 중 가장 먼 노드 (Lv.3) 문제이며 (https://school.programmers.co.kr/learn/courses/30/lessons/49189)
// 노드의 개수를 전달하는 int와 간선에 대한 정보가 담긴 2차원 배열을 매개변수로 받고
// 1번 노드에서 가장 멀리 떨어진 노드의 갯수를 출력해야한다.
// 이때 가장 멀리 떨어진 노드의 정의는 1번 노드에서 최단거리로 이동했을 때
// 간선이 가장 많은 노드를 의미한다.
// 문제의 조건으로
// 1. 노드의 개수 n은 2 이상 20,000 이하입니다.
// 2. 간선은 양방향이며 총 1개 이상 50,000개 이하의 간선이 있습니다.
// 3. vertex 배열 각 행 [a, b]는 a번 노드와 b번 노드 사이에 간선이 있다는 의미입니다.
// 가 주어진다.
// 주어진 간선을 인접리스트 형태의 그래프에 삽입 후 BFS를 이용하여 문제를 풀이하였다.
// 이때 DFS를 사용 하지 않는 이유는 최단거리를 구하기엔 DFS는 불필요한 탐색을 BFS보다 많이 하기때문.

#include <vector>
#include <queue> // BFS를 위한 큐 헤더
#include <algorithm> // max_element와 count 함수를 쓰기 위한 알고리즘 헤더

using namespace std;

// BFS 매개변수를 줄이기 위한 전역변수 선언
vector<vector<int>> Graph; // 인접 리스트
vector<int> costs; // 중복탐색 방지와 거리를 저장하기위한 배열

// 중복탐색을 방지하기위해 1번 노드에서 n번 노드에서까지의 거리를 방문
// 거리가 0 이라면 미방문으로 표현하였음
void BFS()
{
	queue<int> Q; // 큐 선언
	Q.push(1); // 문제에서 1번 노드에서의 가장 먼 노드를 찾아야하므로 1 삽입
	costs[1] = 0; // 1번에서부터 시작하므로 거리는 0
	while(!Q.empty())
	{
		int cur = Q.front(); // 현재 위치
		Q.pop();
		for(int i = 0;i<Graph[cur].size();i++)
		{
			int next = Graph[cur][i]; // 이동할 위치
			if(costs[next] != 0 || next == 1) // 이동한 위치를 방문했거나 다음 위치가 1번 노드라면
				continue; // 다음 노드로 이동
			costs[next] = costs[cur]+1; // 현재 노드에서 1칸 멀어졌기때문에 현재 노드 거리에서 1 추가
			Q.push(next); // 다음에 이동할 노드로 삽입
		}
	}
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
	Graph = vector<vector<int>>(n+1); // 인접 리스트 초기화, 이때 문제에서 1번 노드부터 시작하므로 노드개수에서 1 더하기
	costs = vector<int>(n+1,0); // 배열 초기화, 인접 리스트 조건과 동일
	for(vector<int> V : edge)
	{
		int from = V[0];
		int to = V[1];
		// 양방향 그래프이기 때문에 서로 오고 갈 수 있어야함
		Graph[from].push_back(to);
		Graph[to].push_back(from);
	}
	
	BFS();
	
	int Max = *max_element(costs.begin(),costs.end()); // 가장 먼 노드 찾기
	answer = count(costs.begin(),costs.end(),Max); // 가장 먼 노드와 같은 거리 찾기
    return answer;
}
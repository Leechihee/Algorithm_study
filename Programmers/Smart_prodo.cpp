// 2017 카카오코드 본선 문제 중 스마트한 프로도이다.(프로그래머스 기준 Lv.5) (https://school.programmers.co.kr/learn/courses/30/lessons/1840#)
// 주어진 매개변수들을 이용하여 M_1에서 M_t까지의 변환과정을 출력하는 문제이다.
// 먼저 문제는
// 그래프 G에 대해서, 서로 다른 두 정점 사이에 간선이 존재한다면 단지 한 간선만 존재한다.
// 또한 동일한 정점을 연결하는 간선(셀프 루프)은 존재하지 않는다.
// G의 두 간선 e_1과 e_2가 인접하다면, e_1이 연결하는 두 정점 중 하나는 e_2가 연결하는 정점과 일치한다.
// 그래프 G의 매칭 M은 간선들의 집합이고 M에 속하는 임의의 두 간선은 서로 인접하지 않다.
// 여기서, 공집합은 매칭임에 주목하자.
// 그래프 G와 정수 k에 대해서, 초기에 |M_0|≥k이고 |M_t|≥k 인 두 매칭 M_0와 M_t가 주어진다.
// 우리는 매칭 M_0에서 G의 간선을 추가하거나 또는 삭제해서 M_0를 변환한다.
// 변환의 한 단계에서는 하나의 간선을 추가하거나 삭제할 수 있다.
// 이렇게 해서 변환된 간선들의 집합 M_1은 다시 매칭이 되어야 한다.
// 다시 말해서, 각 변환 단계의 결과물은 매칭이어야 한다.
// 따라서 i번째 단계에서는 매칭 M_i-1를 매칭 M_i로 변환하게 된다.
// 이런 식으로 M_0에서 시작해서 중간 매칭들로의 변환 단계들을 거쳐서 마지막에 M_t를 만들어야 한다.
// 다시 말해서, p번의 단계를 거쳐 만들어진 매칭 M_p에 대해서, M_p = M_t를 만족하면 된다.
// 하지만 중간에 만들어지는 M_i (0 < i < p)는 크기에 제한이 있어서 |M_i| ≥ k-2를 만족해야만 한다.
// 매칭 M_0에서 M_t로 위의 조건들을 만족하면서 항상 변환할 수 있다는 것이 잘 알려져 있다.
// 따라서 여러분은 그 변환 과정을 리턴하는 프로그램을 작성하여야 한다.
// 이다.

// 매개변수는
// 정점과 간선의 개수와 간선이 잇는 두 점을 가진 1차원배열 2개와
// 문제에 설명된 k, 초기 매칭의 크기와 속하는 간선의 정보, 마지막 매칭 크기와 속하는 간선의 정보
// 를 매개변수로 받는다.

// 출력방식은
// 2차원배열로 출력하며 각 행의 첫번째 원소는 0과 1로 이루어지며
// 0은 매칭에서 간선 제거, 1은 매칭에 간선 삽입을 뜻한다.
// 두번째 원소는 간선의 정보를 뜻한다.
// 이때 답이 될 수 있는 방법은 하나가 아닌 여러가지인 경우는 하나만 출력한다.
// 이다.

// 먼저 문제의 난이도는 표기된 난이도에 비해 엄청쉽다.
// 그래프와 백트랙킹에 대한 이해도만 있다면 쉽게 풀 수 있는 문제이다.
// DFS를 이용하여 분기별로 나누어 탐색하고 조건에 맞지않으면 바로 탐색을 취소하고 이전 탐색으로 돌아가서(백트랙킹)
// 다른 분기로 탐색을 시도하는 방법으로 풀이하였다.
// 그리고 문제에서 정점 위주가 아닌 간선 위주로 출력하라고 하였기 때문에 그래프 자체를 선언하지 않고
// 삽입과 탐색이 용이한 map을 이용하여 간선에 대한 정보를 저장하고 필요할때마다 탐색하여 사용할 수 있게 하였다.
// 그리고 매칭은 구성요소가 중요하므로 set을 이용하여 중복삽입을 배제한다.


#include <vector>
#include <set> // 중복삽입을 배제하기 위한 헤더
#include <algorithm> // 기타 알고리즘을 이용하기 위한 헤더
#include <map> // 간선의 정보를 보다 쉽고 빠르게 탐색하기 위한 헤더

using namespace std;


// 매개변수를 줄이기 위한 전역변수
map<int,vector<int>> edge; // 간선의 정보를 저장하기 위한 map 선언

int Km2; // M_i의 개수는 k-2개 이상이여야하므로 k minus 2를 줄여 km2로 칭함
int M1; // 최초 매칭의 크기
int M2; // 최후 매칭의 크기
vector<vector<int>> answer; // 문제의 답
bool flag = false; // 해답을 찾았을때 탐색을 중지하기 위한 bool 변수

// map에 매개변수로 주어진 간선에 대한 정보를 삽입하는 함수
void make_edge(vector<int> from, vector<int> to)
{
	for(int i = 0;i<from.size();i++)
		edge[i+1] = {from[i],to[i]};
}

// 분기별 탐색을 하여 해당 분기가 조건에 맞지 않으면 이전 분기로 백트랙킹하고 다른 분기를 탐색하는 함수(DFS 기반)
void Back_tracking(set<int> M_i, set<int> M_t, vector<vector<int>> Maybe_Ans, vector<bool> visit)
{
	if(flag) // 문제의 답을 찾았다면?
		return; // 탐색을 종료한다.
	map<int,int> M; // M_i의 매칭 유무 확인을 위한 map 선언
	for(int E : M_i) // M_i의 간선들을 탐색하며
	{
		for(int V : edge[E]) // 해당 간선에 대한 정점을 map에 삽입
		{
			if(M.find(V) == M.end()) // M에 해당 정점이 없다면 1로 초기화
				M[V] = 1;
			else
				M[V]++; // 해당 정점이 있다면 1 추가
		}
	}
	
	// map을 탐색하면서 정점의 개수가 2이상이면 M_i는 매칭이 아니므로 이전 분기로 이동
	for(auto C : M)
	{
		if(C.second > 1)
			return;
	}
	
	if(M_i == M_t) // 이번 분기가 M_t라면
	{
		answer = Maybe_Ans; // 정답배열에 결과를 넣고 
		flag = true; // 더이상 탐색을 하지않는다.
		return; // 그리고 탐색을 종료한다.
	}
	
	// 간선을 삭제하는 부분이며 M_i의 크기는 최소 k-2개여야하므로 삭제를 할때 k-2보다 1 커야한다.
	if(M_i.size() > Km2)
	{
		for(int EN : M_i) // M_i를 탐색하며
		{
			// 해당 간선이 M_t에 포함되어있고, 해당간선이 이전 분기에서 추가된 간선이라면(무한루프 방지목적)
			if(M_t.find(EN) != M_t.end() || visit[EN])
				continue; // 다른 간선으로 이동한다.
			set<int> New_M(M_i); // M_i를 보존하기위한 새로운 매칭을 선언한다.
			vector<vector<int>> New_Ans(Maybe_Ans); // Maybe_Ans를 보존하기위한 새로운 배열을 선언한다.
			New_Ans.push_back({0,EN}); // 해당 간선을 삭제하기때문에 인덱스0은 0, 인덱스1은 해당 간선의 번호를 가진 배열을 Maybe_Ans에 삽입한다.
			New_M.erase(New_M.find(EN)); // 해당 간선을 삭제하고
			Back_tracking(New_M,M_t,New_Ans,visit); // 새로운 분기로 탐색을 시도한다.
		}
	}
	
	// 조건을 따지며 추가하기엔 코드 작성하기 어렵기때문에 모든 경우의 수를 연산하며
	// 해당 분기가 아니라면 백트랙킹을 하여 불필요한 탐색 횟수를 줄인다.
	for(int i = 1;i<=edge.size();i++)
	{
		// 중
		if(visit[i]) // 간선이 중복으로 삽입된다면
			continue; // 다른 간선을 삽입한다.
		set<int> New_M(M_i); // M_i를 보존하기위한 새로운 매칭을 선언한다.
		vector<vector<int>> New_Ans(Maybe_Ans); // Maybe_Ans를 보존하기위한 새로운 배열을 선언한다.
		vector<bool> New_visit(visit); // visit을 보존하기위한 새로운 visit을 선언한다.
		New_M.insert(i); // 해당 간선을 삽입하고
		New_Ans.push_back({1,i}); // 삽입하였기때문에 0인덱스에 1, 1인덱스에 해당 간선 번호를 가진 배열을 Maybe_Ans에 삽입한다.
		New_visit[i] = true; // 후에 무한루프 방지를 위한 visit 배열에 해당 간선 번호에 true로 변환
		Back_tracking(New_M,M_t,New_Ans,New_visit); // 새로운 분기로 탐색을 시도한다.
	}
}

vector<vector<int>> solution(int n, int m, vector<int> a, vector<int> b, int k, int m1, int m2, vector<int> e1, vector<int> e2) {
	//전역변수 초기화
	Km2 = max(k-2,0);
	M1 = m1;
	M2 = m2;
	make_edge(a,b);
	
	// 무한루프 방지목적 배열
	vector<bool> visit(m+1,false);
	
	// set으로 탐색하기 때문에 vector로 전달된 e1,e2를 set으로 형변환
	set<int> E1(e1.begin(),e1.end());
	set<int> E2(e2.begin(),e2.end());
	
	// M_0부터 탐색 시작
	Back_tracking(E1,E2,{},visit);
	
    return answer;
}
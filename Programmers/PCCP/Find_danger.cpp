// 2024 PCCP 기출문제 3번(Lv.2) 충돌위험 찾기이며 (https://school.programmers.co.kr/learn/courses/30/lessons/340211#)
// 물류 센터에서 로봇을 이용한 자동 운송 시스템을 운영하고 있으며
// 매개변수로 운송 포인트가 담긴 배열과 로봇들의 운송 경로가 담긴 배열이 주어지며
// 이동 중 동일한 시간에 동일 좌표에 로봇이 2대 이상 모이면 위험 상황으로 판단하고
// 모든 로봇이 물류 센터를 탈출했을 때 위험 상황이 총 몇번 일어나는지를 출력하는 문제이다.
// 먼저 운송 시스템이 작동하는 규칙은
// 1. 물류 센터는 2차원 좌표(r,c)로 나타내며 n개의 포인트가 존재한다.
//    이때 각 포인트는 1~n까지의 서로 다른 번로를 가진다.
// 2. 로봇마다 정해진 운송 경로가 존재하며, 운송 경로는 m개의 포인트로 구성되며
//    첫번째 포인트부터 시작해 마지막 포인트까지 순차대로 방문한다.
// 3. 운송 시스템에 이용되는 로봇은 x대이며, 모든 로봇은 0초에 출발한다.
//    로봇은 매초마다 상하좌우로 한칸씩 움직인다.
// 4. 다음 포인트로 움직일때마다 최단거리로 움직이며 최단경로가 여러개인 경우
//    r 좌표가 변하는 이동을 c 좌표가 변하는 이동보다 먼저 이동한다.
// 5. 마지막 포인트에 도착한 운송 로봇은 물류 센터를 탈출하며 탈출하는 경로는
//    고려하지 않는다.
// 이며
// 문제의 제한사항으로
// 1. 2 ≤ points의 길이 = n ≤ 100
//   1-1. points[i]는 i + 1번 포인트의 [r 좌표, c 좌표]를 나타내는 길이가 2인 정수 배열입니다.
//   1-2. 1 ≤ r ≤ 100
//   1-3. 1 ≤ c ≤ 100
//   1-4. 같은 좌표에 여러 포인트가 존재하는 입력은 주어지지 않습니다.
// 2. 2 ≤ routes의 길이 = 로봇의 수 = x ≤ 100
//   2-1. 2 ≤ routes[i]의 길이 = m ≤ 100
//   2-2. routes[i]는 i + 1번째 로봇의 운송경로를 나타냅니다. routes[i]의 길이는 모두 같습니다.
//   2-3. routes[i][j]는 i + 1번째 로봇이 j + 1번째로 방문하는 포인트 번호를 나타냅니다.
//   2-4. 같은 포인트를 연속으로 방문하는 입력은 주어지지 않습니다.
//   2-5. 1 ≤ routes[i][j] ≤ n
// 가 주어진다.
// 동일 시간에 동일 좌표 위를 로봇들이 지나는 상황을 찾아야하므로
// 모든 로봇들의 좌표를 매 초마다 비교하는 방법으로 문제를 풀이하였다.

#include <vector>
#include <queue> // 운송 포인트를 순차적으로 방문하기때문에 큐 헤더 선언
#include <map> // 동일 시간대에 같은 좌표위를 움직이는 로봇들을 카운팅 하기 위한 맵 헤더 선언

using namespace std;

typedef pair<int,int> point; // 좌표를 쉽게 전달하기 위한 자료구조 선언

// 문제의 조건에 맞추어 좌표이동 함수 선언
point Move_robot(point Cur,point End)
{
	if(Cur.first < End.first)
		Cur.first++;
	else if(Cur.first > End.first)
		Cur.first--;
	else if(Cur.second < End.second)
		Cur.second++;
	else
		Cur.second--;
	return Cur;
}

int solution(vector<vector<int>> points, vector<vector<int>> routes) {
    int answer = 0;
	
	vector<point> Robots(routes.size()+1); // 1번부터 n번까지의 로봇들의 현재위치를 저장하기 위한 배열
	vector<queue<point>> End(routes.size()+1); // 1번부터 n번까지의 로봇들의 운송 포인트를 저장하기 위한 배열
	vector<bool> exit_Robots(routes.size()+1, false); // 마지막 운송 포인트에 도착한 로봇들을 저장하기 위한 배열
	
	//Robots 배열과 End 배열에 데이터를 넣기 위한 for문
	for(int i = 0;i<routes.size();i++)
	{
		Robots[i+1] = {points[routes[i][0]-1][0],points[routes[i][0]-1][1]};
		for(int j = 1;j<routes[0].size();j++)
			End[i+1].push({points[routes[i][j]-1][0],points[routes[i][j]-1][1]});
	}
	
	int end_count = 0; // 탈출한 로봇들의 수를 세기 위한 변수 선언
	
	// 모든 로봇이 탈출할 때까지 반복
	while(end_count < Robots.size()-1)
	{
		map<point,int> M; // 해당 시간에 동일한 좌표위를 지나는 로봇을 세기 위한 맵 선언
		
		// 해당 시간에 모든 로봇을 움직이기 위한 for문
		for(int i = 1;i<Robots.size();i++)
		{
			if(exit_Robots[i] == true) // 탈출한 로봇은 움직일 필요가 없기때문에
				continue; // 다른 로봇을 움직인다.
			
			// 이때 바로 위치를 검사하는 이유는 0초때부터 검사해야하기때문
			// 만약 해당 좌표에 i번 로봇이 처음 방문하면
			if(M.find(Robots[i]) == M.end()) 
				M[Robots[i]] = 1; // 해당 좌표에 로봇이 하나 있다.
			else // 해당 좌표에 로봇이 이미 와있으면
				M[Robots[i]]++; // 해당 좌표에 로봇 수를 하나 늘린다.
			
			// 도착해야할 운송 포인트에 방문했다면
			if(Robots[i] == End[i].front())
			{
				End[i].pop(); // 운송 포인트를 다음 운송 포인트로 바꾼다.
				if(End[i].empty()) // 만약 다음 운송 포인트가 없다면 운송 센터에서 탈출하므로
				{
					end_count++; // 탈출한 로봇 수를 하나 늘리고
					exit_Robots[i] = true; // i번 로봇이 탈출 했다를 저장
					continue; // 후에 오는 이동 함수를 무시
				}
			}
			Robots[i] = Move_robot(Robots[i],End[i].front()); // 도착해야할 운송 포인트로 이동한다.
		}
		for(auto c : M) // 해당 시간대에 모든 로봇이 움직인 후
			if(c.second > 1) answer++; // 로봇들이 있는 좌표들을 탐색하며 2개 이상인 좌표가 있다면 1을 더한다.
        M.clear(); // 다음 시간대를 위한 맵 초기화
	}
	
    return answer;
}
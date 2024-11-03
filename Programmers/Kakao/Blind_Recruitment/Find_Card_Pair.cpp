// 2021 Kakao Blind Recruiment 1차 6번문제이며 (프로그래머스 Lv.3)
// 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/72415

// 문제를 해석하자면 카드 짝 맞추기 게임에서 어느정도 진행된 후의 시점에서
// 짝 맞추기 게임이 끝나기 위한 키 조작 횟수의 최소값을 리턴하는 문제이다.
// 문제의 키포인트는 "카드 뒤집는 순서를 어떻게 하느냐와 뒤집을 카드를 어떻게 찾느냐, 커서를 최단거리로 어떻게 이동시키느냐"이며
// 첫번째로 키 조작 횟수의 최소값을 찾아야 하므로 모든 경우의 수를 탐색하는 완전탐색을 이용한다.
// 두번째로 카드 뒤집는 순서는 완전탐색 중 먼저 탐색 되는 카드를 먼저 뒤집는 것으로 진행한다.
// 예를 들어 탐색 중에 1이 먼저 탐색 되고 2가 후에 탐색이 된다면 1,2 라는 순서로 탐색하며
// 같은 숫자 다른 순서로는 2가 탐색 된 후에 1이 탐색 된다면 2,1 순서로 탐색한다.
// 마지막으로 커서를 최단거리로 이동시켜야 하는데 화살표만 입력하면 한 칸씩 이동이 있고
// Ctrl + 화살표를 입력하면 이동 방향으로 카드가 있다면 그 카드로 한 번에 이동하고,
// 없다면 끝부분으로 한 번에 이동하는 이동이 추가되어있다.
// 하지만 화살표만 입력하는 것과 Ctrl + 화살표를 입력하는 것 둘 다 한 번의 입력으로 이동하기 때문에
// 최단거리 알고리즘 중 자주 이용하는 BFS를 이용할 수 있기 때문에 BFS를 이용하여 커서의 최단거리를 구한다.
// 마지막으로 카드 뒤집는 순서가 달라지면 후에 있을 경우의 수로 달라지기 때문에 bottom-up DFS를 이용하여
// 하위 분기에서 리턴 받은 값 중 최솟값을 선택하여 합산 후 상위 분기로 리턴하는 방식으로 최종 최솟값을 리턴한다.

// 문제를 처음 봤을 때, BFS를 이용한 완전탐색과 bottom-up DFS으로 문제를 풀이를 하였다.
// 하지만 커서의 최단거리를 찾는 방법을 BFS를 이용하지 않았기에 실행시간과 정확도가 차이났었다.
// 카드 찾을 때에도 BFS를 이용했기 때문에 실행시간 차이가 있을 것이다.
// 후에 BFS가 아닌 완전탐색을 이용하여 먼저 탐색된 카드를 순서로 DFS으로 탐색하는 풀이와
// BFS를 이용한 최단거리를 구하는 풀이를 보고 내가 알고도 놓친 부분을 확인했다.
// 처음봤을 땐 내 풀이와 비슷한 풀이인 것처럼 보였지만 조금씩 코드를 이해함과 동시에 차원이 다른 풀이라는 것을 알아냈다.
// 분명 내가 알고 있는 알고리즘이지만 각 함수들의 관계를 생각하지 않고 풀이를 하였기에 이러한 문제를 해결하지 못했다.
// 이 문제를 풀면서 함수를 작성할 때에 각 함수의 관계를 생각하고 풀이해야함을 배워갔다.
	
#include <string>
#include <vector>
#include <algorithm> // min 함수를 이용하기 위한 헤더 선언
#include <queue> // BFS를 이용하기 위한 헤더 선언

using namespace std;

vector<int> dr = {-1,0,1,0};
vector<int> dc = {0,-1,0,1};

//Counting_Press_Key 키 조작 횟수를 리턴하는 함수 BFS를 이용하였다.
int CPK(vector<vector<int>>& board, int r, int c, int tr, int tc)
{
	queue<tuple<int,int,int>> q; // r,c,d 값을 담아야하므로 tuple을 이용한다.
	q.push({r,c,0}); // 최초 좌표와 이동 횟수를 삽입
	while(!q.empty()) // 완전탐색을 해야하므로 큐가 빌 때까지 반복
	{
		auto [cr,cc,d] = q.front(); // 탐색 해야하는 분기
		if(cr == tr && cc == tc) // 현재 좌표가 목표 좌표라면
			return d; // 이동 횟수 리턴
		q.pop(); // 탐색 시작하므로 제거
		for(int i = 0;i<dr.size();i++) // 화살표만 입력했을 때의 이동
		{
			int nr = cr + dr[i];
			int nc = cc + dc[i];
			if(nr<0||nr>=4||nc<0||nc>=4) // 보드판 위에서 벗어나는 이동이라면
				continue; // 다른 이동으로
			q.push({nr,nc,d+1}); // 이동 했기 때문에 큐에 삽입
		}
		
		for(int i = 0;i<dr.size();i++) // Ctrl + 화살표 입력했을 때의 이동
		{
			for(int t = 1;;t++) // 1씩 추가하며 반복한다.
			{
				int nr = cr + t*dr[i];
				int nc = cc + t*dc[i];
				if(nr<0||nr>=4||nc<0||nc>=4) // 보드판 위로 벗어나는 이동이라면
				{
					if(t>1) // 1*dr[i]이므로 한 칸만 이동한 것과 같으므로 1보다 커야한다.
						q.push({nr-dr[i],nc-dc[i],d+1}); // 보드판에서 벗어났으므로 해당 이동 이전을 큐에 삽입하고
					break; // 다른 이동을 탐색한다.
				}
				if(!board[nr][nc]) // 이동한 칸이 빈 칸이라면
					continue; // 이동을 더 한다.
				// 빈 칸이 아니라면
				q.push({nr,nc,d+1}); // 현재 좌표와 이동 횟수에 1를 더한 값을 큐에 삽입한다.
				break;
			}
		}
	}
	return 0;
}

// 카드를 찾는 함수이며 num이 0이면 뒤집은 카드가 없고 0이 아니라면 뒤집은 카드가 있다.
int findCard(vector<vector<int>> board, int r, int c, int num)
{
	int isCard = 0; // 리프분기를 구별하기 위한 탐색
	for(vector<int> v : board)
	{
		for(int n : v)
			isCard = max(isCard,n);
	}
	if(!isCard) // 보드판에 카드가 없다면
		return 0; // 리프분기이므로 0 리턴
	int ret = 1e9;
	if(!num) // 뒤집은 카드가 없다면
	{
		// 보드판을 탐색하며
		for(int nr = 0;nr<4;nr++)
		{
			for(int nc = 0;nc<4;nc++)
			{
				if(!board[nr][nc]) // 해당 칸이 빈 칸이라면
					continue; // 다른 칸으로 이동
				// 해당 칸이 빈 칸이 아니라면
				int move = CPK(board,r,c,nr,nc); // 커서를 해당 칸으로 이동할 떄의 최단거리를 구한다.
				int temp = board[nr][nc]; // 카드 번호 임시저장 변수
				board[nr][nc] = 0; // 해당 칸의 카드를 뒤집었기 때문에 0
				ret = min(ret,move+1+findCard(board,nr,nc,temp)); // 하위 분기로 이동 후 리턴 받은 값과 커서를 이동한 값, enter를 누른 값을 합산하여 최솟값 대입
				board[nr][nc] = temp; // 복귀 했으므로 뒤집었던 카드를 원상복구
			}
		}
		return ret; // 모든 탐색을 마친 후 최솟값 리턴
	}
	// 뒤집은 카드가 있다면 보드를 탐색하며
	for(int nr = 0;nr<4;nr++)
	{
		for(int nc = 0;nc<4;nc++)
		{
			if(board[nr][nc] == num) // 뒤집은 카드를 찾았다면
			{
				int move = CPK(board,r,c,nr,nc); // 커서를 해당 칸으로 이동할 때의 최단거리를 구한다.
				board[nr][nc] = 0; // 뒤집었기 때문에 0
				return move + 1 + findCard(board,nr,nc,0); // 하위분기로 이동하며 짝을 맞추었기 때문에 0을 대입한다.
			}
		}
	}
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = 0;
	answer = findCard(board,r,c,0);
    return answer;
}
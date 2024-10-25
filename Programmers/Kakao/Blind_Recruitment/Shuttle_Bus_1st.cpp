// 2018 KAKAO BLIND RECRUITMENT 기출문제 4번 문제이며 (프로그래머스 Lv.3) (https://school.programmers.co.kr/learn/courses/30/lessons/17678)
// 회사 측에서 무료로 통근버스를 운행하기 때문에 사무실로 편하게 출근이 가능하다.
// 아침마다 많은 사원들이 통근버스를 이용하여 출근한다.
// 문제에서 편의를 위해 통근버스는 이러한 규칙으로 운행한다고 가정한다.
// 1. 셔틀은 09:00부터 총 n회 t분 간격으로 역에 도착하며,
//    하나의 셔틀에는 최대 m명의 승객이 탈 수 있다.
// 2. 셔틀은 도착했을 때 도착한 순간에 대기열에 선 크루까지 포함해서 대기 순서대로 태우고 바로 출발한다.
//    예를 들어 09:00에 도착한 셔틀은 자리가 있다면 09:00에 줄을 선 크루도 탈 수 있다.
// 일찍 나와서 셔틀을 기다리는 것이 귀찮았던 사원 A는 일주일간의 관찰 끝에 다른 사원이
// 몇 시에 버스 대기열에 도착하는지 알아냈다. 이때 사원 A가 사무실에 도착하는 시각 중
// 가장 늦은 시각을 출력하는 문제이다.
// 단, 사원 A는 게으르기 때문에 같은 시각에 도착한 다른 사원 중 대기열에서 가장 뒤에 선다.
// 그리고 모든 사원은 다음날 셔틀을 타는 경우는 없다.

// 문제 해석을 하자면
// 문제 지문 자체의 난이도는 낮은 편이다.
// 사원 A가 통근버스를 이용하여 사무실에 도착하는 시각 중 가장 늦은 시각을 구하는 문제이고
// 다른 사원이 버스 대기열에 도착하는 시간을 오름차순으로 정렬 후 순차적으로 제거하는 방식으로 풀이해 나가면 끝이다.
// 이때, 문제의 중점은 다른 사원들이 도착하는 경우의 수를 생각하여 조건을 잘 세우는 것이 이번 문제의 키포인트이다.
// 어떤 데이터를 삽입과 제거를 하면서 정렬해야 하므로 우선순위 큐를 이용하여 코드를 작성하였다.
// 시간을 탐색하는 문제이기 때문에 문제에 주어진 시간 단위 중에서 최소 단위를 사용하는 것이
// 코드 작성하기 쉽기 때문에 분 단위로 통일 후에 탐색하는 것이 좋다.
// 매개변수로 다른 사원들이 버스 대기열에 도착하는 시간을 문자열로 나타낸 1차원 배열이 주어진다.

// 처음 문제를 봤을 때, 큐 하나를 선언하여 시간 값을 넣고 front 값이 통근버스 출발 시각보다 빠르거나 맞췄다면
// front를 제거하는 방식으로 문제를 풀이하였다. 하지만 큐 하나를 선언하여 문제를 풀이하려고 하니
// 여러 경우의 수에 대한 조건문 작성이 문제가 돼 우선순위 큐 2개를 이용하여 문제를 다시 풀이하였다.
// 결국 정렬과 삽입, 제거가 주가 되는 문제이므로 배열 또는 큐로 코드를 작성하면 O(n)이지만
// 우선순위 큐로 코드를 작성하면 O(logN)이므로 더 빠르게 문제를 해결할 수 있다.
// 우선순위 큐 하나는 시간 값을 저장하는 Q와 버스에 탄 사람을 저장하는 bus 두 개를 선언하였고
// 통근버스 운행 횟수와 하나의 통근버스에 최대 몇 명이 탈 수 있는지를 이용한 이중 반복문을 사용하였다.

#include <string>
#include <vector>
#include <queue> // 우선순위 큐를 이용하기 위한 큐 헤더 선언
#include <sstream> // 출력을 문자열로 해야하므로 형 변환하기 위한 sstrema 헤더 선언

using namespace std;

// 시각이 문자열로 주어지기 때문에 계산을 위해 정수로 변환
int strSplit(string str) 
{
	int min = 0;
	min += ((str[0]-'0')*10+(str[1])-'0')*60;
	min += (str[3]-'0')*10+str[4]-'0';
	return min;
}

// 계산은 정수로 이루어지지만 출력은 문자열로 해야하므로 정수를 문자열로 바꾸는 함수
string itos(int n)
{
	int h = n/60, m = n%60;
	stringstream ss;
	string ret;
	ss << h/10;
	ss << h%10;
	ss << ':';
	ss << m/10;
	ss << m%10;
	ss >> ret;
	return ret;
}


string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
	priority_queue<int> Q; // 시각 정보를 담기 위한 우선순위 큐 선언
	for(string str : timetable) // 모든 시각 정보를 정수로 바꾼 후에
		Q.push(-1*strSplit(str)); // 우선순위 큐에 삽입
	
	int busTime = 540-t; // 계산하기 전에 t 값을 더하고 계산하므로 t를 뺀다.
	int last = 0; // 마지막에 탄 사람을 저장하기 위한 변수 선언
	for(int i = 0;i<n;i++)
	{
		priority_queue<int> bus; // 버스에 탄 사람을 저장하기 위한 우선순위 큐 선언
		busTime += t; // 배차 간격 더하기
		for(int j = 0;j<m;j++) // 탈 수 있는 인원만큼 반복
		{
			// 대기열이 비어있지않고 가장 앞에 있는 사람이 버스 출발 시각보다 일찍 왔다면
			if(!Q.empty() && -Q.top()<=busTime) 
			{
				bus.push(-Q.top()); // 버스에 탑승할 수 있기때문에 큐에 넣고
				Q.pop(); // 대기열에서 제거
			}
		}
		
		if(!bus.empty()) // 버스가 빈 상태로 출발하지 않았다면
		{
			if(bus.size() == m) // 버스 만석이면 마지막에 있는 사람보다 1분 일찍 와야하므로
				last = bus.top()-1; // 마지막에 탄 시각에서 1분을 뺀다.
			else // 버스가 만석이 아니라면 버스 출발 시각에 도착하면 되므로
				last = busTime; // 버스 시각으로 초기화한다.
		}
		else // 버스가 빈 상태로 출발했다면 언제 와도 탈 수 있으므로
			last = busTime; // 버스 시각으로 초기화한다.
		if(Q.empty()) // 대기열에 비었다면 연산을 안해도 되므로
			break; // 반복문 탈출
	}
	answer = itos(last);
    return answer;
}
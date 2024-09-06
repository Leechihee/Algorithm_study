// PCCP 기출문제 1번 동영상 재생기(Lv.1)이며
// 매개변수로 동영상의 길이와 현재 재생위치, 오프닝 시작시간, 오프닝 종료시간, 사용자의 입력 배열이 주어지며
// 사용자의 입력이 끝난 시점의 재생위치를 출력하는 문제이다.
// 먼저 동영상 재생기의 기능으로 10초 전으로 이동(prev), 10초 후로 이동(next), 오프닝 건너뛰기가 있으며
// 기능의 설명으로
// 1. prev는 현재 재생위치에서 10초 전으로 이동, 이동 후 현재 재생위치가 동영상의 처음위치보다 작으면 처음위치로 이동.
// 2. next는 현재 재생위치에서 10초 후로 이동, 이동 후 현재 재생위치가 동영상의 종료위치보다 크면 종료위치로 이동.
// 3. 오프닝 건너뛰기는 현재 재생위치가 오프닝 시작시간과 종료시간 사이에 있다면 오프닝 종료시간으로 이동.
// 가 있으며 문제의 조건으로
// 1. video_len의 길이 = pos의 길이 = op_start의 길이 = op_end의 길이 = 5
//   1-1. video_len, pos, op_start, op_end는 "mm:ss" 형식으로 mm분 ss초를 나타냅니다.
//   1-2. 0 ≤ mm ≤ 59
//   1-3. 0 ≤ ss ≤ 59
//   1-4. 분, 초가 한 자리일 경우 0을 붙여 두 자리로 나타냅니다.
//   1-5. 비디오의 현재 위치 혹은 오프닝이 끝나는 시각이 동영상의 범위 밖인 경우는 주어지지 않습니다.
//   1-6. 오프닝이 시작하는 시각은 항상 오프닝이 끝나는 시각보다 전입니다.
// 2. 1 ≤ commands의 길이 ≤ 100
//   2-1. commands의 원소는 "prev" 혹은 "next"입니다.
//   2-2. "prev"는 10초 전으로 이동하는 명령입니다.
//   2-3. "next"는 10초 후로 이동하는 명령입니다.
// 가 주어진다.
// 기초적인 문법 작성이 가능하면 충분히 풀 수 있는 문제이다.
// 입력을 정수로 받는게 아닌 문자열로 받기때문에 stoi를 이용하여 문자열을 정수로 변환하여 저장 및 연산하고
// stringstream을 이용하여 정수에서 문자열로 형 변환 후 결과를 리턴하는 방식으로 문제를 풀이하였다.

#include <string>
#include <vector>
#include <sstream> // 형 변환을 위한 헤더 선언

using namespace std;

// 작성 하기 용이하게 자료구조 선언
class Time{
public:
	int MAX_min, MAX_sec; // 영상의 최대길이
	int CUR_min, CUR_sec; // 현재 재생위치
	int OPS_min, OPS_sec; // 오프닝 시작위치
	int OPE_min, OPE_sec; // 오프닝 종료위치
	void openning() // 재생위치가 바뀔때마다 바뀐 재생위치가 오프닝 위치인지 확인하는 함수
	{
		int SEC = CUR_min * 60 + CUR_sec; // 간단한 비교를 위한 초단위로 통일
		if(OPS_min*60+OPS_sec <= SEC && SEC <= OPE_min*60+OPE_sec) // 현재 재생위치가 오프닝 시작, 종료위치 사이라면
		{
			// 현재 재생위치를 오프닝 종료위치로 이동한다.
			CUR_min = OPE_min;
			CUR_sec = OPE_sec;
		}
	}
	
	// 생성자, 외부선언
	// 매개변수로 동영상의 길이와 현재 재생위치, 오프닝 시작시간, 오프닝 종료시간을 받아
	// 정수로 형변환 후 저장
	Time(string T, string T2, string T3, string T4);
	
	void operator+=(int n) // next 명령을 위한 연산자 선언
	{
		CUR_sec += n; // 일단 해당 시간만큼 더한 후
		if(CUR_sec >= 60) // 60초가 넘어가면
		{
			CUR_min++; // 1분을 더하고
			CUR_sec %= 60; // 60초로 나눈 나머지값을 대입한다.
		}
		if(CUR_min >= MAX_min && CUR_sec > MAX_sec) // 만약 현재 재생위치가 종료위치를 넘어서면
		{
			// 현재 재생위치를 종료위치로 대입한다.
			CUR_min = MAX_min;
			CUR_sec = MAX_sec;
		}
		openning(); // 현재 위치가 오프닝이면 오프닝 종료위치로 이동한다.
	}
	void operator-=(int n) // prev 명령을 위한 연산자 선언
	{
		CUR_sec -= n; // 일단 해당 시간 만큼 뺀다음
		if(CUR_sec < 0) // 0초보다 작으면
		{
			CUR_min--; // 1분을 빼고
			CUR_sec = 60 + CUR_sec; // 60초에서 남는 시간을 뺀 값을 대입한다.
		}
		if(CUR_min < 0) // 현재 재생위치가 영상의 시작위치보다 작다면
		{
			// 현재 재생위치를 시작위치로 대입한다.
			CUR_min = 0;
			CUR_sec = 0;
		}
		openning(); // 현재 재생위치가 오프닝이면 오프닝 종료위치로 이동한다.
	}
	
	string ret()
	{
		string temp = ""; // 임시저장용 문자열 temp 선언
		stringstream ss(temp); // 정수에서 문자열로 형변환을 위한 stringstream 선언
		if(CUR_min < 10) // 현재 재생위치의 분단위가 두자리가 아니라면
			ss << 0; // 자리수를 맞추기 위해 0을 스트림에 삽입한다.
		ss << CUR_min; // 현재 재생위치의 분단위를 스트림에 삽입한다.
		ss << ':'; // 출력 형식을 위한 :을 스트림에 삽입한다.
		if(CUR_sec < 10) // 현재 재생위치의 초단위가 두자리가 아니라면
			ss << 0; // 자리수를 맞추기 위해 0을 스트림에 삽입한다.
		ss << CUR_sec; // 현재 재생위치의 초단위를 스트림에 삽입한다.
		return ss.str(); // 스트림 안에 있는 문자열을 출력한다.
	}
};

// 문자열로 전달된 시간을 stoi 함수를 이용하여 형변환하여 데이터를 삽입한다.
Time::Time(string T, string T2, string T3, string T4)
{
	string temp = "";
	if(T[0] != '0')
		temp.push_back(T[0]);
	temp.push_back(T[1]);
	MAX_min = stoi(temp);
	temp = "";
	if(T[3] != '0')
		temp.push_back(T[3]);
	temp.push_back(T[4]);
	MAX_sec = stoi(temp);
	
	temp = "";
	if(T2[0] != '0')
		temp.push_back(T2[0]);
	temp.push_back(T2[1]);
	CUR_min = stoi(temp);
	temp = "";
	if(T2[3] != '0')
		temp.push_back(T2[3]);
	temp.push_back(T2[4]);
	CUR_sec = stoi(temp);
	
	temp = "";
	if(T3[0] != '0')
		temp.push_back(T3[0]);
	temp.push_back(T3[1]);
	OPS_min = stoi(temp);
	temp = "";
	if(T3[3] != '0')
		temp.push_back(T3[3]);
	temp.push_back(T3[4]);
	OPS_sec = stoi(temp);
	
	temp = "";
	if(T4[0] != '0')
		temp.push_back(T4[0]);
	temp.push_back(T4[1]);
	OPE_min = stoi(temp);
	temp = "";
	if(T4[3] != '0')
		temp.push_back(T4[3]);
	temp.push_back(T4[4]);
	OPE_sec = stoi(temp);
	
	openning();
}

string solution(string video_len, string pos, string op_start, string op_end, vector<string> commands) {
	string answer = "";
	Time V(video_len, pos, op_start, op_end);
	for(string C : commands)
	{
		if(C[0] == 'n')
			V += 10;
		else if(C[0] == 'p')
			V -= 10;
	}
	answer = V.ret();
    return answer;
}
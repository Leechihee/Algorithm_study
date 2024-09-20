// PCCP 기출문제 4번 수식 복원하기(Lv. 3)이며 (https://school.programmers.co.kr/learn/courses/30/lessons/340210#)
// 매개변수로 N진법으로 표기된 수식이 담긴 문자열 배열이 주어지며
// 주어지는 수식은 결과값이 포함된 수식과 포함되지 않은 수식이 주어지며
// 결과값이 포함된 수식을 이용하여 결과값이 포함되지 않은 수식의 결과값을 구한 뒤
// 완성된 수식을 출력하는 문제이다.
// 이때 수식은 덧셈과 뺼셈만 주어지며 진법은 2~9진법이고
// 여러 진법에 대한 결과값이 1개가 아닌 여러개이면 결과값으로 ?을 출력한다.
// 문제의 조건으로
// 1. 2 ≤ expressions의 길이 ≤ 100
//   1-1. expressions의 원소는 "A + B = C" 혹은 "A - B = C" 형태의 문자열입니다. A, B, C와 연산 기호들은 공백 하나로 구분되어 있습니다.
//   1-2. A, B는 음이 아닌 두 자릿수 이하의 정수입니다.
//   1-3. C는 알파벳 X 혹은 음이 아닌 세 자릿수 이하의 정수입니다. C가 알파벳 X인 수식은 결괏값이 지워진 수식을 의미하며, 이러한 수식은 한 번 이상 등장합니다.
//   	  결괏값이 음수가 되거나 서로 모순되는 수식은 주어지지 않습니다.
// 가 주어진다.

// 문제 자체의 난이도는 타 문제와 비교해서는 그리 어려운 편은 아니다.
// 하지만 구현 난이도는 꽤나 높은 편이며 우리가 실생활에서 쓰는 10진법이 아닌
// 비교적 생소한 2진법부터 9진법을 이용한 문제이므로 진법에 대한 이해도가 없다면
// 문제 해결을 위한 코드 작성이 어려울 수 있다.
// 이 문제의 풀이방법은 수식을 이용하여 예상진법들을 구한 후
// 예상진법들로 계산한 결과값이 같은 것을 이용하여 문제를 풀이해야한다.

#include <string>
#include <vector>
#include <sstream> // 문자열을 나누기 위한 sstream 헤더
#include <map> // 진법을 찾기 위한 map 헤더
#include <set> // 결과값이 여러개인지 확인하기위한 set헤더

using namespace std;

// 매개변수를 줄이기 위한 전역변수
vector<vector<string>> Ans;
vector<int> digit;

// 자릿수를 위한 거듭제곱 함수
int sq(int c,int d) 
{
	int r = 1;
	for(int i = 1;i<c;i++)
		r *= d;
	return r;
}

// digit진법으로 표기된 수를 10진법으로 변환하는 함수
int toDecimal(int target, int digit)
{
	int ret = 0;
	for(int i = 1;target>0;i++)
	{
		if(target%10 >= digit) // 만약 해당진법이 아닌 경우
			return -1; // 나올 수 없는 수인 음수로 리턴
		ret += (target%10) * sq(i,digit);
		target /= 10;
	}
	return ret;
}

// 10진법으로 표기된 수를 digit진법으로 변환하는 함수
int toNdigit(int target, int digit)
{
	int r = 0;
	for(int i = 1;target>0;i++)
	{
		r += (target%digit) * sq(i,10);
		target /= digit;
	}
	return r;
}

// 문자열을 자르는 함수
void Cut_str(vector<string> e)
{
	for(string str : e)
	{
		stringstream ss(str);
		string temp;
		vector<string> ans_T;
		while((ss>>temp))
			ans_T.push_back(temp);
		Ans.push_back(ans_T);
	}
}

// 예상진법을 찾는 함수
void Find_digit()
{
	map<int,int> M; // 모든 수식에서 진법이 사용되어야하므로 수식마다 진법을 사용가능한지 체크하기 위한 map 선언
	for(int i = 2;i<10;i++) // 초기값 선언
		M[i] = 0;
	for(vector<string> v : Ans) // 모든 수식을 탐색
	{
		for(int d = 2;d<10;d++) // 2진법에서 9진법까지 반복한다.
		{
			int A = toDecimal(stoi(v[0]),d); // d진법으로 표기된 수를 10진법으로 변환
			int B = toDecimal(stoi(v[2]),d);
			if(A<0||B<0) // 만약 해당진법으로 10진법으로 변환이 안된다면
				continue; // 다음 진법으로 이동
			if(v[4] != "X") // 해당 수식이 결과값이 있다면
			{
				int C = toDecimal(stoi(v[4]),d);
				if(C<0) 
					continue;
				// 해당 수식이 맞지않는다면
				else if(v[1] == "+" && A + B != C)
					continue; // 다음 진법으로
				else if(v[1] == "-" && A - B != C)
					continue;
			}
			M[d]++; // 해당 진법은 사용할 수 있으므로 1 증가
		}
	}
	
	// 맵을 탐색하면서
	for(auto C : M)
	{
		if(C.second == Ans.size()) // 해당진법이 모든 수식에서 사용할 수 있다면
			digit.push_back(C.first); // 예상진법 배열에 추가한다.
	}
}

// 정수를 문자열로 변환하는 함수
string itos(int n)
{
	string ret;
	stringstream ss;
	ss << n;
	ss >> ret;
	return ret;
}

// 결과값을 계산해야하는 수식에 예상 진법들을 대입하면서 결과값 찾기
void Decording(vector<string>& A)
{
	// 모든 수식을 탐색한다.
	for(vector<string> v : Ans)
	{
		if(v[4] != "X") // 이때 결과값이 존재하다면 다음 수식으로 이동한다.
			continue;
		
		
		set<int> S; // 여러 진법에 대한 결과값이 하나여야하므로 set을 선언한다.
		// 예상진법들을 대입한다.
		for(int i = 0;i<digit.size();i++)
		{
			int A = toDecimal(stoi(v[0]),digit[i]);
			int B = toDecimal(stoi(v[2]),digit[i]);
			int C;
			if(v[1] == "+")
				C = A + B;
			else
				C = A - B;
			
			S.insert(toNdigit(C,digit[i])); // 계산한 값을 해당진법으로 변환 후 셋에 삽입
		}
		
		string temp = "";
		if(S.size() == 1) // 계산한 결과값이 하나로 통일된다면
			temp = v[0] + " " + v[1] + " " + v[2] + " = " + itos(*S.begin()); // 결과값을 넣는다.
		else // 계산한 결과값이 하나로 통일되지않는다면
			temp = v[0] + " " + v[1] + " " + v[2] + " = ?"; // ?를 넣는다.
		A.push_back(temp);
	}
}

vector<string> solution(vector<string> expressions) {
    vector<string> answer;
	
	Cut_str(expressions);
	
	Find_digit();
	
	Decording(answer);
    return answer;
}
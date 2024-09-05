// 2019 카카오 개발자 겨울 인턴십 불량 사용자(Lv.3) 문제이며
// 유저 아이디가 담긴 유저배열과 불량 사용자 아이디가 담긴 불량 사용자 배열을 매개변수로 받고
// 주어진 두 배열을 이용하여 매핑한 제제 아이디의 목록을 만들고
// 만들어진 목록의 가짓수가 총 몇가지인지 출력하는 문제이다.
// 문제의 조건으로
// 1. user_id 배열의 크기는 1 이상 8 이하입니다.
// 2. user_id 배열 각 원소들의 값은 길이가 1 이상 8 이하인 문자열입니다.
// 2-1. 응모한 사용자 아이디들은 서로 중복되지 않습니다.
// 2-2. 응모한 사용자 아이디는 알파벳 소문자와 숫자로만으로 구성되어 있습니다.
// 3. banned_id 배열의 크기는 1 이상 user_id 배열의 크기 이하입니다.
// 3-1. banned_id 배열 각 원소들의 값은 길이가 1 이상 8 이하인 문자열입니다.
// 3-2. 불량 사용자 아이디는 알파벳 소문자와 숫자, 가리기 위한 문자 '*' 로만 이루어져 있습니다.
// 3-3. 불량 사용자 아이디는 '*' 문자를 하나 이상 포함하고 있습니다.
// 4. 불량 사용자 아이디 하나는 응모자 아이디 중 하나에 해당하고 같은 응모자 아이디가 중복해서 제재 아이디 목록에 들어가는 경우는 없습니다.
//    제재 아이디 목록들을 구했을 때 아이디들이 나열된 순서와 관계없이 아이디 목록의 내용이 동일하다면 같은 것으로 처리하여 하나로 세면 됩니다.
// 가 주어진다.
// 제제 아이디 목록의 가짓수를 구하는 문제이므로
// 모든 경우의 가짓수를 구하기 위하여 DFS를 이용하여 제제 아이디를 매핑하고
// 문제조건에 같은 아이디가 중복해서 제제 아이디 목록에 들어가는 경우는 없다 라고 하였으므로 set을 사용하여 목록를 만들고
// 또 중복되는 목록을 제거하기위해 이중 set을 이용하여 중복되는 목록 삽입을 하지 않도록 한다.
// 그 후 이중 set의 크기를 리턴하는 방식으로 문제를 풀이하였다.
// 이때 BFS를 사용하지 않는 이유는 너비 우선 탐색이기때문에 분기를 나누며 탐색하기 까다롭기 때문이다.

#include <string>
#include <vector>
#include <set> // 목록을 만들기 위한 STL

using namespace std;

//DFS 매개변수를 줄이기위한 전역변수 선언
vector<string> USER;
vector<string> BANNED;
vector<int> visit; // 중복탐색 방지를 위한 배열 선언
set<set<string>> ans_arr; // 이중 set을 이용하여 중복되는 제제 아이디 목록 제거

// 매핑 함수
bool Catch_banUser(string user, string banned)
{
	if(user.size() != banned.size())
		return false;
	for(int i = 0;i<user.size();i++)
	{
		if(banned[i] != '*' && user[i] != banned[i])
			return false;
	}
	return true;
}

//DFS 들어가기 앞서 미방문 0, 방문 1로 표현하였음.
void DFS(int index, set<string> temp)
{
	if(temp.size() == BANNED.size()) // 제제 아이디 목록이 만들어지면
	{
		ans_arr.insert(temp); // 제제 아이디 목록들에 삽입
		return; // 후에 다른 분기로 이동
	}
	for(int i = 0;i<USER.size();i++) // 유저 배열을 처음부터 끝까지 반복
	{
		if(visit[i] != 0 || !Catch_banUser(USER[i],BANNED[index])) // 만약 유저아이디가 불량아이디에 의해 매핑이 안된다면
			continue; // 다른 유저아이디로 이동
		visit[i] = 1; // 방문했기때문에 방문으로 대입
		temp.insert(USER[i]); // 해당 유저 아이디가 제제 아이디이므로 목록에 유저 아이디 삽입
		DFS(index+1,temp); // 다음 불량 아이디로 매핑
		temp.erase(USER[i]); // 다음 분기를 위한 이번 분기 제제 아이디 제거
		visit[i] = 0; // 다음 분기를 위한 이번 분기에 대한 유저 아이디 방문을 미방문으로 대입
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	USER = user_id; // 지역변수를 전역변수로 대입
	BANNED = banned_id; // 지역변수를 전역변수로 대입
	visit = vector<int>(user_id.size(),0); // 지역변수 크기만큼 크기 재셜정
	set<string> temp; // 초기 목록 선언
	DFS(0,temp);
    return ans_arr.size();
}
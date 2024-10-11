#include <string>
#include <vector>

using namespace std;

// 각 문자열들을 자동완성 해주는 최소 알파벳 수를 구하는 문제 (https://school.programmers.co.kr/learn/courses/30/lessons/17685)
// 문자열을 다루는 만큼 trie라는 자료구조를 이용하여 문제를 풀이하였음
// trie는 문자열을 탐색하는 방법 중 하나로서 일반적인 트리와 비슷한 형태를 띔
// head가 루트이며 루트의 자식노드는 각 단어의 첫번째 알파벳이고 이후 두번째 알파벳은 첫번째 알파벳의 자식노드로 붙는 방식
// 따라서 주어진 단어들를 trie에 전부 삽입하고 삽입하는 도중에 해당 알파벳노드를 몇번 방문하는지 카운팅하고
// 해당 노드를 1번 방문했다면 그 뒤론 단어가 없다는 것이기때문에 해당 노드에서 리턴하여 알파벳 갯수를 answer에 합하였음

class trie{ // 클래스로 자료구조를 선언하였음
public:
	class node{
	public:
		char key; // 해당 노드가 가진 알파벳
		int count = 0; // 몇번 방문했는지?
		vector<node*> child; // 자식 배열(메모리 문제로 인한 push_back()으로 삽입, 배열을 크기를 알파벳 갯수로 초기화하고 ['a']으로 삽입하여도 됨
		node(char ch) : key(ch) {} // 노드 생성자
	};
	node* head; // 루트, 루트노드이기 때문에 알파벳을 삽입하지않음
	trie() {head = new node(' ');} // 생성자
	void input(string str); // trie에 영단어 삽입
	int AutoCorrect(string str); // 자동 완성을 위한 최소 알파벳 갯수 리턴
};

trie::node* Find(vector<trie::node*>::iterator start, vector<trie::node*>::iterator end, char target) // 해당 노드에 target 알파벳이 있는지 찾는 함수
{
	for(auto it = start;it != end;it++)
	{
		if((*it)->key == target) // 해당 노드에 target이 있다면 해당 노드 리턴
			return *it;
	}
	return NULL; // 아니라면 널리턴
}

void trie::input(string str) 
{
	
	node* cur = head;
	for(int i = 0;i<str.size();i++)
	{
		node* next = Find(cur->child.begin(),cur->child.end(),str[i]); // 해당 노드에 알파벳이 있는지 확인하고 있다면 그 노드로 이동, 아니라면 널포인터
		if(next == NULL) // 널포인터라면 자식노드에 알파벳을 삽입하기
		{
			next = new node(str[i]); // 자식노드 동적할당 후
			cur->child.push_back(next); // 자식노드 배열에 삽입
		}
		next->count++; // 해당 노드 방문횟수 1회 늘리기
		cur = next; // 다음 노드로 이동
	}
}

int trie::AutoCorrect(string str)
{
	node* cur = head;
	string temp = ""; // 탐색한 알파벳을 임시저장
	for(int i = 0;i<str.size() && !(temp == str);i++)
	{
		cur = Find(cur->child.begin(),cur->child.end(),str[i]); // 해당 알파벳이 있는 노드로 이동
		temp += cur->key; // 노드가 가진 알파벳을 temp에 저장
		if(cur->count == 1) // 해당 노드가 한번만 방문됬는지 확인 후 한번만 방문 했다면 루프 정지
			break;
	}
	return temp.size(); // temp 길이를 리턴하여 최소 알파벳 갯수 리턴
}

int solution(vector<string> words) {
    int answer = 0;
	trie Trie;
	for(string str : words)
		Trie.input(str);
	
	for(string str : words)
		answer += Trie.AutoCorrect(str);
    return answer;
}
#include <string>
#include <vector>

using namespace std;

class trie{
public:
	class node{
	public:
		char key;
		int count = 0;
		vector<node*> child;
		node(char ch) : key(ch) {}
	};
	node* head;
	trie() {head = new node(' ');}
	void input(string str);
	int AutoCorrect(string str);
};

trie::node* Find(vector<trie::node*>::iterator start, vector<trie::node*>::iterator end, char target)
{
	for(auto it = start;it != end;it++)
	{
		if((*it)->key == target)
			return *it;
	}
	return NULL;
}

void trie::input(string str)
{
	
	node* cur = head;
	for(int i = 0;i<str.size();i++)
	{
		int test = cur->count;
		node* next = Find(cur->child.begin(),cur->child.end(),str[i]);
		if(next == NULL)
		{
			next = new node(str[i]);
			cur->child.push_back(next);
		}
		next->count++;
		cur = next;
	}
}

int trie::AutoCorrect(string str)
{
	node* cur = head;
	string temp = "";
	for(int i = 0;i<str.size() && !(temp == str);i++)
	{
		cur = Find(cur->child.begin(),cur->child.end(),str[i]);
		temp += cur->key;
		if(cur->count == 1)
			break;
	}
	return temp.size();
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
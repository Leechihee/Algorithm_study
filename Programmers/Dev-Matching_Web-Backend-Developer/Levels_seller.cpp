// 2021 Dev-Matching: 웹 백엔드 개발자(상반기) 문제(프로그래머스 Lv.3) 중 하나이며 (https://school.programmers.co.kr/learn/courses/30/lessons/77486)
// 피라미드 형태의 판매망을 가진 다단계 조직을 이용하여 칫솔을 판매 하고 조장이
// 어느정도 판매가 이루어진 후, 조직 내 누가 얼마나 이득을 가져갔는지 확인하는 프로그램을 작성하려고 한다.
// 조직은 자신을 참여시킨 추천인에게 연결되어있는 구조이며
// 자신의 이익은 칫솔의 판매액과 추천하여 가입시킨 판매원의 칫솔의 판매액의 10%이다.
// 이때, 배분금 또한 자신의 이익이므로 추천해준 판매원에게 배분금의 10%를 배분해야한다.
// 배분금을 10%로 나눌 때 소숫점은 절사하며
// 배분금이 1원미만으로 내려간다면 이득을 배분하지 않고 자신이 모두 가진다.
// 문제의 제한사항으로는
// 1. enroll의 길이는 1 이상 10,000 이하입니다.
//   1-1. enroll에 민호의 이름은 없습니다. 따라서 enroll의 길이는 민호를 제외한 조직 구성원의 총 수입니다.
// 2. referral의 길이는 enroll의 길이와 같습니다.
//   2-1. referral 내에서 i 번째에 있는 이름은 배열 enroll 내에서 i 번째에 있는 판매원을 조직에 참여시킨 사람의 이름입니다.
//   2-2. 어느 누구의 추천도 없이 조직에 참여한 사람에 대해서는 referral 배열 내에 추천인의 이름이 기입되지 않고 “-“ 가 기입됩니다.
//   2-3. enroll 에 등장하는 이름은 조직에 참여한 순서에 따릅니다.
//   2-4. 즉, 어느 판매원의 이름이 enroll 의 i 번째에 등장한다면,
// 	   이 판매원을 조직에 참여시킨 사람의 이름, 즉 referral 의 i 번째 원소는 이미 배열 enroll 의 j 번째 (j < i) 에 등장했음이 보장됩니다.
// 3. seller의 길이는 1 이상 100,000 이하입니다.
//   3-1. seller 내의 i 번째에 있는 이름은 i 번째 판매 집계 데이터가 어느 판매원에 의한 것인지를 나타냅니다.
//   3-2. seller 에는 같은 이름이 중복해서 들어있을 수 있습니다.
// 4. amount의 길이는 seller의 길이와 같습니다.
//   4-1.amount 내의 i 번째에 있는 수는 i 번째 판매 집계 데이터의 판매량을 나타냅니다.
//   4-2.판매량의 범위, 즉 amount 의 원소들의 범위는 1 이상 100 이하인 자연수입니다.
// 5. 칫솔 한 개를 판매하여 얻어지는 이익은 100 원으로 정해져 있습니다.
// 6. 모든 조직 구성원들의 이름은 10 글자 이내의 영문 알파벳 소문자들로만 이루어져 있습니다.
// 이며
// 문제의 매개변수로는 각 판매원의 이름이 담긴 1차원 배열과
// 각 판매원을 다단계 조직에 참여시긴 다른 판매원의 이름이 담긴 1차원 배열,
// 판매량 집계 데이터의 판매원 이름이 담긴 1차원 배열,
// 판매량 집계 데이터의 판매 수량이 담긴 1차원 배열이 주어지며
// 각 판매원이 얻은 이익금을 계산하여 각 판매원의 이름이 담긴 1차원 배열의 순서와 같은 배열로
// 출력하는 문제이다.

// 문제를 해석하자면
// 임의의 한 판매원이 칫솔을 판매하여 얻은 판매금과 추천하여 가입시킨 판매원의 배분금을
// 자신의 이익으로 생각하고 자신의 이익이 생길 때마다 추천해준 판매원에게 배분하여 배분금이 조장까지 배분되거나
// 배분금이 1원 미만으로 내려갈 때까지 배분하는 방식을 가진 피라미드 조직이다.
// 그렇기에 트리를 이용하여 조직을 구체화 후에 bottom-up DFS를 이용하여 트리의 루트노드을 향하여 올라가며
// 계산하는 방식으로 풀이해야 한다.
	
// 처음 문제를 보았을 때, 트리와 DFS를 활용하여 문제를 풀이해야 한다는 것을 확인하였지만
// 트리를 구현할 때에 배열을 이용한 구현이 아닌 포인터를 이용한 구현으로 먼저 하였다.
// 문제는 문제의 조건사항에 따르면 판매원과 판매 집계 데이터의 크기가 각각 10,000과 100,000 이고
// 최초 구현 후 제출한 결과에 시간초과 결과가 나왔기에 두번째로 구현할 때는 배열로 구현하였다.
// 시간초과라는 결과가 나온 이유는 불필요한 탐색을 하였기 때문이다.
// 배열로 구현하면 루트 노드에서 자식 노드까지 탐색할 필요없이 index를 이용하여 타겟 노드부터 탐색할 수 있지만
// 포인터로 구현하면 루트 노드에서 자식 노드까지 탐색을 하여 타겟 노드를 찾고 다시 루트 노드로 올라가야하므로
// 배열로 구현한 트리보다 느릴 수밖에 없다.
// 트리를 구현하였지만 계산 방식에서 착오가 있어서 시간이 조금 걸렸다.
// 판매액이 집계될 때마다 계산하는 것이 문제의 의도였지만
// 잘못 이해하여 판매액의 총합을 이용한 계산을 하는 것으로 이해하였다.
// 후에 계산 방식을 이해하여 수정하였더니 문제를 해결하였다.

#include <string>
#include <vector>
#include <map> // 배열의 인덱스를 빠르게 찾기 위한 map 헤더
#include <cmath> // floor 함수를 쓰기 위한 cmath 헤더

using namespace std;

vector<int> tree; // 피라미드 형태의 조직이므로 트리를 구성하여 탐색(이때, 배열의 index는 판매원, 담긴 내용은 추천해준 판매원이다.)
vector<int> answer; // 이익금을 출력하기 위한 배열

// bottom-up DFS
void DFS(int index, int amount)
{
	if(index == 0 || amount == 0) // 루트 노드거나 배분금이 없다면
		return; // 계산을 끝낸다.
	// 루트 노드가 아니고 배분금도 있다면
	int temp_amount = (amount*0.1<1.0)?amount:floor(amount*0.1); // 배분해야할 돈을 계산한다.
	if(temp_amount == amount) // 계산한 배분해야할 돈이 받은 배분금과 똑같다면
	{
		answer[index-1] += amount; // 내 이익으로 넣고
		return; // 계산을 끝낸다.
	}
	else // 아니라면
	{
		amount -= temp_amount; // 배분금에서 배분해야할 돈을 빼고
		answer[index-1] += amount; // 내 이익으로 넣는다.
	}
	DFS(tree[index],temp_amount); // 추천해준 사람에게 배분금을 전달한다.
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
	tree = vector<int>(enroll.size()+1,0); // index 0은 조장이므로 크기를 enroll 크기에 1을 더한 값으로 설정한다.
	answer = vector<int>(enroll.size(),0); // 이익금을 담을 배열이므로 배열의 크기를 enroll 크기로 설정한다.
	map<string,int> index; // 트리를 배열로 선언하였기 때문에 판매원에 따른 index 값을 쉽게 찾기 위한 map 선언
	// index 0은 조장이므로 1부터 삽입
	for(int i = 0;i<enroll.size();i++)
		index[enroll[i]] = i+1;
	
	// 피라미드 형태의 조직을 구체화
	for(int i = 0;i<referral.size();i++)
	{
		if(referral[i] == "-") // 추천해준 사람이 없다면 조장이 추천했기 때문에
			tree[i+1] = 0; // 부모 노드는 0
		else // 추천해준 판매원이 있다면
			tree[i+1] = index[referral[i]]; // 추천해준 판매원이 부모 노드
	}
	
	for(int i = 0;i<seller.size();i++) // 판매액을 집계
		DFS(index[seller[i]],amount[i]*100);

	return answer;
}
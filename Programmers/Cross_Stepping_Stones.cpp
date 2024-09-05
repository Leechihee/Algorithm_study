// 2019 카카오 개발자 겨울 인턴십 중 징검다리 건너기(Lv.3) 문제이며
// 징검다리의 디딤돌을 디딜때마다 디딤돌에 적힌 숫자가 1씩 줄어들며 0이 되면 딛을 수 없게되는 징검다리 배열과
// 한사람이 한번에 뛸 수 있는 디딤돌의 개수를 매개변수로 받고 한번에 한사람씩 끝까지 징검다리를 건널때
// 주어진 징검다리는 최대 몇명까지 건널 수 있는지 출력하는 문제이다.
// 문제의 조건으로
// 해당 문제는 정확도과 효율성 검사가 각각 존재함
// 1. 징검다리를 건너야 하는 니니즈 친구들의 수는 무제한 이라고 간주합니다.
// 2. stones 배열의 크기는 1 이상 200,000 이하입니다.
// 3. stones 배열 각 원소들의 값은 1 이상 200,000,000 이하인 자연수입니다.
// 4. k는 1 이상 stones의 길이 이하인 자연수입니다.
// 가 주어진다.
// 주어진 징검다리에서 조건에 맞추어 건널 수 있는 사람의 최대값을 출력해야하기때문에
// 한사람이 한번에 뛸 수 있는 거리 내에서 디딤돌의 디딜 수 있는 횟수의 연속적인 비교를 통한 최솟값을 출력해야하므로
// front와 back에서 정보를 삽입, 제거가 가능한 deque를 이용하여 문제를 풀이하였다.
// 다른 방법으로 슬라이딩 윈도우가 있지만 문제 조건에 정확도 검사와 효율성 검사를 동시에 시행하기때문에
// 덱을 이용한 문제풀이가 효율성과 코드 간결성이 높다 생각하여 덱으로 문제풀이 하였다.

#include <vector>
#include <deque> // 연속적인 비교를 위한 덱 헤더

using namespace std;

typedef pair<int,int> record; // 자료구조 선언

int min(int n1, int n2) // 최솟값 비교
{
	return (n1 < n2) ? n1 : n2;
}

int solution(vector<int> stones, int k) {
	int answer = 200000001; // 문제조건에 매개변수 최대값이 20000000이므로 200000001은 변하지않는 최대값
	deque<record> D; // 덱 선언
	for(int i = 0;i<stones.size();i++) // 디딤돌을 한칸씩 뒤로 가며 연속적인 비교
	{
		while(!D.empty() && D.back().first < stones[i]) D.pop_back();
		// 새로 들어오는 디딤돌의 디딜 수 있는 횟수가 앞에 있던 디딤돌의 디딜 수 있는 횟수보다 크면
		// 앞 디딤돌을 디딜 수 없어도 그 전 디딤돌에서 한번에 뛸 수 있으므로 비교하면서 뒤에서부터 제거
		while(!D.empty() && D.front().second + k <= i) D.pop_front();
		// 새로 들어오는 디딤돌의 위치가 앞에 있던 디딤돌에서 뛸 수 있는 거리보다 크면
		// 앞 디딤돌에서 새로 들어오는 디딤돌로 뛸 수 없기 때문에 앞 디딤돌 제거
		
		D.push_back({stones[i],i}); // 새로운 디딤돌 추가
		if(D.size() > k) // 디딤돌 개수가 뛸 수 있는 거리보다 많으면
			D.pop_front(); // 앞 디딤돌을 제거
		if(i >= k-1) // 뛸 수 있는 거리만큼 디딤돌이 들어와야하기 때문
			answer = min(answer,D.front().first);
	}
    return answer;
}
#include <vector>

using namespace std;

// 2024 PCCP 기출문제 1번 붕대감기(Lv.1) 문제이며 (https://school.programmers.co.kr/learn/courses/30/lessons/250137)
// 몬스터의 마지막 공격 직후(이하 end)의 체력을 출력하는 문제이다.
// 매개변수로 힐링스킬에 대한 정보를 가진 배열(이하 bandage)과 최대체력, 몬스터 공격시기와 데미지를 포함하고 있는 배열(이하 attacks)이며
// end 직후 체력을 출력해야하므로 for문과 완전탐색을 이용하여 문제를 풀이하였다.
// 이떄 attacks의 최대길이는 100개로 제한되어있으므로 완전탐색을 이용하여도 무방하다.

typedef vector<vector<int>>::iterator it;

int solution(vector<int> bandage, int health, vector<vector<int>> attacks) {
	int hp = health; // 현재체력
	int cooldown = bandage[0], heal = bandage[1], plus_heal = bandage[2]; //시전시간, 회복량, 추가 회복량 초기화
	int PH_count = 0; // 회복스킬을 몇번 사용했는지 확인하는 변수
	int end = (*(attacks.end()-1))[0];
	// 몬스터의 마지막 공격 시기(이떄, 문제 조건에 attacks는 시전시간을 기준으로 오름차순으로 정렬되어있기 떄문에 마지막index의 정보를 참조)
	it Attacks = attacks.begin(); // 몬스터 공격주기를 시작부터 끝까지 탐색할 iterator
	int monster_time = (*Attacks)[0], damege = (*Attacks)[1]; // 현재 몬스터의 공격주기 및 데미지 저장
	for(int time = 0;time <= end; time++) // end까지 반복
	{
		if(time == monster_time) // 만약 지금이 몬스터의 공격주기라면
		{
			hp -= damege; // 현재체력에서 데미지를 감소
			if(hp < 1) // 현재체력이 0이하라면 -1
				return -1;
			if(time != end) // core dumped 방지를 위한 조건문
			{
				attacks.erase(Attacks); // 다음 공격주기로 이동
				monster_time = (*Attacks)[0]; // 이동한 공격주기 대입
				damege = (*Attacks)[1]; // 이동한 공격주기에 대한 데미지 대입
				PH_count = 0; // 공격 받았기때문에 0
			}
		}
		else // 지금이 몬스터의 공격주기가 아니라면
		{
			hp += heal; // 현재체력에 회복량 추가
			PH_count++; // 회복스킬이 사용되었기때문에 1 추가
			if(PH_count == cooldown) // 만약 회복스킬이 연속으로 cooldown만큼 성공했다면
			{
				hp += plus_heal; // 추가회복량만큼 더하기
				PH_count = 0; // 추가회복을 했기때문에 0
			}
			if(hp > health) // 만약 현재체력이 최대체력을 넘어간다면
				hp = health; // 현재체력을 최대체력으로 재설정
		}
	}
    return hp;
}
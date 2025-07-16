// vector iterator와 forward_list iterator의 차이점을 알아보는 연습 문제
// F1 그랑프리 수상자 명단을 iterator를 사용하여 원하는 정보를 검색해보자.

#include <iostream>
#include <vector>
#include <forward_list>
using namespace std;

int main() {
	// vector에 수상자 명단 초기화
	vector<string> vec = {
		"Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg",
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"
	};

	auto it = vec.begin(); // O(1)
	cout << "가장 최근 우승자 : " << *it << endl;

	it += 8; // O(1)
	cout << "8년 전 우승자 : " << *it << endl;

	advance(it, -3); // O(1)
	cout << "그 후 3년 뒤 우승자 : " << *it << endl;

	// forward_list에 수상자 명단 초기화
	forward_list<string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	cout << "가장 최근 우승자 : " << *it1 << endl;

	advance(it1, 5); // O(n)
	cout << "5년 전 우승자 : " << *it1 << endl;

	// forward_list는 순방향으로만 이동 가능하므로
	// 아래 코드는 에러 발생
	// advance(it1, -2);
	// it1 += 2도 에러 발생 (+= 가 정의되어 있지 않음)
}
// 조건부 원소 삭제를 연습하는 문제
// 선거 기간에 일부 시민들의 정보를 이용하여 선거권이 없는 사람을 가려내보자.

#include <iostream>
#include <string>
#include <forward_list>
using namespace std;

// 시민 구조체 정의
struct citizen {
	string name;
	int age;

	// 출력 양식 정의를 위한 << operator overloading, 어차피 이 구조체에서만 쓸 용도이므로 friend 함수로 만들기.
	friend ostream& operator << (ostream& os, const citizen& c) {
		os << "[" << c.name << ", " << c.age << "]";
		return os;
	}
};

int main() {
	// forward_list 초기화
	forward_list<citizen> citizens = {
		{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
	};

	// deep copy로 citizens 복사. 전체 시민들 데이터 한번 더 써야 함.
	auto citizens_copy = citizens;

	// 전체 시민 정보 출력
	cout << "전체 시민들 : ";
	for (const auto& c : citizens) {
		cout << c << " ";
	}
	cout << endl;

	// remove_if를 이용하여 19세 미만은 투표권 없는 사람으로 정의. 조건자 함수 대신 lambda expression 사용
	citizens.remove_if([](const citizen& c) {return c.age < 19;});

	cout << "투표권이 있는 시민들 : ";
	for (const auto& c : citizens) {
		cout << c << " ";
	}
	cout << endl;

	// 내년에 투표권이 생기는 사람을 찾아보자. 즉 나이가 18살인 사람. 18살이 아니면 지워준다.
	citizens_copy.remove_if([](const citizen& c) {return c.age != 18;});

	cout << "내년에 투표권이 생기는 시민들 : ";
	for (const auto& c : citizens_copy) {
		cout << c << " ";
	}
	cout << endl;
}


// ���Ǻ� ���� ������ �����ϴ� ����
// ���� �Ⱓ�� �Ϻ� �ùε��� ������ �̿��Ͽ� ���ű��� ���� ����� ����������.

#include <iostream>
#include <string>
#include <forward_list>
using namespace std;

// �ù� ����ü ����
struct citizen {
	string name;
	int age;

	// ��� ��� ���Ǹ� ���� << operator overloading, ������ �� ����ü������ �� �뵵�̹Ƿ� friend �Լ��� �����.
	friend ostream& operator << (ostream& os, const citizen& c) {
		os << "[" << c.name << ", " << c.age << "]";
		return os;
	}
};

int main() {
	// forward_list �ʱ�ȭ
	forward_list<citizen> citizens = {
		{"Kim", 22}, {"Lee", 25}, {"Park", 18}, {"Jin", 16}
	};

	// deep copy�� citizens ����. ��ü �ùε� ������ �ѹ� �� ��� ��.
	auto citizens_copy = citizens;

	// ��ü �ù� ���� ���
	cout << "��ü �ùε� : ";
	for (const auto& c : citizens) {
		cout << c << " ";
	}
	cout << endl;

	// remove_if�� �̿��Ͽ� 19�� �̸��� ��ǥ�� ���� ������� ����. ������ �Լ� ��� lambda expression ���
	citizens.remove_if([](const citizen& c) {return c.age < 19;});

	cout << "��ǥ���� �ִ� �ùε� : ";
	for (const auto& c : citizens) {
		cout << c << " ";
	}
	cout << endl;

	// ���⿡ ��ǥ���� ����� ����� ã�ƺ���. �� ���̰� 18���� ���. 18���� �ƴϸ� �����ش�.
	citizens_copy.remove_if([](const citizen& c) {return c.age != 18;});

	cout << "���⿡ ��ǥ���� ����� �ùε� : ";
	for (const auto& c : citizens_copy) {
		cout << c << " ";
	}
	cout << endl;
}


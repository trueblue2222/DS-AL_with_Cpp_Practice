// vector iterator�� forward_list iterator�� �������� �˾ƺ��� ���� ����
// F1 �׶����� ������ ����� iterator�� ����Ͽ� ���ϴ� ������ �˻��غ���.

#include <iostream>
#include <vector>
#include <forward_list>
using namespace std;

int main() {
	// vector�� ������ ��� �ʱ�ȭ
	vector<string> vec = {
		"Lewis Hamilton", "Lewis Hamilton", "Nico Roseberg",
		"Sebastian Vettel", "Lewis Hamilton", "Sebastian Vettel",
		"Sebastian Vettel", "Sebastian Vettel", "Fernando Alonso"
	};

	auto it = vec.begin(); // O(1)
	cout << "���� �ֱ� ����� : " << *it << endl;

	it += 8; // O(1)
	cout << "8�� �� ����� : " << *it << endl;

	advance(it, -3); // O(1)
	cout << "�� �� 3�� �� ����� : " << *it << endl;

	// forward_list�� ������ ��� �ʱ�ȭ
	forward_list<string> fwd(vec.begin(), vec.end());

	auto it1 = fwd.begin();
	cout << "���� �ֱ� ����� : " << *it1 << endl;

	advance(it1, 5); // O(n)
	cout << "5�� �� ����� : " << *it1 << endl;

	// forward_list�� ���������θ� �̵� �����ϹǷ�
	// �Ʒ� �ڵ�� ���� �߻�
	// advance(it1, -2);
	// it1 += 2�� ���� �߻� (+= �� ���ǵǾ� ���� ����)
}
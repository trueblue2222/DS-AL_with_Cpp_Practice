// forward_list�� ���� �����ϸ鼭 �� ���� ����� �����ϴ� ����� ���� �����̳� singly_ll �����

#include <iostream>
#include <algorithm>

// singly_ll ������ �ʿ��� ���� ��� Ŭ���� singly_ll_node ����
struct singly_ll_node {
	int data;
	singly_ll_node* next;
};

// singly_ll Ŭ���� ����. �� Ŭ������ ���� singly_ll_node�� ����ϴ� ���� ����Ʈ Ŭ������.
class singly_ll {
public:
	// aliasing
	using node = singly_ll_node;
	using node_ptr = node*;

private:
	node_ptr head;

// std::forward_list Ŭ�������� �ִ� push_front()�� pop_front() �Լ� ����
public:
	void push_front(int val) {
		auto new_node = new node{ val, NULL };
		if (head != NULL) {
			new_node->next = head;
		}
		head = new_node;
	}

	void pop_front() {
		auto first = head;
		if (first != NULL) {
			head = head->next;
			delete first;
		}
	}
// singly_ll Ŭ������ �⺻ iterator�� ����.
	struct singly_ll_iterator {
	private : 
		node_ptr ptr;

	public : 
		// constructor
		singly_ll_iterator(node_ptr p) : ptr(p) {}

		// *�� �̿��� data�� ��ȯ�ϴ� accessor
		int& operator* () {
			return ptr->data;
		}

		// iterator �� ��ü�� ��ȯ�ϴ� get()
		node_ptr get() { return ptr; }

		// ���� ������ ���� ������ ���� ++ operator overloading ����
		singly_ll_iterator& operator++() // ���� ����
		{
			ptr = ptr->next;
			return *this; // ptr->next ��ȯ
		}
		singly_ll_iterator operator++(int) // ���� ����. int�� ���� �Ű������� ���� ����/���� ���� �����ڷνḸ �ǹ�.
		{
			singly_ll_iterator result = *this;
			++(*this);
			return result; // ���� ptr ��ȯ. �ٵ� �Լ� ȣ�� �� ptr�� prt->next�� ����Ű�� ����.
		}
		// �� iterator�� ������ �Ǵ��ϴ� ���� ������ �Լ��� friend�� ����
		friend bool operator == (const singly_ll_iterator& left, const singly_ll_iterator& right) {
			return left.ptr == right.ptr;
		}
		friend bool operator != (const singly_ll_iterator& left, const singly_ll_iterator& right) {
			return left.ptr != right.ptr;
		}
	};
	// singly_ll Ŭ������ ���� iterator�� �̿��Ͽ� begin(), end() �Լ� �߰�. (��ü�� const�϶��� ��쵵 ���� ����)
	singly_ll_iterator begin() { return singly_ll_iterator(head); }
	singly_ll_iterator begin() const { return singly_ll_iterator(head); }
	singly_ll_iterator end() { return singly_ll_iterator(NULL); }
	singly_ll_iterator end() const { return singly_ll_iterator(NULL); }

	// default constructor
	singly_ll() = default;

	// deep copy constructor
	singly_ll(const singly_ll& other) : head(NULL) {
		if (other.head) {
			head = new node{ 0, NULL };
			auto current = head;
			auto it = other.begin();
			while (true) {
				current->data = *it;

				auto temp = it;
				++temp;
				if (temp == other.end()) break;
				
				current->next = new node{ 0, NULL };
				current = current->next;
				it = temp;
			}
		}
	}

	// initializer_list constructor
	singly_ll(const std::initializer_list<int>& ilist) : head(NULL) {
		for (auto it = std::rbegin(ilist); it != std::rend(ilist); it++) {
			push_front(*it);
		}
	}
};

int main() {
	singly_ll sll = { 1, 2, 3 };
	sll.push_front(0);

	std::cout << "ù ��° ����Ʈ : ";
	for (auto i : sll) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	auto sll2 = sll;
	sll2.push_front(-1);
	std::cout << "ù ��° ����Ʈ�� ������ ��, �� �տ� -1�� �߰� : ";
	for (auto i : sll2) {
		std::cout << i << " "; // ��� : -1 0 1 2 3
	}
	std::cout << std::endl;

	std::cout << "deep copy �� ù ��° ����Ʈ : ";
	for (auto i : sll) {
		std::cout << i << " "; // ��� : 0 1 2 3 -> ���� ���� �����Ƿ� sll2�� ��ȭ�� sll�� ���� ����
	}
	std::cout << std::endl;
}
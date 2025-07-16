// forward_list를 직접 구현하면서 더 많은 기능을 제공하는 사용자 정의 컨테이너 singly_ll 만들기

#include <iostream>
#include <algorithm>

// singly_ll 구현에 필요한 단일 노드 클래스 singly_ll_node 정의
struct singly_ll_node {
	int data;
	singly_ll_node* next;
};

// singly_ll 클래스 구현. 이 클래스는 노드로 singly_ll_node를 사용하는 연결 리스트 클래스임.
class singly_ll {
public:
	// aliasing
	using node = singly_ll_node;
	using node_ptr = node*;

private:
	node_ptr head;

// std::forward_list 클래스에도 있는 push_front()와 pop_front() 함수 구현
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
// singly_ll 클래스의 기본 iterator를 구현.
	struct singly_ll_iterator {
	private : 
		node_ptr ptr;

	public : 
		// constructor
		singly_ll_iterator(node_ptr p) : ptr(p) {}

		// *를 이용한 data를 반환하는 accessor
		int& operator* () {
			return ptr->data;
		}

		// iterator 값 자체를 반환하는 get()
		node_ptr get() { return ptr; }

		// 선행 증가와 후행 증가를 위한 ++ operator overloading 구현
		singly_ll_iterator& operator++() // 선행 증가
		{
			ptr = ptr->next;
			return *this; // ptr->next 반환
		}
		singly_ll_iterator operator++(int) // 후행 증가. int는 더미 매개변수로 단지 선행/후행 증가 구분자로써만 의미.
		{
			singly_ll_iterator result = *this;
			++(*this);
			return result; // 기존 ptr 반환. 근데 함수 호출 후 ptr는 prt->next를 가리키고 있음.
		}
		// 두 iterator가 같은지 판단하는 관계 연산자 함수를 friend로 정의
		friend bool operator == (const singly_ll_iterator& left, const singly_ll_iterator& right) {
			return left.ptr == right.ptr;
		}
		friend bool operator != (const singly_ll_iterator& left, const singly_ll_iterator& right) {
			return left.ptr != right.ptr;
		}
	};
	// singly_ll 클래스를 위한 iterator를 이용하여 begin(), end() 함수 추가. (객체가 const일때의 경우도 같이 구현)
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

	std::cout << "첫 번째 리스트 : ";
	for (auto i : sll) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	auto sll2 = sll;
	sll2.push_front(-1);
	std::cout << "첫 번째 리스트를 복사한 후, 맨 앞에 -1을 추가 : ";
	for (auto i : sll2) {
		std::cout << i << " "; // 출력 : -1 0 1 2 3
	}
	std::cout << std::endl;

	std::cout << "deep copy 후 첫 번째 리스트 : ";
	for (auto i : sll) {
		std::cout << i << " "; // 출력 : 0 1 2 3 -> 깊은 복사 했으므로 sll2의 변화에 sll은 영향 없음
	}
	std::cout << std::endl;
}
// ���� �迭�� ���� ������ �� �л� ������ �����ϴ� ������ ���� ���α׷� ������

#include <iostream>
#include <sstream>
#include <algorithm>

// dynamic_array��� �̸��� ���ø� Ŭ���� �ۼ�. �ֿ� ������ ���� �迭�� ����Ű�� data, �迭�� ũ�� n
template <typename T> class dynamic_array {
	T* data;
	size_t n;
	// �迭 ũ�⸦ ���ڷ� �޴� constructor�� copy constructor ����
public:
	dynamic_array(int n) {
		this->n = n;
		data = new T[n];
	}
	dynamic_array(const dynamic_array<T>& other) {
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++) {
			data[i] = other[i];
		}
	}
	// ��� �����Ϳ� ���� �����ϱ� ���� [] �����ڿ� at() �Լ� ����. const ��ü�� ���� �� �����Ƿ� overloading���� ����
	T& operator[] (int index) { return data[index]; }
	const T& operator [] (int index) { return data[index]; }
	T& at(int index) {
		if (index < n) return data[index];
		throw "Index out of range";
	}
	// �迭 ũ�� ��ȯ�ϴ� size() �Լ�, destructor ����. destructor������ �޸� ���� ������ ���� �޸� ����.
	size_t size() const {
		return n;
	}
	~dynamic_array() {
		delete[] data;
	}
	// dynamic_array�� �迭 ���Ҹ� ��ȸ�� �� ����� iterator ���� �Լ� ����(begin(), end())
	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() { return data + n; }
	// �� �迭�� �ϳ��� ��ġ�� + ������ ����. friend�� ���� => friend�� �����ϴ� ����? class�� private ��� ���� ����
	friend dynamic_array<T> operator + (const dynamic_array<T> arr1, dynamic_array<T> arr2) {
		dynamic_array<T> arr(arr1.size() + arr2.size());
		std::copy(arr1.begin(), arr1.end(), arr.begin()); // �� �κ� arr1�� copy�� ä���
		std::copy(arr2.begin(), arr2.end(), arr.begin() + arr1.size()); // arr1 ä�� �κ��� ������ arr2�� copy�� ä���

		return arr;
	}
	// �迭�� ����� ��� �����͸� ���ڿ��� ��ȯ�ϴ� to_string() ��� �Լ� ����.
	// ��ǥ(", ")�� ���ڿ� ����
	std::string to_string(const std::string& sep = ", ") {
		if (n == 0) return "";

		std::ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++) {
			os << sep << data[i];
		}

		return os.str();
	}
};

// �л� ������ ������ ����ü student ����. �л��� �̸� name�� ���� ������ ��� �ִ� standard ��� ���� ����.
struct student {
	std::string name;
	int standard;
};
// << �����ڸ� �̿��� ǥ�� ��� ����
std::ostream& operator << (std::ostream& os, const student& s) {
	os << "[" << s.name << ", " << s.standard << "]";
	return os;
}

// main �Լ� ����
int main(void) {
	int nStudents;
	std::cout << "1�� �л� ���� �Է��ϼ���: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++) {
		std::string name;
		int standard;
		std::cout << i + 1 << "��° �л� �̸��� ���̸� �Է��ϼ���: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard }; // class[i].name = name; class[i].standard = standard; �� ����	
	}
	// �迭���� ū �ε����� �л��� ������ �� ���� ó�� �׽�Ʈ
	try {
		// class1[nStudents] = students {"John", 8}; 
		// �ش� �� ���� �� ���� ���� ��Ÿ�� ����. �ε��� ���ٿ��� ���� ���� ó�� ���س���.
		class1.at(nStudents) = student{ "John", 8 };
	}
	catch (...) {
		std::cout << "���� �߻�!" << std::endl;
	}
	// deep copy
	auto class2 = class1;
	std::cout << "1���� �����Ͽ� 2�� ����: " << class2.to_string() << std::endl;

	// �� �б��� ���� ���ο� �б� ����
	auto class3 = class1 + class2;
	std::cout << "1�ݰ� 2���� ���� 3�� ����: " << class3.to_string() << std::endl;

	return 0;
}
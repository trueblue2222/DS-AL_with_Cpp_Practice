// 동적 배열을 직접 구현한 후 학생 정보를 관리하는 간단한 응용 프로그램 만들어보기

#include <iostream>
#include <sstream>
#include <algorithm>

// dynamic_array라는 이름의 템플릿 클래스 작성. 주요 변수는 동적 배열을 가리키는 data, 배열의 크기 n
template <typename T> class dynamic_array {
	T* data;
	size_t n;
	// 배열 크기를 인자로 받는 constructor와 copy constructor 생성
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
	// 멤버 데이터에 직접 접근하기 위한 [] 연산자와 at() 함수 정의. const 객체도 있을 수 있으므로 overloading으로 설계
	T& operator[] (int index) { return data[index]; }
	const T& operator [] (int index) { return data[index]; }
	T& at(int index) {
		if (index < n) return data[index];
		throw "Index out of range";
	}
	// 배열 크기 반환하는 size() 함수, destructor 구현. destructor에서는 메모리 누수 방지를 위해 메모리 해제.
	size_t size() const {
		return n;
	}
	~dynamic_array() {
		delete[] data;
	}
	// dynamic_array의 배열 원소를 순회할 때 사용할 iterator 관련 함수 정의(begin(), end())
	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() { return data + n; }
	// 두 배열을 하나로 합치는 + 연산자 정의. friend로 선언 => friend로 선언하는 이유? class의 private 멤버 변수 접근
	friend dynamic_array<T> operator + (const dynamic_array<T> arr1, dynamic_array<T> arr2) {
		dynamic_array<T> arr(arr1.size() + arr2.size());
		std::copy(arr1.begin(), arr1.end(), arr.begin()); // 앞 부분 arr1로 copy해 채우기
		std::copy(arr2.begin(), arr2.end(), arr.begin() + arr1.size()); // arr1 채운 부분의 나머지 arr2로 copy해 채우기

		return arr;
	}
	// 배열에 저장된 모든 데이터를 문자열로 반환하는 to_string() 멤버 함수 선언.
	// 쉼표(", ")로 문자열 구분
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

// 학생 정보를 저장할 구조체 student 정의. 학생의 이름 name과 나이 정보를 담고 있는 standard 멤버 변수 선언.
struct student {
	std::string name;
	int standard;
};
// << 연산자를 이용한 표준 출력 구현
std::ostream& operator << (std::ostream& os, const student& s) {
	os << "[" << s.name << ", " << s.standard << "]";
	return os;
}

// main 함수 구현
int main(void) {
	int nStudents;
	std::cout << "1반 학생 수를 입력하세요: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++) {
		std::string name;
		int standard;
		std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		std::cin >> name >> standard;
		class1[i] = student{ name, standard }; // class[i].name = name; class[i].standard = standard; 와 동일	
	}
	// 배열보다 큰 인덱스의 학생에 접근할 때 예외 처리 테스트
	try {
		// class1[nStudents] = students {"John", 8}; 
		// 해당 줄 있을 시 실행 도중 런타임 오류. 인덱스 접근에는 따로 예외 처리 안해놨음.
		class1.at(nStudents) = student{ "John", 8 };
	}
	catch (...) {
		std::cout << "예외 발생!" << std::endl;
	}
	// deep copy
	auto class2 = class1;
	std::cout << "1반을 복사하여 2반 생성: " << class2.to_string() << std::endl;

	// 두 학급을 합쳐 새로운 학급 생성
	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << std::endl;

	return 0;
}

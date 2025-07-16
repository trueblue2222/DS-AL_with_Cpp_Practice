// 다양한 타입의 데이터 여러 개를 인자로 받아 공통 타입으로 변환하는 함수 만들기

#include <array>
#include <iostream>
#include <type_traits>

// 컨테이너 생성하는 build_array() 함수 선언. array 반환하고 임의 개수의 매개변수 받을 수 있게 가변 템플릿 사용
// array를 사용하기 위해 원소의 타입 : common_type, 후행 리턴 타입을 사용.
// 가변 템플릿을 사용하면서 쓰는 문법들이 너무 어려움. universal reference, common_type 이런 거 좀 더 봐야할듯
template<typename ... Args>
auto build_array(Args&&... args) -> std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
	using commonType = typename std::common_type<Args...>::type;
	return { std::forward<commonType>((Args&&)args)... };
}

int main()
{
	auto data = build_array(1, 0u, 'a', 3.2f, false);

	for (auto i : data)
		std::cout << i << " ";
	std::cout << std::endl;

	// string은 const char* 형태이므로 하나의 공통 타입으로 변환할 수 없음
	// 따라서 아래 코드는 에러가 발생
	// auto data2 = build_array(1, "Packt", 2.0);
}


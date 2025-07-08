// �پ��� Ÿ���� ������ ���� ���� ���ڷ� �޾� ���� Ÿ������ ��ȯ�ϴ� �Լ� �����

#include <array>
#include <iostream>
#include <type_traits>

// �����̳� �����ϴ� build_array() �Լ� ����. array ��ȯ�ϰ� ���� ������ �Ű����� ���� �� �ְ� ���� ���ø� ���
// array�� ����ϱ� ���� ������ Ÿ�� : common_type, ���� ���� Ÿ���� ���.
// ���� ���ø��� ����ϸ鼭 ���� �������� �ʹ� �����. universal reference, common_type �̷� �� �� �� �����ҵ�
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

	// string�� const char* �����̹Ƿ� �ϳ��� ���� Ÿ������ ��ȯ�� �� ����
	// ���� �Ʒ� �ڵ�� ������ �߻�
	// auto data2 = build_array(1, "Packt", 2.0);
}


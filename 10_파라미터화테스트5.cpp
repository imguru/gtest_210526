
// 데이터셋 조합도 가능합니다.
enum Color {
	BLACK, RED, WHITE,
};
const char* animals[] = { "Cat", "Dog" };
const int ages[] = { 10, 20, 30 };

#include <gtest/gtest.h>

// 조합 
//  - InputDataType => std::tuple

class AnimalTest : public testing::TestWithParam<std::tuple<const char*, Color, int>> {
};

using testing::Values;
using testing::ValuesIn;
using testing::Combine;  // !!

INSTANTIATE_TEST_SUITE_P(AnimalVariations, AnimalTest,
	Combine(ValuesIn(animals), Values(BLACK, RED, WHITE), ValuesIn(ages)));

TEST_P(AnimalTest, AnimalLook) {
	// std::tuple<const char*, Color> data = GetParam();
	auto data = GetParam();
	
	const char* animal = std::get<0>(data);
	Color color = std::get<1>(data);
	int age = std::get<2>(data);

	printf("%s(%d) - %d\n", animal, color, age);
}

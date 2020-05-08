#include <cstdio>

#include "tests.h"
#include "dynamic_array.hpp"
#include "array_sequence.hpp"
#include "list.hpp"
#include "list_sequence.hpp"


void test_dynamic_array_basics()
{
	// const-val constructor
	DynamicArray<int> array(5, 10);
	for(size_t i = 0; i < array.size(); ++i){
		assert_equal(array.get(i), 10);
	}

	// copy constructor and operator==
	DynamicArray<int> array2 = array;
	assert_equal(array, array2);


	//array and iter constructors
	int a[] = {1, 2, 3, 4, 5};
	array = DynamicArray<int>(a, 5);
	for(size_t i = 0; i < array.size(); ++i){
		assert_equal(array.get(i), i+1);
	}

	array2 = DynamicArray<int>(a, a+5);
	assert_equal(array, array2);
}

void test_dynamic_array_operations()
{
	int a[10];
	DynamicArray<int> array;
	for(size_t i = 0; i < 10; ++i){
		array.push_back(i);
		a[i] = static_cast<int>(i);
	}
	assert_equal(array, DynamicArray<int>(a, 10, true));

	int a2[] = {0, 1, 2, 3, 6, 7, 8, 9};
	DynamicArray<int> array2 = array;
	array2.erase(4, 6);
	assert_equal(array2, DynamicArray<int>(a2, 8, true));

	array2.clear();
	assert_equal(array2, DynamicArray<int>());
}


int main(){

	TestFunction<void> functions[] = {
		{"dynamic_array_basics", test_dynamic_array_basics},
		{"dynamic_array_operations", test_dynamic_array_operations}
	};
	const unsigned short n = sizeof(functions) / sizeof (TestFunction<Error>);
	unsigned short errors = 0;

	for(unsigned short i = 0; i < n; ++i){
		printf("[%d/%d] Test %s: ", i+1, n, functions[i].name);

		try {
			functions[i]();
			printf("OK");
		}
		catch (std::exception &ex) {
			printf("ERROR!\n");
			printf("%6c%s", ' ', ex.what());
			++errors;
		}


		printf("\n");
	}

	printf("\n\nTotal: tests: %d, errors: %d\n", n, errors);
	if(errors == 0)
		printf("ALL OK\n");
}



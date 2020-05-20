#ifndef TEST_H
#define TEST_H

#include <stdexcept>

template<typename T1, typename T2>
void assert_equal(const T1 &a, const T2 &b, const char* msg = "Not equal in assert_equal!"){
	if(a != b){
		throw std::logic_error(msg);
	}
}


typedef enum {
	OK,
	ERROR
} Error;

template<typename FRet, typename ...FArgs>
class TestFunction {
public:
	FRet operator() (FArgs... args) {return function(args...);}

	const char *name;
	FRet (*const function)(FArgs...);
};

template<typename FRet, typename ...FArgs>
void run_tests(TestFunction<FRet, FArgs...> functions[], size_t n)
{
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

#endif // TEST_H

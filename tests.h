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


#endif // TEST_H

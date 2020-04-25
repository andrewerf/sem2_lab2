#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstdlib>

auto stable_allocator(size_t allocate_count){
	return [allocate_count](size_t current_count){
		return current_count + allocate_count;
	};
}


#endif // ALLOCATOR_HPP

#ifndef LEM_MAC_HPP
#define LEM_MAC_HPP


#define Lem_Iterate(CONTAINER,ItrName)\
	for( __typeof__(CONTAINER.begin()) ItrName = CONTAINER.begin();\
		ItrName!=CONTAINER.end(); ItrName++ )

#define Lem_IterateCount(CONTAINER,ItrName,nMove)\
	for( __typeof__(CONTAINER.begin()) ItrName = CONTAINER.begin();\
		ItrName!=CONTAINER.end(); ItrName++, nMove++ )

#define LEM_VARGS_(_10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N 
#define LEM_VARGS(...) LEM_VARGS_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define LEM_CONCAT_(a, b) a##b
#define LEM_CONCAT(a, b) LEM_CONCAT_(a, b)

template <typename T>
inline T Lem_ItrPrev( T itr ){ T ret = itr; return --ret; }

#endif
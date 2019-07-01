#pragma once

// http://b.atch.se/posts/constexpr-counter/#solution

#define DefineCompileTimeCounter(name_)										\
template<int N>																\
struct name_																\
{																			\
	friend constexpr int adl_func(name_<N>);								\
};																			\
																			\
template<int N>																\
struct name_##Writer														\
{																			\
	friend constexpr int adl_func(name_<N>)									\
	{																		\
		return N;															\
	}																		\
																			\
	static constexpr int Value = N;											\
};																			\
																			\
template<int N, class = char[noexcept(adl_func(name_<N>())) ? +1 : -1]>		\
int constexpr name_##Reader(int, name_<N>)									\
{																			\
	return N;																\
}																			\
																			\
template<int N>																\
int constexpr name_##Reader(float, name_<N>,								\
	int R = name_##Reader(0, name_<N - 1>()))								\
{																			\
	return R;																\
}																			\
																			\
int constexpr name_##Reader(float, name_<0>)								\
{																			\
	return 0;																\
}																			\
																			\
template<int N = 1, int C = name_##Reader(0, name_<32>())>					\
int constexpr name_##Increment(int R = name_##Writer<C + N>::Value)			\
{																			\
	return R;																\
}																			\
template<int N = 1, int C = name_##Reader(0, name_<32>())>					\
int constexpr name_##Next(int R = name_##Writer<C + N>::Value)				\
{																			\
	return R;																\
}
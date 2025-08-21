#pragma once
#ifndef __FILE_Detail_CP_CBool_Hpp
#define __FILE_Detail_CP_CBool_Hpp

#define Operator(name,operator,closer)\
template<typename First, typename Second>	bool name(const First& first, const Second& second)	{ return closer(first) operator closer(second); }\
template<typename First, typename... Args>	bool name(const First& first, const Args&... args)	{ return closer(first) operator name(args...);}
#define TrueCloser(x) (!!x)

Operator(And, &&, TrueCloser);
Operator(Or, || , TrueCloser);

#undef Operator
#undef TrueCloser

namespace Internal
{
	template<bool First, bool... Value> class CAnd_t;
	template<bool First, bool... Value> class COr_t;

	template<> class CAnd_t<true> : public std::true_type {};
	template<> class CAnd_t<false> : public std::false_type {};
	template<bool... Value> class CAnd_t<true, Value...> : public CAnd_t<Value...> {};
	template<bool... Value> class CAnd_t<false, Value...> : public std::false_type {};

	template<> class COr_t<true> : public std::true_type {};
	template<> class COr_t<false> : public std::false_type {};
	template<bool... Value> class COr_t<true, Value...> : public std::true_type {};
	template<bool... Value> class COr_t<false, Value...> : public COr_t<Value...> {};
}

template<bool First, bool... Value> constexpr bool CAnd = Internal::CAnd_t<First, Value...>::value;
template<bool First, bool... Value> constexpr bool COr  = Internal::COr_t<First, Value...>::value;
template<bool First, bool... Value> constexpr bool CXor = CAnd<First, Value...> != COr<First, Value...>;
template<bool Value>				constexpr bool CNot = false == Value;

#endif // !__FILE_Detail_CP_CBool_Hpp

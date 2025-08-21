#pragma once
#ifndef __FILE_Detail_CP_Arithmetic_Hpp
#define __FILE_Detail_CP_Arithmetic_Hpp

#include "detail/CP/CHash.hpp"

namespace Internal
{
	/**
	* Traits class which tests if a type is arithmetic.
	*/
	template <typename T>
	struct TIsArithmeticTool
	{
		constexpr static bool Value = false;
	};

	template <> struct TIsArithmeticTool<float> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<double> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<long double> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<uint8_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<uint16_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<uint32_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<uint64_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<int8_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<int16_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<int32_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<int64_t> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<long> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<unsigned long> { constexpr static bool Value = true; };
	template <> struct TIsArithmeticTool<bool> { constexpr static bool Value = true; };

	template <typename T> struct TIsArithmeticTool<const          T> { constexpr static bool Value = TIsArithmeticTool<T>::Value; };
	template <typename T> struct TIsArithmeticTool<      volatile T> { constexpr static bool Value = TIsArithmeticTool<T>::Value; };
	template <typename T> struct TIsArithmeticTool<const volatile T> { constexpr static bool Value = TIsArithmeticTool<T>::Value; };
}

template <typename T> constexpr bool TIsArithmetic = Internal::TIsArithmeticTool<T>::Value;

namespace Internal
{
	/**
	 * Traits class which tests if a type is a signed integral type.
	 */
	template <typename T>
	struct TIsSignedTool
	{
		constexpr static bool Value = false;
	};

	template <> struct TIsSignedTool<int8_t>  { constexpr static bool Value = true; };
	template <> struct TIsSignedTool<int16_t> { constexpr static bool Value = true; };
	template <> struct TIsSignedTool<int32_t> { constexpr static bool Value = true; };
	template <> struct TIsSignedTool<int64_t> { constexpr static bool Value = true; };

	template <typename T> struct TIsSignedTool<const          T> { constexpr static bool Value = TIsSignedTool<T>::Value; };
	template <typename T> struct TIsSignedTool<      volatile T> { constexpr static bool Value = TIsSignedTool<T>::Value; };
	template <typename T> struct TIsSignedTool<const volatile T> { constexpr static bool Value = TIsSignedTool<T>::Value; };
}

template <typename T> constexpr bool TIsSigned = Internal::TIsSignedTool<T>::Value;

#endif // !__FILE_Detail_CP_Arithmetic_Hpp

#pragma once
#ifndef __FILE_Detail_CP_Arithmetic_Hpp
#define __FILE_Detail_CP_Arithmetic_Hpp

#include "CHash.hpp"

#pragma region TIsArithmetic

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

#pragma endregion

#pragma region TIsSigned

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

#pragma endregion

#pragma region TIsIntegral

namespace Internal
{
	/**
	* Traits class which tests if a type is integral.
	*/
	template <typename T>
	struct TIsIntegralTool
	{
		constexpr static bool Value = false;
	};

	template <> struct TIsIntegralTool<         bool> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         char> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<signed   char> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<unsigned char> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         char16_t> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         char32_t> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         wchar_t> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         short> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<unsigned short> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         int> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<unsigned int> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         long> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<unsigned long> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<         long long> { constexpr static bool Value = true; };
	template <> struct TIsIntegralTool<unsigned long long> { constexpr static bool Value = true; };

	template <typename T> struct TIsIntegralTool<const          T> { constexpr static bool Value = TIsIntegralTool<T>::Value; };
	template <typename T> struct TIsIntegralTool<      volatile T> { constexpr static bool Value = TIsIntegralTool<T>::Value; };
	template <typename T> struct TIsIntegralTool<const volatile T> { constexpr static bool Value = TIsIntegralTool<T>::Value; };
}

template <typename T> constexpr bool TIsIntegral = Internal::TIsIntegralTool<T>::Value;

#pragma endregion

#pragma region TIsFloatingPoint

///////////////////////////////
// TIsFloatingPoint

namespace Internal
{
	/**
	 * Traits class which tests if a type is floating point.
	 */
	template <typename T>
	struct TIsFloatingPointTool
	{
		constexpr static bool Value = false;
	};

	template <> struct TIsFloatingPointTool<float>       { constexpr static bool Value = true; };
	template <> struct TIsFloatingPointTool<double>      { constexpr static bool Value = true; };
	template <> struct TIsFloatingPointTool<long double> { constexpr static bool Value = true; };

	template <typename T> struct TIsFloatingPointTool<const          T> { constexpr static bool Value = TIsFloatingPointTool<T>::Value; };
	template <typename T> struct TIsFloatingPointTool<      volatile T> { constexpr static bool Value = TIsFloatingPointTool<T>::Value; };
	template <typename T> struct TIsFloatingPointTool<const volatile T> { constexpr static bool Value = TIsFloatingPointTool<T>::Value; };
}

template <typename T> constexpr bool TIsFloatingPoint = Internal::TIsFloatingPointTool<T>::Value;

// TIsFloatingPoint
//////////////////////////////////

#pragma endregion

#pragma region About Align

///////////////////////
// About Align Toolkit

#pragma region Align

/**
 * Aligns a value to the nearest higher multiple of 'Alignment', which must be a power of two.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return The value aligned up to the specified alignment.
 */
template <typename T>
FORCEINLINE constexpr T CAlign(T Val, uint64_t Alignment)
{
	return (T)(((uint64_t)Val + Alignment - 1) & ~(Alignment - 1));
}

/**
 * Aligns a value to the nearest higher multiple of 'Alignment', which must be a power of two.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return The value aligned up to the specified alignment.
 */
template <typename T>
FORCEINLINE T Align(T Val, uint64_t Alignment)
{
	return (T)(((uint64_t)Val + Alignment - 1) & ~(Alignment - 1));
}

#pragma endregion

#pragma region AlignDown

/**
 * Aligns a value to the nearest lower multiple of 'Alignment', which must be a power of two.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return The value aligned down to the specified alignment.
 */
template <typename T>
FORCEINLINE constexpr T CAlignDown(T Val, uint64_t Alignment)
{
	return (T)(((uint64_t)Val) & ~(Alignment - 1));
}

/**
 * Aligns a value to the nearest lower multiple of 'Alignment', which must be a power of two.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return The value aligned down to the specified alignment.
 */
template <typename T>
FORCEINLINE T AlignDown(T Val, uint64_t Alignment)
{
	return (T)(((uint64_t)Val) & ~(Alignment - 1));
}

#pragma endregion

#pragma region IsAligned

/**
 * Checks if a pointer is aligned to the specified alignment.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return true if the pointer is aligned to the specified alignment, false otherwise.
 */
template <typename T>
FORCEINLINE constexpr bool CIsAligned(T Val, uint64_t Alignment)
{
	return !((uint64_t)Val & (Alignment - 1));
}

/**
 * Checks if a pointer is aligned to the specified alignment.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, must be a power of two.
 *
 * @return true if the pointer is aligned to the specified alignment, false otherwise.
 */
template <typename T>
FORCEINLINE bool IsAligned(T Val, uint64_t Alignment)
{
	return !((uint64_t)Val & (Alignment - 1));
}

#pragma endregion

#pragma region AlignArbitrary

/**
 * Aligns a value to the nearest higher multiple of 'Alignment'.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, can be any arbitrary value.
 *
 * @return The value aligned up to the specified alignment.
 */
template <typename T>
FORCEINLINE constexpr T CAlignArbitrary(T Val, uint64_t Alignment)
{
	return (T)((((uint64_t)Val + Alignment - 1) / Alignment) * Alignment);
}

/**
 * Aligns a value to the nearest higher multiple of 'Alignment'.
 *
 * @param  Val        The value to align.
 * @param  Alignment  The alignment value, can be any arbitrary value.
 *
 * @return The value aligned up to the specified alignment.
 */
template <typename T>
FORCEINLINE T AlignArbitrary(T Val, uint64_t Alignment)
{
	return (T)((((uint64_t)Val + Alignment - 1) / Alignment) * Alignment);
}

#pragma endregion

// Align Toolkit
////////////////////////

#pragma endregion

#pragma region About Functors

#pragma region Less

///////////////////
// Less

/**
 * Binary predicate class for sorting elements in order.  Assumes < operator is defined for the template type.
 * Forward declaration exists in ContainersFwd.h
 *
 * See: http://en.cppreference.com/w/cpp/utility/functional/less
 */
struct TLess
{
	template <typename T, typename U>
	FORCEINLINE bool operator()(const T& A, const U& B) const
	{
		return A < B;
	}
};

// Less
////////////////////

#pragma endregion

#pragma region Greater

////////////////////////
// Greater

/**
 * Binary predicate class for sorting elements in reverse order.  Assumes < operator is defined for the template type.
 *
 * See: http://en.cppreference.com/w/cpp/utility/functional/greater
 */
struct TGreater
{
	template <typename T, typename U>
	FORCEINLINE bool operator()(const T& A, const U& B) const
	{
		return B < A;
	}
};

// Greater
//////////////////////////

#pragma endregion

#pragma region EqualTo

/////////////////////////////
// EqualTo

/**
 * Binary predicate class for performing equality comparisons.
 *
 * Uses operator== when available.
 *
 * See: https://en.cppreference.com/w/cpp/utility/functional/equal_to
 */
struct TEqualTo
{
	template <typename T, typename U>
	constexpr auto operator()(const T& Lhs, const U& Rhs) const -> decltype(Lhs == Rhs)
	{
		return Lhs == Rhs;
	}
};

// EqualTo
/////////////////////////////

#pragma endregion

#pragma region IdentityFunctor

/////////////////////////////
// IdentityFunctor

/**
 * A functor which returns whatever is passed to it.  Mainly used for generic composition.
 */
struct TIdentityFunctor
{
	template <typename T>
	FORCEINLINE T&& operator()(T&& Val) const
	{
		return (T&&)Val;
	}
};

// IdentityFunctor
///////////////////////////////

#pragma endregion

#pragma endregion

#pragma region IntegralConstant

///////////////////////////////
// IntegralConstant

/**
 * Defines a value metafunction of the given Value.
 */
template <typename T, T Val>
struct TIntegralConstant
{
	static constexpr T Value = Val;

	constexpr operator T() const
	{
		return Value;
	}
};

// IntegralConstant
///////////////////////////////

#pragma endregion

#endif // !__FILE_Detail_CP_Arithmetic_Hpp

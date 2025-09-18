#pragma once
#ifndef __FILE_Detail_CP_Typen_Hpp
#define __FILE_Detail_CP_Typen_Hpp

#include "CHash.hpp"

#pragma region TIdentity

////////////////////////
// TIdentity

/**
 * Returns the same type passed to it.  This is useful in a few cases, but mainly for inhibiting template argument deduction in function arguments, e.g.:
 *
 * template <typename T>
 * void Func1(T Val); // Can be called like Func(123) or Func<int>(123);
 *
 * template <typename T>
 * void Func2(typename TIdentity<T>::Type Val); // Must be called like Func<int>(123)
 */
template <typename T>
struct TIdentity
{
	typedef T Type;
};

// TIdentity
//////////////////////////

#pragma endregion

template <typename Base, typename Derived> constexpr bool TIsBaseOf = std::is_base_of_v<Base, Derived>;

#pragma region TAreSame

/////////////////////////
// TAreSame

namespace Internal
{
	template <typename A, typename B>  struct TAreSameTool { static constexpr bool Value = false; };
	template <typename A            >  struct TAreSameTool<A,A> { static constexpr bool Value = true; };
}

template <typename A, typename B> constexpr bool TAreSame = Internal::TAreSameTool<A, B>::Value;

// TAreSame
////////////////////////

#pragma endregion

#pragma region Conditional Type

///////////////////////////////
// About Conditional

namespace Internal
{
	/** Chooses between two different classes based on a boolean. */
	template<bool Predicate, typename TrueClass, typename FalseClass>
	class TChooseClass;

	template<typename TrueClass, typename FalseClass>
	class TChooseClass<true, TrueClass, FalseClass>
	{
	public:
		typedef TrueClass Result;
	};

	template<typename TrueClass, typename FalseClass>
	class TChooseClass<false, TrueClass, FalseClass>
	{
	public:
		typedef FalseClass Result;
	};


	template<typename IndexType, IndexType Index, typename... Types> struct TConditionalTool
	{

	};
	template<int Index, typename First, typename... Types>
	struct TConditionalTool<int, Index, First, Types...>
	{
		using Type = typename TConditionalTool<int, Index - 1, Types...>::Type;
	};
	template<typename First, typename... Types>
	struct TConditionalTool<int, 0, First, Types...>
	{
		using Type = First;
	};
	template<typename First>
	struct TConditionalTool<int, 0, First>
	{
		using Type = First;
	};
	template<bool Pr, typename First, typename Second>
	struct TConditionalTool<bool, Pr, First, Second>
	{
		using Type = typename TChooseClass<Pr, First, Second>::Result;
	};
}

template<bool Pr, typename First, typename Second> using TChoose = typename Internal::TConditionalTool<bool, Pr, First, Second>::Type;
template<int Index, typename... Types> using TConditional = typename Internal::TConditionalTool<int, Index, Types...>::Type;

// Conditional
///////////////////////////////

#pragma endregion

template <typename T> constexpr bool TIsPointer  = std::is_pointer_v<T>;
template <typename T> constexpr bool TIsConst  = std::is_const_v<T>;
template <typename T> constexpr bool TIsVolatile  = std::is_volatile_v<T>;
template <typename T> constexpr bool TIsRef  = std::is_reference_v<T>;
template <typename T> constexpr bool TIsFunc  = std::is_function_v<T>;
template <typename T> constexpr bool TIsLR = std::is_lvalue_reference_v<T>;
template <typename T> constexpr bool TIsRR = std::is_rvalue_reference_v<T>;
template <typename T> constexpr bool TIsCV = TIsConst<T> && TIsVolatile<T>;
template <typename T> constexpr bool TIsIt = TIsPointer<T> || TIsLR<decltype(*std::declval<T>())>;
template <typename T> constexpr bool TIsVoid = TAreSame<void, T>;
template <typename T> constexpr bool TIsVirtual = std::has_virtual_destructor_v<T>;
template <typename T> constexpr bool TIsPolymorphic = std::is_polymorphic_v<T>;
template <typename T> constexpr bool TIsAbstract = std::is_abstract_v<T>;
template <typename T> constexpr bool TIsClass = std::is_class_v<T>;
template <typename T> constexpr bool TIsPOD = std::is_pod_v<T>;
template <typename T, typename C = char> constexpr bool TIsCStr = TAreSame<T, const C*> && TAreSame<T, C*>;
template <typename T, typename... Args> constexpr bool TIsConstructible = std::is_constructible_v<T, Args...>;

#pragma region About Enum

template <typename T> constexpr bool TIsEnum = std::is_enum_v<T>;

/////////////////////////
// TIsEnumClass

namespace Internal
{
	template <typename T>
	struct TIsEnumConvertibleToIntTool
	{
		static char(&Resolve(int))[2];
		static char Resolve(...);

		enum { Value = sizeof(Resolve(T())) - 1 };
	};
}

/**
 * Traits class which tests if a type is arithmetic.
 */

template <typename T> constexpr bool TIsEnumClass = TIsEnum<T> && !Internal::TIsEnumConvertibleToIntTool<T>;

// TIsEnumClass
///////////////////////////

#pragma endregion

#pragma region TIsTrivial

/////////////////////////
// TIsTriviallyDestructible

template <typename T> constexpr bool TIsTriviallyDestructible = std::is_trivially_destructible_v<T>;

// TIsTriviallyDestructible
///////////////////////////

/////////////////////////
// TIsTriviallyCopyConstructible

template <typename T> constexpr bool TIsTriviallyCopyConstructible = std::is_trivially_constructible_v<T>;

// TIsTriviallyCopyConstructible
//////////////////////////

//////////////////////////
// TIsTriviallyCopyAssignable

template <typename T> constexpr bool TIsTriviallyCopyAssignable = std::is_trivially_copyable_v<T>;

// TIsTriviallyCopyAssignable
///////////////////////////

///////////////////////////
// TIsTrivial

template <typename T> constexpr bool TIsTrivial = std::is_trivial_v<T>;

// TIsTrivial
////////////////////////////

#pragma endregion

#pragma region TIsMemberPointerTool

///////////////////////////////
// TIsMemberPointer

namespace Internal
{
	/**
	 * Traits class which tests if a type is a pointer to member (data member or member function).
	 */
	template <typename T>
	struct TIsMemberPointerTool
	{
		constexpr static bool Value = false;
	};

	template <typename T, typename U> struct TIsMemberPointerTool<T U::*> { constexpr static bool Value = true; };

	template <typename T> struct TIsMemberPointerTool<const          T> { constexpr static bool Value = TIsMemberPointerTool<T>::Value; };
	template <typename T> struct TIsMemberPointerTool<      volatile T> { constexpr static bool Value = TIsMemberPointerTool<T>::Value; };
	template <typename T> struct TIsMemberPointerTool<const volatile T> { constexpr static bool Value = TIsMemberPointerTool<T>::Value; };
}

template <typename T> constexpr bool TIsMemberPointer = Internal::TIsMemberPointerTool<T>::Value;

// TIsMemberPointer
///////////////////////////////

#pragma endregion

#pragma region TIsInitializerList

////////////////////////////////////
// TIsInitializerList

namespace Internal
{
	/**
	 * Traits class which tests if a type is an initializer list.
	 */
	template <typename T>
	struct TIsInitializerListTool
	{
		static constexpr bool Value = false;
	};

	template <typename T>
	struct TIsInitializerListTool<std::initializer_list<T>>
	{
		static constexpr bool Value = true;
	};

	template <typename T> struct TIsInitializerListTool<const          T> { static constexpr Value = TIsInitializerListTool<T>::Value; };
	template <typename T> struct TIsInitializerListTool<      volatile T> { static constexpr Value = TIsInitializerListTool<T>::Value; };
	template <typename T> struct TIsInitializerListTool<const volatile T> { static constexpr Value = TIsInitializerListTool<T>::Value; };
}

template <typename T> constexpr bool TIsInitializerList = Internal::TIsInitializerListTool<T>::Value;

// TIsInitializerList
////////////////////////////////////

#pragma endregion

#pragma region Remove Type

template <typename T> using TRemoveP  = std::remove_pointer_t<T>;
template <typename T> using TRemoveC  = std::remove_const_t<T>;
template <typename T> using TRemoveV  = std::remove_volatile_t<T>;
template <typename T> using TRemoveR  = std::remove_reference_t<T>;
template <typename T> using TRemoveCV = std::remove_cv_t<T>;

#pragma endregion

#pragma region About Array

#pragma region IsArray

/**
 * Traits class which tests if a type is a C++ array.
 */
template <typename T>             struct TIsArray { constexpr static bool Value = false; };
template <typename T>             struct TIsArray<T[]> { constexpr static bool Value = true; };
template <typename T, uint32_t N> struct TIsArray<T[N]> { constexpr static bool Value = true; };

/**
 * Traits class which tests if a type is a bounded C++ array.
 */
template <typename T>             struct TIsBoundedArray { constexpr static bool Value = false; };
template <typename T, uint32_t N> struct TIsBoundedArray<T[N]> { constexpr static bool Value = true; };

/**
 * Traits class which tests if a type is an unbounded C++ array.
 */
template <typename T> struct TIsUnboundedArray { constexpr static bool Value = false; };
template <typename T> struct TIsUnboundedArray<T[]> { constexpr static bool Value = true; };

#pragma endregion

#pragma region Ref Version

/**
 * Type trait which returns true if the type T is an array or a reference to an array of ArrType.
 */
template <typename T, typename ArrType>
struct TIsArrayOrRefOfType
{
	constexpr static bool Value = false;
};

template <typename ArrType> struct TIsArrayOrRefOfType<               ArrType[], ArrType> { constexpr static bool Value = true; };
template <typename ArrType> struct TIsArrayOrRefOfType<const          ArrType[], ArrType> { constexpr static bool Value = true; };
template <typename ArrType> struct TIsArrayOrRefOfType<      volatile ArrType[], ArrType> { constexpr static bool Value = true; };
template <typename ArrType> struct TIsArrayOrRefOfType<const volatile ArrType[], ArrType> { constexpr static bool Value = true; };

template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<               ArrType[N], ArrType> { constexpr static bool Value = true; };
template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<const          ArrType[N], ArrType> { constexpr static bool Value = true; };
template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<      volatile ArrType[N], ArrType> { constexpr static bool Value = true; };
template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<const volatile ArrType[N], ArrType> { constexpr static bool Value = true; };

template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<               ArrType(&)[N], ArrType> { constexpr static bool Value = true; };
template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<const          ArrType(&)[N], ArrType> { constexpr static bool Value = true; };
template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<      volatile ArrType(&)[N], ArrType> { constexpr static bool Value = true; };
template <typename ArrType, unsigned int N> struct TIsArrayOrRefOfType<const volatile ArrType(&)[N], ArrType> { constexpr static bool Value = true; };

#pragma endregion


#pragma endregion

#pragma region TEnableIf

////////////////////////
// TEnableIf

namespace Internal
{
	/**
	 * Includes a function in an overload set if the predicate is true.  It should be used similarly to this:
	 *
	 * // This function will only be instantiated if SomeTrait<T>::Value is true for a particular T
	 * template <typename T>
	 * typename TEnableIf<SomeTrait<T>::Value, ReturnType>::Type Function(const T& Obj)
	 * {
	 *     ...
	 * }
	 *
	 * ReturnType is the real return type of the function.
	 */
	template <bool Predicate, typename Result = void>
	class TEnableIfTool;

	template <typename Result>
	class TEnableIfTool<true, Result>
	{
	public:
		using type = Result;
		using Type = Result;
	};

	template <typename Result>
	class TEnableIfTool<false, Result>
	{
	};

}

template <bool Pr, typename T = void> using TEnableIf = typename Internal::TEnableIfTool<Pr, T>::Type;

// TEnableIf
////////////////////////

////////////////////////
// TLazyEnableIf

namespace Internal
{
	/**
	 * This is a variant of the above that will determine the return type 'lazily', i.e. only if the function is enabled.
	 * This is useful when the return type isn't necessarily legal code unless the enabling condition is true.
	 *
	 * // This function will only be instantiated if SomeTrait<T>::Value is true for a particular T.
	 * // The function's return type is typename Transform<T>::Type.
	 * template <typename T>
	 * typename TLazyEnableIf<SomeTrait<T>::Value, Transform<T>>::Type Function(const T& Obj)
	 * {
	 *     ...
	 * }
	 *
	 * See boost::lazy_enable_if for more details.
	 */
	template <bool Predicate, typename Func>
	class TLazyEnableIfTool;

	template <typename Func>
	class TLazyEnableIfTool<true, Func>
	{
	public:
		using type = typename Func::Type;
		using Type = typename Func::Type;
	};

	template <typename Func>
	class TLazyEnableIfTool<false, Func>
	{
	};
}

template <bool Predicate, typename Func> using TLazyEnableIf = Internal::TLazyEnableIfTool<Predicate, Func>;

// TLazyEnableIf
////////////////////////

#pragma endregion

#pragma region TDecay

/////////////////////
// TDeacy

namespace Internal
{
	template <typename T>
	struct TDecayNonReference
	{
		using Type = TRemoveCV<T>;
	};

	template <typename T>
	struct TDecayNonReference<T[]>
	{
		using Type = T*;
	};

	template <typename T, uint32_t N>
	struct TDecayNonReference<T[N]>
	{
		using Type = T*;
	};

	template <typename RetType, typename... Params>
	struct TDecayNonReference<RetType(Params...)>
	{
		using Type = RetType(*)(Params...);
	};


	/**
	 * Returns the decayed type of T, meaning it removes all references, qualifiers and
	 * applies array-to-pointer and function-to-pointer conversions.
	 *
	 * http://en.cppreference.com/w/cpp/types/decay
	 */
	template <typename T>
	struct TDecayTool
	{
		typedef typename TDecayNonReference<typename TRemoveReference<T>::Type>::Type Type;
	};
}

template <typename T> using TDecay = typename Internal::TDecayTool<T>::Type;

// TDeacy
//////////////////////

#pragma endregion

#pragma region THasToString

////////////////////////////
// THasToString

namespace Internal
{
	template <typename T>
	struct StringAbleTool
	{
		template <typename U, typename = decltype(std::to_string(std::declval<U>()))>
		static constexpr bool check_std_to_string(U*) { return true; }

		template <typename U>
		static constexpr bool check_std_to_string(...) { return false; }

		template <typename U, typename = decltype(to_string(std::declval<U>()))>
		static constexpr bool check_to_string(U*) { return true; }

		template <typename U>
		static constexpr bool check_to_string(...) { return false; }

		template <typename U, typename = decltype(std::declval<U>().ToString)>
		static constexpr bool check_self_to_string(U*) { return true; }

		template <typename U>
		static constexpr bool check_self_to_string(...) { return false; }

		static constexpr bool Value = check_std_to_string<T>(nullptr) || check_to_string<T>(nullptr) || check_self_to_string<T>(nullptr);

		template <typename U, typename = decltype(atoi(std::declval<U>()))>
		static constexpr bool check_atoi_parse(U*) { return true; }

		template <typename U>
		static constexpr bool check_atoi_parse(...) { return true; }

		template <typename U, typename = decltype(atof(std::declval<U>()))>
		static constexpr bool check_atof_parse(U*) { return true; }

		template <typename U>
		static constexpr bool check_atof_parse(...) { return true; }

		template <typename U, typename = decltype(atol(std::declval<U>()))>
		static constexpr bool check_atol_parse(U*) { return true; }

		template <typename U>
		static constexpr bool check_atol_parse(...) { return true; }

		template <typename U, typename = decltype(atoll(std::declval<U>()))>
		static constexpr bool check_atoll_parse(U*) { return true; }

		template <typename U>
		static constexpr bool check_atoll_parse(...) { return true; }

		template <typename U, typename = decltype(from_string(std::declval<U*>(),(const char*const)nullptr,0))>
		static constexpr bool check_parse_string(U*) { return true; }

		template <typename U>
		static constexpr bool check_parse_string(...) { return false; }

		template <typename U, typename = decltype(std::declval<U>().Parse((const char* const)nullptr, 0))>
		static constexpr bool check_self_parse(U*) { return true; }

		template <typename U>
		static constexpr bool check_self_parse(...) { return false; }
	};
}

template <typename T> constexpr bool THasToString = Internal::StringAbleTool<T>::Value;

// THasToString
////////////////////////////

#pragma endregion

#pragma region TIsConvertible

/////////////////////////////
// TIsConvertible

namespace Internal
{
	template <typename From, typename To>
	struct TIsConvertibleImpl
	{
	private:
		static uint_fast8_t  Test(...);
		static uint_fast16_t Test(To);

	public:
		enum { Value = sizeof(Test((From)std::declval<From>())) - 1 };
	};
}

template <typename From, typename To> constexpr bool TIsConvertible = Internal::TIsConvertibleImpl<From, To>::Value;
template <typename From, typename To> constexpr bool TIsPointerConvertible   = TIsConvertible<From*, To*>;
template <typename From, typename To> constexpr bool TIsReferenceConvertible = TIsConvertible<From&, To&>;

// TIsConvertible
/////////////////////////////

#pragma endregion

#pragma region TCopyQualifiers

///////////////////////////////
// TCopyQualifiers

namespace Internal
{
	/**
	 * Copies the cv-qualifiers from one type to another, e.g.:
	 *
	 * TCopyQualifiers<const    T1,       T2>::Type == const T2
	 * TCopyQualifiers<volatile T1, const T2>::Type == const volatile T2
	 */
	template <typename From, typename To> struct TCopyQualifiersTool						  { typedef                To Type; };
	template <typename From, typename To> struct TCopyQualifiersTool<const          From, To> { typedef const          To Type; };
	template <typename From, typename To> struct TCopyQualifiersTool<      volatile From, To> { typedef       volatile To Type; };
	template <typename From, typename To> struct TCopyQualifiersTool<const volatile From, To> { typedef const volatile To Type; };
}

template <typename From, typename To> using TCopyQualifiers = typename Internal::TCopyQualifiersTool<From, To>::Type;

// TCopyQualifiers
////////////////////////////////

////////////////////////////////
// TCopyQualifiersAndRefs

namespace Internal
{
	/**
	 * Copies the cv-qualifiers and references from one type to another
	 */
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool { using Type = typename TCopyQualifiersTool<From, To>::Type; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From, To& > { using Type = typename TCopyQualifiersTool<From, To>::Type&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From, To&&> { using Type = typename TCopyQualifiersTool<From, To>::Type&&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From&, To  > { using Type = typename TCopyQualifiersTool<From, To>::Type&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From&, To& > { using Type = typename TCopyQualifiersTool<From, To>::Type&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From&, To&&> { using Type = typename TCopyQualifiersTool<From, To>::Type&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From&&, To  > { using Type = typename TCopyQualifiersTool<From, To>::Type&&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From&&, To& > { using Type = typename TCopyQualifiersTool<From, To>::Type&; };
	template <typename From, typename To> struct TCopyQualifiersAndRefsTool<From&&, To&&> { using Type = typename TCopyQualifiersTool<From, To>::Type&&; };
}

template <typename From, typename To> using TCopyQualifiersAndRefsFromTo_T = typename Internal::TCopyQualifiersAndRefsTool<From, To>::Type;

// TCopyQualifiersAndRefs
////////////////////////////////

template <typename From, typename To> constexpr bool TLosesQualifiers = !TAreSame<TCopyQualifiers<From, To>, To>;

#pragma endregion

#pragma region TLosesQualifiersFromTo

///////////////////////
// TLosesQualifiersFromTo

namespace Internal
{
	/**
	 * Tests if qualifiers are lost between one type and another, e.g.:
	 *
	 * TLosesQualifiersFromTo<const    T1,                T2>::Value == true
	 * TLosesQualifiersFromTo<volatile T1, const volatile T2>::Value == false
	 */
	template <typename From, typename To>
	struct TLosesQualifiersFromToTool
	{
		constexpr static bool Value = !TAreSame<TCopyQualifiersFromTo<From, To>, To>;
	};
}

template <typename From, typename To> using TLosesQualifiersFromTo = Internal::TLosesQualifiersFromToTool<From, To>;

// TLosesQualifiersFromTo
///////////////////////////

#pragma endregion

#pragma region TTrait

//////////////////////
// TTrait

namespace Internal
{
#pragma region Tools

	struct PrettyFunctionTag {};

	template<typename T>
	constexpr std::string_view PrettyFunction() 
	{
		return __FUNCSIG__;
	}

	template<typename T, T Value>
	constexpr std::string_view PrettyFunction()
	{
		return __FUNCSIG__;
	}

	constexpr size_t GetPrettyFunctionPrefix()
	{
		auto a = PrettyFunction<PrettyFunctionTag>();
		auto b = PrettyFunction<void>();
		size_t result = 0;
		size_t end = std::min(a.size(), b.size());
		for (; result < end; result++)
		{
			if (a.substr(0, result) != b.substr(0, result))
				return result;
		}
		return result;
	}

	constexpr size_t GetPrettyFunctionSuffix()
	{
		auto a = PrettyFunction<PrettyFunctionTag>();
		auto b = PrettyFunction<void>();
		size_t result = 0;
		size_t end = std::min(a.size(), b.size());
		for (; result < end; result++)
		{
			if (a.substr(a.size() - result - 1, end) != b.substr(b.size() - result - 1, end))
				return result;
		}
		return result;
	}

	template<typename T>
	constexpr size_t GetPrettyFunctionWithValuePrefix()
	{
		auto a = PrettyFunction<T, static_cast<T>(0)>();
		auto b = PrettyFunction<T, static_cast<T>(1)>();
		size_t result = 0;
		size_t end = std::min(a.size(), b.size());
		for (; result < end; result++)
		{
			if (a.substr(0, result) != b.substr(0, result))
				return result;
		}
		return result;
	}

	template<typename T>
	constexpr size_t GetPrettyFunctionWithValueSuffix()
	{
		auto a = PrettyFunction<T, static_cast<T>(0)>();
		auto b = PrettyFunction<T, static_cast<T>(1)>();
		size_t result = 0;
		size_t end = std::min(a.size(), b.size());
		for (; result < end; result++)
		{
			if (a.substr(a.size() - result - 1, end) != b.substr(b.size() - result - 1, end))
				return result;
		}
		return result;
	}

	template<typename T>
	constexpr std::string_view SymbolNameTool() 
	{
		auto name = PrettyFunction<T>();
		name.remove_prefix(GetPrettyFunctionPrefix() - 1);
		name.remove_suffix(GetPrettyFunctionSuffix());
		return name;
	}

	template<typename T,T Value>
	constexpr std::string_view ValueNameTool()
	{
		auto name = PrettyFunction<T, Value>();
		name.remove_prefix(GetPrettyFunctionWithValuePrefix<T>() - 1);
		name.remove_suffix(GetPrettyFunctionWithValueSuffix<T>());
		return name;
	}

#pragma endregion

	template <typename T, bool IsIntegral> struct TraitTool;
	template <typename T> struct TraitTool<T,false>
	{
	public:
		constexpr static bool IsPointer = TIsPointer<T>;
		constexpr static bool IsRef = TIsRef<T>;
		constexpr static bool IsVoid = TIsVoid<T>;
		constexpr static bool IsVirtual = TIsVirtual<T>;
		constexpr static bool IsPolymorphic = TIsPolymorphic<T>;
		constexpr static bool IsAbstract = TIsAbstract<T>;
		constexpr static bool IsClass = TIsClass<T>;
		constexpr static bool IsPOD = TIsPOD<T>;
		constexpr static bool IsEnum = TIsEnum<T>;
		constexpr static bool IsEnumClass = TIsEnum<T>;
		constexpr static bool IsTriviallyDestructible = TIsTriviallyDestructible<T>;
		constexpr static bool IsTriviallyCopyConstructible = TIsTriviallyCopyConstructible<T>;
		constexpr static bool IsTriviallyCopyAssignable = TIsTriviallyCopyAssignable<T>;
		constexpr static bool IsTrivial = TIsTrivial<T>;
		constexpr static bool IsMemberPointer = TIsMemberPointer<T>;
		constexpr static bool IsInitializerList = TIsInitializerList<T>;
		constexpr static bool HasToString = THasToString<T>;
	public:
		template<typename P, bool Derived = true> static constexpr bool Is() { return (TAreSame<T, P> || (Derived && TIsBaseOf<T, P>)); }
		template<typename P, bool Derived = true> static constexpr bool Is(P) { return (TAreSame<T, P> || (Derived && TIsBaseOf<T, P>)); }
		template<typename P, bool Derived = true> static constexpr bool Is(P from, T& to)
		{
			to = static_cast<T&>(from);
			return (TAreSame<T, P> || (Derived && TIsBaseOf<T, P>));
		}
		static bool Is(void* ptr)
		{
			using TSymbol = decltype(Symbol());
			return Symbol() == *reinterpret_cast<TSymbol*>(reinterpret_cast<size_t>(ptr) - sizeof(TSymbol));
		}
		static intptr_t Symbol()
		{
			static auto symbol = typeid(T).hash_code();
			return (intptr_t)&symbol;
		}

		constexpr static uint32_t NewPtrMemorySize = sizeof(decltype(Symbol())) + sizeof(T);

		static T* New(void* memory, size_t capacity)
		{
			using TSymbol = decltype(Symbol());
			constexpr auto size = NewPtrMemorySize;
			if (capacity < size || memory == nullptr)
				return nullptr;
			char* ptr = new(memory) char[size];
			auto&& head = reinterpret_cast<TSymbol&>(*ptr);
			head = Symbol();
			T* result = reinterpret_cast<T*>(&(ptr[sizeof(TSymbol)]));
			return result;
		}
		static void Delete(T* ptr)
		{
			using TSymbol = decltype(Symbol());
			*reinterpret_cast<TSymbol*>(reinterpret_cast<size_t>(ptr) - sizeof(TSymbol)) = 0;
			ptr->~T();
		}
		static T* FirstInMemory(void* memory, size_t capacity)
		{
			for (char* head = (char*)memory, *end = (char*)memory + capacity; head != end; head++)
			{
				if (Is(head))
					return (T*)head;
			}
			return nullptr;
		}

		static bool WriteBinary(T* object, char* buffer, size_t capacity)
		{
			if (sizeof(T) + sizeof(decltype(Symbol())) > capacity)
				return false;
			*reinterpret_cast<decltype(Symbol())*>(&buffer[0]) = Symbol();
			memcpy_s(&buffer[sizeof(decltype(Symbol()))], capacity, object, sizeof(T));
			return true;
		}
		static bool Write(T* object, char* buffer, size_t capacity, bool is_allow_binary_write = false)
		{
			if constexpr (StringAbleTool<T>::check_self_to_string<T>(nullptr))
			{
				auto str = object->ToString();
				size_t strCsize = 0;
				if constexpr (TIsCStr<decltype(str), char>)
				{
					constexpr auto _strCsize = sizeof(decltype(*str[0]));
					strCsize = _strCsize;
				}
				else
				{
					constexpr auto _strCsize = sizeof(decltype(*str.begin()));
					strCsize = _strCsize;
				}
				if (strCsize == 0)
					return false;
				if (str.size() * strCsize > capacity)
					return false;
				memcpy_s(buffer, capacity, str.c_str(), str.size() * strCsize);
			}
			else if constexpr (StringAbleTool<T>::check_to_string<T>(nullptr))
			{
				auto str = to_string(*object);
				size_t strCsize = 0;
				if constexpr (TIsCStr<decltype(str), char>)
				{
					constexpr auto _strCsize = sizeof(decltype(*str[0]));
					strCsize = _strCsize;
				}
				else
				{
					constexpr auto _strCsize = sizeof(decltype(*str.begin()));
					strCsize = _strCsize;
				}
				if (strCsize == 0)
					return false;
				if (str.size() * strCsize > capacity)
					return false;
				memcpy_s(buffer, capacity, str.c_str(), str.size() * strCsize);
			}
			else if constexpr (StringAbleTool<T>::check_std_to_string<T>(nullptr))
			{
				std::string str = std::to_string(*object);
				if (str.size() > capacity)
					return false;
				memcpy_s(buffer, capacity, str.c_str(), str.size());
			}
			else
			{
				if (is_allow_binary_write == false)
					return false;
				WriteBinary(object, buffer, capacity);
			}
			return true;
		}
		static T* ReadBinaryWithoutToken(T* object, char* buffer, size_t capacity)
		{
			constexpr auto offset = sizeof(decltype(Symbol()));
			if (capacity > sizeof(T) + offset && *reinterpret_cast<decltype(Symbol())*>(&buffer[0]) == Symbol())
				memcpy(object, &buffer[offset], capacity);
			else
			{
				if (capacity > sizeof(T))
					memcpy(object, buffer, capacity);
				else
					return nullptr;
			}
			return object;
		}
		static T* ReadBinary(void* memory, size_t capacity, char* buffer, size_t buffer_capacity)
		{
			constexpr auto size = sizeof(T) + sizeof(decltype(Symbol()));
			if (size > buffer_capacity)
				return nullptr;
			if (size > capacity)
				return nullptr;
			if (*reinterpret_cast<decltype(Symbol())*>(&buffer[0]) != Symbol())
				return nullptr;
			T* object = reinterpret_cast<T*>(&buffer[sizeof(decltype(Symbol()))]);
			memcpy(memory, buffer, size);
			return object;
		}
		static bool Parse(T* object, const char* const buffer, size_t capacity)
		{
			if constexpr (StringAbleTool<T>::check_self_parse<T>(nullptr))
			{
				object->Parse(buffer, capacity);
			}
			else if constexpr (StringAbleTool<T>::check_parse_string<T>(nullptr))
			{
				from_string(object, buffer, capacity);
			}
			else if constexpr (TAreSame<bool, T>)
			{
				if (strcmp(buffer, "true") == 0)
					*object = true;
				else if (strcmp(buffer, "false") == 0)
					*object = false;
				else
					return false;
			}
			else if constexpr (StringAbleTool<T>::check_atoll_parse<T>(nullptr))
			{
				*object = static_cast<T>(atoll(buffer));
			}
			else if constexpr (StringAbleTool<T>::check_atol_parse<T>(nullptr))
			{
				*object = static_cast<T>(atol(buffer));
			}
			else if constexpr (StringAbleTool<T>::check_atoi_parse<T>(nullptr))
			{
				*object = static_cast<T>(atoi(buffer));
			}
			else if constexpr (StringAbleTool<T>::check_atof_parse<T>(nullptr))
			{
				*object = static_cast<T>(atof(buffer));
			}
			else
			{
				return false;
			}
			return true;
		}

		constexpr static std::string_view SymbolName()
		{
			return SymbolNameTool<T>();
		}

		static uint32_t Hash(const T& v)
		{
			if constexpr (std::is_integral_v<T>)
				return Hash(v);
			else
				return THash(&v);
		}
		static uint32_t Hash(T* v)
		{
			if constexpr (std::is_integral_v<T>)
				return Hash(*v);
			else
				return THash(v);
		}

	private:
		constexpr static uint32_t InjectTypeHash()
		{
			auto str = SymbolName();
			return CHash(str.data());
		}
	public:
		constexpr static int TypeHash = InjectTypeHash();
	};
	template <typename T> struct TraitTool<T, true> : public TraitTool<T, false>
	{
		template<T Value>
		constexpr static std::string_view ValueName()
		{
			return ValueNameTool<T, Value>();
		}
	};
	template <typename T, bool IsIntegral> struct TraitTool<const          T, IsIntegral> : public TraitTool<T,IsIntegral> {};
	template <typename T, bool IsIntegral> struct TraitTool<      volatile T, IsIntegral> : public TraitTool<T,IsIntegral> {};
	template <typename T, bool IsIntegral> struct TraitTool<const volatile T, IsIntegral> : public TraitTool<T,IsIntegral> {};
}

template <typename T> using TTrait = Internal::TraitTool<T, std::is_integral_v<T>>;

// TTrait
////////////////////////

////////////////////////
// ValueTrait

namespace Internal
{
	template<typename T> class ValueClass : public TTrait<T>
	{
	private:
		using _Mybase = TTrait<T>;
		char MyMemoryInside[NewPtrMemorySize];
		T* MyCachePtr;
	public:
		template<typename = TEnableIf<TIsConstructible<T>>>
		ValueClass()
		{
			MyCachePtr = _Mybase::New(MyMemoryInside, NewPtrMemorySize);
			new(MyCachePtr) T();
		}
		template<typename First, typename = TEnableIf<TIsConstructible<T, First>>>
		ValueClass(First first)
		{
			MyCachePtr = _Mybase::New(MyMemoryInside, NewPtrMemorySize);
			new(MyCachePtr) T(first);
		}
		template<typename First, typename Second,
			typename = TEnableIf<TIsConstructible<T, First, Second>>>
		ValueClass(First first, Second second)
		{
			MyCachePtr = _Mybase::New(MyMemoryInside, NewPtrMemorySize);
			new(MyCachePtr) T(first, second);
		}
		template<typename First, typename Second, typename Third,
			typename = TEnableIf<TIsConstructible<T, First, Second, Third>>>
		ValueClass(First first, Second second, Third third)
		{
			MyCachePtr = _Mybase::New(MyMemoryInside, NewPtrMemorySize);
			new(MyCachePtr) T(first, second, third);
		}
		template<typename First, typename Second, typename Third, typename Other,
			typename = TEnableIf<TIsConstructible<T, First, Second, Third, Other>>>
		ValueClass(First first, Second second, Third third, Other other)
		{
			MyCachePtr = _Mybase::New(MyMemoryInside, NewPtrMemorySize);
			new(MyCachePtr) T(first, second, third, other);
		}

		T& ReadValue()
		{
			return *MyCachePtr;
		}

		const T& ReadValue() const
		{
			return *MyCachePtr;
		}

		constexpr operator T& ()
		{
			return *MyCachePtr;
		}

		constexpr operator const T& () const
		{
			return *MyCachePtr;
		}

		uint32_t Hash()
		{
			return _Mybase::Hash(MyCachePtr);
		}
	};
}

// ValueTrait
////////////////////////

using Bool   = Internal::ValueClass<bool>;
using Int    = Internal::ValueClass<int>;
using Float  = Internal::ValueClass<float>;
using Double = Internal::ValueClass<double>;
using Long   = Internal::ValueClass<long>;
using UInt   = Internal::ValueClass<unsigned int>;
using Int8   = Internal::ValueClass<int8_t>;
using Int16  = Internal::ValueClass<int16_t>;
using Int32  = Internal::ValueClass<int32_t>;
using Int64  = Internal::ValueClass<int64_t>;
using UInt8  = Internal::ValueClass<uint8_t>;
using UInt16 = Internal::ValueClass<uint16_t>;
using UInt32 = Internal::ValueClass<uint32_t>;
using UInt64 = Internal::ValueClass<uint64_t>;
using LongDouble = Internal::ValueClass<long double>;

#pragma endregion

#pragma region nameof

namespace Internal
{
	template <typename T> constexpr auto __Inject_nameof_type()
	{
		return TTrait<T>::SymbolName();
	}
	template <typename T, T Value> constexpr auto __Inject_nameof_value()
	{
		return TTrait<T>::ValueName<Value>();
	}
}
#define nameof(x) Internal::__Inject_nameof_type<x>();
#define nameofEnum(x) Internal::__Inject_nameof_value<decltype(x),x>();

#pragma endregion


template <typename T> using TUnwrapped = TEnableIf<TIsIt<T>, TConditional<TIsPointer<T>, TRemoveP<T>, decltype(*std::declval<T>())>>;
template <typename T, typename Unwrapped = TUnwrapped<T>> decltype(auto) Unwrapping(T from)
{
	return *from;
}

template <typename From, typename To, bool = TIsConvertible<TUnwrapped<From>, To> || TIsConvertible<From, To>> To Cast(From data)
{
	if constexpr (TIsConvertible<From, To>)
		return static_cast<To>(data);
	return static_cast<To>(Unwrapping(data));
}

#endif // !__FILE_Detail_CP_Typen_Hpp

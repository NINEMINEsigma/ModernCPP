#pragma once
#ifndef __FILE_Detail_CP_Typen_Hpp
#define __FILE_Detail_CP_Typen_Hpp

#include "detail/CP/CHash.hpp"

template <typename Base, typename Derived> constexpr bool TIsBaseOf = std::is_base_of_v<Base, Derived>;

template <typename A, typename B> constexpr bool TAreSame = std::is_same_v<A, B>;

namespace Internal
{
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
		using Type = std::conditional_t<Pr, First, Second>;
	};
}

template<bool Pr, typename First, typename Second> using TChoose = typename Internal::TConditionalTool<bool, Pr, First, Second>::Type;
template<int Index, typename... Types> using TConditional = typename Internal::TConditionalTool<int, Index, Types...>::Type;

template <typename T> using TDecay = std::decay_t<T>;

template <typename T> constexpr bool TIsP  = std::is_pointer_v<T>;
template <typename T> constexpr bool TIsC  = std::is_const_v<T>;
template <typename T> constexpr bool TIsV  = std::is_volatile_v<T>;
template <typename T> constexpr bool TIsR  = std::is_reference_v<T>;
template <typename T> constexpr bool TIsF  = std::is_function_v<T>;
template <typename T> constexpr bool TIsLR = std::is_lvalue_reference_v<T>;
template <typename T> constexpr bool TIsRR = std::is_rvalue_reference_v<T>;
template <typename T> constexpr bool TIsCV = TIsC<T> && TIsV<T>;
template <typename T> constexpr bool TIsIt = TIsP<T> || TIsLR<decltype(*std::declval<T>())>;
template <typename T> constexpr bool TIsVoid = std::is_same_v<void, T>;
template <typename T> constexpr bool THasVirtual = std::has_virtual_destructor_v<T>;
template <typename T, typename C> constexpr bool TIsCStr = TAreSame<T, const C*>&& TAreSame<T, C*>;

template <typename T> using TRemoveP  = std::remove_pointer_t<T>;
template <typename T> using TRemoveC  = std::remove_const_t<T>;
template <typename T> using TRemoveV  = std::remove_volatile_t<T>;
template <typename T> using TRemoveR  = std::remove_reference_t<T>;
template <typename T> using TRemoveCV = std::remove_cv_t<T>;

template <bool Pr, typename T = void> using TEnableIf = std::enable_if_t<Pr, T>;

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

template <typename From, typename To> constexpr bool TLosesQualifiers = !TAreSame<TCopyQualifiers<From, To>, To>;

namespace Internal
{
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

	template <typename T, bool IsIntegral> struct TraitTool;
	template <typename T> struct TraitTool<T,false>
	{
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
		static T* New(void* memory, size_t capacity)
		{
			using TSymbol = decltype(Symbol());
			constexpr auto size = sizeof(TSymbol) + sizeof(T);
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
				return GetTypeHash(v);
			else
				return GetTypeHash(&v);
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

namespace Internal
{
	template<typename T> class ValueClass : public TTrait<T>
	{
	private:
		T value;
		using _Mybase = TTrait<T>;
	public:
		ValueClass(const T& value) : value(value) {}
		ValueClass(T& value) : value(value) {}
		ValueClass(T&& value) : value(std::move(value)) {}
		ValueClass<T>& operator=(const T& value) noexcept
		{
			this->value = value;
		}
		ValueClass<T>& operator=(T& value) noexcept
		{
			this->value = value;
		}
		ValueClass<T>& operator=(T&& value) noexcept
		{
			this->value = std::move(value);
		}
		constexpr operator T& ()
		{
			return value;
		}
		constexpr operator const T& () const
		{
			return value;
		}
		uint32_t Hash()
		{
			return _Mybase::Hash(value);
		}
	};
}

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

#if !defined(nameofT)&&!defined(nameofEnum)
template <typename T> constexpr auto __Inject_nameof()
{
	return TTrait<T>::SymbolName();
}
template <typename T, T Value> constexpr auto __Inject_nameof()
{
	return TTrait<T>::ValueName<Value>();
}
#define nameofT(x) __Inject_nameof<x>();
#define nameofEnum(x) __Inject_nameof<decltype(x),x>();
#else
template <typename T> constexpr auto nameof()
{
	return TTrait<T>::SymbolName();
}
template <typename T, T Value> constexpr auto nameof()
{
	return TTrait<T>::ValueName<Value>();
}
#endif // !nameof


template <typename T> using TUnwrapped = TEnableIf<TIsIt<T>, TConditional<TIsP<T>, TRemoveP<T>, decltype(*std::declval<T>())>>;
template <typename T, typename Unwrapped = TUnwrapped<T>> decltype(auto) Unwrapping(T from)
{
	return *from;
}

template <typename From, typename To, bool = TIsConvertible<TUnwrapped<From, To>> || TIsConvertible<From, To>> To Cast(From data)
{
	if constexpr (TIsConvertible<From, To>)
		return static_cast<To>(data);
	return static_cast<To>(Unwrapping(data));
}

#endif // !__FILE_Detail_CP_Typen_Hpp

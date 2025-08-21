#pragma once
#ifndef __FILE_Detail_Core_Object_Hpp
#define __FILE_Detail_Core_Object_Hpp

#include "detail/CP/Typen.hpp"

/**
* 所有object体系中的非实例类都不包含虚函数和数据结构, 并以私有方式继承
* @code
*	class Base : private Object<Base>{};
*	class Derived : public Base, Object<Derived>{};
*/
template <typename DerivedTerminal> struct Object;
template <> struct Object<void>
{
	template<typename T>
	Object<T>& ObjectCast()
	{
		return *static_cast<Object<T>*>(this);
	}
};
template <typename DerivedTerminal> struct Object : private Object<void>
{
	using TDerivedTerminal = DerivedTerminal;
	constexpr DerivedTerminal* operator->() noexcept
	{
		return static_cast<DerivedTerminal*>(this);
	}

	template<typename T,
		typename R = TEnableIf<
		TIsConvertible<DerivedTerminal, T> || TIsConvertible<DerivedTerminal&, T&> || TIsBaseOf<DerivedTerminal, T>,
		TChoose<TIsConvertible<DerivedTerminal, T>, T, T&>
		>
	>
	R Cast()
	{
		if constexpr (std::is_base_of_v<DerivedTerminal, T> && std::has_virtual_destructor_v<DerivedTerminal>)
			return dynamic_cast<T&>(static_cast<DerivedTerminal&>(*this));
		else
			return *static_cast<T*>(this);
	}
};

template <typename DataType, bool PublicGetter = true, typename PublicSetterParam = DataType, int ID = 0> struct IInterface;
template <typename DataType, int ID> struct IInterface<DataType, true, DataType, ID>: private Object<IInterface<DataType, true, DataType, ID>>
{
protected:
	DataType data;
public:
	virtual DataType& ReadValue()
	{
		return data;
	}
};
template <typename DataType, int ID> struct IInterface<DataType, true, void, ID> : private Object<IInterface<DataType, true, void, ID>>
{
protected:
	DataType data;
public:
	virtual const DataType& ReadValue()
	{
		return data;
	}
};
template <typename DataType, int ID> struct IInterface<DataType, false, DataType, ID> : private Object<IInterface<DataType, false, DataType, ID>>
{
protected:
	DataType data;
public:
	virtual void SetValue(DataType value)
	{
		data = value;
	}
};
template <typename DataType, bool PublicGetter, typename PublicSetterParam, int ID> struct IInterface : private Object<IInterface<DataType, PublicGetter, PublicSetterParam, ID>>
{
protected:
	DataType data;
};

template <typename Symbol, typename DataType = Symbol, bool PublicGetter = true, typename PublicSetterParam = DataType>
using ITypenInterface = IInterface<DataType, PublicGetter, PublicSetterParam, TTrait<Symbol>::TypeHash>;


#endif // !__FILE_Detail_Core_Object_Hpp

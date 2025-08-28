#pragma once
#ifndef __FILE_Detail_CP_CHash_Hpp
#define __FILE_Detail_CP_CHash_Hpp

//
// Hash functions for common types.
//

inline uint32_t Hash(const uint8_t A)
{
	return A;
}

inline uint32_t Hash(const int8_t A)
{
	return A;
}

inline uint32_t Hash(const uint16_t A)
{
	return A;
}

inline uint32_t Hash(const int16_t A)
{
	return A;
}

inline uint32_t Hash(const int32_t A)
{
	return A;
}

inline uint32_t Hash(const uint32_t A)
{
	return A;
}

inline uint32_t Hash(const uint64_t A)
{
	return (uint32_t)A + ((uint32_t)(A >> 32) * 23);
}

inline uint32_t Hash(const int64_t A)
{
	return (uint32_t)A + ((uint32_t)(A >> 32) * 23);
}

uint32_t Hash(const char* str, uint32_t hash = 5381)
{
	return *str == '\0' ? hash : Hash(str + 1, ((hash << 5) + hash) + *str);
}

uint32_t Hash(std::string_view str, uint32_t hash = 5381)
{
	for (size_t i = 0; i < str.length(); ++i)
	{
		hash = ((hash << 5) + hash) + str[i];
	}
	return hash;
}

constexpr uint32_t CHash(const uint8_t A)
{
	return A;
}

constexpr uint32_t CHash(const int8_t A)
{
	return A;
}

constexpr uint32_t CHash(const uint16_t A)
{
	return A;
}

constexpr uint32_t CHash(const int16_t A)
{
	return A;
}

constexpr uint32_t CHash(const int32_t A)
{
	return A;
}

constexpr uint32_t CHash(const uint32_t A)
{
	return A;
}

constexpr uint32_t CHash(const uint64_t A)
{
	return (uint32_t)A + ((uint32_t)(A >> 32) * 23);
}

constexpr uint32_t CHash(const int64_t A)
{
	return (uint32_t)A + ((uint32_t)(A >> 32) * 23);
}

constexpr uint32_t CHash(const char* str, uint32_t hash = 5381)
{
	return *str == '\0' ? hash : CHash(str + 1, ((hash << 5) + hash) + *str);
}

constexpr uint32_t CHash(std::string_view str, uint32_t hash = 5381)
{
	for (size_t i = 0; i < str.length(); ++i) 
	{
		hash = ((hash << 5) + hash) + str[i];
	}
	return hash;
}

#endif // !__FILE_Detail_CP_CHash_Hpp

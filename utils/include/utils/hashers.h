#pragma once
#include <cstddef>

namespace utils
{
	template<std::size_t Size = sizeof(std::size_t)>
	struct fnv_1;

	template<>
	struct fnv_1<8>
	{
		static const std::size_t offset_basis = 14695981039346656037ULL;
		static const std::size_t prime = 1099511628211ULL;
	};

	struct fnv_1a_hasher
	{
		static std::size_t hash(const char *raw, std::size_t size)
		{
			std::size_t result = fnv_1<>::offset_basis;

			for (std::size_t byte = 0; byte < size; ++byte)
			{
				result ^= (std::size_t)raw[byte];
				result *= fnv_1<>::prime;
			}

			return result;
		}

		template<typename Type>
		static std::size_t hash(const Type& obj)
		{
			return hash((const char *)&obj, sizeof(Type));
		}

		template<typename Type>
		std::size_t operator()(const Type& obj) const
		{
			return hash(obj);
		}
	};
}

#pragma once

#include <string>
#include <vector>
#include "hashers.h"

namespace utils
{
	template<typename CharType>
	class basic_string_ref
	{
	public:
		static constexpr std::size_t npos = std::size_t(~0ull);

		using char_type = CharType;
		using const_iterator = const char_type *;

	private:
		const char_type *m_begin = nullptr;
		const char_type *m_end = nullptr;

	public:
		basic_string_ref(const std::basic_string<char_type> &string)
			: m_begin(string.c_str())
			, m_end(string.c_str() + string.length())
		{
		}

		basic_string_ref(std::basic_string<char_type> &&string) = delete;

		template<std::size_t N>
		constexpr basic_string_ref(const char_type(&c_string)[N])
			: m_begin(c_string)
			, m_end(c_string + (N - 1))
		{
		}

		constexpr basic_string_ref(const_iterator begin, const_iterator end)
			: m_begin(begin)
			, m_end(end)
		{
		}

		constexpr basic_string_ref() = default;

		constexpr std::size_t length() const
		{
			return empty() ? 0 : m_end - m_begin;
		}

		constexpr std::size_t size() const
		{
			return length();
		}

		constexpr bool empty() const
		{
			return m_begin == m_end;
		}

		constexpr const_iterator begin() const
		{
			return m_begin;
		}

		constexpr const_iterator end() const
		{
			return m_end;
		}

		constexpr const_iterator cbegin() const
		{
			return m_begin;
		}

		constexpr const_iterator cend() const
		{
			return m_end;
		}

		constexpr basic_string_ref substr(const std::size_t offset, const std::size_t length_ = npos) const
		{
			return{ m_begin + offset, (length_ < (length() - offset) ? m_end - (length() - offset - length_) : m_end) };
		}

		constexpr char_type operator[](std::size_t index) const
		{
			return m_begin[index];
		}

		constexpr char_type at(std::size_t index) const
		{
			return index < length() ? m_begin[index] : throw std::out_of_range("basic_string_ref out of range");
		}

		constexpr char_type front() const
		{
			return m_begin[0];
		}

		constexpr char_type back() const
		{
			return m_end[-1];
		}

		void clear()
		{
			m_begin = m_end;
		}

		bool contains(char_type char_) const
		{
			for (char_type internal_char : *this)
			{
				if (internal_char == char_)
				{
					return true;
				}
			}

			return false;
		}

		basic_string_ref ltrim(const basic_string_ref &skip_chars = " \t\n\r") const
		{
			basic_string_ref result = *this;

			while (!result.empty() && skip_chars.contains(result.front()))
			{
				++result.m_begin;
			}

			return result;
		}

		basic_string_ref rtrim(const basic_string_ref &skip_chars = " \t\n\r") const
		{
			basic_string_ref result = *this;

			while (!result.empty() && skip_chars.contains(result.back()))
			{
				--result.m_end;
			}

			return result;
		}

		basic_string_ref trim(const basic_string_ref &skip_chars = " \t\n\r") const
		{
			basic_string_ref result = *this;

			while (!result.empty() && skip_chars.contains(result.front()))
			{
				++result.m_begin;
			}

			while (!result.empty() && skip_chars.contains(result.back()))
			{
				--result.m_end;
			}

			return result;
		}

		template<typename ContainerType = std::vector<basic_string_ref>>
		ContainerType split(const basic_string_ref &separators = " \t\n\r", bool skip_empty = false) const
		{
			ContainerType result;

			const_iterator word_begin = end();
			for (const_iterator it = begin(); it != end(); ++it)
			{
				if (separators.contains(*it))
				{
					if (word_begin != end())
					{
						if (!skip_empty || word_begin != it - 1)
						{
							result.emplace_back(word_begin, it);
						}

						word_begin = end();
					}
				}
				else
				{
					if (word_begin == end())
					{
						word_begin = it;
					}
				}
			}

			if (word_begin != end())
			{
				if (!skip_empty || word_begin != end() - 1)
				{
					result.emplace_back(word_begin, end());
				}
			}

			return result;
		}

		int compare(const basic_string_ref& other) const
		{
			for (
				const_iterator it_this = begin(), it_other = other.begin();
				it_this != end() || it_other != other.end();
				++it_this, ++it_other
				)
			{
				int diff = *it_this - *it_other;

				if (diff)
				{
					return diff;
				}
			}

			return 0;
		}

		bool starts_with(const basic_string_ref& other) const
		{
			return other.size() > size() ? false : (basic_string_ref(begin(), begin() + other.size()) == other);
		}

		bool ends_with(const basic_string_ref& other) const
		{
			return other.size() > size() ? false : (basic_string_ref(end() - other.size(), end()) == other);
		}

		bool operator ==(const basic_string_ref& rhs) const
		{
			return length() == rhs.length() && compare(rhs) == 0;
		}

		bool operator !=(const basic_string_ref& rhs) const
		{
			return length() != rhs.length() || compare(rhs) != 0;
		}

		std::basic_string<char_type> to_string() const
		{
			return{ m_begin, length() };
		}

		std::vector<char_type> to_vector(bool place_string_terminator = true) const
		{
			std::vector<char_type> result;
			result.reserve(length() + std::size_t(place_string_terminator));

			for (auto c : *this)
			{
				result.push_back(c);
			}

			if (place_string_terminator)
			{
				result.push_back('\0');
			}

			return result;
		}

		std::size_t to_vector(std::vector<char_type> &destination, bool place_string_terminator = true) const
		{
			std::size_t offset = destination.size();

			destination.reserve(offset + length() + std::size_t(place_string_terminator));

			for (auto c : *this)
			{
				destination.push_back(c);
			}

			if (place_string_terminator)
			{
				destination.push_back('\0');
			}

			return offset;
		}
	};

	using string_ref = basic_string_ref<char>;
	using wstring_ref = basic_string_ref<wchar_t>;
	using u16string_ref = basic_string_ref<char16_t>;
	using u32string_ref = basic_string_ref<char32_t>;
}

namespace std
{
	template<typename CharType>
	struct hash<utils::basic_string_ref<CharType>>
	{
		std::size_t operator()(const utils::basic_string_ref<CharType>& key_value) const
		{
			return utils::fnv_1a_hasher::hash((const char *)key_value.begin(), key_value.size() * sizeof(CharType));
		}
	};
}

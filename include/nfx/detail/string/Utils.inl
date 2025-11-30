/*
 * MIT License
 *
 * Copyright (c) 2025 nfx
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file Utils.inl
 * @brief Implementation file for high-performance string utilities
 * @details Inline implementations of string validation, parsing, and comparison functions
 *          with optimized algorithms for maximum runtime performance and minimal overhead.
 */

#include <algorithm>
#include <cctype>
#include <cmath>
#include <charconv>

namespace nfx::string
{
	//=====================================================================
	// String utilities
	//=====================================================================

	//----------------------------------------------
	// String validation
	//----------------------------------------------

	inline constexpr bool hasExactLength( std::string_view str, std::size_t expectedLength ) noexcept
	{
		return str.size() == expectedLength;
	}

	inline constexpr bool isEmpty( std::string_view str ) noexcept
	{
		return str.empty();
	}

	inline constexpr bool isNullOrWhiteSpace( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return true;
		}

		for ( const char c : str )
		{
			// Check for standard whitespace characters: space, tab, newline, carriage return, form feed, vertical tab
			if ( c != ' ' && c != '\t' && c != '\n' && c != '\r' && c != '\f' && c != '\v' )
			{
				return false;
			}
		}
		return true;
	}

	inline constexpr bool isAllDigits( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}
		return std::all_of( str.begin(), str.end(), []( char c ) { return isDigit( c ); } );
	}

	//----------------------------------------------
	// Character Classification
	//----------------------------------------------

	inline constexpr bool isWhitespace( char c ) noexcept
	{
		return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
	}

	inline constexpr bool isDigit( char c ) noexcept
	{
		return static_cast<unsigned char>( c - '0' ) <= 9u;
	}

	inline constexpr bool isAlpha( char c ) noexcept
	{
		return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' );
	}

	inline constexpr bool isAlphaNumeric( char c ) noexcept
	{
		return isAlpha( c ) || isDigit( c );
	}

	//----------------------------------------------
	// String operations
	//----------------------------------------------

	inline constexpr bool startsWith( std::string_view str, std::string_view prefix ) noexcept
	{
		// Thin wrapper only
		return str.starts_with( prefix );
	}

	inline constexpr bool contains( std::string_view str, std::string_view substr ) noexcept
	{
		return str.find( substr ) != std::string_view::npos;
	}

	inline constexpr bool endsWith( std::string_view str, std::string_view suffix ) noexcept
	{
		// Thin wrapper only
		return str.ends_with( suffix );
	}

	inline constexpr bool equals( std::string_view lhs, std::string_view rhs ) noexcept
	{
		return lhs == rhs;
	}

	inline bool iequals( std::string_view lhs, std::string_view rhs ) noexcept
	{
		if ( lhs.size() != rhs.size() )
		{
			return false;
		}

		return std::equal( lhs.begin(), lhs.end(), rhs.begin(),
			[]( char a, char b ) noexcept { return toLower( a ) == toLower( b ); } );
	}

	inline std::size_t count( std::string_view str, std::string_view substr ) noexcept
	{
		if ( substr.empty() || str.empty() || substr.size() > str.size() )
		{
			return 0;
		}

		std::size_t occurrences = 0;
		std::size_t pos = 0;

		while ( ( pos = str.find( substr, pos ) ) != std::string_view::npos )
		{
			++occurrences;
			pos += substr.size(); // Move past this occurrence (non-overlapping)
		}

		return occurrences;
	}

	inline std::size_t countOverlapping( std::string_view str, std::string_view substr ) noexcept
	{
		if ( substr.empty() || str.empty() || substr.size() > str.size() )
		{
			return 0;
		}

		std::size_t occurrences = 0;
		std::size_t pos = 0;

		while ( ( pos = str.find( substr, pos ) ) != std::string_view::npos )
		{
			++occurrences;
			++pos; // Move by 1 to find overlapping occurrences
		}

		return occurrences;
	}

	inline constexpr std::size_t count( std::string_view str, char ch ) noexcept
	{
		std::size_t occurrences = 0;
		for ( char c : str )
		{
			if ( c == ch )
			{
				++occurrences;
			}
		}
		return occurrences;
	}

	inline std::string replace( std::string_view str, std::string_view oldStr, std::string_view newStr )
	{
		if ( oldStr.empty() || str.empty() )
		{
			return std::string{ str };
		}

		std::size_t pos = str.find( oldStr );
		if ( pos == std::string_view::npos )
		{
			return std::string{ str };
		}

		std::string result;
		result.reserve( str.size() - oldStr.size() + newStr.size() );
		result.append( str.substr( 0, pos ) );
		result.append( newStr );
		result.append( str.substr( pos + oldStr.size() ) );

		return result;
	}

	inline std::string replaceAll( std::string_view str, std::string_view oldStr, std::string_view newStr )
	{
		if ( oldStr.empty() || str.empty() )
		{
			return std::string{ str };
		}

		std::string result;
		result.reserve( str.size() ); // Initial reservation, may grow

		std::size_t lastPos = 0;
		std::size_t pos = 0;

		while ( ( pos = str.find( oldStr, lastPos ) ) != std::string_view::npos )
		{
			result.append( str.substr( lastPos, pos - lastPos ) );
			result.append( newStr );
			lastPos = pos + oldStr.size();
		}

		// Append remaining part
		result.append( str.substr( lastPos ) );

		return result;
	}

	template <typename Container>
	inline std::string join( const Container& elements, std::string_view delimiter )
	{
		return join( std::begin( elements ), std::end( elements ), delimiter );
	}

	template <typename Iterator>
	inline std::string join( Iterator begin, Iterator end, std::string_view delimiter )
	{
		if ( begin == end )
		{
			return {};
		}

		std::string result;

		// Add first element without delimiter
		auto it = begin;
		result.append( std::string_view{ *it } );
		++it;

		// Add remaining elements with delimiter prefix
		for ( ; it != end; ++it )
		{
			result.append( delimiter );
			result.append( std::string_view{ *it } );
		}

		return result;
	}

	inline std::string reverse( std::string_view str )
	{
		std::string result{ str };
		std::reverse( result.begin(), result.end() );

		return result;
	}

	inline constexpr std::size_t indexOf( std::string_view str, std::string_view substr ) noexcept
	{
		return str.find( substr );
	}

	inline constexpr std::size_t lastIndexOf( std::string_view str, std::string_view substr ) noexcept
	{
		return str.rfind( substr );
	}

	//----------------------------------------------
	// String formatting and padding
	//----------------------------------------------

	inline std::string padLeft( std::string_view str, std::size_t width, char fillChar )
	{
		if ( str.size() >= width )
		{
			return std::string{ str };
		}

		std::string result;
		result.reserve( width );

		std::size_t paddingSize = width - str.size();
		result.append( paddingSize, fillChar );
		result.append( str );

		return result;
	}

	inline std::string padRight( std::string_view str, std::size_t width, char fillChar )
	{
		if ( str.size() >= width )
		{
			return std::string{ str };
		}

		std::string result;
		result.reserve( width );

		result.append( str );
		std::size_t paddingSize = width - str.size();
		result.append( paddingSize, fillChar );

		return result;
	}

	inline std::string center( std::string_view str, std::size_t width, char fillChar )
	{
		if ( str.size() >= width )
		{
			return std::string{ str };
		}

		std::string result;
		result.reserve( width );

		std::size_t totalPadding = width - str.size();
		std::size_t leftPadding = totalPadding / 2;
		std::size_t rightPadding = totalPadding - leftPadding; // Extra char goes right if odd

		result.append( leftPadding, fillChar );
		result.append( str );
		result.append( rightPadding, fillChar );

		return result;
	}

	inline std::string repeat( std::string_view str, std::size_t count )
	{
		if ( count == 0 || str.empty() )
		{
			return {};
		}

		std::string result;
		result.reserve( str.size() * count );

		for ( std::size_t i = 0; i < count; ++i )
		{
			result.append( str );
		}

		return result;
	}

	//----------------------------------------------
	// Substring extraction
	//----------------------------------------------

	inline constexpr std::string_view substringBefore( std::string_view str, std::string_view delimiter ) noexcept
	{
		if ( delimiter.empty() )
		{
			return str;
		}

		const std::size_t pos = str.find( delimiter );
		if ( pos == std::string_view::npos )
		{
			return str;
		}

		return str.substr( 0, pos );
	}

	inline constexpr std::string_view substringAfter( std::string_view str, std::string_view delimiter ) noexcept
	{
		if ( delimiter.empty() )
		{
			return {};
		}

		const std::size_t pos = str.find( delimiter );
		if ( pos == std::string_view::npos )
		{
			return {};
		}

		return str.substr( pos + delimiter.size() );
	}

	inline constexpr std::string_view substringBeforeLast( std::string_view str, std::string_view delimiter ) noexcept
	{
		if ( delimiter.empty() )
		{
			return str;
		}

		const std::size_t pos = str.rfind( delimiter );
		if ( pos == std::string_view::npos )
		{
			return str;
		}

		return str.substr( 0, pos );
	}

	inline constexpr std::string_view substringAfterLast( std::string_view str, std::string_view delimiter ) noexcept
	{
		if ( delimiter.empty() )
		{
			return {};
		}

		const std::size_t pos = str.rfind( delimiter );
		if ( pos == std::string_view::npos )
		{
			return {};
		}

		return str.substr( pos + delimiter.size() );
	}

	inline constexpr std::string_view extractBetween( std::string_view str, std::string_view start, std::string_view end ) noexcept
	{
		if ( start.empty() || end.empty() )
		{
			return {};
		}

		const std::size_t startPos = str.find( start );
		if ( startPos == std::string_view::npos )
		{
			return {};
		}

		const std::size_t contentStart = startPos + start.size();
		const std::size_t endPos = str.find( end, contentStart );
		if ( endPos == std::string_view::npos )
		{
			return {};
		}

		return str.substr( contentStart, endPos - contentStart );
	}

	inline constexpr std::string_view removePrefix( std::string_view str, std::string_view prefix ) noexcept
	{
		if ( str.starts_with( prefix ) )
		{
			return str.substr( prefix.size() );
		}
		return str;
	}

	inline constexpr std::string_view removeSuffix( std::string_view str, std::string_view suffix ) noexcept
	{
		if ( str.ends_with( suffix ) )
		{
			return str.substr( 0, str.size() - suffix.size() );
		}
		return str;
	}

	//----------------------------------------------
	// String Trimming
	//----------------------------------------------

	//----------------------------
	// Non-allocating
	//----------------------------

	inline constexpr std::string_view trimStart( std::string_view str ) noexcept
	{
		std::size_t start = 0;
		while ( start < str.size() && isWhitespace( str[start] ) )
		{
			++start;
		}
		return str.substr( start );
	}

	inline constexpr std::string_view trimEnd( std::string_view str ) noexcept
	{
		std::size_t end = str.size();
		while ( end > 0 && isWhitespace( str[end - 1] ) )
		{
			--end;
		}
		return str.substr( 0, end );
	}

	inline constexpr std::string_view trim( std::string_view str ) noexcept
	{
		return trimEnd( trimStart( str ) );
	}

	//----------------------------------------------
	// Character & String Removal
	//----------------------------------------------

	inline std::string removeAll( std::string_view str, char ch )
	{
		std::string result;
		result.reserve( str.size() );

		for ( char c : str )
		{
			if ( c != ch )
			{
				result += c;
			}
		}

		return result;
	}

	inline std::string removeAll( std::string_view str, std::string_view substr )
	{
		if ( substr.empty() )
		{
			return std::string( str );
		}

		std::string result;
		result.reserve( str.size() );

		std::size_t pos = 0;
		std::size_t found_pos = 0;

		while ( ( found_pos = str.find( substr, pos ) ) != std::string_view::npos )
		{
			result.append( str.substr( pos, found_pos - pos ) );
			pos = found_pos + substr.size();
		}

		result.append( str.substr( pos ) );
		return result;
	}

	template <typename Predicate>
	inline std::string removeIf( std::string_view str, Predicate pred )
	{
		std::string result;
		result.reserve( str.size() );

		for ( char c : str )
		{
			if ( !pred( c ) )
			{
				result += c;
			}
		}

		return result;
	}

	inline std::string removeWhitespace( std::string_view str )
	{
		return removeIf( str, []( char c ) { return isWhitespace( c ); } );
	}

	inline std::string collapseWhitespace( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() );

		bool in_whitespace = true; // Start as true to skip leading whitespace

		for ( char c : str )
		{
			if ( isWhitespace( c ) )
			{
				if ( !in_whitespace )
				{
					result += ' '; // Replace any whitespace with single space
					in_whitespace = true;
				}
			}
			else
			{
				result += c;
				in_whitespace = false;
			}
		}

		// Remove trailing space if added
		if ( !result.empty() && result.back() == ' ' )
		{
			result.pop_back();
		}

		return result;
	}

	//----------------------------------------------
	// Predicate-based operations
	//----------------------------------------------

	template <typename Predicate>
	inline constexpr std::string_view trimStartIf( std::string_view str, Predicate pred ) noexcept
	{
		auto start = str.begin();
		auto end = str.end();

		while ( start != end && pred( *start ) )
		{
			++start;
		}

		return str.substr( static_cast<std::size_t>( start - str.begin() ) );
	}

	template <typename Predicate>
	inline constexpr std::string_view trimEndIf( std::string_view str, Predicate pred ) noexcept
	{
		auto start = str.begin();
		auto end = str.end();

		while ( start != end && pred( *( end - 1 ) ) )
		{
			--end;
		}

		return str.substr( 0, static_cast<std::size_t>( end - start ) );
	}

	template <typename Predicate>
	inline constexpr std::string_view trimIf( std::string_view str, Predicate pred ) noexcept
	{
		return trimEndIf( trimStartIf( str, pred ), pred );
	}

	template <typename Predicate>
	inline constexpr std::size_t countIf( std::string_view str, Predicate pred ) noexcept
	{
		std::size_t count = 0;
		for ( char c : str )
		{
			if ( pred( c ) )
			{
				++count;
			}
		}
		return count;
	}

	template <typename Predicate>
	inline constexpr std::size_t findIf( std::string_view str, Predicate pred ) noexcept
	{
		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( pred( str[i] ) )
			{
				return i;
			}
		}
		return std::string_view::npos;
	}

	template <typename Predicate>
	inline constexpr std::size_t findIfNot( std::string_view str, Predicate pred ) noexcept
	{
		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( !pred( str[i] ) )
			{
				return i;
			}
		}
		return std::string_view::npos;
	}

	template <typename Predicate>
	inline std::string replaceIf( std::string_view str, Predicate pred, char replacement )
	{
		std::string result( str );
		for ( char& c : result )
		{
			if ( pred( c ) )
			{
				c = replacement;
			}
		}
		return result;
	}

	//----------------------------------------------
	// String case conversion
	//----------------------------------------------

	inline std::string toLower( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() );

		for ( char c : str )
		{
			result.push_back( toLower( c ) );
		}

		return result;
	}

	inline std::string toUpper( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() );

		for ( char c : str )
		{
			result.push_back( toUpper( c ) );
		}

		return result;
	}

	//----------------------------------------------
	// Character case conversion
	//----------------------------------------------

	inline constexpr char toLower( char c ) noexcept
	{
		return ( c >= 'A' && c <= 'Z' ) ? static_cast<char>( c + ( 'a' - 'A' ) ) : c;
	}

	inline constexpr char toUpper( char c ) noexcept
	{
		return ( c >= 'a' && c <= 'z' ) ? static_cast<char>( c - ( 'a' - 'A' ) ) : c;
	}

	//----------------------------------------------
	// Parsing
	//----------------------------------------------

	//----------------------------------------------
	// Unified parsing API: fromString<T>
	//----------------------------------------------

	/**
	 * @brief Parse string to type T using output parameter
	 * @tparam T Target type (bool, int, uint32_t, int64_t, uint64_t, float, double)
	 * @param str String to parse
	 * @param result Output parameter to store parsed value
	 * @return True if parsing succeeded, false otherwise
	 * @details Zero-overhead parsing for performance-critical code.
	 *          Supports: bool, int, uint32_t, int64_t, uint64_t, float, double
	 *          For bool: "true"/"false", "1"/"0", "yes"/"no", "on"/"off", "t"/"f", "y"/"n" (case-insensitive)
	 *          For float/double: decimal, scientific notation, special values (nan, inf, infinity)
	 *          Example: int value; if (fromString("42", value)) { use(value); }
	 */
	template <typename T>
		requires(
			std::is_same_v<std::decay_t<T>, bool> ||
			std::is_same_v<std::decay_t<T>, int> ||
			std::is_same_v<std::decay_t<T>, std::uint32_t> ||
			std::is_same_v<std::decay_t<T>, std::int64_t> ||
			std::is_same_v<std::decay_t<T>, std::uint64_t> ||
			std::is_same_v<std::decay_t<T>, float> ||
			std::is_same_v<std::decay_t<T>, double> )
	[[nodiscard]] inline bool fromString( std::string_view str, T& result ) noexcept
	{
		if constexpr ( std::is_same_v<std::decay_t<T>, bool> )
		{
			if ( str.empty() )
			{
				result = false;
				return false;
			}

			// Handle single character cases first
			if ( str.size() == 1 )
			{
				const char c{ toLower( str[0] ) };
				if ( c == '1' || c == 't' || c == 'y' )
				{
					result = true;
					return true;
				}
				else if ( c == '0' || c == 'f' || c == 'n' )
				{
					result = false;
					return true;
				}
				return false;
			}

			// Handle multi-character cases
			if ( str.size() == 2 )
			{
				if ( ( toLower( str[0] ) == 'o' && toLower( str[1] ) == 'n' ) )
				{
					result = true;
					return true;
				}
				else if ( ( toLower( str[0] ) == 'n' && toLower( str[1] ) == 'o' ) )
				{
					result = false;
					return true;
				}
			}
			else if ( str.size() == 3 )
			{
				if ( toLower( str[0] ) == 'y' && toLower( str[1] ) == 'e' && toLower( str[2] ) == 's' )
				{
					result = true;
					return true;
				}
				else if ( toLower( str[0] ) == 'o' && toLower( str[1] ) == 'f' && toLower( str[2] ) == 'f' )
				{
					result = false;
					return true;
				}
			}
			else if ( str.size() == 4 )
			{
				if ( toLower( str[0] ) == 't' && toLower( str[1] ) == 'r' &&
					 toLower( str[2] ) == 'u' && toLower( str[3] ) == 'e' )
				{
					result = true;
					return true;
				}
			}
			else if ( str.size() == 5 )
			{
				if ( toLower( str[0] ) == 'f' && toLower( str[1] ) == 'a' &&
					 toLower( str[2] ) == 'l' && toLower( str[3] ) == 's' && toLower( str[4] ) == 'e' )
				{
					result = false;
					return true;
				}
			}

			result = false;
			return false;
		}
		else if constexpr ( std::is_same_v<std::decay_t<T>, int> )
		{
			if ( str.empty() )
			{
				result = 0;
				return false;
			}

			const char* const begin = str.data();
			const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.length() ) );
			const auto parseResult{ std::from_chars( begin, end, result ) };
			return parseResult.ec == std::errc{} && parseResult.ptr == end;
		}
		else if constexpr ( std::is_same_v<std::decay_t<T>, std::int64_t> )
		{
			if ( str.empty() )
			{
				result = 0LL;
				return false;
			}

			const char* const begin = str.data();
			const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
			const auto parseResult{ std::from_chars( begin, end, result ) };
			return parseResult.ec == std::errc{} && parseResult.ptr == end;
		}
		else if constexpr ( std::is_same_v<std::decay_t<T>, std::uint32_t> )
		{
			if ( str.empty() )
			{
				result = 0u;
				return false;
			}

			const char* const begin = str.data();
			const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
			const auto parseResult{ std::from_chars( begin, end, result ) };
			return parseResult.ec == std::errc{} && parseResult.ptr == end;
		}
		else if constexpr ( std::is_same_v<std::decay_t<T>, std::uint64_t> )
		{
			if ( str.empty() )
			{
				result = 0ULL;
				return false;
			}

			const char* const begin = str.data();
			const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
			const auto parseResult{ std::from_chars( begin, end, result ) };
			return parseResult.ec == std::errc{} && parseResult.ptr == end;
		}
		else if constexpr ( std::is_same_v<std::decay_t<T>, float> )
		{
			if ( str.empty() )
			{
				result = 0.f;
				return false;
			}

			const char* const begin = str.data();
			const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
			const auto parseResult{ std::from_chars( begin, end, result ) };
			return parseResult.ec == std::errc{} && parseResult.ptr == end;
		}
		else if constexpr ( std::is_same_v<std::decay_t<T>, double> )
		{
			if ( str.empty() )
			{
				result = 0.0;
				return false;
			}

			const char* const begin = str.data();
			const char* const end = std::next( begin, static_cast<std::ptrdiff_t>( str.size() ) );
			const auto parseResult{ std::from_chars( begin, end, result ) };
			return parseResult.ec == std::errc{} && parseResult.ptr == end;
		}
	}

	/**
	 * @brief Parse string to type T using modern std::optional interface
	 * @tparam T Target type (bool, int, uint32_t, int64_t, uint64_t, float, double)
	 * @param str String to parse
	 * @return std::optional<T> containing parsed value, or std::nullopt on failure
	 * @details Modern C++ interface for parsing. Returns empty optional on parse error.
	 *          Supports all fundamental types with zero overhead.
	 *          Example: if (auto val = fromString<int>("42")) { use(*val); }
	 */
	template <typename T>
		requires(
			std::is_same_v<std::decay_t<T>, bool> ||
			std::is_same_v<std::decay_t<T>, int> ||
			std::is_same_v<std::decay_t<T>, std::uint32_t> ||
			std::is_same_v<std::decay_t<T>, std::int64_t> ||
			std::is_same_v<std::decay_t<T>, std::uint64_t> ||
			std::is_same_v<std::decay_t<T>, float> ||
			std::is_same_v<std::decay_t<T>, double> )
	[[nodiscard]] inline std::optional<T> fromString( std::string_view str ) noexcept
	{
		T result;
		if ( fromString( str, result ) )
		{
			return result;
		}
		return std::nullopt;
	}

	//----------------------------------------------
	// Network and URI validation
	//----------------------------------------------

	//-----------------------------
	// URI character classification
	//-----------------------------

	inline constexpr bool isURIReserved( char c ) noexcept
	{
		// RFC 3986 Section 2.2 - Reserved Characters
		// gen-delims: : / ? # [ ] @
		// sub-delims: ! $ & ' ( ) * + , ; =
		return c == ':' || c == '/' || c == '?' || c == '#' || c == '[' || c == ']' || c == '@' ||
			   c == '!' || c == '$' || c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' ||
			   c == '+' || c == ',' || c == ';' || c == '=';
	}

	inline constexpr bool isURIReserved( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}
		return std::all_of( str.begin(), str.end(), []( char c ) { return isURIReserved( c ); } );
	}

	inline constexpr bool isURIUnreserved( char c ) noexcept
	{
		// RFC 3986 Section 2.3 - Unreserved Characters
		// ALPHA / DIGIT / "-" / "." / "_" / "~"
		return isAlphaNumeric( c ) || c == '-' || c == '.' || c == '_' || c == '~';
	}

	inline constexpr bool isURIUnreserved( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}
		return std::all_of( str.begin(), str.end(), []( char c ) { return isURIUnreserved( c ); } );
	}

	//-----------------------------
	// URL encoding/decoding
	//-----------------------------

	inline std::string urlEncode( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() * 3 ); // Reserve for worst case (all chars encoded)

		// Hex digits for percent-encoding
		constexpr char hex_digits[] = "0123456789ABCDEF";

		for ( unsigned char c : str )
		{
			// Unreserved characters (RFC 3986 Section 2.3): A-Z a-z 0-9 - . _ ~
			if ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) || ( c >= '0' && c <= '9' ) || c == '-' || c == '.' || c == '_' || c == '~' )
			{
				result += static_cast<char>( c );
			}
			else
			{
				// Percent-encode everything else
				result += '%';
				result += hex_digits[c >> 4];	// High nibble
				result += hex_digits[c & 0x0F]; // Low nibble
			}
		}

		return result;
	}

	inline std::string urlDecode( std::string_view str ) noexcept
	{
		std::string result;
		result.reserve( str.size() ); // Decoded is always <= original

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '%' )
			{
				// Need at least 2 more characters for %XX
				if ( i + 2 >= str.size() )
				{
					return ""; // Invalid encoding
				}

				// Get the two hex digits
				char high = str[i + 1];
				char low = str[i + 2];

				// Convert hex digits to values
				auto hexToInt = []( char c ) -> int {
					if ( c >= '0' && c <= '9' )
						return c - '0';
					if ( c >= 'A' && c <= 'F' )
						return c - 'A' + 10;
					if ( c >= 'a' && c <= 'f' )
						return c - 'a' + 10;
					return -1; // Invalid hex digit
				};

				int high_val = hexToInt( high );
				int low_val = hexToInt( low );

				if ( high_val == -1 || low_val == -1 )
				{
					return ""; // Invalid hex digits
				}

				// Combine nibbles and add decoded character
				result += static_cast<char>( ( high_val << 4 ) | low_val );
				i += 2; // Skip the two hex digits
			}
			else
			{
				result += str[i];
			}
		}

		return result;
	}

	//-----------------------------
	// JSON escape/unescape
	//-----------------------------

	inline std::string jsonEscape( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() * 2 ); // Reserve for common case

		// Hex digits for Unicode escape sequences
		constexpr char hex_digits[] = "0123456789ABCDEF";

		for ( unsigned char c : str )
		{
			switch ( c )
			{
				case '\"':
					result += "\\\"";
					break;
				case '\\':
					result += "\\\\";
					break;
				case '/':
					result += "\\/";
					break;
				case '\b':
					result += "\\b";
					break;
				case '\f':
					result += "\\f";
					break;
				case '\n':
					result += "\\n";
					break;
				case '\r':
					result += "\\r";
					break;
				case '\t':
					result += "\\t";
					break;
				default:
					// Control characters (U+0000 to U+001F) must be escaped
					if ( c < 0x20 )
					{
						result += "\\u00";
						result += hex_digits[c >> 4];	// High nibble
						result += hex_digits[c & 0x0F]; // Low nibble
					}
					else
					{
						result += static_cast<char>( c );
					}
					break;
			}
		}

		return result;
	}

	inline std::string jsonUnescape( std::string_view str ) noexcept
	{
		std::string result;
		result.reserve( str.size() );

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '\\' )
			{
				if ( i + 1 >= str.size() )
				{
					return ""; // Invalid: backslash at end
				}

				char next = str[i + 1];
				switch ( next )
				{
					case '\"':
						result += '\"';
						i++;
						break;
					case '\\':
						result += '\\';
						i++;
						break;
					case '/':
						result += '/';
						i++;
						break;
					case 'b':
						result += '\b';
						i++;
						break;
					case 'f':
						result += '\f';
						i++;
						break;
					case 'n':
						result += '\n';
						i++;
						break;
					case 'r':
						result += '\r';
						i++;
						break;
					case 't':
						result += '\t';
						i++;
						break;
					case 'u':
					{
						// Unicode escape: \uXXXX
						if ( i + 5 >= str.size() )
						{
							return ""; // Invalid: not enough characters for \uXXXX
						}

						// Parse 4 hex digits
						auto hexToInt = []( char c ) -> int {
							if ( c >= '0' && c <= '9' )
								return c - '0';
							if ( c >= 'A' && c <= 'F' )
								return c - 'A' + 10;
							if ( c >= 'a' && c <= 'f' )
								return c - 'a' + 10;
							return -1;
						};

						int value = 0;
						for ( int j = 0; j < 4; ++j )
						{
							int digit = hexToInt( str[i + 2 + j] );
							if ( digit == -1 )
							{
								return ""; // Invalid hex digit
							}
							value = ( value << 4 ) | digit;
						}

						// Convert Unicode codepoint to UTF-8
						if ( value <= 0x7F )
						{
							// 1-byte UTF-8
							result += static_cast<char>( value );
						}
						else if ( value <= 0x7FF )
						{
							// 2-byte UTF-8
							result += static_cast<char>( 0xC0 | ( value >> 6 ) );
							result += static_cast<char>( 0x80 | ( value & 0x3F ) );
						}
						else
						{
							// 3-byte UTF-8 (covers Basic Multilingual Plane)
							result += static_cast<char>( 0xE0 | ( value >> 12 ) );
							result += static_cast<char>( 0x80 | ( ( value >> 6 ) & 0x3F ) );
							result += static_cast<char>( 0x80 | ( value & 0x3F ) );
						}

						i += 5; // Skip \uXXXX
						break;
					}
					default:
						return ""; // Invalid escape sequence
				}
			}
			else
			{
				result += str[i];
			}
		}

		return result;
	}

	//-----------------------------
	// XML/HTML escape/unescape
	//-----------------------------

	inline std::string xmlEscape( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() ); // Minimum size needed

		for ( char c : str )
		{
			switch ( c )
			{
				case '&':
					result += "&amp;";
					break;
				case '<':
					result += "&lt;";
					break;
				case '>':
					result += "&gt;";
					break;
				case '"':
					result += "&quot;";
					break;
				case '\'':
					result += "&apos;";
					break;
				default:
					result += c;
					break;
			}
		}

		return result;
	}

	inline std::string xmlUnescape( std::string_view str ) noexcept
	{
		std::string result;
		result.reserve( str.size() ); // Result will be smaller or equal

		// Helper lambda to convert hex char to int
		auto hexToInt = []( char c ) -> int {
			if ( c >= '0' && c <= '9' )
				return c - '0';
			if ( c >= 'a' && c <= 'f' )
				return c - 'a' + 10;
			if ( c >= 'A' && c <= 'F' )
				return c - 'A' + 10;
			return -1;
		};

		for ( size_t i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '&' )
			{
				// Find the closing semicolon
				size_t semi = str.find( ';', i + 1 );
				if ( semi == std::string_view::npos )
				{
					return ""; // Malformed entity (no closing semicolon)
				}

				std::string_view entity = str.substr( i + 1, semi - i - 1 );

				// Check for numeric character references
				if ( !entity.empty() && entity[0] == '#' )
				{
					int value = 0;

					if ( entity.size() > 1 && entity[1] == 'x' )
					{
						// Hexadecimal: &#xHHHH;
						if ( entity.size() <= 2 )
						{
							return ""; // No hex digits after &#x
						}

						for ( size_t j = 2; j < entity.size(); ++j )
						{
							int digit = hexToInt( entity[j] );
							if ( digit == -1 )
							{
								return ""; // Invalid hex digit
							}
							value = ( value << 4 ) | digit;
						}
					}
					else
					{
						// Decimal: &#DDDD;
						if ( entity.size() <= 1 )
						{
							return ""; // No decimal digits after &#
						}

						for ( size_t j = 1; j < entity.size(); ++j )
						{
							if ( entity[j] < '0' || entity[j] > '9' )
							{
								return ""; // Invalid decimal digit
							}
							value = value * 10 + ( entity[j] - '0' );
						}
					}

					// Convert Unicode codepoint to UTF-8
					if ( value <= 0x7F )
					{
						// 1-byte UTF-8
						result += static_cast<char>( value );
					}
					else if ( value <= 0x7FF )
					{
						// 2-byte UTF-8
						result += static_cast<char>( 0xC0 | ( value >> 6 ) );
						result += static_cast<char>( 0x80 | ( value & 0x3F ) );
					}
					else if ( value <= 0xFFFF )
					{
						// 3-byte UTF-8
						result += static_cast<char>( 0xE0 | ( value >> 12 ) );
						result += static_cast<char>( 0x80 | ( ( value >> 6 ) & 0x3F ) );
						result += static_cast<char>( 0x80 | ( value & 0x3F ) );
					}
					else if ( value <= 0x10FFFF )
					{
						// 4-byte UTF-8
						result += static_cast<char>( 0xF0 | ( value >> 18 ) );
						result += static_cast<char>( 0x80 | ( ( value >> 12 ) & 0x3F ) );
						result += static_cast<char>( 0x80 | ( ( value >> 6 ) & 0x3F ) );
						result += static_cast<char>( 0x80 | ( value & 0x3F ) );
					}
					else
					{
						return ""; // Invalid codepoint
					}

					i = semi; // Skip the entire entity
				}
				else if ( entity == "amp" )
				{
					result += '&';
					i = semi;
				}
				else if ( entity == "lt" )
				{
					result += '<';
					i = semi;
				}
				else if ( entity == "gt" )
				{
					result += '>';
					i = semi;
				}
				else if ( entity == "quot" )
				{
					result += '"';
					i = semi;
				}
				else if ( entity == "apos" )
				{
					result += '\'';
					i = semi;
				}
				else
				{
					return ""; // Unknown entity
				}
			}
			else
			{
				result += str[i];
			}
		}

		return result;
	}

	//-----------------------------
	// C/C++ escape sequences
	//-----------------------------

	inline std::string cppEscape( std::string_view str )
	{
		std::string result;
		result.reserve( str.size() ); // Minimum size needed

		for ( unsigned char c : str )
		{
			switch ( c )
			{
				case '\n':
					result += "\\n";
					break;
				case '\t':
					result += "\\t";
					break;
				case '\r':
					result += "\\r";
					break;
				case '\\':
					result += "\\\\";
					break;
				case '"':
					result += "\\\"";
					break;
				case '\'':
					result += "\\'";
					break;
				case '\0':
					result += "\\0";
					break;
				case '\b':
					result += "\\b";
					break;
				case '\f':
					result += "\\f";
					break;
				case '\v':
					result += "\\v";
					break;
				case '\a':
					result += "\\a";
					break;
				default:
					// Escape other control characters as \xHH
					if ( c < 32 || c == 127 )
					{
						constexpr char hex_digits[] = "0123456789abcdef";
						result += "\\x";
						result += hex_digits[c >> 4];
						result += hex_digits[c & 0x0F];
					}
					else
					{
						result += static_cast<char>( c );
					}
					break;
			}
		}

		return result;
	}

	inline std::string cppUnescape( std::string_view str ) noexcept
	{
		std::string result;
		result.reserve( str.size() ); // Result will be smaller or equal

		// Helper lambda to convert hex char to int
		auto hexToInt = []( char c ) -> int {
			if ( c >= '0' && c <= '9' )
				return c - '0';
			if ( c >= 'a' && c <= 'f' )
				return c - 'a' + 10;
			if ( c >= 'A' && c <= 'F' )
				return c - 'A' + 10;
			return -1;
		};

		// Helper lambda to check if char is octal digit
		auto isOctal = []( char c ) -> bool {
			return c >= '0' && c <= '7';
		};

		for ( size_t i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '\\' )
			{
				if ( i + 1 >= str.size() )
				{
					return ""; // Backslash at end of string
				}

				switch ( str[i + 1] )
				{
					case 'n':
						result += '\n';
						++i;
						break;
					case 't':
						result += '\t';
						++i;
						break;
					case 'r':
						result += '\r';
						++i;
						break;
					case '\\':
						result += '\\';
						++i;
						break;
					case '"':
						result += '"';
						++i;
						break;
					case '\'':
						result += '\'';
						++i;
						break;
					case '0':
						// Could be \0 or octal \NNN
						if ( i + 2 < str.size() && isOctal( str[i + 2] ) )
						{
							// Octal sequence \NNN
							int value = 0;
							size_t j = i + 1;
							for ( int count = 0; count < 3 && j < str.size() && isOctal( str[j] ); ++count, ++j )
							{
								value = value * 8 + ( str[j] - '0' );
								if ( value > 255 )
								{
									return ""; // Octal value out of range
								}
							}
							result += static_cast<char>( value );
							i = j - 1;
						}
						else
						{
							// Just \0
							result += '\0';
							++i;
						}
						break;
					case 'b':
						result += '\b';
						++i;
						break;
					case 'f':
						result += '\f';
						++i;
						break;
					case 'v':
						result += '\v';
						++i;
						break;
					case 'a':
						result += '\a';
						++i;
						break;
					case 'x':
					{
						// Hexadecimal: \xHH
						if ( i + 3 >= str.size() )
						{
							return ""; // Incomplete hex sequence
						}

						int high = hexToInt( str[i + 2] );
						int low = hexToInt( str[i + 3] );

						if ( high == -1 || low == -1 )
						{
							return ""; // Invalid hex digits
						}

						result += static_cast<char>( ( high << 4 ) | low );
						i += 3;
						break;
					}
					default:
						// Check if it's an octal sequence starting with 1-7
						if ( isOctal( str[i + 1] ) )
						{
							// Octal sequence \NNN
							int value = 0;
							size_t j = i + 1;
							for ( int count = 0; count < 3 && j < str.size() && isOctal( str[j] ); ++count, ++j )
							{
								value = value * 8 + ( str[j] - '0' );
								if ( value > 255 )
								{
									return ""; // Octal value out of range
								}
							}
							result += static_cast<char>( value );
							i = j - 1;
						}
						else
						{
							return ""; // Unknown escape sequence
						}
						break;
				}
			}
			else
			{
				result += str[i];
			}
		}

		return result;
	}

	//-----------------------------
	// String formatting utilities
	//-----------------------------

	inline std::string truncate( std::string_view str, size_t maxLength )
	{
		if ( str.size() <= maxLength )
		{
			return std::string( str );
		}
		return std::string( str.substr( 0, maxLength ) );
	}

	inline std::string truncate( std::string_view str, size_t maxLength, std::string_view ellipsis )
	{
		if ( str.size() <= maxLength )
		{
			return std::string( str );
		}

		// If ellipsis is too long, just truncate without it
		if ( ellipsis.size() >= maxLength )
		{
			// But if there's still room for content + ellipsis, include it
			if ( maxLength > 0 )
			{
				size_t contentLen = maxLength > ellipsis.size() ? maxLength - ellipsis.size() : 0;
				if ( contentLen > 0 )
				{
					std::string result;
					result.reserve( maxLength );
					result.append( str.substr( 0, contentLen ) );
					result.append( ellipsis.substr( 0, maxLength - contentLen ) );
					return result;
				}
			}
			return std::string( str.substr( 0, maxLength ) );
		}

		size_t truncLen = maxLength - ellipsis.size();
		std::string result;
		result.reserve( maxLength );
		result.append( str.substr( 0, truncLen ) );
		result.append( ellipsis );
		return result;
	}

	inline std::string wordWrap( std::string_view str, size_t width )
	{
		if ( str.empty() || width == 0 )
		{
			return std::string( str );
		}

		std::string result;
		result.reserve( str.size() + str.size() / width );

		size_t lineStart = 0;

		while ( lineStart < str.size() )
		{
			// Find the end of the current line (existing newline or end of string)
			size_t newlinePos = str.find( '\n', lineStart );
			size_t lineEnd = ( newlinePos != std::string_view::npos ) ? newlinePos : str.size();

			// Process this line
			size_t pos = lineStart;
			while ( pos < lineEnd )
			{
				// If remaining text on this line fits within width, append it
				if ( lineEnd - pos <= width )
				{
					result.append( str.substr( pos, lineEnd - pos ) );
					pos = lineEnd;
					break;
				}

				// Find the last space within width
				size_t breakPos = pos + width;
				size_t lastSpace = std::string_view::npos;
				for ( size_t i = pos; i < breakPos && i < lineEnd; ++i )
				{
					if ( str[i] == ' ' )
					{
						lastSpace = i;
					}
				}

				if ( lastSpace != std::string_view::npos )
				{
					// Break at the space
					result.append( str.substr( pos, lastSpace - pos ) );
					result += '\n';
					pos = lastSpace + 1; // Skip the space
				}
				else
				{
					// No space found, break at width
					result.append( str.substr( pos, std::min( width, lineEnd - pos ) ) );
					result += '\n';
					pos += width;
				}
			}

			// Add the original newline if there was one
			if ( newlinePos != std::string_view::npos )
			{
				result += '\n';
				lineStart = newlinePos + 1;
			}
			else
			{
				break;
			}
		}

		return result;
	}

	inline std::string indent( std::string_view str, size_t spaces )
	{
		if ( str.empty() || spaces == 0 )
		{
			return std::string( str );
		}

		std::string indentStr( spaces, ' ' );
		std::string result;
		result.reserve( str.size() + ( spaces * ( 1 + std::count( str.begin(), str.end(), '\n' ) ) ) );

		// Add indentation to first line
		result.append( indentStr );

		for ( size_t i = 0; i < str.size(); ++i )
		{
			result += str[i];
			// Add indentation after newline (even if it's the last character)
			if ( str[i] == '\n' )
			{
				result.append( indentStr );
			}
		}

		return result;
	}

	inline std::string dedent( std::string_view str )
	{
		if ( str.empty() )
		{
			return std::string( str );
		}

		// Find minimum indentation across all non-empty lines
		size_t minIndent = std::string_view::npos;
		size_t lineStart = 0;

		while ( lineStart < str.size() )
		{
			// Find end of line
			size_t lineEnd = str.find( '\n', lineStart );
			if ( lineEnd == std::string_view::npos )
			{
				lineEnd = str.size();
			}

			// Skip empty lines
			if ( lineEnd > lineStart )
			{
				// Count leading whitespace
				size_t indent = 0;
				while ( lineStart + indent < lineEnd && ( str[lineStart + indent] == ' ' || str[lineStart + indent] == '\t' ) )
				{
					++indent;
				}

				// Only count if line has non-whitespace content
				if ( lineStart + indent < lineEnd )
				{
					minIndent = ( minIndent == std::string_view::npos ) ? indent : std::min( minIndent, indent );
				}
			}

			lineStart = lineEnd + 1;
		}

		// If no indentation found, return original
		if ( minIndent == std::string_view::npos || minIndent == 0 )
		{
			return std::string( str );
		}

		// Remove minIndent from all lines
		std::string result;
		result.reserve( str.size() );
		lineStart = 0;

		while ( lineStart < str.size() )
		{
			size_t lineEnd = str.find( '\n', lineStart );
			if ( lineEnd == std::string_view::npos )
			{
				lineEnd = str.size();
			}

			// Remove indentation or entire line if it's whitespace-only
			size_t contentStart = lineStart;
			size_t indent = 0;
			while ( contentStart < lineEnd && ( str[contentStart] == ' ' || str[contentStart] == '\t' ) && indent < minIndent )
			{
				++contentStart;
				++indent;
			}

			// Append line content
			if ( lineEnd > contentStart )
			{
				result.append( str.substr( contentStart, lineEnd - contentStart ) );
			}

			// Append newline if not at end
			if ( lineEnd < str.size() )
			{
				result += '\n';
			}

			lineStart = lineEnd + 1;
		}

		return result;
	}

	//-----------------------------
	// Advanced comparison
	//-----------------------------

	inline constexpr int compareIgnoreCase( std::string_view lhs, std::string_view rhs ) noexcept
	{
		const size_t minLen = ( lhs.size() < rhs.size() ) ? lhs.size() : rhs.size();

		for ( size_t i = 0; i < minLen; ++i )
		{
			const char lc = toLower( lhs[i] );
			const char rc = toLower( rhs[i] );

			if ( lc < rc )
			{
				return -1;
			}
			if ( lc > rc )
			{
				return 1;
			}
		}

		// All characters matched, compare lengths
		if ( lhs.size() < rhs.size() )
		{
			return -1;
		}
		if ( lhs.size() > rhs.size() )
		{
			return 1;
		}
		return 0;
	}

	inline constexpr int naturalCompare( std::string_view lhs, std::string_view rhs ) noexcept
	{
		size_t i = 0;
		size_t j = 0;

		while ( i < lhs.size() && j < rhs.size() )
		{
			const char lc = lhs[i];
			const char rc = rhs[j];

			// Check if both characters are digits
			if ( isDigit( lc ) && isDigit( rc ) )
			{
				// Extract numeric values and track digit counts
				unsigned long long lNum = 0;
				unsigned long long rNum = 0;
				size_t lStart = i;
				size_t rStart = j;

				// Parse left number
				while ( i < lhs.size() && isDigit( lhs[i] ) )
				{
					lNum = lNum * 10 + ( lhs[i] - '0' );
					++i;
				}

				// Parse right number
				while ( j < rhs.size() && isDigit( rhs[j] ) )
				{
					rNum = rNum * 10 + ( rhs[j] - '0' );
					++j;
				}

				// Compare numbers
				if ( lNum < rNum )
				{
					return -1;
				}
				if ( lNum > rNum )
				{
					return 1;
				}

				// If numbers are equal, compare digit counts (e.g., "0" vs "00")
				const size_t lDigits = i - lStart;
				const size_t rDigits = j - rStart;
				if ( lDigits < rDigits )
				{
					return -1;
				}
				if ( lDigits > rDigits )
				{
					return 1;
				}
			}
			else
			{
				// Regular character comparison
				if ( lc < rc )
				{
					return -1;
				}
				if ( lc > rc )
				{
					return 1;
				}
				++i;
				++j;
			}
		}

		// All matched, compare remaining lengths
		if ( i < lhs.size() )
		{
			return 1; // lhs has more characters
		}
		if ( j < rhs.size() )
		{
			return -1; // rhs has more characters
		}
		return 0;
	}

	inline constexpr std::string_view commonPrefix( std::string_view lhs, std::string_view rhs ) noexcept
	{
		const size_t minLen = ( lhs.size() < rhs.size() ) ? lhs.size() : rhs.size();
		size_t i = 0;

		while ( i < minLen && lhs[i] == rhs[i] )
		{
			++i;
		}

		return lhs.substr( 0, i );
	}

	inline constexpr std::string_view commonSuffix( std::string_view lhs, std::string_view rhs ) noexcept
	{
		if ( lhs.empty() || rhs.empty() )
		{
			return {};
		}

		size_t lIdx = lhs.size() - 1;
		size_t rIdx = rhs.size() - 1;
		size_t matchCount = 0;

		while ( lhs[lIdx] == rhs[rIdx] )
		{
			++matchCount;

			if ( lIdx == 0 || rIdx == 0 )
			{
				break;
			}

			--lIdx;
			--rIdx;
		}

		return lhs.substr( lhs.size() - matchCount, matchCount );
	}

	//-----------------------------
	// IP address validation
	//-----------------------------

	inline constexpr bool isIPv4Address( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 15 ) // Max: "255.255.255.255"
		{
			return false;
		}

		int octetCount = 0;
		int currentOctet = 0;
		int digitCount = 0;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];

			if ( c == '.' )
			{
				if ( digitCount == 0 || currentOctet > 255 )
				{
					return false;
				}
				++octetCount;
				currentOctet = 0;
				digitCount = 0;
			}
			else if ( isDigit( c ) )
			{
				// Check for leading zero: if we have '0' and there are more digits coming in this octet
				if ( digitCount == 1 && currentOctet == 0 )
				{
					return false; // Leading zero like "01", "001", etc.
				}

				currentOctet = currentOctet * 10 + ( c - '0' );
				++digitCount;
				if ( digitCount > 3 || currentOctet > 255 )
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}

		// Must have exactly 3 dots (4 octets) and valid last octet
		return octetCount == 3 && digitCount > 0 && currentOctet <= 255;
	}

	inline constexpr bool isIPv6Address( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 45 ) // Max with zone: "[ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255%interface]"
		{
			return false;
		}

		int groupCount = 0;
		int digitCount = 0;
		bool hasDoubleColon = false;
		bool prevWasColon = false;
		std::size_t groupStartPos = 0;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];

			if ( c == ':' )
			{
				if ( prevWasColon )
				{
					if ( hasDoubleColon )
					{
						return false; // Only one :: allowed
					}
					hasDoubleColon = true;
				}
				else if ( digitCount > 0 )
				{
					++groupCount;
				}
				digitCount = 0;
				prevWasColon = true;
				groupStartPos = i + 1; // Next group starts after this colon
			}
			else if ( ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' ) )
			{
				++digitCount;
				if ( digitCount > 4 )
				{
					return false; // Max 4 hex digits per group
				}
				prevWasColon = false;
			}
			else if ( c == '.' )
			{
				// IPv4-mapped address (e.g., ::ffff:192.0.2.1)
				// Extract IPv4 part starting from where current group began
				const std::string_view ipv4Part = str.substr( groupStartPos );

				// Find where IPv4 actually ends (before % if present)
				const std::size_t percentPos = ipv4Part.find( '%' );
				const std::string_view ipv4Only = ( percentPos != std::string_view::npos )
													  ? ipv4Part.substr( 0, percentPos )
													  : ipv4Part;

				if ( !isIPv4Address( ipv4Only ) )
				{
					return false;
				}
				// IPv4 part counts as 2 groups (32 bits = 2 x 16-bit groups)
				groupCount += 2;
				break; // IPv4 is at the end
			}
			else if ( c == '%' )
			{
				// Zone ID - rest is interface name, accept it
				if ( digitCount > 0 )
				{
					++groupCount;
				}
				break;
			}
			else
			{
				return false;
			}
		}

		if ( digitCount > 0 && str.find( '.' ) == std::string_view::npos )
		{
			++groupCount; // Only count if not IPv4-mapped (already counted above)
		}

		// Valid: 8 groups, or less with :: compression
		return ( groupCount == 8 && !hasDoubleColon ) || ( groupCount < 8 && hasDoubleColon );
	}

	//-----------------------------
	// Host validation
	//-----------------------------

	inline constexpr bool isValidHostname( std::string_view str ) noexcept
	{
		// RFC 1123: max 253 chars, labels max 63 chars, alphanumeric + hyphen
		if ( str.empty() || str.size() > 253 )
		{
			return false;
		}

		int labelLength = 0;
		bool prevWasDot = true;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];

			if ( c == '.' )
			{
				if ( prevWasDot || labelLength == 0 )
				{
					return false; // Empty label or consecutive dots
				}
				if ( str[i - 1] == '-' )
				{
					return false; // Label can't end with hyphen
				}
				labelLength = 0;
				prevWasDot = true;
			}
			else if ( isAlphaNumeric( c ) || c == '-' )
			{
				if ( prevWasDot && c == '-' )
				{
					return false; // Label can't start with hyphen
				}
				++labelLength;
				if ( labelLength > 63 )
				{
					return false; // Label too long
				}
				prevWasDot = false;
			}
			else
			{
				return false; // Invalid character
			}
		}

		// Can't end with dot or hyphen
		return !prevWasDot && labelLength > 0 && str[str.size() - 1] != '-';
	}

	inline constexpr bool isDomainName( std::string_view str ) noexcept
	{
		// Must be valid hostname AND contain at least one dot
		if ( !isValidHostname( str ) )
		{
			return false;
		}

		// Check for at least one dot
		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( str[i] == '.' )
			{
				return true;
			}
		}

		return false;
	}

	//-----------------------------
	// Port validation
	//-----------------------------

	inline constexpr bool isValidPort( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 5 ) // Max: "65535"
		{
			return false;
		}

		int portValue = 0;

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( !isDigit( str[i] ) )
			{
				return false;
			}
			portValue = portValue * 10 + ( str[i] - '0' );
			if ( portValue > 65535 )
			{
				return false;
			}
		}

		return true;
	}

	//-----------------------------
	// Endpoint parsing
	//-----------------------------

	inline bool tryParseEndpoint( std::string_view endpoint, std::string_view& host, uint16_t& port ) noexcept
	{
		if ( endpoint.empty() )
		{
			return false;
		}

		// Check for IPv6 format: [host]:port
		if ( endpoint[0] == '[' )
		{
			const std::size_t closingBracket = endpoint.find( ']' );
			if ( closingBracket == std::string_view::npos )
			{
				return false;
			}

			host = endpoint.substr( 1, closingBracket - 1 );

			// Check for :port after ]
			if ( closingBracket + 1 < endpoint.size() )
			{
				if ( endpoint[closingBracket + 1] != ':' )
				{
					return false;
				}
				const std::string_view portStr = endpoint.substr( closingBracket + 2 );
				if ( !isValidPort( portStr ) )
				{
					return false;
				}
				// Parse port
				uint32_t portValue = 0;
				if ( !fromString<uint32_t>( portStr, portValue ) || portValue > 65535 )
				{
					return false;
				}
				port = static_cast<uint16_t>( portValue );
			}
			else
			{
				return false; // No port specified
			}

			return isIPv6Address( host );
		}

		// IPv4 or hostname format: host:port
		const std::size_t colonPos = endpoint.rfind( ':' ); // Last colon
		if ( colonPos == std::string_view::npos )
		{
			return false; // No port separator
		}

		host = endpoint.substr( 0, colonPos );
		const std::string_view portStr = endpoint.substr( colonPos + 1 );

		if ( host.empty() || portStr.empty() )
		{
			return false;
		}

		if ( !isValidPort( portStr ) )
		{
			return false;
		}

		// Parse port
		uint32_t portValue = 0;
		if ( !fromString<uint32_t>( portStr, portValue ) || portValue > 65535 )
		{
			return false;
		}
		port = static_cast<uint16_t>( portValue );

		// If host contains only digits and dots, it must be a valid IPv4
		// Otherwise validate as hostname
		const bool looksLikeIPv4 = std::all_of( host.begin(), host.end(),
			[]( char c ) { return isDigit( c ) || c == '.'; } );

		if ( looksLikeIPv4 )
		{
			return isIPv4Address( host );
		}

		return isValidHostname( host );
	}

	//-----------------------------
	// Date and Time validation (RFC 3339)
	//-----------------------------

	inline constexpr bool isDate( std::string_view str ) noexcept
	{
		// Format: YYYY-MM-DD (10 characters)
		if ( str.size() != 10 )
		{
			return false;
		}

		// Check format: YYYY-MM-DD
		if ( str[4] != '-' || str[7] != '-' )
		{
			return false;
		}

		// Validate year (4 digits)
		for ( int i = 0; i < 4; ++i )
		{
			if ( !isDigit( str[i] ) )
			{
				return false;
			}
		}

		// Validate month (01-12)
		if ( !isDigit( str[5] ) || !isDigit( str[6] ) )
		{
			return false;
		}
		const int month = ( str[5] - '0' ) * 10 + ( str[6] - '0' );
		if ( month < 1 || month > 12 )
		{
			return false;
		}

		// Validate day (01-31)
		if ( !isDigit( str[8] ) || !isDigit( str[9] ) )
		{
			return false;
		}
		const int day = ( str[8] - '0' ) * 10 + ( str[9] - '0' );
		if ( day < 1 || day > 31 )
		{
			return false;
		}

		// Basic month/day validation (not checking leap years for simplicity)
		constexpr int daysInMonth[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if ( day > daysInMonth[month] )
		{
			return false;
		}

		return true;
	}

	inline constexpr bool isTime( std::string_view str ) noexcept
	{
		// Minimum format: HH:MM:SSZ (9 characters)
		if ( str.size() < 9 )
		{
			return false;
		}

		// Validate hours (00-23)
		if ( !isDigit( str[0] ) || !isDigit( str[1] ) )
		{
			return false;
		}
		const int hour = ( str[0] - '0' ) * 10 + ( str[1] - '0' );
		if ( hour > 23 )
		{
			return false;
		}

		if ( str[2] != ':' )
		{
			return false;
		}

		// Validate minutes (00-59)
		if ( !isDigit( str[3] ) || !isDigit( str[4] ) )
		{
			return false;
		}
		const int minute = ( str[3] - '0' ) * 10 + ( str[4] - '0' );
		if ( minute > 59 )
		{
			return false;
		}

		if ( str[5] != ':' )
		{
			return false;
		}

		// Validate seconds (00-60, where 60 is for leap seconds)
		if ( !isDigit( str[6] ) || !isDigit( str[7] ) )
		{
			return false;
		}
		const int second = ( str[6] - '0' ) * 10 + ( str[7] - '0' );
		if ( second > 60 )
		{
			return false;
		}

		std::size_t pos = 8;

		// Optional fractional seconds
		if ( pos < str.size() && str[pos] == '.' )
		{
			++pos;
			if ( pos >= str.size() || !isDigit( str[pos] ) )
			{
				return false;
			}
			while ( pos < str.size() && isDigit( str[pos] ) )
			{
				++pos;
			}
		}

		// Timezone required: Z or ±HH:MM
		if ( pos >= str.size() )
		{
			return false;
		}

		if ( str[pos] == 'Z' || str[pos] == 'z' )
		{
			return pos + 1 == str.size();
		}

		if ( str[pos] != '+' && str[pos] != '-' )
		{
			return false;
		}
		++pos;

		// Validate timezone offset HH:MM
		if ( pos + 5 != str.size() )
		{
			return false;
		}

		// Timezone hours (00-23)
		if ( !isDigit( str[pos] ) || !isDigit( str[pos + 1] ) )
		{
			return false;
		}
		const int tzHour = ( str[pos] - '0' ) * 10 + ( str[pos + 1] - '0' );
		if ( tzHour > 23 )
		{
			return false;
		}

		if ( str[pos + 2] != ':' )
		{
			return false;
		}

		// Timezone minutes (00-59)
		if ( !isDigit( str[pos + 3] ) || !isDigit( str[pos + 4] ) )
		{
			return false;
		}
		const int tzMinute = ( str[pos + 3] - '0' ) * 10 + ( str[pos + 4] - '0' );
		if ( tzMinute > 59 )
		{
			return false;
		}

		return true;
	}

	inline constexpr bool isDateTime( std::string_view str ) noexcept
	{
		// Minimum format: YYYY-MM-DDTHH:MM:SSZ (20 characters)
		if ( str.size() < 20 )
		{
			return false;
		}

		// Check separator (T or t)
		if ( str[10] != 'T' && str[10] != 't' )
		{
			return false;
		}

		// Validate date part
		if ( !isDate( str.substr( 0, 10 ) ) )
		{
			return false;
		}

		// Validate time part
		if ( !isTime( str.substr( 11 ) ) )
		{
			return false;
		}

		// Special validation for leap seconds (60 seconds only valid at 23:59:60 on June 30 or December 31)
		// Check if time has :60 seconds
		if ( str.size() >= 19 && str[17] == '6' && str[18] == '0' )
		{
			// Must be 23:59:60
			if ( str[11] != '2' || str[12] != '3' || str[14] != '5' || str[15] != '9' )
			{
				return false;
			}

			// Must be June 30 (06-30) or December 31 (12-31)
			const bool isJune30 = ( str[5] == '0' && str[6] == '6' && str[8] == '3' && str[9] == '0' );
			const bool isDec31 = ( str[5] == '1' && str[6] == '2' && str[8] == '3' && str[9] == '1' );

			if ( !isJune30 && !isDec31 )
			{
				return false;
			}
		}

		return true;
	}

	inline constexpr bool isDuration( std::string_view str ) noexcept
	{
		// Minimum: P followed by at least one designator
		if ( str.size() < 2 || str[0] != 'P' )
		{
			return false;
		}

		std::size_t pos = 1;
		bool hasDatePart = false;
		bool hasTimePart = false;
		bool inTimePart = false;

		// Check for week format: P[n]W
		if ( pos < str.size() && isDigit( str[pos] ) )
		{
			while ( pos < str.size() && isDigit( str[pos] ) )
			{
				++pos;
			}
			if ( pos < str.size() && str[pos] == 'W' )
			{
				return pos + 1 == str.size(); // Week format must be alone
			}
			// Reset for non-week format
			pos = 1;
		}

		while ( pos < str.size() )
		{
			if ( str[pos] == 'T' )
			{
				if ( inTimePart )
				{
					return false; // Duplicate T
				}
				inTimePart = true;
				++pos;
				continue;
			}

			// Parse number
			if ( !isDigit( str[pos] ) )
			{
				return false;
			}

			while ( pos < str.size() && isDigit( str[pos] ) )
			{
				++pos;
			}

			// Handle decimal in seconds
			if ( pos < str.size() && str[pos] == '.' )
			{
				++pos;
				if ( pos >= str.size() || !isDigit( str[pos] ) )
				{
					return false;
				}
				while ( pos < str.size() && isDigit( str[pos] ) )
				{
					++pos;
				}
			}

			if ( pos >= str.size() )
			{
				return false; // Number without designator
			}

			const char designator = str[pos];
			++pos;

			if ( inTimePart )
			{
				if ( designator != 'H' && designator != 'M' && designator != 'S' )
				{
					return false;
				}
				hasTimePart = true;
			}
			else
			{
				if ( designator != 'Y' && designator != 'M' && designator != 'D' )
				{
					return false;
				}
				hasDatePart = true;
			}
		}

		// If T was present, must have time parts
		if ( inTimePart && !hasTimePart )
		{
			return false;
		}

		return hasDatePart || hasTimePart;
	}

	//-----------------------------
	// Email validation (RFC 5321)
	//-----------------------------

	inline constexpr bool isEmail( std::string_view str ) noexcept
	{
		if ( str.empty() || str.size() > 254 )
		{
			return false;
		}

		// Find @ symbol
		std::size_t atPos = str.find( '@' );
		if ( atPos == std::string_view::npos || atPos == 0 || atPos == str.size() - 1 )
		{
			return false;
		}

		const std::string_view localPart = str.substr( 0, atPos );
		const std::string_view domain = str.substr( atPos + 1 );

		// Local part validation (simplified)
		if ( localPart.empty() || localPart.size() > 64 )
		{
			return false;
		}

		// Local part: alphanumeric and special chars .!#$%&'*+/=?^_`{|}~-
		// Cannot start or end with dot, no consecutive dots
		bool prevDot = true; // Treat start as after dot to catch leading dot
		for ( char c : localPart )
		{
			if ( c == '.' )
			{
				if ( prevDot )
				{
					return false; // Consecutive dots or leading dot
				}
				prevDot = true;
			}
			else
			{
				if ( !isAlphaNumeric( c ) && c != '!' && c != '#' && c != '$' && c != '%' &&
					 c != '&' && c != '\'' && c != '*' && c != '+' && c != '/' && c != '=' &&
					 c != '?' && c != '^' && c != '_' && c != '`' && c != '{' && c != '|' &&
					 c != '}' && c != '~' && c != '-' )
				{
					return false;
				}
				prevDot = false;
			}
		}
		if ( prevDot )
		{
			return false; // Trailing dot
		}

		// Domain validation: must be valid domain name (hostname with at least one dot)
		return isDomainName( domain );
	}

	//-----------------------------
	// UUID validation (RFC 4122)
	//-----------------------------

	inline constexpr bool isUUID( std::string_view str ) noexcept
	{
		// Format: 8-4-4-4-12 = 36 characters
		if ( str.size() != 36 )
		{
			return false;
		}

		// Check hyphens at positions 8, 13, 18, 23
		if ( str[8] != '-' || str[13] != '-' || str[18] != '-' || str[23] != '-' )
		{
			return false;
		}

		// Validate hex digits
		auto isHexDigit = []( char c ) constexpr noexcept {
			return isDigit( c ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' );
		};

		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			if ( i == 8 || i == 13 || i == 18 || i == 23 )
			{
				continue; // Skip hyphens
			}
			if ( !isHexDigit( str[i] ) )
			{
				return false;
			}
		}

		return true;
	}

	//-----------------------------
	// URI validation (RFC 3986)
	//-----------------------------

	inline constexpr bool isURI( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}

		// Scheme must start with letter
		if ( !isAlpha( str[0] ) )
		{
			return false;
		}

		// Find scheme separator ':'
		std::size_t colonPos = 0;
		for ( std::size_t i = 1; i < str.size(); ++i )
		{
			const char c = str[i];
			if ( c == ':' )
			{
				colonPos = i;
				break;
			}
			// Scheme: ALPHA *( ALPHA / DIGIT / "+" / "-" / "." )
			if ( !isAlphaNumeric( c ) && c != '+' && c != '-' && c != '.' )
			{
				return false;
			}
		}

		if ( colonPos == 0 )
		{
			return false; // No scheme
		}

		// After scheme, must have something (could be empty path, but typically has content)
		// Basic validation: no whitespace allowed
		for ( std::size_t i = colonPos + 1; i < str.size(); ++i )
		{
			if ( isWhitespace( str[i] ) )
			{
				return false;
			}
		}

		return true;
	}

	inline constexpr bool isURIReference( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return true; // Empty string is valid relative-reference
		}

		// Check if it's a URI (has scheme)
		for ( std::size_t i = 0; i < str.size(); ++i )
		{
			const char c = str[i];
			if ( c == ':' )
			{
				// Has scheme, validate as URI
				if ( i > 0 && isAlpha( str[0] ) )
				{
					return isURI( str );
				}
				break;
			}
			if ( c == '/' || c == '?' || c == '#' )
			{
				break; // Relative reference
			}
			if ( i == 0 && !isAlpha( c ) )
			{
				break; // Can't be scheme
			}
			if ( !isAlphaNumeric( c ) && c != '+' && c != '-' && c != '.' )
			{
				break; // Invalid scheme char
			}
		}

		// Relative reference: no whitespace allowed
		for ( char c : str )
		{
			if ( isWhitespace( c ) )
			{
				return false;
			}
		}

		return true;
	}

	//-----------------------------
	// JSON Pointer validation (RFC 6901)
	//-----------------------------

	inline constexpr bool isJSONPointer( std::string_view str ) noexcept
	{
		// Empty string is valid (references whole document)
		if ( str.empty() )
		{
			return true;
		}

		// Must start with '/'
		if ( str[0] != '/' )
		{
			return false;
		}

		// Validate reference tokens
		for ( std::size_t i = 1; i < str.size(); ++i )
		{
			const char c = str[i];

			// Check escape sequences
			if ( c == '~' )
			{
				// Must be followed by 0 or 1
				if ( i + 1 >= str.size() )
				{
					return false;
				}
				const char next = str[i + 1];
				if ( next != '0' && next != '1' )
				{
					return false;
				}
				++i; // Skip the escaped character
			}
			// '/' starts new token (always valid)
		}

		return true;
	}

	inline constexpr bool isRelativeJSONPointer( std::string_view str ) noexcept
	{
		if ( str.empty() )
		{
			return false;
		}

		// Must start with non-negative integer
		if ( !isDigit( str[0] ) )
		{
			return false;
		}

		// Leading zeros not allowed (except "0" alone)
		if ( str[0] == '0' && str.size() > 1 && isDigit( str[1] ) )
		{
			return false;
		}

		std::size_t pos = 0;
		while ( pos < str.size() && isDigit( str[pos] ) )
		{
			++pos;
		}

		if ( pos == str.size() )
		{
			return true; // Just a non-negative integer is valid
		}

		if ( str[pos] == '#' )
		{
			return pos + 1 == str.size(); // # must be at end
		}

		// Rest must be valid JSON Pointer (starting with /)
		return isJSONPointer( str.substr( pos ) );
	}
} // namespace nfx::string

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
 * @file Utils.h
 * @brief High-performance string utilities for NFX C++ library
 * @details Provides fast, zero-allocation string operations including validation,
 *          parsing, and comparison functions using std::string_view for maximum performance.
 */

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace nfx::string
{
    //=====================================================================
    // String utilities
    //=====================================================================

    //----------------------------------------------
    // String validation
    //----------------------------------------------

    /**
     * @brief Fast check if string has exact length
     * @param str String to check
     * @param expectedLength Expected length
     * @return True if string has exact expected length
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool hasExactLength( std::string_view str, std::size_t expectedLength ) noexcept;

    /**
     * @brief Fast check if string is empty
     * @param str String to check
     * @return True if string is empty
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isEmpty( std::string_view str ) noexcept;

    /**
     * @brief Fast check if string is null, empty, or contains only whitespace
     * @param str String to check
     * @return True if string is empty or contains only whitespace characters
     * @details Considers space, tab, newline, carriage return, form feed, and vertical tab as whitespace
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isNullOrWhiteSpace( std::string_view str ) noexcept;

    /**
     * @brief Check if string contains only ASCII digits
     * @param str String to check
     * @return True if string is non-empty and contains only digits (0-9)
     * @details Returns false for empty strings. Uses the existing isDigit() function for validation.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isAllDigits( std::string_view str ) noexcept;

    //----------------------------------------------
    // Character classification
    //----------------------------------------------

    /**
     * @brief Check if character is whitespace
     * @param c Character to check
     * @return True if character is space, tab, newline, carriage return, form feed, or vertical tab
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isWhitespace( char c ) noexcept;

    /**
     * @brief Check if character is ASCII digit
     * @param c Character to check
     * @return True if character is 0-9
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isDigit( char c ) noexcept;

    /**
     * @brief Check if character is ASCII alphabetic
     * @param c Character to check
     * @return True if character is a-z or A-Z
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isAlpha( char c ) noexcept;

    /**
     * @brief Check if character is ASCII alphanumeric
     * @param c Character to check
     * @return True if character is a-z, A-Z, or 0-9
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isAlphaNumeric( char c ) noexcept;

    /**
     * @brief Check if character is ASCII hexadecimal digit
     * @param c Character to check
     * @return True if character is 0-9, a-f, or A-F
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isHexDigit( char c ) noexcept;

    //----------------------------------------------
    // String operations
    //----------------------------------------------

    /**
     * @brief Fast check if string starts with prefix
     * @param str String to check
     * @param prefix Prefix to find
     * @return True if str starts with prefix
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool startsWith( std::string_view str, std::string_view prefix ) noexcept;

    /**
     * @brief Fast check if string starts with character
     * @param str String to check
     * @param prefix Character to find
     * @return True if str starts with prefix
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool startsWith( std::string_view str, char prefix ) noexcept;

    /**
     * @brief Fast check if string starts with C-string prefix
     * @param str String to check
     * @param prefix C-string prefix to find
     * @return True if str starts with prefix
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool startsWith( std::string_view str, const char* prefix ) noexcept;

    /**
     * @brief Case-insensitive check if string starts with prefix
     * @param str String to check
     * @param prefix Prefix to find (case-insensitive)
     * @return True if str starts with prefix (ignoring case)
     * @details Performs ASCII case-insensitive comparison. Useful for protocol detection, file extensions, etc.
     *          Example: istartsWith("Hello", "hel") returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool istartsWith( std::string_view str, std::string_view prefix ) noexcept;

    /**
     * @brief Case-insensitive check if string starts with character
     * @param str String to check
     * @param prefix Character to find (case-insensitive)
     * @return True if str starts with prefix (ignoring case)
     * @details Performs ASCII case-insensitive comparison.
     *          Example: istartsWith("Hello", 'h') returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool istartsWith( std::string_view str, char prefix ) noexcept;

    /**
     * @brief Case-insensitive check if string starts with C-string prefix
     * @param str String to check
     * @param prefix C-string prefix to find (case-insensitive)
     * @return True if str starts with prefix (ignoring case)
     * @details Performs ASCII case-insensitive comparison.
     *          Example: istartsWith("HTTPS://example.com", "http") returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool istartsWith( std::string_view str, const char* prefix ) noexcept;

    /**
     * @brief Fast check if string ends with suffix
     * @param str String to check
     * @param suffix Suffix to find
     * @return True if str ends with suffix
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool endsWith( std::string_view str, std::string_view suffix ) noexcept;

    /**
     * @brief Fast check if string ends with character
     * @param str String to check
     * @param suffix Character to find
     * @return True if str ends with suffix
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool endsWith( std::string_view str, char suffix ) noexcept;

    /**
     * @brief Fast check if string ends with C-string suffix
     * @param str String to check
     * @param suffix C-string suffix to find
     * @return True if str ends with suffix
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool endsWith( std::string_view str, const char* suffix ) noexcept;

    /**
     * @brief Case-insensitive check if string ends with suffix
     * @param str String to check
     * @param suffix Suffix to find (case-insensitive)
     * @return True if str ends with suffix (ignoring case)
     * @details Performs ASCII case-insensitive comparison. Useful for file extension checking.
     *          Example: iendsWith("file.TXT", ".txt") returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool iendsWith( std::string_view str, std::string_view suffix ) noexcept;

    /**
     * @brief Case-insensitive check if string ends with character
     * @param str String to check
     * @param suffix Character to find (case-insensitive)
     * @return True if str ends with suffix (ignoring case)
     * @details Performs ASCII case-insensitive comparison.
     *          Example: iendsWith("Test", 't') returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool iendsWith( std::string_view str, char suffix ) noexcept;

    /**
     * @brief Case-insensitive check if string ends with C-string suffix
     * @param str String to check
     * @param suffix C-string suffix to find (case-insensitive)
     * @return True if str ends with suffix (ignoring case)
     * @details Performs ASCII case-insensitive comparison.
     *          Example: iendsWith("Document.PDF", ".pdf") returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool iendsWith( std::string_view str, const char* suffix ) noexcept;

    /**
     * @brief Fast check if string contains substring
     * @param str String to check
     * @param substr Substring to find
     * @return True if str contains substr
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool contains( std::string_view str, std::string_view substr ) noexcept;

    /**
     * @brief Fast check if string contains character
     * @param str String to check
     * @param ch Character to find
     * @return True if str contains ch
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool contains( std::string_view str, char ch ) noexcept;

    /**
     * @brief Fast check if string contains C-string substring
     * @param str String to check
     * @param substr C-string substring to find
     * @return True if str contains substr
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool contains( std::string_view str, const char* substr ) noexcept;

    /**
     * @brief Case-insensitive check if string contains substring
     * @param str String to check
     * @param substr Substring to find (case-insensitive)
     * @return True if str contains substr (ignoring case)
     * @details Performs ASCII case-insensitive search. Useful for search functionality, keyword matching.
     *          Example: icontains("Hello World", "WORLD") returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool icontains( std::string_view str, std::string_view substr ) noexcept;

    /**
     * @brief Case-insensitive check if string contains character
     * @param str String to check
     * @param ch Character to find (case-insensitive)
     * @return True if str contains ch (ignoring case)
     * @details Performs ASCII case-insensitive search.
     *          Example: icontains("Hello", 'L') returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool icontains( std::string_view str, char ch ) noexcept;

    /**
     * @brief Case-insensitive check if string contains C-string substring
     * @param str String to check
     * @param substr C-string substring to find (case-insensitive)
     * @return True if str contains substr (ignoring case)
     * @details Performs ASCII case-insensitive search.
     *          Example: icontains("Content-Type", "type") returns true
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool icontains( std::string_view str, const char* substr ) noexcept;

    /**
     * @brief Fast case-sensitive string comparison
     * @param lhs First string
     * @param rhs Second string
     * @return True if strings are exactly equal
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool equals( std::string_view lhs, std::string_view rhs ) noexcept;

    /**
     * @brief Fast case-insensitive string comparison
     * @param lhs First string
     * @param rhs Second string
     * @return True if strings are equal (case-insensitive)
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool iequals( std::string_view lhs, std::string_view rhs ) noexcept;

    /**
     * @brief Count occurrences of substring in string
     * @param str String to search in
     * @param substr Substring to count
     * @return Number of non-overlapping occurrences of substr in str
     * @details Returns 0 if substr is empty or not found. Counts non-overlapping matches.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::size_t count( std::string_view str, std::string_view substr ) noexcept;

    /**
     * @brief Count overlapping occurrences of substring in string
     * @param str String to search in
     * @param substr Substring to count
     * @return Number of overlapping occurrences of substr in str
     * @details Returns 0 if substr is empty or not found. Counts all matches including overlapping ones.
     *          Example: countOverlapping("aaaa", "aa") returns 3 (positions 0, 1, 2)
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::size_t countOverlapping( std::string_view str, std::string_view substr ) noexcept;

    /**
     * @brief Count occurrences of character in string
     * @param str String to search in
     * @param ch Character to count
     * @return Number of occurrences of ch in str
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::size_t count( std::string_view str, char ch ) noexcept;

    /**
     * @brief Replace first occurrence of substring with replacement
     * @param str String to search in
     * @param oldStr Substring to replace
     * @param newStr Replacement string
     * @return New string with first occurrence replaced, or copy of original if oldStr not found
     * @details Returns original string if oldStr is empty
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string replace( std::string_view str, std::string_view oldStr, std::string_view newStr );

    /**
     * @brief Replace all occurrences of substring with replacement
     * @param str String to search in
     * @param oldStr Substring to replace
     * @param newStr Replacement string
     * @return New string with all non-overlapping occurrences replaced
     * @details Returns original string if oldStr is empty or not found
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string replaceAll( std::string_view str, std::string_view oldStr, std::string_view newStr );

    /**
     * @brief Join container elements with delimiter
     * @tparam Container Container type (must support begin()/end() and value_type convertible to string_view)
     * @param elements Container of elements to join
     * @param delimiter Delimiter to insert between elements
     * @return Joined string with delimiter between elements
     * @details Returns empty string for empty container. Single element returns that element without delimiter.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Container>
    [[nodiscard]] inline std::string join( const Container& elements, std::string_view delimiter );

    /**
     * @brief Join iterator range with delimiter
     * @tparam Iterator Forward iterator type (value_type must be convertible to string_view)
     * @param begin Iterator to first element
     * @param end Iterator past last element
     * @param delimiter Delimiter to insert between elements
     * @return Joined string with delimiter between elements
     * @details Returns empty string for empty range. Single element returns that element without delimiter.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Iterator>
    [[nodiscard]] inline std::string join( Iterator begin, Iterator end, std::string_view delimiter );

    /**
     * @brief Reverse a string
     * @param str String to reverse
     * @return New string with characters in reverse order
     * @details Returns empty string for empty input. Efficient single-pass algorithm.
     *          Example: reverse("hello") returns "olleh"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string reverse( std::string_view str );

    /**
     * @brief Find first occurrence of substring
     * @param str String to search in
     * @param substr Substring to find
     * @return Index of first occurrence, or std::string_view::npos if not found
     * @details Returns 0 for empty substr. Case-sensitive search.
     *          Example: indexOf("hello world", "world") returns 6
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::size_t indexOf( std::string_view str, std::string_view substr ) noexcept;

    /**
     * @brief Find first occurrence of character
     * @param str String to search in
     * @param ch Character to find
     * @return Index of first occurrence, or std::string_view::npos if not found
     * @details Case-sensitive search.
     *          Example: indexOf("hello world", 'o') returns 4
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::size_t indexOf( std::string_view str, char ch ) noexcept;

    /**
     * @brief Find last occurrence of substring
     * @param str String to search in
     * @param substr Substring to find
     * @return Index of last occurrence, or std::string_view::npos if not found
     * @details Returns 0 for empty substr. Case-sensitive search.
     *          Example: lastIndexOf("hello hello", "hello") returns 6
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::size_t lastIndexOf( std::string_view str, std::string_view substr ) noexcept;

    /**
     * @brief Find last occurrence of character
     * @param str String to search in
     * @param ch Character to find
     * @return Index of last occurrence, or std::string_view::npos if not found
     * @details Case-sensitive search.
     *          Example: lastIndexOf("hello", 'l') returns 3
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::size_t lastIndexOf( std::string_view str, char ch ) noexcept;

    //----------------------------------------------
    // String formatting and padding
    //----------------------------------------------

    /**
     * @brief Pad string on the left to reach specified width
     * @param str String to pad
     * @param width Target width (total length after padding)
     * @param fillChar Character to use for padding (default: space)
     * @return Padded string (right-aligned). Returns original if already wider than width.
     * @details Example: padLeft("42", 5, '0') returns "00042"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string padLeft( std::string_view str, std::size_t width, char fillChar = ' ' );

    /**
     * @brief Pad string on the right to reach specified width
     * @param str String to pad
     * @param width Target width (total length after padding)
     * @param fillChar Character to use for padding (default: space)
     * @return Padded string (left-aligned). Returns original if already wider than width.
     * @details Example: padRight("42", 5, '0') returns "42000"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string padRight( std::string_view str, std::size_t width, char fillChar = ' ' );

    /**
     * @brief Center string within specified width
     * @param str String to center
     * @param width Target width (total length after padding)
     * @param fillChar Character to use for padding (default: space)
     * @return Centered string with fillChar on both sides. Returns original if already wider than width.
     * @details If padding is odd, extra character goes on the right.
     *          Example: center("Hi", 6, '*') returns "**Hi**"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string center( std::string_view str, std::size_t width, char fillChar = ' ' );

    /**
     * @brief Repeat string specified number of times
     * @param str String to repeat
     * @param count Number of repetitions
     * @return String repeated count times. Returns empty string if count is 0.
     * @details Example: repeat("*", 5) returns "*****"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string repeat( std::string_view str, std::size_t count );

    //----------------------------------------------
    // Substring extraction
    //----------------------------------------------

    /**
     * @brief Extract substring before first occurrence of delimiter
     * @param str String to search in
     * @param delimiter Delimiter to search for
     * @return String view of portion before delimiter, or entire string if delimiter not found
     * @details Zero-allocation. Example: substringBefore("hello.world.txt", ".") returns "hello"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringBefore( std::string_view str, std::string_view delimiter ) noexcept;

    /**
     * @brief Extract substring before first occurrence of character delimiter
     * @param str String to search in
     * @param delimiter Character delimiter to search for
     * @return String view of portion before delimiter, or entire string if delimiter not found
     * @details Zero-allocation. Example: substringBefore("hello.world", '.') returns "hello"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringBefore( std::string_view str, char delimiter ) noexcept;

    /**
     * @brief Extract substring after first occurrence of delimiter
     * @param str String to search in
     * @param delimiter Delimiter to search for
     * @return String view of portion after delimiter, or empty string if delimiter not found
     * @details Zero-allocation. Example: substringAfter("hello.world.txt", ".") returns "world.txt"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringAfter( std::string_view str, std::string_view delimiter ) noexcept;

    /**
     * @brief Extract substring after first occurrence of character delimiter
     * @param str String to search in
     * @param delimiter Character delimiter to search for
     * @return String view of portion after delimiter, or empty string if delimiter not found
     * @details Zero-allocation. Example: substringAfter("hello.world", '.') returns "world"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringAfter( std::string_view str, char delimiter ) noexcept;

    /**
     * @brief Extract substring before last occurrence of delimiter
     * @param str String to search in
     * @param delimiter Delimiter to search for
     * @return String view of portion before last delimiter, or entire string if delimiter not found
     * @details Zero-allocation. Example: substringBeforeLast("hello.world.txt", ".") returns "hello.world"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringBeforeLast( std::string_view str, std::string_view delimiter ) noexcept;

    /**
     * @brief Extract substring before last occurrence of character delimiter
     * @param str String to search in
     * @param delimiter Character delimiter to search for
     * @return String view of portion before last delimiter, or entire string if delimiter not found
     * @details Zero-allocation. Example: substringBeforeLast("hello.world.txt", '.') returns "hello.world"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringBeforeLast( std::string_view str, char delimiter ) noexcept;

    /**
     * @brief Extract substring after last occurrence of delimiter
     * @param str String to search in
     * @param delimiter Delimiter to search for
     * @return String view of portion after last delimiter, or empty string if delimiter not found
     * @details Zero-allocation. Example: substringAfterLast("hello.world.txt", ".") returns "txt"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringAfterLast( std::string_view str, std::string_view delimiter ) noexcept;

    /**
     * @brief Extract substring after last occurrence of character delimiter
     * @param str String to search in
     * @param delimiter Character delimiter to search for
     * @return String view of portion after last delimiter, or empty string if delimiter not found
     * @details Zero-allocation. Example: substringAfterLast("hello.world.txt", '.') returns "txt"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view substringAfterLast( std::string_view str, char delimiter ) noexcept;

    /**
     * @brief Extract substring between start and end delimiters
     * @param str String to search in
     * @param start Starting delimiter
     * @param end Ending delimiter
     * @return String view of portion between delimiters, or empty string if either delimiter not found
     * @details Zero-allocation. Searches for first occurrence of start, then first occurrence of end after that.
     *          Example: extractBetween("Hello [world] test", "[", "]") returns "world"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view extractBetween( std::string_view str, std::string_view start, std::string_view end ) noexcept;

    /**
     * @brief Remove prefix from string if present
     * @param str String to process
     * @param prefix Prefix to remove
     * @return String view with prefix removed, or original string if prefix not present
     * @details Zero-allocation. Example: removePrefix("HelloWorld", "Hello") returns "World"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view removePrefix( std::string_view str, std::string_view prefix ) noexcept;

    /**
     * @brief Remove suffix from string if present
     * @param str String to process
     * @param suffix Suffix to remove
     * @return String view with suffix removed, or original string if suffix not present
     * @details Zero-allocation. Example: removeSuffix("HelloWorld", "World") returns "Hello"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view removeSuffix( std::string_view str, std::string_view suffix ) noexcept;

    //----------------------------------------------
    // Character & String Removal
    //----------------------------------------------

    /**
     * @brief Remove all occurrences of a character from string
     * @param str String to process
     * @param ch Character to remove
     * @return New string with all occurrences of character removed
     * @details Allocates a new std::string. Example: removeAll("hello", 'l') returns "heo"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string removeAll( std::string_view str, char ch );

    /**
     * @brief Remove all occurrences of a substring from string
     * @param str String to process
     * @param substr Substring to remove
     * @return New string with all occurrences of substring removed
     * @details Allocates a new std::string. Does not handle overlapping matches.
     *          Example: removeAll("hello world", "l") returns "heo word"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string removeAll( std::string_view str, std::string_view substr );

    /**
     * @brief Remove all characters matching a predicate from string
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to process
     * @param pred Predicate function or lambda to test each character
     * @return New string with all matching characters removed
     * @details Allocates a new std::string. Example: removeIf("hello123", isDigit) returns "hello"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline std::string removeIf( std::string_view str, Predicate pred );

    /**
     * @brief Remove all whitespace characters from string
     * @param str String to process
     * @return New string with all whitespace removed
     * @details Allocates a new std::string. Removes spaces, tabs, newlines, etc.
     *          Example: removeWhitespace("hello world") returns "helloworld"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string removeWhitespace( std::string_view str );

    /**
     * @brief Collapse consecutive whitespace characters to single space
     * @param str String to process
     * @return New string with consecutive whitespace collapsed and trimmed
     * @details Allocates a new std::string. Trims leading/trailing whitespace and collapses
     *          consecutive whitespace (spaces, tabs, newlines) to single space.
     *          Example: collapseWhitespace("  hello   world  ") returns "hello world"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string collapseWhitespace( std::string_view str );

    //----------------------------------------------
    // String trimming
    //----------------------------------------------

    /**
     * @brief Remove leading whitespace from string
     * @param str String to trim
     * @return String view with leading whitespace removed
     * @details Returns a view into the original string, no allocation performed
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view trimStart( std::string_view str ) noexcept;

    /**
     * @brief Remove trailing whitespace from string
     * @param str String to trim
     * @return String view with trailing whitespace removed
     * @details Returns a view into the original string, no allocation performed
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view trimEnd( std::string_view str ) noexcept;

    /**
     * @brief Remove leading and trailing whitespace from string
     * @param str String to trim
     * @return String view with leading and trailing whitespace removed
     * @details Returns a view into the original string, no allocation performed
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view trim( std::string_view str ) noexcept;

    //----------------------------------------------
    // Predicate-based operations
    //----------------------------------------------

    /**
     * @brief Remove leading characters matching predicate
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to trim
     * @param pred Predicate function to test characters
     * @return String view with leading matching characters removed
     * @details Returns a view into the original string, no allocation performed.
     *          Predicate should return true for characters to remove.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline constexpr std::string_view trimStartIf( std::string_view str, Predicate pred ) noexcept;

    /**
     * @brief Remove trailing characters matching predicate
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to trim
     * @param pred Predicate function to test characters
     * @return String view with trailing matching characters removed
     * @details Returns a view into the original string, no allocation performed.
     *          Predicate should return true for characters to remove.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline constexpr std::string_view trimEndIf( std::string_view str, Predicate pred ) noexcept;

    /**
     * @brief Remove leading and trailing characters matching predicate
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to trim
     * @param pred Predicate function to test characters
     * @return String view with leading and trailing matching characters removed
     * @details Returns a view into the original string, no allocation performed.
     *          Predicate should return true for characters to remove.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline constexpr std::string_view trimIf( std::string_view str, Predicate pred ) noexcept;

    /**
     * @brief Count characters matching predicate
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to count from
     * @param pred Predicate function to test characters
     * @return Number of characters matching predicate
     * @details Predicate should return true for characters to count.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline constexpr std::size_t countIf( std::string_view str, Predicate pred ) noexcept;

    /**
     * @brief Find first character matching predicate
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to search
     * @param pred Predicate function to test characters
     * @return Position of first matching character, or std::string_view::npos if not found
     * @details Predicate should return true for the character to find.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline constexpr std::size_t findIf( std::string_view str, Predicate pred ) noexcept;

    /**
     * @brief Find first character NOT matching predicate
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to search
     * @param pred Predicate function to test characters
     * @return Position of first non-matching character, or std::string_view::npos if not found
     * @details Predicate should return true for characters to skip.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline constexpr std::size_t findIfNot( std::string_view str, Predicate pred ) noexcept;

    /**
     * @brief Replace characters matching predicate with replacement character
     * @tparam Predicate Callable type accepting char and returning bool
     * @param str String to process
     * @param pred Predicate function to test characters
     * @param replacement Character to replace matching characters with
     * @return New string with matching characters replaced
     * @details Predicate should return true for characters to replace.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    template <typename Predicate>
    [[nodiscard]] inline std::string replaceIf( std::string_view str, Predicate pred, char replacement );

    //----------------------------------------------
    // String case conversion
    //----------------------------------------------

    /**
     * @brief Convert string to lowercase
     * @param str String to convert
     * @return New string with all ASCII characters converted to lowercase
     * @details Only ASCII characters (A-Z) are converted. Non-ASCII characters are preserved unchanged.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string toLower( std::string_view str );

    /**
     * @brief Convert string to uppercase
     * @param str String to convert
     * @return New string with all ASCII characters converted to uppercase
     * @details Only ASCII characters (a-z) are converted. Non-ASCII characters are preserved unchanged.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string toUpper( std::string_view str );

    //----------------------------------------------
    // Character case conversion
    //----------------------------------------------

    /**
     * @brief Convert ASCII character to lowercase
     * @param c Character to convert
     * @return Lowercase character if ASCII letter, otherwise unchanged
     * @details Only works with ASCII characters (A-Z, a-z). Non-ASCII characters are returned unchanged.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr char toLower( char c ) noexcept;

    /**
     * @brief Convert ASCII character to uppercase
     * @param c Character to convert
     * @return Uppercase character if ASCII letter, otherwise unchanged
     * @details Only works with ASCII characters (A-Z, a-z). Non-ASCII characters are returned unchanged.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr char toUpper( char c ) noexcept;

    //----------------------------------------------
    // String parsing
    //----------------------------------------------

    // Note: fromString<T> templates are defined in Utils.inl

    //----------------------------------------------
    // Network and URI validation
    //----------------------------------------------

    //-----------------------------
    // URI character classification
    //-----------------------------

    /**
     * @brief Check if character is URI reserved (RFC 3986 Section 2.2)
     * @param c Character to check
     * @return True if character is a reserved URI character (:/?#[]@!$&'()*+,;=)
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUriReserved( char c ) noexcept;

    /**
     * @brief Check if string contains only URI reserved characters
     * @param str String to check
     * @return True if string is non-empty and contains only reserved characters
     * @details Returns false for empty strings. Uses RFC 3986 Section 2.2 definition.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUriReserved( std::string_view str ) noexcept;

    /**
     * @brief Check if character is URI unreserved (RFC 3986 Section 2.3)
     * @param c Character to check
     * @return True if character is A-Z, a-z, 0-9, -, ., _, or ~
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUriUnreserved( char c ) noexcept;

    /**
     * @brief Check if string contains only URI unreserved characters
     * @param str String to check
     * @return True if string is non-empty and contains only unreserved characters
     * @details Returns false for empty strings. Uses RFC 3986 Section 2.3 definition.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUriUnreserved( std::string_view str ) noexcept;

    //-----------------------------
    // URL encoding/decoding
    //-----------------------------

    /**
     * @brief Encode string for use in URLs (percent-encoding per RFC 3986)
     * @param str String to encode
     * @return URL-encoded string with special characters percent-encoded
     * @details Encodes all characters except unreserved characters (A-Z, a-z, 0-9, -, ., _, ~).
     *          Reserved characters and all other characters are percent-encoded as %XX.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string urlEncode( std::string_view str );

    /**
     * @brief Decode percent-encoded URL string (RFC 3986)
     * @param str Percent-encoded string to decode
     * @return Decoded string, or empty string if input contains invalid percent-encoding
     * @details Decodes %XX sequences to their corresponding characters.
     *          Returns empty string if malformed encoding is detected (invalid hex digits).
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string urlDecode( std::string_view str ) noexcept;

    //-----------------------------
    // JSON escape/unescape
    //-----------------------------

    /**
     * @brief Escape string for use in JSON (RFC 8259)
     * @param str String to escape
     * @return JSON-escaped string with special characters properly escaped
     * @details Escapes: quote, backslash, slash, backspace, form-feed, newline, carriage-return, tab
     *          and control characters (U+0000 to U+001F) as \\uXXXX Unicode escape sequences.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string jsonEscape( std::string_view str );

    /**
     * @brief Unescape JSON string literal (RFC 8259)
     * @param str Escaped JSON string to unescape
     * @return Unescaped string, or empty string if input contains invalid escape sequences
     * @details Unescapes all standard JSON escape sequences and \\uXXXX Unicode sequences.
     *          Returns empty string if malformed escape sequences are detected.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string jsonUnescape( std::string_view str ) noexcept;

    //-----------------------------
    // XML/HTML escape/unescape
    //-----------------------------

    /**
     * @brief Escape string for use in XML/HTML content
     * @param str String to escape
     * @return XML-escaped string with special characters replaced by entities
     * @details Escapes the five predefined XML entities:
     *          & (ampersand) -> &amp;
     *          < (less-than) -> &lt;
     *          > (greater-than) -> &gt;
     *          " (quote) -> &quot;
     *          ' (apostrophe) -> &apos;
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string xmlEscape( std::string_view str );

    /**
     * @brief Unescape XML/HTML entity references
     * @param str XML/HTML string with entity references
     * @return Unescaped string, or empty string if input contains invalid entity references
     * @details Unescapes predefined XML entities (&amp;, &lt;, &gt;, &quot;, &apos;)
     *          and numeric character references (&#xHHHH; and &#DDDD;).
     *          Returns empty string if malformed entity references are detected.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string xmlUnescape( std::string_view str ) noexcept;

    //-----------------------------
    // C/C++ escape sequences
    //-----------------------------

    /**
     * @brief Escape string for use as C/C++ string literal
     * @param str String to escape
     * @return C++-escaped string with special characters replaced by escape sequences
     * @details Escapes common C++ escape sequences:
     *          newline -> \\n, tab -> \\t, carriage-return -> \\r,
     *          backslash -> \\\\, double-quote -> \\", single-quote -> \\',
     *          null -> \\0, backspace -> \\b, form-feed -> \\f, vertical-tab -> \\v,
     *          alert -> \\a. Other control characters are escaped as \\xHH.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string cppEscape( std::string_view str );

    /**
     * @brief Unescape C/C++ string literal escape sequences
     * @param str C++ string literal with escape sequences
     * @return Unescaped string, or empty string if input contains invalid escape sequences
     * @details Unescapes all standard C++ escape sequences including:
     *          \\n, \\t, \\r, \\\\, \\", \\', \\0, \\b, \\f, \\v, \\a,
     *          hexadecimal (\\xHH), and octal (\\NNN) sequences.
     *          Returns empty string if malformed escape sequences are detected.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string cppUnescape( std::string_view str ) noexcept;

    //-----------------------------
    // String formatting utilities
    //-----------------------------

    /**
     * @brief Truncate string to maximum length
     * @param str String to truncate
     * @param maxLength Maximum length of result
     * @return Truncated string, or original if shorter than maxLength
     * @details If string is longer than maxLength, it is truncated to exactly maxLength characters.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string truncate( std::string_view str, size_t maxLength );

    /**
     * @brief Truncate string to maximum length with ellipsis
     * @param str String to truncate
     * @param maxLength Maximum length of result (including ellipsis)
     * @param ellipsis String to append when truncating (default: "...")
     * @return Truncated string with ellipsis, or original if shorter than maxLength
     * @details If string is longer than maxLength, it is truncated and ellipsis is appended.
     *          The total length including ellipsis will not exceed maxLength.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string truncate( std::string_view str, size_t maxLength, std::string_view ellipsis );

    /**
     * @brief Wrap text to specified width
     * @param str Text to wrap
     * @param width Maximum width per line
     * @return Text wrapped to specified width with newlines inserted
     * @details Breaks text at word boundaries when possible. If a single word is longer
     *          than width, it will be placed on its own line exceeding the width.
     *          Existing newlines are preserved.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string wordWrap( std::string_view str, size_t width );

    /**
     * @brief Add indentation to all lines
     * @param str Text to indent
     * @param spaces Number of spaces to indent each line
     * @return Indented text
     * @details Adds the specified number of spaces to the beginning of each line,
     *          including the first line. Empty lines are also indented.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string indent( std::string_view str, size_t spaces );

    /**
     * @brief Remove common leading whitespace from all lines
     * @param str Text to dedent
     * @return Text with common leading whitespace removed
     * @details Finds the minimum indentation across all non-empty lines and removes
     *          that amount of leading whitespace from every line.
     *          This function allocates a new std::string.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline std::string dedent( std::string_view str );

    //-----------------------------
    // Advanced comparison
    //-----------------------------

    /**
     * @brief Case-insensitive three-way comparison
     * @param lhs First string to compare
     * @param rhs Second string to compare
     * @return Negative if lhs < rhs, 0 if equal, positive if lhs > rhs
     * @details Performs case-insensitive comparison similar to strcasecmp.
     *          Returns -1/0/+1 for ordering. ASCII-only conversion.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr int compareIgnoreCase( std::string_view lhs, std::string_view rhs ) noexcept;

    /**
     * @brief Natural sorting comparison (handles embedded numbers)
     * @param lhs First string to compare
     * @param rhs Second string to compare
     * @return Negative if lhs < rhs, 0 if equal, positive if lhs > rhs
     * @details Compares strings naturally, treating embedded numbers as integers.
     *          Example: "file2.txt" < "file10.txt" (not "file10.txt" < "file2.txt").
     *          Useful for sorting filenames, version numbers, etc.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr int naturalCompare( std::string_view lhs, std::string_view rhs ) noexcept;

    /**
     * @brief Find longest common prefix of two strings
     * @param lhs First string
     * @param rhs Second string
     * @return View of the common prefix substring
     * @details Returns a string_view pointing to the beginning of lhs that matches rhs.
     *          If no common prefix, returns empty string_view.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view commonPrefix( std::string_view lhs, std::string_view rhs ) noexcept;

    /**
     * @brief Find longest common suffix of two strings
     * @param lhs First string
     * @param rhs Second string
     * @return View of the common suffix substring
     * @details Returns a string_view pointing to the end of lhs that matches rhs.
     *          If no common suffix, returns empty string_view.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr std::string_view commonSuffix( std::string_view lhs, std::string_view rhs ) noexcept;

    //-----------------------------
    // IP address validation
    //-----------------------------

    /**
     * @brief Validate IPv4 address format (RFC 791)
     * @param str String to validate
     * @return True if string is a valid IPv4 address (e.g., "192.168.1.1")
     * @details Validates dotted-decimal notation with four octets (0-255 each).
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isIpv4Address( std::string_view str ) noexcept;

    /**
     * @brief Validate IPv6 address format (RFC 4291, RFC 5952)
     * @param str String to validate
     * @return True if string is a valid IPv6 address
     * @details Validates standard and compressed notation.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isIpv6Address( std::string_view str ) noexcept;

    //-----------------------------
    // Host validation
    //-----------------------------

    /**
     * @brief Validate hostname format (RFC 1123)
     * @param str String to validate
     * @return True if string is a valid hostname
     * @details Validates DNS hostname format: labels separated by dots, alphanumeric with hyphens.
     *          Max length 253 characters, labels max 63 characters. Case-insensitive.
     *          Examples: "localhost", "example.com", "my-server-01.local"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isHostname( std::string_view str ) noexcept;

    /**
     * @brief Validate Internationalized Domain Name (IDN) hostname format
     * @param str String to validate
     * @return True if string is a valid IDN hostname
     * @details Validates hostnames containing Unicode characters (IDN).
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isIdnHostname( std::string_view str ) noexcept;

    /**
     * @brief Validate domain name format (RFC 1035)
     * @param str String to validate
     * @return True if string is a valid domain name
     * @details Validates fully qualified domain names (FQDN). Stricter than hostname validation.
     *          Must contain at least one dot. Examples: "example.com", "mail.google.com"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isDomainName( std::string_view str ) noexcept;

    //-----------------------------
    // Port validation
    //-----------------------------

    /**
     * @brief Validate port number string (RFC 6335)
     * @param str String to validate
     * @return True if string represents a valid port number (0-65535)
     * @details Validates string contains only digits and value is in valid port range.
     *          Examples: "80", "8080", "443", "65535"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isPortNumber( std::string_view str ) noexcept;

    //-----------------------------
    // Endpoint parsing
    //-----------------------------

    /**
     * @brief Parse network endpoint into host and port
     * @param endpoint Endpoint string to parse
     * @param host Output parameter for host portion
     * @param port Output parameter for port number
     * @return True if parsing succeeded, false otherwise
     * @details Supports formats: "host:port", "ipv4:port", "[ipv6]:port"
     *          IPv6 addresses must be enclosed in brackets.
     *          Examples: "localhost:8080", "192.168.1.1:80", "[::1]:443"
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline bool tryParseEndpoint( std::string_view endpoint,
        std::string_view& host,
        uint16_t& port ) noexcept;

    //-----------------------------
    // Date and Time validation (RFC 3339)
    //-----------------------------

    /**
     * @brief Validate RFC 3339 date-time format
     * @param str String to validate
     * @return True if string is a valid date-time (e.g., "2025-11-29T14:30:00Z")
     * @details Validates YYYY-MM-DDTHH:MM:SS with optional fractional seconds and timezone.
     *          Timezone can be 'Z' or ±HH:MM offset. Does not allocate memory.
     * @see https://datatracker.ietf.org/doc/html/rfc3339
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isDateTime( std::string_view str ) noexcept;

    /**
     * @brief Validate RFC 3339 full-date format
     * @param str String to validate
     * @return True if string is a valid date (e.g., "2025-11-29")
     * @details Validates YYYY-MM-DD format with proper month/day ranges.
     * @see https://datatracker.ietf.org/doc/html/rfc3339
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isDate( std::string_view str ) noexcept;

    /**
     * @brief Validate RFC 3339 full-time format
     * @param str String to validate
     * @return True if string is a valid time (e.g., "14:30:00Z")
     * @details Validates HH:MM:SS with optional fractional seconds and required timezone.
     * @see https://datatracker.ietf.org/doc/html/rfc3339
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isTime( std::string_view str ) noexcept;

    /**
     * @brief Validate ISO 8601 duration format
     * @param str String to validate
     * @return True if string is a valid duration (e.g., "P1Y2M3DT4H5M6S")
     * @details Validates P[n]Y[n]M[n]DT[n]H[n]M[n]S or P[n]W format.
     * @see https://en.wikipedia.org/wiki/ISO_8601#Durations
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isDuration( std::string_view str ) noexcept;

    //-----------------------------
    // Email validation (RFC 5321)
    //-----------------------------

    /**
     * @brief Validate email address format (RFC 5321)
     * @param str String to validate
     * @return True if string is a valid email address
     * @details Validates basic email format: local-part followed by at-sign and domain.
     *          Not exhaustive per RFC 5321.
     * @see https://datatracker.ietf.org/doc/html/rfc5321
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isEmail( std::string_view str ) noexcept;

    /**
     * @brief Validate Internationalized email address format (EAI/SMTPUTF8)
     * @param str String to validate
     * @return True if string is a valid internationalized email address
     * @details Validates email addresses containing Unicode characters in the local-part or domain.
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isIdnEmail( std::string_view str ) noexcept;

    //-----------------------------
    // UUID validation (RFC 4122)
    //-----------------------------

    /**
     * @brief Validate UUID format (RFC 4122)
     * @param str String to validate
     * @return True if string is a valid UUID (e.g., "550e8400-e29b-41d4-a716-446655440000")
     * @details Validates 8-4-4-4-12 hexadecimal digit format with hyphens.
     * @see https://datatracker.ietf.org/doc/html/rfc4122
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUuid( std::string_view str ) noexcept;

    //-----------------------------
    // URI validation (RFC 3986)
    //-----------------------------

    /**
     * @brief Validate URI format (RFC 3986)
     * @param str String to validate
     * @return True if string is a valid URI (e.g., "https://example.com/path")
     * @details Validates scheme://authority/path?query#fragment format.
     * @see https://datatracker.ietf.org/doc/html/rfc3986
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUri( std::string_view str ) noexcept;

    /**
     * @brief Validate URI-reference format (RFC 3986)
     * @param str String to validate
     * @return True if string is a valid URI or relative-reference
     * @details Validates URI or relative-reference (scheme optional).
     * @see https://datatracker.ietf.org/doc/html/rfc3986
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUriReference( std::string_view str ) noexcept;

    /**
     * @brief Validate URI Template format (RFC 6570)
     * @param str String to validate
     * @return True if string is a valid URI Template (e.g., "https://example.com/{user}/repos")
     * @details Validates URI templates with {expression} syntax. Expressions may contain
     *          operator prefixes (+, #, ., /, ;, ?, &) and variable names.
     *          No whitespace allowed. Braces must be balanced.
     * @see https://datatracker.ietf.org/doc/html/rfc6570
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isUriTemplate( std::string_view str ) noexcept;

    //-----------------------------
    // IRI validation (RFC 3987)
    //-----------------------------

    /**
     * @brief Validate IRI format (RFC 3987)
     * @param str String to validate
     * @return True if string is a valid IRI (e.g., "https://example.com/路径")
     * @details Validates Internationalized Resource Identifier with Unicode characters.
     * @see https://datatracker.ietf.org/doc/html/rfc3987
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isIri( std::string_view str ) noexcept;

    /**
     * @brief Validate IRI-reference format (RFC 3987)
     * @param str String to validate
     * @return True if string is a valid IRI or relative IRI-reference
     * @details Validates IRI or relative-reference with Unicode support (scheme optional).
     * @see https://datatracker.ietf.org/doc/html/rfc3987
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isIriReference( std::string_view str ) noexcept;

    //-----------------------------
    // JSON Pointer validation (RFC 6901)
    //-----------------------------

    /**
     * @brief Validate JSON Pointer format (RFC 6901)
     * @param str String to validate
     * @return True if string is a valid JSON Pointer (e.g., "/foo/bar/0")
     * @details Validates empty string or sequence of /reference-token.
     *          Escape sequences ~0 and ~1 are validated.
     * @see https://datatracker.ietf.org/doc/html/rfc6901
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isJsonPointer( std::string_view str ) noexcept;

    /**
     * @brief Validate relative JSON Pointer format
     * @param str String to validate
     * @return True if string is a valid relative JSON Pointer (e.g., "1/foo")
     * @details Validates non-negative integer followed by either # or JSON Pointer.
     * @see https://datatracker.ietf.org/doc/html/draft-handrews-relative-json-pointer
     * @note This function is marked [[nodiscard]] - the return value should not be ignored
     */
    [[nodiscard]] inline constexpr bool isRelativeJsonPointer( std::string_view str ) noexcept;
} // namespace nfx::string

#include "nfx/detail/string/Utils.inl"

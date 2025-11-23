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
 * @file Sample_StringPredicates.cpp
 * @brief Demonstrates predicate-based string operations
 * @details This sample shows custom predicates for trimming, counting, finding,
 *          and replacing with user-defined and built-in character predicates
 */

#include <iostream>
#include <string>

#include <nfx/string/Utils.h>

int main()
{
	using namespace nfx::string;

	std::cout << "=== nfx-stringutils Library - Predicate-based Operations ===\n\n";

	//=====================================================================
	// 1. Predicate-based operations
	//=====================================================================
	{
		std::cout << "1. Predicate-based operations\n";
		std::cout << "------------------------------\n";

		// Define custom predicates
		auto is_digit = []( char c ) { return c >= '0' && c <= '9'; };
		auto is_vowel = []( char c ) {
			char lower = ( c >= 'A' && c <= 'Z' ) ? c + 32 : c;
			return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
		};
		auto is_punct = []( char c ) { return c == '.' || c == '!' || c == '?' || c == ','; };
		auto is_special = []( char c ) { return c == '*' || c == '#' || c == '@'; };

		// Trimming with predicates
		std::cout << "Custom trimming:\n";
		std::cout << "  trimStartIf(\"123abc456\", is_digit): " << trimStartIf( "123abc456", is_digit ) << "\n";
		std::cout << "  trimEndIf(\"abc123\", is_digit): " << trimEndIf( "abc123", is_digit ) << "\n";
		std::cout << "  trimIf(\"***Hello***\", is_special): " << trimIf( "***Hello***", is_special ) << "\n";
		std::cout << "  trimIf(\"...text!!!\", is_punct): " << trimIf( "...text!!!", is_punct ) << "\n";

		// Counting with predicates
		std::cout << "\n"
				  << "Custom counting:\n";
		std::string text{ "Hello World 2025!" };
		std::cout << "  Text: \"" << text << "\"\n";
		std::cout << "  Digits: " << countIf( text, is_digit ) << "\n";
		std::cout << "  Vowels: " << countIf( text, is_vowel ) << "\n";
		std::cout << "  Punctuation: " << countIf( text, is_punct ) << "\n";
		std::cout << "  Uppercase: " << countIf( text, []( char c ) { return c >= 'A' && c <= 'Z'; } ) << "\n";

		// Finding with predicates
		std::cout << "\n"
				  << "Custom searching:\n";
		std::string code{ "var_name123" };
		std::cout << "  Code: \"" << code << "\"\n";
		std::cout << "  First digit at: " << findIf( code, is_digit ) << "\n";
		std::cout << "  First non-letter at: " << findIfNot( code, []( char c ) { return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ); } ) << "\n";

		// Replacing with predicates
		std::cout << "\n"
				  << "Custom replacement:\n";
		std::cout << "  replaceIf(\"abc123xyz\", is_digit, '#'): " << replaceIf( "abc123xyz", is_digit, '#' ) << "\n";
		std::cout << "  replaceIf(\"hello world\", is_vowel, '*'): " << replaceIf( "hello world", is_vowel, '*' ) << "\n";
		std::cout << "  replaceIf(\"test@email.com\", is_special, '_'): " << replaceIf( "test@email.com", is_special, '_' ) << "\n";

		// Real-world example: Clean user input
		std::cout << "\n"
				  << "Real-world: Sanitizing user input\n";
		std::string userInput{ "###User@Input123!!!" };
		auto isAlphaNum = []( char c ) { return ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ); };
		auto isNotAlphaNum = [isAlphaNum]( char c ) { return !isAlphaNum( c ); };

		std::cout << "  Original: \"" << userInput << "\"\n";
		std::cout << "  Trimmed: \"" << trimIf( userInput, isNotAlphaNum ) << "\"\n";
		std::cout << "  Special chars: " << countIf( userInput, is_special ) << "\n";
		std::cout << "  Sanitized: \"" << replaceIf( userInput, isNotAlphaNum, '_' ) << "\"\n";

		// Using library predicates
		std::cout << "\n"
				  << "Using built-in predicates:\n";
		std::string mixed{ "   abc123   " };
		std::cout << "  Original: \"" << mixed << "\"\n";
		std::cout << "  trimIf(mixed, isWhitespace): \"" << trimIf( mixed, isWhitespace ) << "\"\n";
		std::cout << "  countIf(mixed, isDigit): " << countIf( mixed, isDigit ) << "\n";
		std::cout << "  countIf(mixed, isAlpha): " << countIf( mixed, isAlpha ) << "\n";
		std::cout << "  replaceIf(mixed, isDigit, 'X'): \"" << replaceIf( mixed, isDigit, 'X' ) << "\"\n";
		std::cout << "\n";
	}

	return 0;
}

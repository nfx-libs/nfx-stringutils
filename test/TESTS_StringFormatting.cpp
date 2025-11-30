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
 * @file TESTS_StringFormatting.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
	//=====================================================================
	// String formatting tests
	//=====================================================================

	//----------------------------------------------
	// truncate tests
	//----------------------------------------------

	TEST( StringFormatting, Truncate_BasicTruncation )
	{
		EXPECT_EQ( "Hello", truncate( "Hello World", 5 ) );
		EXPECT_EQ( "Hello W", truncate( "Hello World", 7 ) );
		EXPECT_EQ( "", truncate( "Hello", 0 ) );
	}

	TEST( StringFormatting, Truncate_WithEllipsis )
	{
		EXPECT_EQ( "Hel...", truncate( "Hello World", 6, "..." ) );
		EXPECT_EQ( "Hello W...", truncate( "Hello World", 10, "..." ) );
		EXPECT_EQ( "H>>", truncate( "Hello", 3, ">>" ) );
		EXPECT_EQ( "Hello", truncate( "Hello", 10, "..." ) ); // Shorter than maxLength
	}

	TEST( StringFormatting, Truncate_ShortStrings )
	{
		EXPECT_EQ( "Hi", truncate( "Hi", 10 ) );
		EXPECT_EQ( "Hi", truncate( "Hi", 10, "..." ) );
		EXPECT_EQ( "Hello", truncate( "Hello", 5 ) );
	}

	TEST( StringFormatting, Truncate_EmptyStrings )
	{
		EXPECT_EQ( "", truncate( "", 10 ) );
		EXPECT_EQ( "", truncate( "", 10, "..." ) );
		EXPECT_EQ( "", truncate( "", 0 ) );
	}

	TEST( StringFormatting, Truncate_ExactLength )
	{
		EXPECT_EQ( "Hello", truncate( "Hello", 5 ) );
		EXPECT_EQ( "Hello", truncate( "Hello", 5, "..." ) );
	}

	TEST( StringFormatting, Truncate_EllipsisLongerThanMaxLength )
	{
		EXPECT_EQ( "H...", truncate( "Hello World", 4, "..." ) ); // Ellipsis equals maxLength, include 1 char + partial ellipsis
		EXPECT_EQ( "H>>", truncate( "Hello", 3, ">>" ) );
		EXPECT_EQ( "Hell", truncate( "Hello", 4, "......" ) ); // Ellipsis much longer than maxLength, just truncate
	}

	//----------------------------------------------
	// wordWrap tests
	//----------------------------------------------

	TEST( StringFormatting, WordWrap_BasicWrapping )
	{
		EXPECT_EQ( "Hello\nWorld", wordWrap( "Hello World", 8 ) );
		EXPECT_EQ( "This is\na test", wordWrap( "This is a test", 9 ) ); // "This is" = 7 chars, fits within 9
		EXPECT_EQ( "One Two\nThree", wordWrap( "One Two Three", 8 ) );
	}

	TEST( StringFormatting, WordWrap_LongWords )
	{
		// Long words get broken at width
		EXPECT_EQ( "Supercalif\nragilistic\nexpialidoc\nious is\nlong", wordWrap( "Supercalifragilisticexpialidocious is long", 10 ) );
		EXPECT_EQ( "A\nvery\nlong\nword", wordWrap( "A very long word", 5 ) );
	}

	TEST( StringFormatting, WordWrap_MultipleLines )
	{
		EXPECT_EQ( "Line\none\nLine\ntwo", wordWrap( "Line one\nLine two", 6 ) );
		EXPECT_EQ( "First\nSecond\nThird", wordWrap( "First\nSecond\nThird", 10 ) );
	}

	TEST( StringFormatting, WordWrap_EmptyLines )
	{
		EXPECT_EQ( "\n\n", wordWrap( "\n\n", 10 ) );
		EXPECT_EQ( "Text\n\nMore", wordWrap( "Text\n\nMore", 10 ) );
	}

	TEST( StringFormatting, WordWrap_Punctuation )
	{
		EXPECT_EQ( "Hello,\nWorld!", wordWrap( "Hello, World!", 8 ) );
		EXPECT_EQ( "Test;\nanother\ntest.", wordWrap( "Test; another test.", 9 ) );
	}

	TEST( StringFormatting, WordWrap_EdgeCases )
	{
		EXPECT_EQ( "", wordWrap( "", 10 ) );
		EXPECT_EQ( "Hello", wordWrap( "Hello", 0 ) );				// Width 0
		EXPECT_EQ( "Hello World", wordWrap( "Hello World", 100 ) ); // Width larger than string
	}

	//----------------------------------------------
	// indent tests
	//----------------------------------------------

	TEST( StringFormatting, Indent_SingleLine )
	{
		EXPECT_EQ( "  Hello", indent( "Hello", 2 ) );
		EXPECT_EQ( "    World", indent( "World", 4 ) );
		EXPECT_EQ( " Text", indent( "Text", 1 ) );
	}

	TEST( StringFormatting, Indent_MultiLine )
	{
		EXPECT_EQ( "  Line1\n  Line2", indent( "Line1\nLine2", 2 ) );
		EXPECT_EQ( "    First\n    Second\n    Third", indent( "First\nSecond\nThird", 4 ) );
	}

	TEST( StringFormatting, Indent_EmptyLines )
	{
		EXPECT_EQ( "  \n  ", indent( "\n", 2 ) );
		EXPECT_EQ( "  Text\n  \n  More", indent( "Text\n\nMore", 2 ) );
	}

	TEST( StringFormatting, Indent_MixedContent )
	{
		EXPECT_EQ( "  if (true) {\n      code();\n  }", indent( "if (true) {\n    code();\n}", 2 ) );
	}

	TEST( StringFormatting, Indent_ZeroSpaces )
	{
		EXPECT_EQ( "Hello", indent( "Hello", 0 ) );
		EXPECT_EQ( "Line1\nLine2", indent( "Line1\nLine2", 0 ) );
	}

	TEST( StringFormatting, Indent_EmptyString )
	{
		EXPECT_EQ( "", indent( "", 4 ) );
	}

	//----------------------------------------------
	// dedent tests
	//----------------------------------------------

	TEST( StringFormatting, Dedent_CommonWhitespace )
	{
		EXPECT_EQ( "Line1\nLine2", dedent( "  Line1\n  Line2" ) );
		EXPECT_EQ( "Line1\n  Line2", dedent( "    Line1\n      Line2" ) );
		EXPECT_EQ( "First\nSecond", dedent( "   First\n   Second" ) );
	}

	TEST( StringFormatting, Dedent_MixedIndentation )
	{
		EXPECT_EQ( "Line1\n  Line2\nLine3", dedent( "  Line1\n    Line2\n  Line3" ) );
		EXPECT_EQ( "Code\n    More", dedent( "    Code\n        More" ) );
	}

	TEST( StringFormatting, Dedent_EmptyLines )
	{
		EXPECT_EQ( "Text\n\nMore", dedent( "  Text\n\n  More" ) );
		EXPECT_EQ( "\n\n", dedent( "\n\n" ) );
	}

	TEST( StringFormatting, Dedent_NoLeadingWhitespace )
	{
		EXPECT_EQ( "Hello\nWorld", dedent( "Hello\nWorld" ) );
		EXPECT_EQ( "Text", dedent( "Text" ) );
	}

	TEST( StringFormatting, Dedent_TabsAndSpaces )
	{
		EXPECT_EQ( "Line1\nLine2", dedent( "\tLine1\n\tLine2" ) );
		EXPECT_EQ( "A\n  B", dedent( "  A\n    B" ) );
	}

	TEST( StringFormatting, Dedent_EdgeCases )
	{
		EXPECT_EQ( "", dedent( "" ) );
		EXPECT_EQ( "   ", dedent( "   " ) ); // Only whitespace
		EXPECT_EQ( "Text", dedent( "Text" ) );
	}
} // namespace nfx::string::test

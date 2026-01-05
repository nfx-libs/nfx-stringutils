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
 * @file TESTS_CharacterClassification.cpp
 * @brief Unit tests for StringUtils string library
 */

#include <gtest/gtest.h>

#include <nfx/string/Utils.h>

namespace nfx::string::test
{
    //=====================================================================
    // Character classification tests
    //=====================================================================

    TEST( CharacterClassification, IsWhitespace )
    {
        // Whitespace characters
        EXPECT_TRUE( isWhitespace( ' ' ) );
        EXPECT_TRUE( isWhitespace( '\t' ) );
        EXPECT_TRUE( isWhitespace( '\n' ) );
        EXPECT_TRUE( isWhitespace( '\r' ) );
        EXPECT_TRUE( isWhitespace( '\f' ) );
        EXPECT_TRUE( isWhitespace( '\v' ) );

        // Non-whitespace characters
        EXPECT_FALSE( isWhitespace( 'a' ) );
        EXPECT_FALSE( isWhitespace( 'Z' ) );
        EXPECT_FALSE( isWhitespace( '0' ) );
        EXPECT_FALSE( isWhitespace( '9' ) );
        EXPECT_FALSE( isWhitespace( '!' ) );
        EXPECT_FALSE( isWhitespace( '@' ) );
        EXPECT_FALSE( isWhitespace( '\0' ) );
    }

    TEST( CharacterClassification, IsDigit )
    {
        // Digits
        EXPECT_TRUE( isDigit( '0' ) );
        EXPECT_TRUE( isDigit( '1' ) );
        EXPECT_TRUE( isDigit( '5' ) );
        EXPECT_TRUE( isDigit( '9' ) );

        // Non-digits
        EXPECT_FALSE( isDigit( 'a' ) );
        EXPECT_FALSE( isDigit( 'Z' ) );
        EXPECT_FALSE( isDigit( ' ' ) );
        EXPECT_FALSE( isDigit( '!' ) );
        EXPECT_FALSE( isDigit( '\t' ) );
        EXPECT_FALSE( isDigit( '\0' ) );
    }

    TEST( CharacterClassification, IsAlpha )
    {
        // Lowercase letters
        EXPECT_TRUE( isAlpha( 'a' ) );
        EXPECT_TRUE( isAlpha( 'm' ) );
        EXPECT_TRUE( isAlpha( 'z' ) );

        // Uppercase letters
        EXPECT_TRUE( isAlpha( 'A' ) );
        EXPECT_TRUE( isAlpha( 'M' ) );
        EXPECT_TRUE( isAlpha( 'Z' ) );

        // Non-alphabetic
        EXPECT_FALSE( isAlpha( '0' ) );
        EXPECT_FALSE( isAlpha( '9' ) );
        EXPECT_FALSE( isAlpha( ' ' ) );
        EXPECT_FALSE( isAlpha( '!' ) );
        EXPECT_FALSE( isAlpha( '\t' ) );
        EXPECT_FALSE( isAlpha( '\0' ) );
    }

    TEST( CharacterClassification, IsAlphaNumeric )
    {
        // Letters
        EXPECT_TRUE( isAlphaNumeric( 'a' ) );
        EXPECT_TRUE( isAlphaNumeric( 'Z' ) );
        EXPECT_TRUE( isAlphaNumeric( 'm' ) );

        // Digits
        EXPECT_TRUE( isAlphaNumeric( '0' ) );
        EXPECT_TRUE( isAlphaNumeric( '5' ) );
        EXPECT_TRUE( isAlphaNumeric( '9' ) );

        // Non-alphanumeric
        EXPECT_FALSE( isAlphaNumeric( ' ' ) );
        EXPECT_FALSE( isAlphaNumeric( '!' ) );
        EXPECT_FALSE( isAlphaNumeric( '@' ) );
        EXPECT_FALSE( isAlphaNumeric( '\t' ) );
        EXPECT_FALSE( isAlphaNumeric( '\0' ) );
    }
} // namespace nfx::string::test

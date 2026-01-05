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
 * @file Sample_StringBasics.cpp
 * @brief Demonstrates basic string validation, parsing, and operations
 * @details This sample shows fundamental StringUtils operations including validation,
 *          boolean/numeric parsing, case conversion, and pattern matching
 */

#include <iostream>
#include <vector>

#include <nfx/string/Utils.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - String Basics ===\n\n";

    //=====================================================================
    // 1. String validation - Fast length and emptiness checks
    //=====================================================================
    {
        std::cout << "1. String validation - Fast length and emptiness checks\n";
        std::cout << "---------------------------------------------------------\n";

        // Length validation examples
        std::string_view password{ "MySecurePassword123!" };
        std::cout << "Password validation:\n";
        std::cout << "  Password: \"" << password << "\"\n";
        std::cout << "  Has exactly 20 characters: " << ( hasExactLength( password, 20 ) ? "Yes" : "No" ) << "\n";
        std::cout << "  Has exactly 8 characters: " << ( hasExactLength( password, 8 ) ? "Yes" : "No" ) << "\n";

        // Empty string checks
        std::vector<std::string_view> inputs{ "", "   ", "content", "\t", "a" };
        std::cout << "\nEmpty string detection:\n";

        for ( const auto& input : inputs )
        {
            std::cout << "  \"" << input << "\" is empty: " << ( isEmpty( input ) ? "Yes" : "No" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 2. Boolean parsing - Comprehensive format support
    //=====================================================================
    {
        std::cout << "2. Boolean parsing - Comprehensive format support\n";
        std::cout << "---------------------------------------------------\n";

        // Test various boolean formats
        std::vector<std::string_view> boolInputs{
            "true", "TRUE", "True",
            "1", "t", "T", "yes",
            "YES", "on", "ON",
            "false", "FALSE", "False",
            "0", "f", "F", "no",
            "NO", "off", "OFF",
            "maybe", "2", "",
            "invalid" };

        std::cout << "Boolean parsing results:\n";
        for ( const auto& input : boolInputs )
        {
            bool result{};
            bool success{ fromString<bool>( input, result ) };
            std::cout << "  \"" << input << "\" -> ";
            if ( success )
            {
                std::cout << ( result ? "true" : "false" );
            }
            else
            {
                std::cout << "invalid";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 3. Numeric parsing - Safe conversion with error handling
    //=====================================================================
    {
        std::cout << "3. Numeric parsing - Safe conversion with error handling\n";
        std::cout << "----------------------------------------------------------\n";

        // Integer parsing examples
        std::vector<std::string_view> intInputs{ "123", "-456", "0", "2147483647", "invalid", "12.34", "" };
        std::cout << "Integer parsing:\n";
        for ( const auto& input : intInputs )
        {
            int result{};
            bool success{ fromString<int>( input, result ) };
            std::cout << "  \"" << input << "\" -> ";
            if ( success )
            {
                std::cout << result;
            }
            else
            {
                std::cout << "invalid";
            }
            std::cout << "\n";
        }

        // Double parsing examples
        std::vector<std::string_view> doubleInputs{ "123.456", "-78.9", "1.23e-4", "0.0", "invalid", "" };
        std::cout << "\nDouble parsing:\n";
        for ( const auto& input : doubleInputs )
        {
            double result{};
            bool success{ fromString<double>( input, result ) };
            std::cout << "  \"" << input << "\" -> ";
            if ( success )
            {
                std::cout << result;
            }
            else
            {
                std::cout << "invalid";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 4. String operations - Fast matching and comparison
    //=====================================================================
    {
        std::cout << "4. String operations - Fast matching and comparison\n";
        std::cout << "-----------------------------------------------------\n";

        // File extension checking
        std::vector<std::string_view> filenames{ "document.pdf", "image.PNG", "script.js", "data.CSV", "readme" };
        std::cout << "File extension detection:\n";
        for ( const auto& filename : filenames )
        {
            std::cout << "  " << filename << ":\n";

            bool isPdf{ iequals( filename.substr( filename.find_last_of( '.' ) + 1 ), "pdf" ) };
            bool isImage{ endsWith( filename, ".png" ) || endsWith( filename, ".PNG" ) };
            bool hasExtension{ contains( filename, "." ) };

            std::cout << "    PDF: " << ( isPdf ? "Yes" : "No" ) << "\n";
            std::cout << "    Image: " << ( isImage ? "Yes" : "No" ) << "\n";
            std::cout << "    Has extension: " << ( hasExtension ? "Yes" : "No" ) << "\n";
        }

        // URL validation example
        std::cout << "\nURL validation:\n";

        std::vector<std::string_view> urls{
            "https://api.example.com/v1/data",
            "http://localhost:8080/test",
            "ftp://files.server.com/download",
            "invalid-url",
            "https://secure.bank.com/api" };

        for ( const auto& url : urls )
        {
            std::cout << "  " << url << ":\n";

            bool isHttps{ startsWith( url, "https://" ) };
            bool isApiEndpoint{ contains( url, "/api" ) };
            bool isLocal{ contains( url, "localhost" ) };

            std::cout << "    HTTPS: " << ( isHttps ? "Yes" : "No" ) << "\n";
            std::cout << "    API endpoint: " << ( isApiEndpoint ? "Yes" : "No" ) << "\n";
            std::cout << "    Local: " << ( isLocal ? "Yes" : "No" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 5. Case conversion - ASCII-optimized transformations
    //=====================================================================
    {
        std::cout << "5. Case conversion - ASCII-optimized transformations\n";
        std::cout << "------------------------------------------------------\n";

        // Character conversion examples
        std::cout << "Character conversion:\n";
        std::string alphabet{ "AaBbCcDdEeFf123!@#" };
        std::cout << "  Original: " << alphabet << "\n";

        std::string lowerResult{};
        std::string upperResult{};
        for ( char c : alphabet )
        {
            lowerResult += toLower( c );
            upperResult += toUpper( c );
        }
        std::cout << "  Lowercase: " << lowerResult << "\n";
        std::cout << "  Uppercase: " << upperResult << "\n";

        // String conversion examples
        std::cout << "\nString conversion:\n";
        std::vector<std::string_view> testStrings{
            "Hello World",
            "MixedCASE123!",
            "ALREADY_UPPER",
            "already_lower",
            "Café_Unicode_Ñoël",
            "" };

        for ( const auto& str : testStrings )
        {
            std::cout << "  Original:  \"" << str << "\"\n";
            std::cout << "  Lowercase: \"" << toLower( str ) << "\"\n";
            std::cout << "  Uppercase: \"" << toUpper( str ) << "\"\n";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 6. Real-world use cases - Configuration and validation
    //=====================================================================
    {
        std::cout << "6. Real-world use cases - Configuration and validation\n";
        std::cout << "---------------------------------------------------------\n";

        // Configuration parsing
        std::cout << "Configuration file parsing:\n";
        std::vector<std::string_view> configLines{
            "debug=true",
            "port=8080",
            "ssl=false",
            "timeout=30.5",
            "retries=3" };

        for ( const auto& line : configLines )
        {
            auto pos{ line.find( '=' ) };
            if ( pos != std::string_view::npos )
            {
                auto key{ line.substr( 0, pos ) };
                auto value{ line.substr( pos + 1 ) };

                std::cout << "  " << key << " = " << value;

                // Try parsing as different types
                bool boolVal{};
                int intVal{};
                double doubleVal{};

                if ( fromString<bool>( value, boolVal ) )
                {
                    std::cout << " (boolean: " << ( boolVal ? "true" : "false" ) << ")";
                }
                else if ( fromString<int>( value, intVal ) )
                {
                    std::cout << " (integer: " << intVal << ")";
                }
                else if ( fromString<double>( value, doubleVal ) )
                {
                    std::cout << " (double: " << doubleVal << ")";
                }
                else
                {
                    std::cout << " (string)";
                }
                std::cout << "\n";
            }
        }

        // Command validation
        std::cout << "\nCommand validation:\n";
        std::vector<std::string_view> commands{ "start", "STOP", "restart", "Status", "invalid" };
        std::vector<std::string_view> validCommands{ "start", "stop", "restart", "status" };

        for ( const auto& cmd : commands )
        {
            std::cout << "  Command \"" << cmd << "\": ";
            bool valid{ false };
            for ( const auto& validCmd : validCommands )
            {
                if ( iequals( cmd, validCmd ) )
                {
                    valid = true;
                    break;
                }
            }
            std::cout << ( valid ? "Valid" : "Invalid" ) << "\n";
        }
        std::cout << "\n";
    }

    //=====================================================================
    // 7. String counting and pattern matching
    //=====================================================================
    {
        std::cout << "7. String counting and pattern matching\n";
        std::cout << "-----------------------------------------\n";

        // Character counting
        std::string_view dnaSequence{ "ATCGATCGATCG" };
        std::cout << "DNA sequence analysis: " << dnaSequence << "\n";
        std::cout << "  Adenine (A) count: " << count( dnaSequence, 'A' ) << "\n";
        std::cout << "  Thymine (T) count: " << count( dnaSequence, 'T' ) << "\n";
        std::cout << "  Cytosine (C) count: " << count( dnaSequence, 'C' ) << "\n";
        std::cout << "  Guanine (G) count: " << count( dnaSequence, 'G' ) << "\n";

        // Substring counting (non-overlapping)
        std::string_view logData{ "ERROR: Failed to connect. ERROR: Timeout. ERROR: Retry failed." };
        std::cout << "\nLog analysis: " << logData << "\n";
        std::cout << "  ERROR occurrences: " << count( logData, "ERROR" ) << "\n";
        std::cout << "  Failed occurrences: " << count( logData, "Failed" ) << "\n";

        // Overlapping pattern detection
        std::string_view repeatPattern{ "aaaa" };
        std::cout << "\nPattern: " << repeatPattern << "\n";
        std::cout << "  Non-overlapping 'aa': " << count( repeatPattern, "aa" ) << "\n";
        std::cout << "  Overlapping 'aa': " << countOverlapping( repeatPattern, "aa" ) << "\n";

        std::string_view genome{ "AGAGAGAG" };
        std::cout << "\nGenome: " << genome << "\n";
        std::cout << "  Non-overlapping 'AGA': " << count( genome, "AGA" ) << "\n";
        std::cout << "  Overlapping 'AGA': " << countOverlapping( genome, "AGA" ) << "\n";
        std::cout << "\n";
    }

    return 0;
}

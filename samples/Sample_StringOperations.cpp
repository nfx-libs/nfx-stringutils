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
 * @file Sample_StringOperations.cpp
 * @brief Demonstrates string manipulation operations
 * @details This sample shows replacement, joining, padding, searching, and performance
 */

#include <chrono>
#include <iostream>
#include <vector>

#include <nfx/string/Utils.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - String Operations ===\n\n";

    //=====================================================================
    // 1. String replacement
    //=====================================================================
    {
        std::cout << "1. String replacement\n";
        std::cout << "----------------------\n";

        // Replace first occurrence
        std::string_view template1{ "Hello {name}, welcome to {name}!" };
        std::string replaced1{ replace( template1, "{name}", "Alice" ) };
        std::cout << "Replace first:\n";
        std::cout << "  Original:  " << template1 << "\n";
        std::cout << "  Result:    " << replaced1 << "\n";

        // Replace all occurrences
        std::string replacedAll{ replaceAll( template1, "{name}", "Bob" ) };
        std::cout << "\nReplace all:\n";
        std::cout << "  Original:  " << template1 << "\n";
        std::cout << "  Result:    " << replacedAll << "\n";

        // Path normalization
        std::string_view windowsPath{ "C:\\Users\\Documents\\file.txt" };
        std::string unixPath{ replaceAll( windowsPath, "\\", "/" ) };
        std::cout << "\nPath normalization:\n";
        std::cout << "  Windows:   " << windowsPath << "\n";
        std::cout << "  Unix:      " << unixPath << "\n";

        // HTML escaping
        std::string_view htmlText{ "Use <script> tags carefully & escape \"quotes\"" };
        std::string escaped{ replaceAll( htmlText, "<", "&lt;" ) };
        escaped = replaceAll( escaped, ">", "&gt;" );
        escaped = replaceAll( escaped, "&", "&amp;" );
        std::cout << "\nHTML escaping:\n";
        std::cout << "  Original:  " << htmlText << "\n";
        std::cout << "  Escaped:   " << escaped << "\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 2. String joining
    //=====================================================================
    {
        std::cout << "2. String joining\n";
        std::cout << "------------------\n";

        // Join vector with delimiter
        std::vector<std::string> tags{ "cpp", "performance", "zero-copy", "string-utils" };
        std::string tagString{ join( tags, ", " ) };
        std::cout << "Tags: " << tagString << "\n";

        // CSV generation
        std::vector<std::string> csvRow{ "John", "Doe", "30", "Engineer", "75000" };
        std::string csvLine{ join( csvRow, "," ) };
        std::cout << "CSV: " << csvLine << "\n";

        // URL query parameters
        std::vector<std::string> params{ "page=1", "limit=10", "sort=name", "order=asc" };
        std::string queryString{ "?" + join( params, "&" ) };
        std::cout << "Query: " << queryString << "\n";

        // Join with custom range
        std::vector<std::string> words{ "The", "quick", "brown", "fox", "jumps" };
        std::string sentence{ join( words.begin(), words.begin() + 3, " " ) };
        std::cout << "Partial join: " << sentence << "\n";

        // Empty and single element
        std::vector<std::string> empty{};
        std::vector<std::string> single{ "alone" };
        std::cout << "Empty join: \"" << join( empty, "," ) << "\"\n";
        std::cout << "Single join: \"" << join( single, "," ) << "\"\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 3. String formatting and padding
    //=====================================================================
    {
        std::cout << "3. String formatting and padding\n";
        std::cout << "-----------------------------------\n";

        // Table formatting
        std::cout << "Financial report (padded):\n";
        std::cout << "  " << padRight( "Item", 20 ) << padLeft( "Amount", 12 ) << "\n";
        std::cout << "  " << repeat( "-", 32 ) << "\n";
        std::cout << "  " << padRight( "Revenue", 20 ) << padLeft( "1,250,000", 12 ) << "\n";
        std::cout << "  " << padRight( "Expenses", 20 ) << padLeft( "875,000", 12 ) << "\n";
        std::cout << "  " << padRight( "Profit", 20 ) << padLeft( "375,000", 12 ) << "\n";

        // Number formatting
        std::cout << "\nNumber formatting:\n";
        std::cout << "  " << padLeft( "42", 5, '0' ) << " (zero-padded)\n";
        std::cout << "  " << padLeft( "123", 8, '0' ) << " (transaction ID)\n";
        std::cout << "  $" << padLeft( "99.99", 10, ' ' ) << " (price)\n";

        // Centered headers
        std::cout << "\nCentered headers:\n";
        std::cout << "  " << center( "MENU", 40, '=' ) << "\n";
        std::cout << "  " << center( "Daily Specials", 40, ' ' ) << "\n";
        std::cout << "  " << center( "***", 40, '-' ) << "\n";

        // Progress bars and separators
        std::cout << "\nVisual elements:\n";
        std::cout << "  Progress: [" << repeat( "#", 7 ) << repeat( "-", 3 ) << "] 70%\n";
        std::cout << "  " << repeat( "=", 50 ) << "\n";
        std::cout << "  Loading" << repeat( ".", 3 ) << "\n";

        // Box drawing
        std::cout << "\nText box:\n";
        std::string boxContent{ "Important Message" };
        int boxWidth{ 40 };
        std::cout << "  " << repeat( "*", boxWidth ) << "\n";
        std::cout << "  *" << center( boxContent, boxWidth - 2 ) << "*\n";
        std::cout << "  " << repeat( "*", boxWidth ) << "\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 4. String search and reversal
    //=====================================================================
    {
        std::cout << "4. String search and reversal\n";
        std::cout << "--------------------------------\n";

        // Palindrome detection
        std::vector<std::string_view> palindromeTests{ "radar", "hello", "level", "world", "noon" };
        std::cout << "Palindrome detection:\n";
        for ( const auto& word : palindromeTests )
        {
            bool isPalindrome{ word == reverse( word ) };
            std::cout << "  " << word << " -> " << ( isPalindrome ? "palindrome" : "not palindrome" ) << "\n";
        }

        // String reversal use cases
        std::cout << "\nReversal examples:\n";
        std::cout << "  \"hello\" reversed: " << reverse( "hello" ) << "\n";
        std::cout << "  \"12345\" reversed: " << reverse( "12345" ) << "\n";
        std::cout << "  DNA \"ATCG\" reversed: " << reverse( "ATCG" ) << "\n";

        // Finding first occurrence
        std::string_view url{ "https://api.example.com/v1/users?id=123" };
        std::cout << "\nURL parsing: " << url << "\n";
        auto protocolPos{ indexOf( url, "://" ) };
        auto pathPos{ indexOf( url, "/v1" ) };
        auto queryPos{ indexOf( url, "?" ) };
        std::cout << "  Protocol separator at: " << protocolPos << "\n";
        std::cout << "  API path at: " << pathPos << "\n";
        std::cout << "  Query string at: " << queryPos << "\n";

        // Finding last occurrence
        std::string_view filePath{ "C:/Users/Documents/project/src/utils/helper.cpp" };
        std::cout << "\nFile path: " << filePath << "\n";
        auto lastSlash{ lastIndexOf( filePath, "/" ) };
        auto lastDot{ lastIndexOf( filePath, "." ) };
        if ( lastSlash != std::string_view::npos )
        {
            std::cout << "  Filename: " << filePath.substr( lastSlash + 1 ) << "\n";
        }
        if ( lastDot != std::string_view::npos )
        {
            std::cout << "  Extension: " << filePath.substr( lastDot ) << "\n";
        }

        // Email parsing
        std::string_view email{ "user.name@mail.example.com" };
        std::cout << "\nEmail: " << email << "\n";
        auto atPos{ indexOf( email, "@" ) };
        auto lastDotPos{ lastIndexOf( email, "." ) };
        if ( atPos != std::string_view::npos && lastDotPos != std::string_view::npos )
        {
            std::cout << "  Username: " << email.substr( 0, atPos ) << "\n";
            std::cout << "  Domain: " << email.substr( atPos + 1 ) << "\n";
            std::cout << "  TLD: " << email.substr( lastDotPos + 1 ) << "\n";
        }

        // Search not found
        std::cout << "\nSearch results:\n";
        std::cout << "  indexOf(\"hello\", \"xyz\"): "
                  << ( indexOf( "hello", "xyz" ) == std::string_view::npos ? "not found" : "found" ) << "\n";
        std::cout << "  lastIndexOf(\"test\", \"missing\"): "
                  << ( lastIndexOf( "test", "missing" ) == std::string_view::npos ? "not found" : "found" ) << "\n";
        std::cout << "\n";
    }

    //=====================================================================
    // 5. Performance demonstration
    //=====================================================================
    {
        std::cout << "5. Performance demonstration\n";
        std::cout << "------------------------------\n";

        // Large string processing
        const std::string largeText( 10000, 'X' );
        const std::string searchPattern{ "XXXX" };

        auto start{ std::chrono::high_resolution_clock::now() };

        // Perform multiple operations
        bool hasLength{ hasExactLength( largeText, 10000 ) };
        bool containsPattern{ contains( largeText, searchPattern ) };
        bool startsWithX{ startsWith( largeText, "XXX" ) };
        bool endsWithX{ endsWith( largeText, "XXX" ) };
        std::string lowerCase{ toLower( largeText ) };

        auto end{ std::chrono::high_resolution_clock::now() };
        auto duration{ std::chrono::duration_cast<std::chrono::microseconds>( end - start ) };

        std::cout << "Large string operations (10,000 characters):\n";
        std::cout << "  Length check: " << ( hasLength ? "Passed" : "Failed" ) << "\n";
        std::cout << "  Contains pattern: " << ( containsPattern ? "Yes" : "No" ) << "\n";
        std::cout << "  Starts with XXX: " << ( startsWithX ? "Yes" : "No" ) << "\n";
        std::cout << "  Ends with XXX: " << ( endsWithX ? "Yes" : "No" ) << "\n";
        std::cout << "  Case conversion: " << ( lowerCase.size() == 10000 ? "Success" : "Failed" ) << "\n";
        std::cout << "  Total time: " << duration.count() << " microseconds\n";
        std::cout << "\n";
    }

    return 0;
}

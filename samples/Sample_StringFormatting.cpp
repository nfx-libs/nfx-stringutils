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
 * @file Sample_StringFormatting.cpp
 * @brief Demonstrates text formatting utilities
 * @details This sample shows truncation, word wrapping, indentation, and dedentation
 *          for formatting text output and content manipulation
 */

#include <iostream>
#include <string>

#include <nfx/string/Splitter.h>
#include <nfx/string/Utils.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - Text Formatting ===\n\n";

    //=====================================================================
    // 1. String formatting utilities
    //=====================================================================
    {
        std::cout << "1. String formatting utilities\n";
        std::cout << "-------------------------------\n";

        // Basic truncation
        std::cout << "\n"
                  << "Basic truncation:\n";
        std::cout << "  \"" << truncate( "Hello World", 5 ) << "\" (max 5 chars)\n";
        std::cout << "  \"" << truncate( "Hello World", 11 ) << "\" (max 11 chars, no truncation)\n";
        std::cout << "  \"" << truncate( "Hello", 100 ) << "\" (shorter than limit)\n";

        // Truncation with ellipsis
        std::cout << "\n"
                  << "Truncation with ellipsis:\n";
        std::cout << "  \"" << truncate( "Hello World", 10, "..." ) << "\"\n";
        std::cout << "  \"" << truncate( "This is a very long sentence", 20, "..." ) << "\"\n";
        std::cout << "  \"" << truncate( "Short", 20, "..." ) << "\" (no truncation needed)\n";
        std::cout << "  \"" << truncate( "Hello World", 10, " >>>" ) << "\" (custom ellipsis)\n";

        // Real-world truncation examples
        std::cout << "\n"
                  << "Real-world truncation examples:\n";
        std::cout << "  Filename: \"" << truncate( "very_long_document_name_that_exceeds_display_width.txt", 30, "..." ) << "\"\n";
        std::cout << "  Log message: \"" << truncate( "ERROR: Failed to connect to database server at 192.168.1.1:5432 - connection timeout", 50, "..." ) << "\"\n";
        std::cout << "  User comment: \"" << truncate( "This is a really long comment that someone posted...", 35, "..." ) << "\"\n";

        // Word wrapping
        std::cout << "\n"
                  << "Word wrapping:\n";
        std::string text1{ "This is a simple example of word wrapping" };
        std::cout << "  Original: \"" << text1 << "\"\n";
        std::cout << "  Wrapped (width 20):\n";
        for ( const auto& line : nfx::string::Splitter{ wordWrap( text1, 20 ), '\n' } )
        {
            std::cout << "    \"" << line << "\"\n";
        }

        // Word wrapping preserves existing newlines
        std::cout << "\n"
                  << "Wrapping preserves existing newlines:\n";
        std::string text2{ "First paragraph here.\nSecond paragraph here." };
        std::cout << "  Original:\n    \"First paragraph here.\\nSecond paragraph here.\"\n";
        std::cout << "  Wrapped (width 15):\n";
        for ( const auto& line : nfx::string::Splitter{ wordWrap( text2, 15 ), '\n' } )
        {
            std::cout << "    \"" << line << "\"\n";
        }

        // Word wrapping with long words
        std::cout << "\n"
                  << "Handling long words:\n";
        std::string text3{ "The word Supercalifragilisticexpialidocious is very long" };
        std::cout << "  Original: \"" << text3 << "\"\n";
        std::cout << "  Wrapped (width 20):\n";
        for ( const auto& line : nfx::string::Splitter{ wordWrap( text3, 20 ), '\n' } )
        {
            std::cout << "    \"" << line << "\"\n";
        }

        // Real-world word wrapping example
        std::cout << "\n"
                  << "Real-world example - help text formatting:\n";
        std::string helpText{ "Usage: program [OPTIONS] FILE... Process the specified files with various options. Use --help for more information." };
        std::cout << "  Wrapped to 40 columns:\n";
        for ( const auto& line : nfx::string::Splitter{ wordWrap( helpText, 40 ), '\n' } )
        {
            std::cout << "    " << line << "\n";
        }

        // Basic indentation
        std::cout << "\n"
                  << "Basic indentation:\n";
        std::cout << "  Single line:\n";
        std::cout << "    " << indent( "Hello World", 4 ) << "\n";

        std::cout << "\n"
                  << "  Multi-line text:\n";
        std::string multiLine{ "First line\nSecond line\nThird line" };
        std::cout << indent( multiLine, 2 ) << "\n";

        // Code block formatting
        std::cout << "\n"
                  << "Code block formatting:\n";
        std::string codeBlock{ "if (condition) {\n    doSomething();\n    doSomethingElse();\n}" };
        std::cout << "  Original:\n"
                  << codeBlock << "\n";
        std::cout << "\n  Indented by 4 spaces:\n"
                  << indent( codeBlock, 4 ) << "\n";

        // Nested indentation example
        std::cout << "\n"
                  << "Nested output example:\n";
        std::cout << "Configuration:\n";
        std::cout << indent( "Database:\n" + indent( "Host: localhost\nPort: 5432\nName: mydb", 2 ), 2 ) << "\n";

        // Dedenting - removing common indentation
        std::cout << "\n"
                  << "Dedenting - removing common indentation:\n";
        std::string indentedText{ "    First line\n    Second line\n    Third line" };
        std::cout << "  Original (4 spaces on each line):\n";
        std::cout << "\"" << indentedText << "\"\n";
        std::cout << "\n  After dedent():\n";
        std::cout << "\"" << dedent( indentedText ) << "\"\n";

        // Mixed indentation
        std::cout << "\n"
                  << "Mixed indentation:\n";
        std::string mixedIndent{ "  Line with 2 spaces\n    Line with 4 spaces\n  Back to 2 spaces" };
        std::cout << "  Original:\n";
        for ( const auto& line : nfx::string::Splitter{ mixedIndent, '\n' } )
        {
            std::cout << "    \"" << line << "\"\n";
        }
        std::cout << "\n  After dedent() (removes 2 spaces from all):\n";
        for ( const auto& line : nfx::string::Splitter{ dedent( mixedIndent ), '\n' } )
        {
            std::cout << "    \"" << line << "\"\n";
        }

        // Real-world dedenting example
        std::cout << "\n"
                  << "Real-world example - cleaning multi-line string literals:\n";
        std::string literal = R"(
        class Example {
        public:
            void method() {
                // code here
            }
        };)";

        std::cout << "  Original (from indented code):\n";
        std::cout << "\"" << literal << "\"\n";
        std::cout << "\n  After dedent():\n";
        std::cout << "\"" << dedent( literal ) << "\"\n";

        // Combined formatting example
        std::cout << "\n"
                  << "Combined formatting example:\n";
        std::cout << "Formatting a log entry:\n";
        std::string timestamp{ "[2024-01-15 10:30:45]" };
        std::string level{ "ERROR" };
        std::string longMessage{ "Failed to establish connection to remote server database.example.com:5432 after 3 retry attempts with exponential backoff strategy" };

        // Truncate the message if too long
        std::string displayMessage{ truncate( longMessage, 60, "..." ) };

        // Word wrap detailed information
        std::string details{ "Connection parameters: host=database.example.com port=5432 timeout=30s retry_count=3 backoff_strategy=exponential" };
        std::string wrappedDetails{ wordWrap( details, 50 ) };

        // Indent the details
        std::string indentedDetails{ indent( wrappedDetails, 4 ) };

        // Display the formatted log entry
        std::cout << "\n";
        std::cout << timestamp << " " << level << ": " << displayMessage << "\n";
        std::cout << "  Details:\n";
        std::cout << indentedDetails << "\n";
        std::cout << "\n";
    }

    return 0;
}

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
 * @file Sample_StringComparison.cpp
 * @brief Demonstrates advanced comparison operations
 * @details This sample shows case-insensitive comparison, natural sorting with
 *          embedded numbers, and finding common prefixes and suffixes
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <nfx/string/Utils.h>

int main()
{
    using namespace nfx::string;

    std::cout << "=== nfx-stringutils Library - Advanced Comparisons ===\n\n";

    //=====================================================================
    // 1. Advanced comparison operations
    //=====================================================================
    {
        std::cout << "1. Advanced comparison operations\n";
        std::cout << "-----------------------------------\n";

        // Case-insensitive comparison
        std::cout << "\nCase-insensitive comparison (compareIgnoreCase):\n";
        std::cout << "  compareIgnoreCase(\"apple\", \"APPLE\"): " << compareIgnoreCase( "apple", "APPLE" ) << " (equal)\n";
        std::cout << "  compareIgnoreCase(\"apple\", \"BANANA\"): " << compareIgnoreCase( "apple", "BANANA" ) << " (apple < banana)\n";
        std::cout << "  compareIgnoreCase(\"zebra\", \"APPLE\"): " << compareIgnoreCase( "zebra", "APPLE" ) << " (zebra > apple)\n";

        // Sorting with case-insensitive comparison
        std::vector<std::string> names{ "charlie", "ALICE", "bob", "DAVID" };
        std::cout << "\nSorting names (case-insensitive):\n";
        std::cout << "  Before: ";
        for ( const auto& name : names )
        {
            std::cout << name << " ";
        }
        std::sort( names.begin(), names.end(), []( const auto& a, const auto& b ) { return compareIgnoreCase( a, b ) < 0; } );
        std::cout << "\n  After:  ";
        for ( const auto& name : names )
        {
            std::cout << name << " ";
        }
        std::cout << "\n";

        // Natural sorting (handles embedded numbers)
        std::cout << "\nNatural sorting comparison (naturalCompare):\n";
        std::cout << "  naturalCompare(\"file2.txt\", \"file10.txt\"): " << naturalCompare( "file2.txt", "file10.txt" ) << " (file2 < file10)\n";
        std::cout << "  naturalCompare(\"v1.9\", \"v1.10\"): " << naturalCompare( "v1.9", "v1.10" ) << " (1.9 < 1.10)\n";
        std::cout << "  naturalCompare(\"chapter2\", \"chapter10\"): " << naturalCompare( "chapter2", "chapter10" ) << " (chapter2 < chapter10)\n";

        // Sorting filenames naturally
        std::vector<std::string> files{ "file10.txt", "file2.txt", "file1.txt", "file20.txt" };
        std::cout << "\nSorting filenames (natural order):\n";
        std::cout << "  Before: ";
        for ( const auto& file : files )
        {
            std::cout << file << " ";
        }
        std::sort( files.begin(), files.end(), []( const auto& a, const auto& b ) { return naturalCompare( a, b ) < 0; } );
        std::cout << "\n  After:  ";
        for ( const auto& file : files )
        {
            std::cout << file << " ";
        }
        std::cout << "\n";

        // Version sorting
        std::vector<std::string> versions{ "v1.10.0", "v1.2.0", "v1.9.5", "v2.0.0", "v1.2.3" };
        std::cout << "\nSorting version numbers:\n";
        std::cout << "  Before: ";
        for ( const auto& ver : versions )
        {
            std::cout << ver << " ";
        }
        std::sort( versions.begin(), versions.end(), []( const auto& a, const auto& b ) { return naturalCompare( a, b ) < 0; } );
        std::cout << "\n  After:  ";
        for ( const auto& ver : versions )
        {
            std::cout << ver << " ";
        }
        std::cout << "\n";

        // Common prefix
        std::cout << "\nFinding common prefix (commonPrefix):\n";
        std::cout << "  commonPrefix(\"/usr/local/bin\", \"/usr/local/lib\"): \"" << commonPrefix( "/usr/local/bin", "/usr/local/lib" ) << "\"\n";
        std::cout << "  commonPrefix(\"testing\", \"tester\"): \"" << commonPrefix( "testing", "tester" ) << "\"\n";
        std::cout << "  commonPrefix(\"file_1.txt\", \"file_2.txt\"): \"" << commonPrefix( "file_1.txt", "file_2.txt" ) << "\"\n";
        std::cout << "  commonPrefix(\"Hello\", \"World\"): \"" << commonPrefix( "Hello", "World" ) << "\" (no match)\n";

        // Path comparison using common prefix
        std::cout << "\nFinding common directory paths:\n";
        std::string path1{ "/home/user/documents/work/project" };
        std::string path2{ "/home/user/documents/personal/photos" };
        auto prefix = commonPrefix( path1, path2 );
        std::cout << "  Path 1: " << path1 << "\n";
        std::cout << "  Path 2: " << path2 << "\n";
        std::cout << "  Common: " << prefix << "\n";

        // Common suffix
        std::cout << "\nFinding common suffix (commonSuffix):\n";
        std::cout << "  commonSuffix(\"file1.txt\", \"file2.txt\"): \"" << commonSuffix( "file1.txt", "file2.txt" ) << "\"\n";
        std::cout << "  commonSuffix(\"testing\", \"running\"): \"" << commonSuffix( "testing", "running" ) << "\"\n";
        std::cout << "  commonSuffix(\"unit_test.cpp\", \"integration_test.cpp\"): \"" << commonSuffix( "unit_test.cpp", "integration_test.cpp" ) << "\"\n";
        std::cout << "  commonSuffix(\"Hello\", \"World\"): \"" << commonSuffix( "Hello", "World" ) << "\" (no match)\n";

        // File extension grouping using common suffix
        std::cout << "\nGrouping files by extension:\n";
        std::vector<std::string> allFiles{ "report.pdf", "data.csv", "image.jpg", "document.pdf", "chart.jpg", "config.ini" };
        for ( const auto& file : allFiles )
        {
            auto ext = commonSuffix( file, ".pdf" );
            if ( !ext.empty() )
            {
                std::cout << "  PDF: " << file << "\n";
            }
        }

        // Real-world: Autocomplete suggestions
        std::cout << "\nAutocomplete example (finding common prefix):\n";
        std::vector<std::string> commands{ "create_user", "create_group", "create_role" };
        std::cout << "  Commands: ";
        for ( const auto& cmd : commands )
        {
            std::cout << cmd << " ";
        }
        auto suggestion = commonPrefix( commonPrefix( commands[0], commands[1] ), commands[2] );
        std::cout << "\n  Auto-complete suggestion: \"" << suggestion << "\"\n";
        std::cout << "\n";
    }

    return 0;
}

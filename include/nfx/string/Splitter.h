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
 * @file Splitter.h
 * @brief Zero-allocation string splitting utilities for high-performance string processing
 * @details Provides efficient string_view-based splitting without heap allocations,
 *          perfect for performance-critical paths and CSV parsing applications
 */

#pragma once

#include <cstddef>
#include <iterator>
#include <string_view>

namespace nfx::string
{
	//=====================================================================
	// Splitter class
	//=====================================================================

	/**
	 * @brief Zero-allocation string splitting iterator for performance-critical paths
	 * @details Provides efficient string_view-based splitting without heap allocations
	 */
	class Splitter
	{
	public:
		//----------------------------------------------
		// Forward declarations
		//----------------------------------------------

		class Iterator;

		//----------------------------------------------
		// Construction
		//----------------------------------------------

		/**
		 * @brief Constructs a Splitter for the given string and delimiter
		 * @details Accepts any string-like type that can be converted to std::string_view
		 * @tparam String Any type convertible to std::string_view (std::string, const char*, etc.)
		 * @param str String to split
		 * @param delimiter Character to split on
		 */
		template <typename String>
		inline explicit Splitter( String&& str, char delimiter ) noexcept;

		//----------------------------------------------
		// Iteration
		//----------------------------------------------

		/**
		 * @brief Returns iterator to first segment
		 * @return Iterator pointing to the first string segment
		 */
		inline Iterator begin() const noexcept;

		/**
		 * @brief Returns end iterator for range-based loops
		 * @return End iterator for range-based iteration
		 */
		inline Iterator end() const noexcept;

		//----------------------------------------------
		// Splitter::Iterator class
		//----------------------------------------------

		/**
		 * @brief Forward iterator for string segments
		 */
		class Iterator
		{
		public:
			//-----------------------------
			// Iterator traits
			//-----------------------------

			/**
			 * @brief Iterator category tag
			 * @details Defines this as a forward iterator, supporting multi-pass guarantee
			 */
			using iterator_category = std::forward_iterator_tag;

			/**
			 * @brief Type of values returned by dereferencing the iterator
			 * @details Returns std::string_view for zero-copy string segments
			 */
			using value_type = std::string_view;

			/**
			 * @brief Type for representing distances between iterators
			 * @details Used by STL algorithms like std::distance and std::advance
			 */
			using difference_type = std::ptrdiff_t;

			/**
			 * @brief Pointer type to the value_type
			 * @details Pointer to const string_view for safety
			 */
			using pointer = const std::string_view*;

			/**
			 * @brief Reference type returned by dereferencing
			 * @details Returns string_view by value (not a true reference)
			 */
			using reference = std::string_view;

			//-----------------------------
			// Construction
			//-----------------------------

			/**
			 * @brief Default constructor
			 * @details Creates an invalid iterator that must be assigned before use
			 */
			inline Iterator() noexcept = default;

			/**
			 * @brief Constructs iterator at beginning or end position
			 * @param splitter Reference to the parent Splitter object
			 * @param at_end Whether to position iterator at end (default: false for begin)
			 */
			inline explicit Iterator( const Splitter& splitter, bool at_end = false ) noexcept;

			//-----------------------------
			// Iterator operators
			//-----------------------------

			/**
			 * @brief Dereferences iterator to get current string segment
			 * @return String view of the current segment
			 */
			inline std::string_view operator*() const noexcept;

			/**
			 * @brief Pre-increment operator to advance to next segment
			 * @return Reference to this iterator after advancement
			 */
			inline Iterator& operator++() noexcept;

			/**
			 * @brief Post-increment operator to advance to next segment
			 * @return Copy of iterator before advancement
			 */
			inline Iterator operator++( int ) noexcept;

			//-----------------------------
			// Comparison operators
			//-----------------------------

			/**
			 * @brief Compares iterators for equality
			 * @param other Iterator to compare with
			 * @return true if iterators are equal, false otherwise
			 */
			inline bool operator==( const Iterator& other ) const noexcept;

			/**
			 * @brief Compares iterators for inequality
			 * @param other Iterator to compare with
			 * @return true if iterators are not equal, false otherwise
			 */
			inline bool operator!=( const Iterator& other ) const noexcept;

		private:
			//-----------------------------
			// Private member variables
			//-----------------------------

			const Splitter* m_splitter{ nullptr };
			size_t m_start{};
			size_t m_end{};
			bool m_isAtEnd{ true };
		};

	private:
		std::string_view m_str;
		char m_delimiter;
	};

	//=====================================================================
	// String splitting factory functions
	//=====================================================================

	/**
	 * @brief Templated factory function for zero-copy string splitting
	 * @details Creates a Splitter for efficient iteration over string segments
	 *          without heap allocations. Accepts any string-like type that can
	 *          be converted to std::string_view.
	 * @tparam String Any type convertible to std::string_view (std::string, const char*, etc.)
	 * @param str String to split
	 * @param delimiter Character to split on
	 * @return Splitter object for range-based iteration
	 * @note This function is marked [[nodiscard]] - the return value should not be ignored
	 */
	template <typename String>
	[[nodiscard]] inline Splitter splitView( String&& str, char delimiter ) noexcept;
} // namespace nfx::string

#include "nfx/detail/string/Splitter.inl"

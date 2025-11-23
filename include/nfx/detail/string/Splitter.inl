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
 * @file Splitter.inl
 * @brief Implementation of zero-allocation string splitting utilities
 * @details Inline implementations for high-performance string_view-based splitting
 */

namespace nfx::string
{
	//=====================================================================
	// Splitter class
	//=====================================================================

	//----------------------------------------------
	// Construction
	//----------------------------------------------

	template <typename String>
	inline Splitter::Splitter( String&& str, char delimiter ) noexcept
		: m_str{ std::string_view{ std::forward<String>( str ) } },
		  m_delimiter{ delimiter }
	{
	}

	//----------------------------------------------
	// Iteration
	//----------------------------------------------

	inline Splitter::Iterator Splitter::begin() const noexcept
	{
		return Iterator{ *this };
	}

	inline Splitter::Iterator Splitter::end() const noexcept
	{
		return Iterator{ *this, true };
	}

	//----------------------------------------------
	// Splitter::Iterator class
	//----------------------------------------------

	//-----------------------------
	// Construction
	//-----------------------------

	inline Splitter::Iterator::Iterator( const Splitter& splitter, bool at_end ) noexcept
		: m_splitter{ &splitter },
		  m_start{ 0 },
		  m_end{ 0 },
		  m_isAtEnd{ at_end || splitter.m_str.empty() }
	{
		if ( !m_isAtEnd )
		{
			m_end = m_splitter->m_str.find( m_splitter->m_delimiter, 0 );
			if ( m_end == std::string_view::npos )
			{
				m_end = m_splitter->m_str.length();
			}
		}
	}

	//-----------------------------
	// Iterator operators
	//-----------------------------

	inline std::string_view Splitter::Iterator::operator*() const noexcept
	{
		const size_t length = m_end - m_start;
		return m_splitter->m_str.substr( m_start, length );
	}

	inline Splitter::Iterator& Splitter::Iterator::operator++() noexcept
	{
		m_start = m_end + 1;

		const size_t str_len = m_splitter->m_str.length();
		if ( m_start > str_len )
		{
			m_isAtEnd = true;
			return *this;
		}

		m_end = m_splitter->m_str.find( m_splitter->m_delimiter, m_start );
		if ( m_end == std::string_view::npos )
		{
			m_end = str_len;
		}

		return *this;
	}

	inline Splitter::Iterator Splitter::Iterator::operator++( int ) noexcept
	{
		Iterator temp = *this;
		++( *this );
		return temp;
	}

	//-----------------------------
	// Comparison operators
	//-----------------------------

	inline bool Splitter::Iterator::operator==( const Iterator& other ) const noexcept
	{
		return m_isAtEnd == other.m_isAtEnd;
	}

	inline bool Splitter::Iterator::operator!=( const Iterator& other ) const noexcept
	{
		return !( *this == other );
	}

	//=====================================================================
	// String splitting factory functions
	//=====================================================================

	template <typename String>
	inline Splitter splitView( String&& str, char delimiter ) noexcept
	{
		return Splitter{ std::string_view{ std::forward<String>( str ) }, delimiter };
	}
} // namespace nfx::string

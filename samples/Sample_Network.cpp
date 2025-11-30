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
 * @file Sample_Network.cpp
 * @brief Demonstrates comprehensive usage of network and URI validation utilities
 * @details This sample shows how to validate IPv4/IPv6 addresses, hostnames,
 *          domains, ports, and endpoints using RFC-compliant validation functions
 */

#include <iostream>
#include <string>
#include <string_view>

#include <nfx/string/Utils.h>

int main()
{
	using namespace nfx::string;

	std::cout << "=== nfx-stringutils Library - Network & URI Validation ===\n\n";

	//=====================================================================
	// 1. IPv4 address validation (RFC 791)
	//=====================================================================
	{
		std::cout << "1. IPv4 address validation (RFC 791)\n";
		std::cout << "---------------------------------------\n";

		const std::string_view ipv4Examples[]{
			"192.168.1.1",	   // Valid private IP
			"10.0.0.1",		   // Valid private IP
			"172.16.0.1",	   // Valid private IP
			"8.8.8.8",		   // Valid public IP (Google DNS)
			"255.255.255.255", // Valid broadcast address
			"0.0.0.0",		   // Valid (any address)
			"127.0.0.1",	   // Valid loopback
			"256.1.1.1",	   // Invalid (octet > 255)
			"192.168.1",	   // Invalid (missing octet)
			"192.168.1.1.1",   // Invalid (too many octets)
			"192.168.-1.1",	   // Invalid (negative)
			"192.168.01.1",	   // Invalid (leading zero)
			"",				   // Invalid (empty)
			"not.an.ip.addr"   // Invalid (non-numeric)
		};

		for ( const auto& ip : ipv4Examples )
		{
			const bool isValid{ isIpv4Address( ip ) };
			std::cout << "  ";
			if ( ip.empty() )
			{
				std::cout << "(empty)";
				std::cout << std::string( 20 - 7, ' ' );
			}
			else
			{
				std::cout << ip;
				if ( ip.length() < 20 )
				{
					std::cout << std::string( 20 - ip.length(), ' ' );
				}
			}
			std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 2. IPv6 address validation (RFC 4291/5952)
	//=====================================================================
	{
		std::cout << "2. IPv6 address validation (RFC 4291/5952)\n";
		std::cout << "---------------------------------------------\n";

		const std::string_view ipv6Examples[]{
			"2001:0db8:85a3:0000:0000:8a2e:0370:7334", // Valid full form
			"2001:db8:85a3::8a2e:370:7334",			   // Valid compressed
			"::1",									   // Valid loopback
			"::",									   // Valid any address
			"fe80::1",								   // Valid link-local
			"ff02::1",								   // Valid multicast
			"2001:db8::1",							   // Valid compressed
			"::ffff:192.0.2.1",						   // Valid IPv4-mapped
			"fe80::1%eth0",							   // Valid with zone ID
			"2001:db8:85a3::8a2e:370g:7334",		   // Invalid (g is not hex)
			"02001:db8::1",							   // Invalid (5 hex digits)
			"2001:db8:::1",							   // Invalid (triple colon)
			"",										   // Invalid (empty)
			"hello::world"							   // Invalid (non-hex)
		};

		for ( const auto& ip : ipv6Examples )
		{
			const bool isValid{ isIpv6Address( ip ) };
			std::cout << "  ";
			if ( ip.empty() )
			{
				std::cout << "(empty)";
				std::cout << std::string( 40 - 7, ' ' );
			}
			else
			{
				std::cout << ip;
				if ( ip.length() < 40 )
				{
					std::cout << std::string( 40 - ip.length(), ' ' );
				}
			}
			std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 3. Hostname validation (RFC 1123)
	//=====================================================================
	{
		std::cout << "3. Hostname validation (RFC 1123)\n";
		std::cout << "-----------------------------------\n";

		const std::string_view hostnameExamples[]{
			"localhost",																  // Valid
			"example",																	  // Valid single label
			"my-server",																  // Valid with hyphen
			"web01",																	  // Valid alphanumeric
			"api-gateway-prod",															  // Valid multi-hyphen
			"a",																		  // Valid single char
			"example.com",																  // Valid (also a domain)
			"-invalid",																	  // Invalid (starts with hyphen)
			"invalid-",																	  // Invalid (ends with hyphen)
			"my_server",																  // Invalid (underscore not allowed in hostname)
			"",																			  // Invalid (empty)
			"this-label-is-way-too-long-because-it-exceeds-sixty-three-characters-limit", // Invalid (label > 63)
			"example..com"																  // Invalid (consecutive dots make empty label)
		};

		for ( const auto& hostname : hostnameExamples )
		{
			const bool isValid{ isHostname( hostname ) };
			std::cout << "  ";
			if ( hostname.empty() )
			{
				std::cout << "(empty)";
				std::cout << std::string( 75 - 7, ' ' );
			}
			else
			{
				std::cout << hostname;
				if ( hostname.length() < 75 )
				{
					std::cout << std::string( 75 - hostname.length(), ' ' );
				}
			}
			std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 4. Domain name validation (RFC 1035)
	//=====================================================================
	{
		std::cout << "4. Domain name validation (RFC 1035)\n";
		std::cout << "--------------------------------------\n";

		const std::string_view domainExamples[]{
			"example.com",			 // Valid
			"www.example.com",		 // Valid subdomain
			"api.v2.example.com",	 // Valid multiple subdomains
			"my-site.co.uk",		 // Valid with hyphen
			"example.museum",		 // Valid long TLD
			"xn--e1afmkfd.xn--p1ai", // Valid internationalized domain (punycode)
			"localhost",			 // Invalid (no dot, not FQDN)
			"example",				 // Invalid (no TLD)
			".example.com",			 // Invalid (starts with dot)
			"example.com.",			 // Valid (trailing dot is FQDN notation, but we accept it)
			"example..com",			 // Invalid (consecutive dots)
			"",						 // Invalid (empty)
			"-example.com",			 // Invalid (label starts with hyphen)
			"example-.com"			 // Invalid (label ends with hyphen)
		};

		for ( const auto& domain : domainExamples )
		{
			const bool isValid{ isDomainName( domain ) };
			std::cout << "  ";
			if ( domain.empty() )
			{
				std::cout << "(empty)";
				std::cout << std::string( 30 - 7, ' ' );
			}
			else
			{
				std::cout << domain;
				if ( domain.length() < 30 )
				{
					std::cout << std::string( 30 - domain.length(), ' ' );
				}
			}
			std::cout << " -> " << ( isValid ? "[OK] Valid    " : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 5. Port number validation (RFC 6335)
	//=====================================================================
	{
		std::cout << "5. Port number validation (RFC 6335)\n";
		std::cout << "--------------------------------------\n";

		std::cout << "  Compile-time validation with templates:\n";

		// Valid port numbers
		constexpr auto httpPort{ "80" };
		constexpr auto httpsPort{ "443" };
		constexpr auto sshPort{ "22" };
		constexpr auto customPort{ "8080" };
		constexpr auto maxPort{ "65535" };

		std::cout << "    HTTP port " << httpPort << " -> " << ( isPortNumber( httpPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		std::cout << "    HTTPS port " << httpsPort << " -> " << ( isPortNumber( httpsPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		std::cout << "    SSH port " << sshPort << " -> " << ( isPortNumber( sshPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		std::cout << "    Custom port " << customPort << " -> " << ( isPortNumber( customPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		std::cout << "    Max port " << maxPort << " -> " << ( isPortNumber( maxPort ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		std::cout << "\n";
	}

	//=====================================================================
	// 6. Endpoint parsing (Host:Port)
	//=====================================================================
	{
		std::cout << "6. Endpoint parsing (Host:Port)\n";
		std::cout << "---------------------------------\n";

		const std::string_view endpointExamples[]{
			"192.168.1.1:8080",		// Valid IPv4
			"example.com:443",		// Valid domain
			"localhost:3000",		// Valid hostname
			"[2001:db8::1]:80",		// Valid IPv6
			"[::1]:8080",			// Valid IPv6 loopback
			"[fe80::1%eth0]:22",	// Valid IPv6 with zone
			"api.example.com:8443", // Valid subdomain
			"192.168.1.1",			// Invalid (no port)
			"example.com:",			// Invalid (empty port)
			":8080",				// Invalid (empty host)
			"192.168.1.1:70000",	// Invalid (port > 65535)
			"[2001:db8::1:80",		// Invalid (missing bracket)
			"256.1.1.1:80",			// Invalid (invalid IPv4)
			"",						// Invalid (empty)
			"example.com:abc"		// Invalid (non-numeric port)
		};

		for ( const auto& endpoint : endpointExamples )
		{
			std::string_view host{};
			uint16_t port{};
			const bool parsed{ tryParseEndpoint( endpoint, host, port ) };

			std::cout << "  ";
			if ( endpoint.empty() )
			{
				std::cout << "(empty)";
				std::cout << std::string( 30 - 7, ' ' );
			}
			else
			{
				std::cout << endpoint;
				if ( endpoint.length() < 30 )
				{
					std::cout << std::string( 30 - endpoint.length(), ' ' );
				}
			}
			std::cout << " -> ";

			if ( parsed )
			{
				std::cout << "[OK] Host: \"" << host << "\", Port: " << port;
			}
			else
			{
				std::cout << "[FAIL] Invalid";
			}
			std::cout << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 7. URI character validation (RFC 3986)
	//=====================================================================
	{
		std::cout << "7. URI character validation (RFC 3986)\n";
		std::cout << "----------------------------------------\n";

		std::cout << "  Reserved characters (must be percent-encoded in certain contexts):\n";
		const std::string_view reservedChars{ ":/?#[]@!$&'()*+,;=" };
		for ( const char ch : reservedChars )
		{
			std::cout << "    '" << ch << "' -> " << ( isUriReserved( ch ) ? "[OK] Reserved" : "[FAIL] Not reserved" ) << "\n";
		}

		std::cout << "\n";
		std::cout << "  Unreserved characters (safe to use without encoding):\n";
		const std::string_view unreservedChars{ "ABCabc123-._~" };
		for ( const char ch : unreservedChars )
		{
			std::cout << "    '" << ch << "' -> " << ( isUriUnreserved( ch ) ? "[OK] Unreserved" : "[FAIL] Not unreserved" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 8. Real-world use case: Server configuration validation
	//=====================================================================
	{
		std::cout << "8. Real-world use case: Server configuration validation\n";
		std::cout << "----------------------------------------------------------\n";

		const std::string_view serverEndpoint{ "api.example.com:8443" };
		std::string_view serverHost{};
		uint16_t serverPort{};

		if ( tryParseEndpoint( serverEndpoint, serverHost, serverPort ) )
		{
			if ( isDomainName( serverHost ) || isHostname( serverHost ) )
			{
				std::cout << "  [OK] Server configuration is valid\n";
				std::cout << "    Endpoint: " << serverEndpoint << "\n";
				std::cout << "    Host: " << serverHost << "\n";
				std::cout << "    Port: " << serverPort << "\n";
			}
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 9. Real-world use case: Network address classification
	//=====================================================================
	{
		std::cout << "9. Real-world use case: Network address classification\n";
		std::cout << "---------------------------------------------------------\n";

		const std::string_view addresses[]{ "192.168.1.1", "2001:db8::1", "example.com", "localhost" };

		for ( const auto& addr : addresses )
		{
			std::cout << "  Address: " << addr << " -> ";
			if ( isIpv4Address( addr ) )
			{
				std::cout << "IPv4";
			}
			else if ( isIpv6Address( addr ) )
			{
				std::cout << "IPv6";
			}
			else if ( isDomainName( addr ) )
			{
				std::cout << "Domain name";
			}
			else if ( isHostname( addr ) )
			{
				std::cout << "Hostname";
			}
			else
			{
				std::cout << "Unknown/Invalid";
			}
			std::cout << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 10. Real-world use case: Connection string parsing
	//=====================================================================
	{
		std::cout << "10. Real-world use case: Connection string parsing\n";
		std::cout << "-----------------------------------------------------\n";

		const std::string_view connections[]{ "localhost:5432", "[::1]:3306", "db.prod.internal:27017" };

		for ( const auto& conn : connections )
		{
			std::string_view dbHost{};
			uint16_t dbPort{};

			if ( tryParseEndpoint( conn, dbHost, dbPort ) )
			{
				std::cout << "  [OK] Connection: " << conn << "\n";
				std::cout << "    Database host: " << dbHost << "\n";
				std::cout << "    Database port: " << dbPort << "\n";
			}
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 11. Date/Time validation (RFC 3339)
	//=====================================================================
	{
		std::cout << "11. Date/Time validation (RFC 3339)\n";
		std::cout << "--------------------------------------\n";

		std::cout << "  Dates:\n";
		const std::string_view dateExamples[]{
			"2025-11-29",
			"2000-01-01",
			"2025-13-01", // Invalid month
			"2025-02-30", // Invalid day
		};

		for ( const auto& date : dateExamples )
		{
			std::cout << "    " << date << std::string( 20 - date.length(), ' ' )
					  << " -> " << ( isDate( date ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n  Times:\n";
		const std::string_view timeExamples[]{
			"14:30:00Z",
			"23:59:59+05:30",
			"14:30:00.123Z",
			"14:30:00", // Missing timezone
		};

		for ( const auto& time : timeExamples )
		{
			std::cout << "    " << time << std::string( 20 - time.length(), ' ' )
					  << " -> " << ( isTime( time ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n  DateTimes:\n";
		const std::string_view dateTimeExamples[]{
			"2025-11-29T14:30:00Z",
			"2025-11-29T14:30:00+05:30",
			"2025-11-29 14:30:00Z", // Space instead of T
		};

		for ( const auto& dt : dateTimeExamples )
		{
			std::cout << "    " << dt << std::string( 30 - dt.length(), ' ' )
					  << " -> " << ( isDateTime( dt ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 12. Duration validation (ISO 8601)
	//=====================================================================
	{
		std::cout << "12. Duration validation (ISO 8601)\n";
		std::cout << "-------------------------------------\n";

		const std::string_view durationExamples[]{
			"P1Y",
			"P1Y2M3D",
			"PT1H30M",
			"P1Y2M3DT4H5M6S",
			"P2W",
			"PT0.5S",
			"P",	// Invalid
			"1Y2M", // Missing P
		};

		for ( const auto& dur : durationExamples )
		{
			std::cout << "  " << dur << std::string( 20 - dur.length(), ' ' )
					  << " -> " << ( isDuration( dur ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 13. Email validation (RFC 5321)
	//=====================================================================
	{
		std::cout << "13. Email validation (RFC 5321)\n";
		std::cout << "----------------------------------\n";

		const std::string_view emailExamples[]{
			"user@example.com",
			"user.name+tag@example.co.uk",
			"admin@localhost",	// Invalid (no TLD)
			"@example.com",		// Invalid (no local)
			"user@.com",		// Invalid
			"user..name@x.com", // Invalid (consecutive dots)
		};

		for ( const auto& email : emailExamples )
		{
			std::cout << "  " << email << std::string( 35 - email.length(), ' ' )
					  << " -> " << ( isEmail( email ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 14. UUID validation (RFC 4122)
	//=====================================================================
	{
		std::cout << "14. UUID validation (RFC 4122)\n";
		std::cout << "---------------------------------\n";

		const std::string_view uuidExamples[]{
			"550e8400-e29b-41d4-a716-446655440000",
			"00000000-0000-0000-0000-000000000000",
			"FFFFFFFF-FFFF-FFFF-FFFF-FFFFFFFFFFFF",
			"550e8400e29b41d4a716446655440000",		// Missing hyphens
			"550e8400-e29b-41d4-a716",				// Too short
			"550g8400-e29b-41d4-a716-446655440000", // Invalid hex
		};

		for ( const auto& uuid : uuidExamples )
		{
			std::cout << "  " << uuid << std::string( 40 - uuid.length(), ' ' )
					  << " -> " << ( isUuid( uuid ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 15. URI validation (RFC 3986)
	//=====================================================================
	{
		std::cout << "15. URI validation (RFC 3986)\n";
		std::cout << "--------------------------------\n";

		const std::string_view uriExamples[]{
			"https://example.com",
			"http://example.com/path?query=1#frag",
			"mailto:user@example.com",
			"file:///path/to/file",
			"urn:isbn:0451450523",
			"example.com",	  // Invalid (no scheme)
			"://example.com", // Invalid (empty scheme)
		};

		for ( const auto& uri : uriExamples )
		{
			std::cout << "  " << uri << std::string( 40 - uri.length(), ' ' )
					  << " -> " << ( isUri( uri ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n  URI References (includes relative):\n";
		const std::string_view uriRefExamples[]{
			"/path/to/resource",
			"../parent/path",
			"?query=value",
			"#fragment",
		};

		for ( const auto& ref : uriRefExamples )
		{
			std::cout << "    " << ref << std::string( 25 - ref.length(), ' ' )
					  << " -> " << ( isUriReference( ref ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	//=====================================================================
	// 16. JSON Pointer validation (RFC 6901)
	//=====================================================================
	{
		std::cout << "16. JSON Pointer validation (RFC 6901)\n";
		std::cout << "-----------------------------------------\n";

		std::cout << "  JSON Pointers:\n";
		const std::string_view jsonPtrExamples[]{
			"", // Root document
			"/foo",
			"/foo/bar/0",
			"/a~1b", // Escaped /
			"/m~0n", // Escaped ~
			"foo",	 // Invalid (no leading /)
			"/foo~", // Invalid (incomplete escape)
		};

		for ( const auto& ptr : jsonPtrExamples )
		{
			const std::string display = ptr.empty() ? "(empty)" : std::string( ptr );
			std::cout << "    " << display << std::string( 20 - display.length(), ' ' )
					  << " -> " << ( isJsonPointer( ptr ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n  Relative JSON Pointers:\n";
		const std::string_view relPtrExamples[]{
			"0#",
			"1/foo",
			"2/foo/bar",
			"0/a~0b",
			"",		  // Invalid
			"/foo",	  // Invalid (absolute)
			"01/foo", // Invalid (leading zero)
		};

		for ( const auto& ptr : relPtrExamples )
		{
			const std::string display = ptr.empty() ? "(empty)" : std::string( ptr );
			std::cout << "    " << display << std::string( 20 - display.length(), ' ' )
					  << " -> " << ( isRelativeJsonPointer( ptr ) ? "[OK] Valid" : "[FAIL] Invalid" ) << "\n";
		}

		std::cout << "\n";
	}

	return 0;
}

/*
    MIT License
    Copyright (c) 2020 Cos8o
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#ifndef _GDCRYPTO_HPP
#define _GDCRYPTO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstdint>
#include <array>
#include <string_view>
#include "GDCrypto/Utility.hpp"

namespace gdcrypto
{
	#if defined(GDCRYPTO_BUILD)
		#if !defined(GDCRYPTO_STATIC)
			#if defined(_MSC_VER)
				#define GDCRYPTO_API __declspec(dllexport)
			#else
				#define GDCRYPTO_API __attribute__((visibility("default")))
			#endif
		#endif
	#else
		#define GDCRYPTO_API
	#endif

	/*
		Null key
		Does not affect the data
	*/
	static std::array<std::uint8_t, 1> const NULL_KEY = { 0x00 };

	/*
		Savegame key
		Used to encode/decode savegames
	*/
	static std::array<std::uint8_t, 1> const SAVEGAME_KEY = { 0x0B };

	/*
		GJP key
		Used to encode/decode passwords
	*/
	static std::array<std::uint8_t, 5> const GJP_KEY = { 0x33, 0x37, 0x35, 0x32, 0x36 };

	/*
		Message key
		Used to encode/decode messages
	*/
	static std::array<std::uint8_t, 5> const MESSAGE_KEY = { 0x31, 0x34, 0x32, 0x35, 0x31 };

	/*
		Level key
		Used when generating level checks in requests

		Level downloading check (chk): LevelID + Inc + RS + AccountID + UDID + UUID
		Level uploading check (seed2): levelSeed
		Generate "levelSeed" using the utility function
	*/
	static std::array<std::uint8_t, 5> const LEVEL_KEY = { 0x34, 0x31, 0x32, 0x37, 0x34 };

	/*
		Comment key
		Used when generating comment checks in requests

		Comment check (chk): Username + Comment + LevelID + Percentage +
		Comment Type (0 = Level, 1 = User)
	*/
	static std::array<std::uint8_t, 5> const COMMENT_KEY = { 0x32, 0x39, 0x34, 0x38, 0x31 };

	/*
		Challenges key
		Used when generating challenges checks in requests

		Challenges check (chk): 5 random chars + Random number
	*/
	static std::array<std::uint8_t, 5> const CHALLENGES_KEY = { 0x31, 0x39, 0x38, 0x34, 0x37 };

	/*
		Rewards key
		Used when generating rewards checks in requests

		Rewards check (chk): 5 random chars + Random number
	*/
	static std::array<std::uint8_t, 5> const REWARDS_KEY = { 0x35, 0x39, 0x31, 0x38, 0x32 };

	/*
		Like key
		Used when generating like checks in requests

		Like check (chk): Special + ItemID + Like + Type + RS + AccountID +
		UDID + UUID
	*/
	static std::array<std::uint8_t, 5> const LIKE_KEY = { 0x35, 0x38, 0x32, 0x38, 0x31 };

	/*
		Rate key
		Used when generating rate checks in requests

		Rate check (chk): LevelID + Stars + RS + AccountID + UDID + UUID
	*/
	static std::array<std::uint8_t, 5> const RATE_KEY = { 0x35, 0x38, 0x32, 0x38, 0x31 };

	/*
		Userscore key
		Used when generating userscore checks in requests

		Userscore check (seed2): AccountID + UserCoins + Demons + Stars +
		Coins + IconType + Icon + Diamonds + AccIcon + AccShip + AccBall +
		AccBird + AccDart + AccRobot + AccGlow + AccSpider + AccExplosion
	*/
	static std::array<std::uint8_t, 5> const USERSCORE_KEY = { 0x38, 0x35, 0x32, 0x37, 0x31 };

	/*
		Levelscore key
		Used when generating checks for the level leaderboards

		Userscore check (chk): AccountID + LevelID + Percentage + Seconds +
		Jumps + Attempts + levelscoreSeed + Bests Differences + UNKNOWN (always 1)
		+ UserCoins + DailyID + Seed7 ("s7" from packet)
		Seconds = seconds taken to reach the best
		Jumps = jumps taken to reach the best
		Bests Differences = differences between bests, ex: 0% - 65% - 100% -> (65 - 0), (100 - 65) -> 65,35
		Generate "levelscoreSeed" using the utility function
	*/
	static std::array<std::uint8_t, 5> const LEVELSCORE_KEY = { 0x33, 0x39, 0x36, 0x37, 0x33 };

	/*
		Level salt
		Used when generating level checks in requests
	*/
	//static std::string_view constexpr LEVEL_SALT("xI25fpAapCQg");

	///*
	//	Comment salt
	//	Used when generating comment checks in requests
	//*/
	//static std::string_view constexpr COMMENT_SALT("xPT6iUrtws0J");

	///*
	//	Challenges salt
	//	Used when generating challenges checks in requests
	//*/
	//static std::string_view constexpr CHALLENGES_SALT("");

	///*
	//	Rewards salt
	//	Used when generating rewards checks in requests
	//*/
	//static std::string_view constexpr REWARDS_SALT("");

	///*
	//	Like salt
	//	Used when generating like checks in requests
	//*/
	//static std::string_view constexpr LIKE_SALT("ysg6pUrtjn0J");

	///*
	//	Rate salt
	//	Used when generating rate checks in requests
	//*/
	//static std::string_view constexpr RATE_SALT("ysg6pUrtjn0J");

	///*
	//	Userscore salt
	//	Used when generating userscore checks in requests
	//*/
	//static std::string_view constexpr USERSCORE_SALT("xI35fsAapCRg");

	///*
	//	Levelscore salt
	//	Used when generating level leaderboard checks in requests
	//*/
	//static std::string_view constexpr LEVELSCORE_SALT("yPg6pUrtWn0J");

	/*
		RobTopCipher

		The RobTop Cipher is a cipher widely used in Geometry Dash. It's the combination
		of the base64 (url safe) algorithm and the bitwise XOR operation, where every
		char of the result string is XORed with a character of the key (array of chars).
		Note: if you dont set a key/set the key to { '\0' }, the cipher will effectively
		act as a Base64 encoder/decoder (see Base64Cipher below).
	*/
	class GDCRYPTO_API RobTopCipher
	{
	protected:
		std::vector<std::uint8_t> m_Key;
	public:
		RobTopCipher(std::vector<std::uint8_t> const& key)
			: m_Key(key) {}

		std::string encode(std::vector<std::uint8_t> const& buffer) const;
		std::string encode(std::string const& s) const;
		std::string encode(std::istream& in) const;

		std::vector<std::uint8_t> decode(std::vector<std::uint8_t> const& buffer) const;
		std::vector<std::uint8_t> decode(std::string const& s) const;
		std::vector<std::uint8_t> decode(std::istream& in) const;
	};

	//class Base64Cipher
	//	: public RobTopCipher
	//{
	//public:
	//	Base64Cipher()
	//		: RobTopCipher(gdcrypto::vecFromArray(keys::NULL_KEY)) {}
	//};

	/*
		DataCipher

		This class is used to encode/decode data, like savegames or level strings.
		The algorithm used is either:
		1) Deflate + base64 (url safe) for encoding, base64 + inflate for decoding;
		2) AES-256 ECB mode with a fixed key.
		A XOR operation can be applied after the algorithm.
	*/
	class GDCRYPTO_API DataCipher
	{
	protected:
		bool m_AES;
		std::vector<std::uint8_t> m_Key;
	public:
		DataCipher(
			bool aes = false,
			std::vector<std::uint8_t> const& key = {})
			: m_AES(aes),
			m_Key(key) {}
		DataCipher(
			std::vector<std::uint8_t> const& key)
			: m_AES(false),
			m_Key(key) {}

		std::string encode(std::vector<std::uint8_t> const& buffer) const;
		std::string encode(std::string const& s) const;
		std::string encode(std::istream& in) const;

		std::vector<std::uint8_t> decode(std::vector<std::uint8_t> const& buffer) const;
		std::vector<std::uint8_t> decode(std::string const& s) const;
		std::vector<std::uint8_t> decode(std::istream& in) const;
	};

	class LevelDataCipher
		: public DataCipher
	{
	public:
		LevelDataCipher()
			: DataCipher(false, {}) {}
	};

	//class SavegameCipher
	//	: public DataCipher
	//{
	//public:
	//	SavegameCipher()
	//		: DataCipher(false, gdcrypto::vecFromArray(keys::SAVEGAME_KEY)) {}
	//};

	//class IOSSavegameCipher
	//	: public DataCipher
	//{
	//public:
	//	IOSSavegameCipher()
	//		: DataCipher(true, gdcrypto::vecFromArray(keys::NULL_KEY)) {}
	//};

	/*
		CheckGenerator

		Checks (chk, sometimes seed2) are encoded strings that contains data
		used by the server to validate requests. Every check is encoded in this way:
		Raw data -> SHA1 string -> RobTop Cipher (every check has a different key).
		The raw data is a combination of various values and a salt, which
		also differs between checks.
	*/
	class CheckGenerator
	{
		std::vector<std::uint8_t> m_Buffer;
		std::vector<std::uint8_t> m_Key;
		std::string m_Salt;
		std::vector<std::uint8_t> m_Last;
	public:
		CheckGenerator(
			std::vector<std::uint8_t> const& key,
			std::string const& salt)
			: m_Key(key),
			m_Salt(salt) {}

		void insert(std::vector<std::uint8_t> const& buffer);
		void insert(std::string const& s);
		void insert(std::istream& in);

		void digest(std::vector<std::uint8_t>& buffer);
		void digest(std::string& s);
		void digest(std::ostream& out);

		std::string generate(std::vector<std::vector<std::uint8_t>> const& buffers);
		std::string generate(std::vector<std::string> const& buffers);

		std::string digestAsString()
		{
			std::string s;
			this->digest(s);
			return s;
		}
	};

	CheckGenerator& operator<<(CheckGenerator& g, std::vector<std::uint8_t> const& buffer);
	CheckGenerator& operator<<(CheckGenerator& g, std::string const& s);
	CheckGenerator& operator<<(CheckGenerator& g, std::istream& in);
	CheckGenerator& operator>>(CheckGenerator& g, std::vector<std::uint8_t>& buffer);
	CheckGenerator& operator>>(CheckGenerator& g, std::string& s);
	CheckGenerator& operator>>(CheckGenerator& g, std::ostream& in);
}

#endif /* _GDCRYPTO_HPP */
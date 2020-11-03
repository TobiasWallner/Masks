#pragma once

/*

	This is a header that provides useful templated  masks and patterns for integral types

	Implemented: 
	* Mask everything						all_v			1 ... 1
	* Mask none								none_v			0 ... 0
	* Mask the msb							msb_v			1 0 ... 0
	* Mask everything but the msb			but_msb_v		0 1 ... 1
	* Mask the lsb							lsb_v			0 ... 0 1
	* Mask everything but the lsb			but_lsb_v		1 ... 1 0
	* Mask bit								bit				0 ... 0 1 0 ... 0
														 bit n ~~~~~^ 

	* Mask everything but bit				bit				1 ... 1 0 1 ... 1
														 bit n ~~~~~^

	* Mask everything from lsb up to n		up_to_v			0 ... 0 1 ... 1
												         bit n ~~~~~^ 

	* Mask everything from msb down to n	down_to_v		1 ... 1 0 ... 0
												       bit n ~~~~~^ 

	* Mask everything from n1 to n2			from_to_v		0 ... 0 1 ... 1 0 ... 0
											            bit n2 ~~~~~^     ^~~~~~ bit n1

	* Mask everything but from_to			but_from_to_v	1 ... 1 0 ... 0 1 ... 1
											            bit n2 ~~~~~^     ^~~~~~ bit n1
*/

#include <type_traits>

/* Masks */
namespace mask {

	namespace detail {
		template<typename T>
		T constexpr make_up_to(unsigned long bit) {
			T value = 1;
			for (unsigned long i = 0; i < bit; ++i) {
				value |= value << 1;
			}
			return value;
		}

		template<typename T>
		T constexpr make_down_to(unsigned long bit) {
			T value = static_cast<T>(1) << (sizeof(T) * 8 - 1); //msb
			unsigned long count = (sizeof(T) * 8 - 1) - bit;
			for (unsigned long i = 0; i < count; ++i) {
				value |= value >> 1;
			}
			return value;
		}

		template<typename T>
		T constexpr make_from_to(unsigned long n1, unsigned long n2) {
			return make_up_to<T>(n2) & make_down_to<T>(n1);
		}
	}

	//mask everything
	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct all {
		static constexpr T value = static_cast<T>(~0);
	};

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T all_v = all<T>::value;

	//Mask none
	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct none {
		static constexpr T value = 0;
	};

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T none_v = none<T>::value;

	//Mask the most significant bit
	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct msb {
		static constexpr T value = static_cast<T>(1) << (sizeof(T) * 8 - 1);
	};

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T msb_v = msb<T>::value;

	//Mask everything but the most significant bit
	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct but_msb {
		static constexpr T value = msb_v<T> ^ ((T)-1);
	};

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T but_msb_v = but_msb<T>::value;

	//Mask the lsb

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct lsb {
		static constexpr T value = 1;
	};

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T lsb_v = lsb<T>::value;

	//Mask everything but the lsb

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct but_lsb {
		static constexpr T value = 1 ^ ((T)-1);
	};

	template<typename T, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T but_lsb_v = but_lsb<T>::value;

	//Mask Bit

	template<typename T, unsigned long n, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct bit {
		static_assert(n < sizeof(T) * 8, "Error in mask::bit<typename T, unsigned long n> n has to satisfy: n < sizeof(T) * 8");
		static constexpr T value = static_cast<T>(1) << n;
	};

	template<typename T, unsigned long n, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T bit_v = bit<T, n>::value;

	//everything but Mask Bit

	template<typename T, unsigned long n, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct but_bit {
		static_assert(n < sizeof(T) * 8, "Error in mask::bit<typename T, unsigned long n> n has to satisfy: n < sizeof(T) * 8");
		static constexpr T value = ~(static_cast<T>(1) << n);
	};

	template<typename T, unsigned long n, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T but_bit_v = but_bit<T, n>::value;

	//mask everything from bit 0 up to the given bit

	template<typename T, unsigned long bit, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct up_to {
		static_assert(bit < sizeof(T) * 8, "Error in mask::down_to<typename T, unsigned long bit> bit has to satisfy:  bit < sizeof(T) * 8 ");
		static constexpr T value = detail::make_up_to<T>(bit);
	};

	template<typename T, unsigned long bit, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T up_to_v = up_to<T,bit>::value;

	//mask everything from msb down to the given bit

	template<typename T, unsigned long bit, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct down_to {
		static_assert(bit < sizeof(T) * 8,"Error in mask::down_to<typename T, unsigned long bit> bit has to satisfy:  bit < sizeof(T) * 8 ");
		static constexpr T value = detail::make_down_to<T>(bit);
	};

	template<typename T, unsigned long bit, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T down_to_v = down_to<T, bit>::value;

	//mask everything from n1 to n2

	template<typename T, unsigned long n1, unsigned long n2, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	struct from_to {
		static_assert(n1 < n2, "Error in mask::from_to<typename T, unsigned long n1, unsigned long n2> n1 has to be smaller than n2");
		static_assert(n2 < sizeof(T) * 8, "Error in mask::from_to<typename T, unsigned long n1, unsigned long n2> n2 has to satisfy:  n2 < sizeof(T) * 8 ");
		static constexpr T value = detail::make_from_to<T>(n1,n2);
	};

	template<typename T, unsigned long n1, unsigned long n2, std::enable_if_t<std::is_integral<T>::value, int> = 0>
	static constexpr T make_from_v = from_to<T, n1, n2>::value;
	
}
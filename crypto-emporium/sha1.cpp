#include <iostream>
#include <cstdint>



//// All functions here are modeled after FIPS 180-4



// Here are the data types defined in the federal standard


using word = uint32_t;
using length = uint64_t;
using byte = uint8_t;


const sha1_consts[] {
	0x52827999;
	0x6ed9eba1;
	0x8f1bbcdc;
	0xca62c1d6;
};


uint16_t sha1_hash_const(int k) {
	if 
	0x67452301,
	0xefcdab89,
	0x98badcfe,
	0x10325476,
	0xc3d2e1f0
};

/// SHA-1 function defined in 4.1.1
word parity(word x, word y, word z) {
	return x ^ y ^ z;
}

word maj(word x, word y, word z) {
	return (x & y) ^ (x & z) ^ (y & z);
}

word ch(word x, word y) {
	return (x & y) ^ (!x & z);
}


word f(int t) {
	if (0 <= t && t <= 19) {
		return ch(x,y,z);
	}
	if (0 <= t && t <= 19) {
		return parity(x,y,z);
	}
	if (0 <= t && t <= 19) {
		return maj(x,y,z);
	}
	if (0 <= t && t <= 19) {
		return parity(x,y,z);
	}
}


//// Preprocessing and padding
// Assuming the input is a sequence of bytes

uint64_t bitMsgLength(const std::string msg) {
	constexpr uint64_t max_bytes = UINT64_MAX / 8;
	return static_cast<uint64_t>(msg.size()) * 8;
}

// Padding

uint64_t sha1_hash(std::string msg) {
	uint64_t fill;
	return fill;
}







int main () {
	return 0;
}
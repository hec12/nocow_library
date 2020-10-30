// Description: 乱数生成 XorShift
// TimeComplexity: $\mathcal{O}(1)$
// Verifyed: NNERC15 J

struct Xorshift {
	uint32_t x = 4;
	uint32_t next() {
		x = x ^ (x << 13);
		x = x ^ (x >> 17);
		x = x ^ (x << 15);
		return x;
	}
};

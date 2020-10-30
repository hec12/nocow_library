int mobius[limit];
int prime[limit];

void init() {
	rep(i, limit) prime[i] = i;

	for (ll i = 2; i * i < limit; ++i) {
		if (prime[i] == i) {
			for (ll j = i * i; j < limit; j += i) {
				prime[j] = i;
			}
		}
	}

	mobius[1] = 1;
	for (ll i = 2; i < limit; ++i) {
		if (i == prime[i])
			mobius[i] = -1;
		else
			mobius[i] = -1 * mobius[i / prime[i]];
	}

	for (ll i = 2; i * i < limit; ++i) {
		if (i == prime[i]) {
			for (ll j = i * i; j < limit; j += i * i) {
				mobius[j] = 0;
			}
		}
	}
}

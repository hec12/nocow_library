// Fast Zeta Transfrom
// $g(S)=\sum_{S \subseteq T}{f(T)} $
rep(i, n) rep(j, 1 << n) if (!(j & (1 << i))) f[j] += f[j | (1 << i)];
// Fast Mobius Transfrom
// $g(S)=\sum_{T \subseteq S}{ -1^{|S|-|T|} f(T)}$
rep(i, n) rep(j, 1 << n) if (j & (1 << i)) f[j] -= f[j ^ (1 << i)];

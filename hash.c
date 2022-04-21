#include <stdio.h>
#include <unistd.h>
#include <time.h>

unsigned long int primes[255];
static inline int is_prime(unsigned long int n) // n shouldn't be a factor of 2; pretty inefficient but, I'm lazy and just want to get this working
{
	unsigned long int i;
	for (i = 3; i < n/2; i += 2) {
		if ((n % i) == 0) return 1;
	};
	return 0;
}

void gen_primes()
{
	int i;
	unsigned int n;
	n = 1;
	for (i = 0; i < 255; i++, n += 2) {
		while (is_prime(n)) n += 2;
		primes[i] = n;	
	};
}

unsigned long int hash(char *k, unsigned long int salt)
{
	unsigned long int p;
	int si, i;
	char c;

	i = 0;
	while (1) {
		c = *(k + i);
		if (c == 0) break;
		p = primes[c];
		for (si = 0; si < (i + 1); si++)
			salt *= p;
		i++;
	};
	return salt;
}

int main()
{
	char buff[1000000]; // too lazy, this is just a prototype
	int r;
	unsigned long int d, salt;
	gen_primes();
	salt = (unsigned long int) clock();
	while (1) {
		r = read(0, buff, 999999);
		buff[r] = 0;
		d = hash(buff, 1);
		printf("%lu\n", (long int) d);
	}
	return 0;
}

#include <stdio.h>

int lab05(a, b)
{
	int i;
	int max = 0;

	if (a < b) {
		i = a;
		a = b;
		b = i;
	}

	while (a > b) {
		b++;
		i = 2;
		while (b % i != 0) {
			i++;
		}
		if (b == i && b > max) {
			max = b;
		}
	}

	return max;
}

int lab06(k, ticket)
{
	int A[63];
	int sum1, sum2;
	int n1, n2, n3, n4, n = 0;
	int i;

	if (k < 1000 || k > 2000) {
		return 0;
	} else {
		while (k <= 2000) {
			n1 = k / 1000;
			n2 = (k / 100) % 10;
			n3 = (k / 10) % 10;
			n4 = k % 10;

			sum1 = n1 + n2;
			sum2 = n3 + n4;

			if (sum1 == sum2) {
				A[n] = k;
				n++;
			}

			k++;
		}
	}

	if (n == 0) {
		A[ticket] = 0;
		i = 0;
	} else
		i = A[ticket];

	return i;
}

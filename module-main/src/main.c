#include <stdio.h>
#include <stdlib.h>
#include <time.h> // чтобы использовать функцию time()
#include "lib.h"

int main(int argc, char *argv[])
{
	long int t = 2000;
	int x;
	int y;
	int res1, res2, res[9999];
	char *c;

	srand((unsigned int)time(NULL));
	x = rand() % 100;
	y = rand() % (x - 1);
	lab05(x, y);

	if (argc > 1) {
		t = strtol(argv[1], &c, 10);
		if (t > 1000 && t < 9999) {
			lab06(t,0);
		}
	} else {
		lab06(t,0);
	}

	return 0;
}

#include <stdio.h> 
/* copy input to output; 2nd version */

main()
{
	int c;

	/* braces are not always needed in order to run */
	while ((c = getchar()) != EOF) 
		putchar(c);
}

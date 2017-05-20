#include <stdio.h>

int factorial( int n )
{
    int fact = 1;

    while ( n > 1) {
        fact = fact * n;
        n = n - 1;
    }
    return fact;
}

/*-------- main( ) starts here ------------------*/
int main(void)
{
    int N;
    int f;

    printf( "Enter n: " );
    scanf( " %i", &N );

    f = factorial( N );

    printf( "factorial of %i is %i\n", N, f);
    getchar();
    getchar();
    return 0;
} 

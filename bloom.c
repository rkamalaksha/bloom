#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_BYTE 8

#define SET_NTH_BIT(x, n)	( x |= ( typeof(x) )1 << n)
#define TEST_NTH_BIT(x, n)	( x &  ( typeof(x) )1 << n)

int main(int argc, char *arg[])
{
	int	*filter_base;
	int	filter_size;
	int	nth_int;
	int	nth_bit;
	int	num_items;
	int	hash_value;

	printf("Enter the number of items\n");
	scanf("%d", &num_items);

	filter_size = (num_items) / (sizeof(int) * BITS_PER_BYTE );
	printf("Size of the filter for %d items is %d bytes\n", num_items, filter_size);

	filter_base = (int *) malloc( filter_size );
	if(!filter_base) {
		printf("Could not allcoate memory\n");
		exit(1);
	}

	printf("Enter hash values, one line at a time\n");
	while( scanf("%d", &hash_value ) != EOF ) {
		if( hash_value < 0 ) {
			break;
		}
		if( hash_value > num_items ) {
			hash_value = hash_value % num_items;
			printf("Value outside range. Modulus applied to make it %d\n", hash_value);
		}
		nth_int = hash_value / sizeof(int);
		nth_bit = hash_value % sizeof(int);
		printf("Setting %d bit in %d int\n", nth_bit, nth_int);
		if(TEST_NTH_BIT( filter_base[nth_int], nth_bit ) ) {
			printf(".........%d already set\n", hash_value);
		} else {
			SET_NTH_BIT( filter_base[nth_int], nth_bit );
			printf("%d set\n", hash_value);
		}
	}

	free( filter_base );
}

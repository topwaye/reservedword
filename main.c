/*
 * main.c
 *
 * Copyright (C) 2025.9.22 TOP WAYE topwaye@hotmail.com
 * 
 * copy and replace HTML or SQL reserved words with predefined words
 * for converting command text into non-command text
 */

#include <stdio.h>

#define MAX_RESERVED_PLACE_COUNT	2
#define MAX_RESERVED_CHAR_COUNT		32
		
char reserved_words [ ] [ MAX_RESERVED_PLACE_COUNT ] [ MAX_RESERVED_CHAR_COUNT ] =
{
	{ "<HTML>" , "&#60;&#72;&#84;&#77;&#76;&#62;" },
	{ "<DIV>"  , "&#60;&#68;&#73;&#86;&#62;"      },
	{ "SELECT" , "&#83;&#69;&#76;&#69;&#67;&#84;" },
	{ "INSERT" , "&#73;&#78;&#83;&#69;&#82;&#84;" },
	{ "CREATE" , "&#67;&#82;&#69;&#65;&#84;&#69;" }
};

int reserved_word_count = sizeof ( reserved_words ) / sizeof ( reserved_words [ 0 ] );

int copy_and_replace ( char * src, int src_len, char * dst, int dst_size, int reverse = 0 )
{
	char * pos;
	int h, i, j, k;
	int a, ii;

	if ( dst_size < 1 ) /* size >= len + 1 */
		return 0;

	h = 0, i = 0; 
	while ( i < src_len )
	{		
		a = 0;
		for ( j = 0; j < reserved_word_count; j ++ )
		{
			pos = reserved_words [ j ] [ reverse ];

			k = 0; 
			while ( *( pos + k ) )
			{
				if ( ! a )
				{
					if ( *( src + i ) != *( pos + k ) )
						break;

					printf ( "%c", *( src + i ) );
					a = 1;
					ii = i ++;
				}
				else
				{
					if ( i == src_len )
					{
						a = 0;
						i = ii;
						break;
					}
					
					if ( *( src + i ) != *( pos + k ) )
					{
						printf ( "?\n" );
						a = 0;
						i = ii;
						break;
					}

					printf ( "%c", *( src + i ) );
					i ++;
				}
				
				k++;
			} /* end while */

			if ( a )
			{
				printf ( "<--OK\n" );

				pos = reserved_words [ j ] [ ! reverse ];

				k = 0;
				while ( *( pos + k ) )
				{			
					if ( h + 1 == dst_size )
						return 0;

					*( dst + h ++ ) = *( pos + k ++ );
				}

				break;
			}
		} /* end for */

		if ( a )
			continue;
		
		if ( h + 1 == dst_size )
			return 0;

		*( dst + h ++ ) = *( src + i ++ );
	}

	*( dst + h ) = 0;

	return h;
}

#define MAX_TEST_SIZE	128

int main ( )
{
	char unknown_chars_1 [ ] = "x<HTML>x<HTM>xSELECTx";
	char unknown_chars_2 [ MAX_TEST_SIZE ];
	char unknown_chars_3 [ MAX_TEST_SIZE ];

	int len = sizeof ( unknown_chars_1 ) / sizeof ( unknown_chars_1 [ 0 ] ) - 1;

	len = copy_and_replace ( unknown_chars_1, len, unknown_chars_2, MAX_TEST_SIZE );
	printf ( "%d:%s\n", len, unknown_chars_2 );

	len = copy_and_replace ( unknown_chars_2, len, unknown_chars_3, MAX_TEST_SIZE, 1 );
	printf ( "%d:%s\n", len, unknown_chars_3 );

	return 0;
}

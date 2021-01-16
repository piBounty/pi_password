#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pi_password.h"
#include "derive_key.h"

#define KEYLEN 32

int main ( int argc, char* argv[] )
{
    unsigned char key[KEYLEN];
    char pass[TOTAL_PI_PASS_LEN+1];

    struct pi_password * pp = (struct pi_password*) malloc(sizeof(struct pi_password));
    if ( init_pi_password(pp, NULL, 0) == -1) {
        free(pp);
        return -1;
    }
    if ( derive_pi_password ( pp, pass, TOTAL_PI_PASS_LEN+1 ) == -1 ){
        free(pp);
        return -1;
    }

    if ( derive_key ( "/home/pi/random.salt", pass, strlen ( pass ), key, KEYLEN ) == -1 ){
        free(pp);
        return -1;
    }

    for ( int i=0; i<KEYLEN; i++ ) {
        printf ( "%02x", key[i] );
    }
    printf ( "\n" );
    
    return 0;
}

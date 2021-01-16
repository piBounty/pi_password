#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h> // memset
#include <unistd.h> // write
#include <fcntl.h> // open

#define ROUNDS 200000
#define SALTLEN 16

int get_salt ( const char* filename, int len, unsigned char* salt )
{
    // read a file containing a random salt, or create one if it doesn't exist
    int fd, count;
    if ( access ( filename, F_OK ) == 0 ) {
        if ( ( fd = open ( filename, O_RDONLY ) ) == -1 )
            return -1;
        count = read ( fd, salt, len );
    } else {
        RAND_pseudo_bytes ( salt, len );

        if ( ( fd = open ( filename, O_CREAT|O_WRONLY, 0644 ) ) == -1 )
            return -1;
        count = write ( fd, salt, len );
    }
    close ( fd );
    return ( count == len ) ? 0 : -1;
}

int derive_key ( const char* salt_filename, const char* pass, int passlen, unsigned char* key, int keylen )
{
    unsigned char salt[SALTLEN];

    if ( get_salt ( salt_filename, SALTLEN, salt ) == -1 )
        return -1;

    PKCS5_PBKDF2_HMAC_SHA1 ( pass, passlen, salt, SALTLEN, ROUNDS, keylen, key );

    return 0;
}



#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "pi_password.h"

#define MIN_SERIAL_LEN 8
#define MAX_SERIAL_LEN 128

int populate_env_pass ( char * env_pass )
{
    const char ser_path[] = "/sys/firmware/devicetree/base/serial-number";
    char serial[MAX_SERIAL_LEN];

    int fd = open ( ser_path, O_RDONLY );
    read ( fd, serial, MAX_SERIAL_LEN );

    if ( strlen ( serial ) < MIN_SERIAL_LEN )
        return -1;

    int serial_start = 0, serial_len = strlen ( serial );

    if ( serial_len > MAX_ENV_PASS_LEN ) {
        serial_start = serial_len - MAX_ENV_PASS_LEN;
        serial_len = MAX_ENV_PASS_LEN;
    }

    memcpy ( env_pass, serial + serial_start, serial_len );
    return 0;
}

int init_pi_password ( struct pi_password * pp, const char * user_pass, unsigned int len )
{
    if ( len > MAX_USER_PASS_LEN )
        return -1;
    if ( len > 0 )
        memcpy ( pp->user_pass, user_pass, len );
    return populate_env_pass ( pp->env_pass );
}

int derive_pi_password ( const struct pi_password * pp, char* out, int len )
{
    int env_len = strlen ( pp->env_pass );
    int usr_len = strlen ( pp->user_pass );

    if ( len <= env_len+usr_len )
        return -1;

    memcpy ( out, pp->env_pass, env_len );
    memcpy ( out+env_len, pp->user_pass, usr_len );
    out[env_len+usr_len] = 0;
    return 0;
}

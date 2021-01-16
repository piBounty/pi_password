#ifndef PI_PASSWORD_H
#define PI_PASSWORD_H

#define TOTAL_PI_PASS_LEN 64
#define MAX_ENV_PASS_LEN 32
#define MAX_USER_PASS_LEN 32

struct pi_password {
    char env_pass[MAX_ENV_PASS_LEN];
    char user_pass[MAX_USER_PASS_LEN];
};

int init_pi_password ( struct pi_password* pp, const char* user_pass, unsigned int len );

int derive_pi_password ( const struct pi_password * pp, char* out, int len);

#endif

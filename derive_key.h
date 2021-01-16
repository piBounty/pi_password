#ifndef DERIVE_KEY_H
#define DERIVE_KEY_H

int derive_key ( const char* salt_filename, const char* pass, int passlen, unsigned char* key, int keylen );

#endif

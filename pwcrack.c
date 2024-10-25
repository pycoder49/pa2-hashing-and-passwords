#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <openssl/sha.h>
#include <assert.h>

// Milestone 1 part 1
uint8_t hex_to_byte(unsigned char h1, unsigned char h2){
    int answer = 0;

    if('A' <= h1 && h1 <= 'F'){
        answer += (h1 - 55) * 16;
    }
    else if ('a' <= h1 && h1 <= 'f'){
        answer += (h1 - 87) * 16;
    }
    else if('0' <= h1 && h1 <= '9'){
        answer += (h1 - 48) * 16;
    }

    if('A' <= h2 && h2 <= 'F'){
        answer += (h2 - 55);
    }
    else if ('a' <= h2 && h2 <= 'f'){
        answer += (h2 - 87);
    }
    else if ('0' <= h2 && h2 <= '9'){
        answer += (h2 - 48);
    }

    return answer;
}

// Milestone 1 part 2
void hexstr_to_hash(char hexstr[], unsigned char hash[32]){
    int hex_index = 0;
    for(int i = 1; i < strlen(hexstr); i += 2){
        hash[hex_index] = hex_to_byte((unsigned char) hexstr[i-1], (unsigned char) hexstr[i]);
        hex_index++;
    }
}

// Milestone 2
int8_t check_password(char password[], unsigned char given_hash[32]){
    unsigned char hash[32];
    SHA256(password, strlen(password), hash);

    for(int i = 0; i < 32; i++){
        if(hash[i] != given_hash[i]){
            return 0;
        }
    }
    return 1;
}

// Milestone 3
int8_t crack_password(char password[], unsigned char given_hash[]){
    if(check_password(password, given_hash)){
        return 1;
    }

    for(int i = 0; i < strlen(password); i++){
        if(!( ('a' <= password[i] && password[i] <= 'z') || ('A' <= password[i] && password[i] <= 'Z') )){
            continue;
        }

        char original_character = password[i];

        if('a' <= password[i] && password[i] <= 'z'){
            password[i] = password[i] - 32;
        }
        else if('A' <= password[i] && password[i] <= 'Z'){
            password[i] = password[i] + 32;
        }

        if(check_password(password, given_hash)){
            return 1;
        }

        password[i] = original_character;
    }
    return 0;
}

/*
 * All test functions for each function above
*/
void test_hex_to_byte() {
    assert(hex_to_byte('c', '8') == 200);
    assert(hex_to_byte('0', '3') == 3);
    assert(hex_to_byte('0', 'a') == 10);
    assert(hex_to_byte('1', '0') == 16);
}

void test_hexstr_to_hash() {
    char hexstr[64] = "a2c3b02cb22af83d6d1ead1d4e18d916599be7c2ef2f017169327df1f7c844fd";
    unsigned char hash[32];
    hexstr_to_hash(hexstr, hash);

    for(int i = 0; i < 32; i += 1) {
        printf("0x%02x", hash[i]);
    }
    printf("\n");

    assert(hash[0] == 0xa2);
    assert(hash[31] == 0xfd);
}

void test_check_password() {
    char hexstr[64] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8";
    unsigned char hash[32];
    hexstr_to_hash(hexstr, hash);

    assert(check_password("password", hash) == 1);
    assert(check_password("hellalongpassword", hash) == 0);

    printf("it worked???");
}

void test_crack_password(){
    char hexstr[64] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8";
    unsigned char hash[32];
    hexstr_to_hash(hexstr, hash);

    assert(crack_password("password", hash) == 1);
    assert(crack_password("hellalongpassword", hash) == 0);

    printf("it worked???");
}


// main function
int main(int argc, char** argv){

    if (argc < 2) {
        printf("Error: Not enough arguments provided\n");
        printf("Correct way to input: %s <hex hash>\n", argv[0]);
        return 1;
    }

    if (strlen(argv[1]) != 64) {
        printf("Error: The hash must be exactly 64 hex characters long.\n");
        return 1;
    }

    unsigned char hash[32];
    hexstr_to_hash(argv[1], hash);

    char password[128];

    // keeps asking user for input until they press CTRL+D
    while (fgets(password, sizeof(password), stdin) != NULL) {
        if (password[strlen(password) - 1] == '\n') {
            password[strlen(password) - 1] = '\0';
        }

        if (crack_password(password, hash)) {
            printf("Found password: SHA256(%s) = %s\n", password, argv[1]);
            return 0;
        }
    }
    
    // prints this out when they give up
    printf("Did not find a matching password\n");

    return 0;
}
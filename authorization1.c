#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <password>\n", argv[0]);
            exit(0);
    }

    if(check_authorization(argv[1])) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf(" Access Granted.\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    } else {
        printf("\nAccess Denied.\n");
    }
}

int check_authorization(char *password) {
    int is_authorized = 0;
    char password_buffer[16];

    strcpy(password_buffer, password);

    if(strcmp(password_buffer, "$uper$ECR3T") == 0)
        is_authorized = 1;
    if(strcmp(password_buffer, "notsosecret") == 0)
        is_authorized = 1;

    return is_authorized;
}

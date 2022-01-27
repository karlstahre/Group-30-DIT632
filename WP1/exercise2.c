#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
    int encryptionKey = atoi(argv[1]);

    char input[1000];

    fgets(input, sizeof(input), stdin);

    for (int i = 0; i < strlen(input); i++)
    {
        if (isupper(input[i]))
        {
            input[i] = ((input[i] - 65 + encryptionKey) % 26) + 65;
        }
        else if (islower(input[i]))
        {
            input[i] = ((input[i] - 97 + encryptionKey) % 26) + 97;
        }
    }
    printf("%s", input);
}
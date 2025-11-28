#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char generator[30], message[50], appended[80], remainder[30], received[80];
    int genLen, msgLen, i, j, k, t, hasError = 0;
    char c;

    // Input Generator Polynomial
    printf("Enter the generator polynomial (binary): ");
    fgets(generator, sizeof(generator), stdin);
    generator[strcspn(generator, "\n")] = '\0';  // Remove newline

    genLen = strlen(generator);
    k = genLen - 1;
    printf("Generator polynomial (CRC-CCITT): %s\n", generator);

    //   Input Message
    printf("Enter the message (binary): ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';  // Remove newline

    msgLen = strlen(message);

    //   Append zeros to message
    strcpy(appended, message);
    for (i = 0; i < k; i++)
        appended[msgLen + i] = '0';
    appended[msgLen + k] = '\0';

    printf("\nMessage polynomial appended with zeros:\n%s\n", appended);

    //   Perform Division (for checksum calculation)
    for (i = 0; i < msgLen; i++) {
        if (appended[i] == '1') {
            for (j = 0; j < genLen; j++) {
                appended[i + j] = (appended[i + j] == generator[j]) ? '0' : '1';
            }
        }
    }

    //   Extract Remainder (Checksum)
    strncpy(remainder, appended + msgLen, k);
    remainder[k] = '\0';

    printf("\nChecksum (Remainder): %s\n", remainder);

    //   Append Checksum to Original Message
    strcpy(appended, message);
    strcat(appended, remainder);

    printf("\nTransmitted message with checksum:\n%s\n", appended);

    //   Input Received Message
    printf("\nEnter the received message: ");
    fgets(received, sizeof(received), stdin);
    received[strcspn(received, "\n")] = '\0';  // Remove newline

    int recvLen = strlen(received);

    //   Perform Division on Received Message
    for (i = 0; i < recvLen - k; i++) {
        if (received[i] == '1') {
            for (j = 0; j < genLen; j++) {
                received[i + j] = (received[i + j] == generator[j]) ? '0' : '1';
            }
        }
    }

    //   Extract Remainder from Received Message
    strncpy(remainder, received + recvLen - k, k);
    remainder[k] = '\0';

    //   Check for Errors
    hasError = 0;
    for (i = 0; i < k; i++) {
        if (remainder[i] == '1') {
            hasError = 1;
            break;
        }
    }

    if (hasError)
        printf("\n Received polynomial contains an error.\n");
    else
        printf("\n Received polynomial is error-free.\n");

    return 0;
}

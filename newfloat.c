#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


//Function to convert binary string to decimal for exponent.
double binaryToDecimal(char *binary, int length) 
{
    double decimal = 0.0;
    int m = pow(2, length - 1) - 1;
    for (int i = 0; i < length; i++) 
    {
        decimal += (binary[i] - '0') * pow(2, length - i - 1);
    }

    decimal = decimal - m;
    return decimal;
}

//Function to convert binary string to decimal for mantissa.
double binaryToDecimal2(char *binary, int length) 
{
    double decimal = 0.0;
    for (int i = 0; i < length; i++) 
    {
        decimal += (binary[i] - '0') * pow(2, 0 - i - 1);
    }
    return decimal;
}

// Function to check if all characters in the exponent are '1'.
bool checkBits1(char *string, int length) 
{
    for (int i = 0; i < length; i++) 
    {
        if (string[i] != '1') 
        {
            return false;
        }
    }
    return true;
}

// Function to check if all characters in the exponent are '0'.
bool checkBits0(char *string, int length) 
{
    for (int i = 0; i < length; i++) 
    {
        if (string[i] != '0') 
        {
            return false;
        }
    }
    return true;
}

// Function to convert hexadecimal string to binary.
void hexToBinary(char *hex, char *binary) 
{
    int i, j = 0;
    for (i = 0; hex[i] != '\0'; i++) 
    {
        switch (hex[i]) 
        {
            case '0':
                strcat(binary, "0000");
                break;
            case '1':
                strcat(binary, "0001");
                break;
            case '2':
                strcat(binary, "0010");
                break;
            case '3':
                strcat(binary, "0011");
                break;
            case '4':
                strcat(binary, "0100");
                break;
            case '5':
                strcat(binary, "0101");
                break;
            case '6':
                strcat(binary, "0110");
                break;
            case '7':
                strcat(binary, "0111");
                break;
            case '8':
                strcat(binary, "1000");
                break;
            case '9':
                strcat(binary, "1001");
                break;
            case 'A':
            case 'a':
                strcat(binary, "1010");
                break;
            case 'B':
            case 'b':
                strcat(binary, "1011");
                break;
            case 'C':
            case 'c':
                strcat(binary, "1100");
                break;
            case 'D':
            case 'd':
                strcat(binary, "1101");
                break;
            case 'E':
            case 'e':
                strcat(binary, "1110");
                break;
            case 'F':
            case 'f':
                strcat(binary, "1111");
                break;
        }
    }
}


int main(int argc, char *argv[]) 
{
    int totalBits = atoi(argv[1]);
    int mantissaBits = atoi(argv[2]);
    char *operation = argv[3];

    // Validate totalBits and mantissaBits
    if (totalBits < 8 || totalBits > 64 || mantissaBits < 1 || mantissaBits >= (totalBits - 1)) 
    {
        printf("Invalid total bits or mantissa bits\n");
        return 1;
    }

    // According argv[3], including convert, minmax, and addhex, to do the operations.
    if (strcmp(operation, "convert") == 0)
    {
        char *bitstring = argv[4];
        int bitStringLength = strlen(bitstring);
        double decimalValue;
        int m;

        if (bitStringLength != totalBits) 
        {
            printf("Invalid bitstring length\n");
            return 1;
        }

        // Extract sign, exponent, and mantissa from the bitstring.
        char sign[2], exponent[64], mantissa[64];
        
        strncpy(sign, bitstring, 1);
        sign[1] = '\0';
        int signInt = atoi(sign);

        strncpy(exponent, bitstring + 1, totalBits - mantissaBits - 1);
        exponent[totalBits - mantissaBits - 1] = '\0';

        strncpy(mantissa, bitstring + totalBits - mantissaBits, mantissaBits);
        mantissa[mantissaBits] = '\0';

        if (checkBits1(exponent, totalBits - mantissaBits - 1) == true)
        {
            // If exponent is all 1 and mantissa is all 0, then it is infinite.
            // Otherwise, it is NAN.
            if (checkBits0(mantissa, mantissaBits) == true)
            {
                decimalValue = pow(-1, signInt) * INFINITY;
                printf("%lf\n", decimalValue);
            }
            else
            {
                decimalValue = pow(-1, signInt) * NAN;
                printf("%lf\n", decimalValue);
            }
        }
        else
        {
            if (checkBits0(exponent, totalBits - mantissaBits - 1) == true)
            {
                if (checkBits0(mantissa, mantissaBits) == true)
                {
                    // The case when exponent is 0 and mantissa is 0.
                    decimalValue = 0;
                    printf("%lf\n", decimalValue);
                }
                else
                {
                    // The case when exponent is 0 but mantissa is not 0.
                    decimalValue = pow(-1, signInt) * (1 + binaryToDecimal2(mantissa, mantissaBits)) * pow(2, binaryToDecimal(exponent, totalBits - mantissaBits - 1));
                    printf("%lf\n", decimalValue);
                }
            }
            else
            {
                // Normal case.
                decimalValue = pow(-1, signInt) * (1 + binaryToDecimal2(mantissa, mantissaBits)) * pow(2, binaryToDecimal(exponent, totalBits - mantissaBits - 1));
                printf("%lf\n", decimalValue);
            }
        }
    }
    else if (strcmp(operation, "minmax") == 0)
    {
        double minPositive, maxPositive;
        char exponentMin[64], mantissaMin[64], exponentMax[64], mantissaMax[64];
        int signInt2 = 0;
        int exponentBits = totalBits - mantissaBits - 1;

        // According the bits of the mantissa and exponent to set bits for min and max of positive values.
        // Set bits for max of positive values of the exponent.
        for (int i = 0; i < exponentBits; i++) 
        {
            int temp1 = exponentBits - 1;
            if (i != temp1)
            {
                exponentMax[i] = '1';
            }
            else
            {
                exponentMax[i] = '0';
            }
        }
        exponentMax[exponentBits] = '\0';

        // Set bits for min of positive values of the exponent.
        for (int i = 0; i < exponentBits; i++) 
        {
            exponentMin[i] = '0';
        }
        exponentMin[exponentBits] = '\0';

        // Set bits for max of positive values of the mantissa.
        for (int i = 0; i < mantissaBits; i++) 
        {
            mantissaMax[i] = '1';
        }
        mantissaMax[mantissaBits] = '\0';

        // Set bits for min of positive values of the mantissa.
        for (int i = 0; i < mantissaBits; i++) 
        {
            if (i != (mantissaBits - 1))
            {
                mantissaMin[i] = '0';
            }
            else
            {
                mantissaMin[i] = '1';
            }
        }
        mantissaMin[mantissaBits] = '\0';

        // Calculate the min and max positive values based on the number of bits of mantissa and exponent. 
        minPositive = (1 + binaryToDecimal2(mantissaMin, mantissaBits)) * pow(2, binaryToDecimal(exponentMin, exponentBits));
        maxPositive = (1 + binaryToDecimal2(mantissaMax, mantissaBits)) * pow(2, binaryToDecimal(exponentMax, exponentBits));
        double a = binaryToDecimal(exponentMin, exponentBits);
        printf("Min Positive: %.40lf\n", minPositive);
        printf("Max: %f\n", maxPositive);
    }
    else if (strcmp(operation, "addhex") == 0)
    {
        char binary1[256] = "", binary2[256] = "";

        // Convert the hex to binary.
        hexToBinary(argv[4], binary1);
        hexToBinary(argv[5], binary2);

        // Perform addition in decimal
        char sign1[2], exponent1[64], mantissa1[64], sign2[2], exponent2[64], mantissa2[64];

        // Split the first value into the sign, exponent and mantissa.
        strncpy(sign1, binary1, 1);
        sign1[1] = '\0';
        int signInt1 = atoi(sign1);

        strncpy(exponent1, binary1 + 1, totalBits - mantissaBits - 1);
        exponent1[totalBits - mantissaBits - 1] = '\0';

        strncpy(mantissa1, binary1 + totalBits - mantissaBits, mantissaBits);
        mantissa1[mantissaBits] = '\0';

        // Split the second value into the sign, exponent and mantissa.
        strncpy(sign2, binary2, 1);
        sign2[1] = '\0';
        int signInt2 = atoi(sign2);

        strncpy(exponent2, binary2 + 1, totalBits - mantissaBits - 1);
        exponent2[totalBits - mantissaBits - 1] = '\0';

        strncpy(mantissa2, binary2 + totalBits - mantissaBits, mantissaBits);
        mantissa2[mantissaBits] = '\0';

        double value1, value2, sum;
        // Check the first value and convert to decimal. The flow is almost similar to the part of convert.
        if (checkBits1(exponent1, totalBits - mantissaBits - 1) == true)
        {
            if (checkBits0(mantissa1, mantissaBits) == true)
            {
                value1 = pow(-1, signInt1) * INFINITY;
            }
            else
            {
                value1 = pow(-1, signInt1) * NAN;
            }
        }
        else
        {
            if (checkBits0(exponent1, totalBits - mantissaBits - 1) == true)
            {
                if (checkBits0(mantissa1, mantissaBits) == true)
                {
                    // The case when exponent is 0 and mantissa is 0.
                    value1 = 0;
                }
                else
                {
                    // The case when exponent is 0 but mantissa is not 0.
                    value1 = pow(-1, signInt1) * (1 + binaryToDecimal2(mantissa1, mantissaBits)) * pow(2, binaryToDecimal(exponent1, totalBits - mantissaBits - 1));
                }
            }
            else
            {
                value1 = pow(-1, signInt1) * (1 + binaryToDecimal2(mantissa1, mantissaBits)) * pow(2, binaryToDecimal(exponent1, totalBits - mantissaBits - 1));
            }
        }

        // Check the second value and convert to decimal. The flow is almost similar to the part of convert.
        if (checkBits1(exponent2, totalBits - mantissaBits - 1) == true)
        {
            if (checkBits0(mantissa2, mantissaBits) == true)
            {
                value2 = pow(-1, signInt2) * INFINITY;
            }
            else
            {
                value2 = pow(-1, signInt2) * NAN;
            }
        }
        else
        {
            if (checkBits0(exponent2, totalBits - mantissaBits - 1) == true)
            {
                if (checkBits0(mantissa2, mantissaBits) == true)
                {
                    // The case when exponent is 0 and mantissa is 0.
                    value2 = 0;
                }
                else
                {
                    // The case when exponent is 0 but mantissa is not 0.
                    value2 = pow(-1, signInt2) * (1 + binaryToDecimal2(mantissa2, mantissaBits)) * pow(2, binaryToDecimal(exponent2, totalBits - mantissaBits - 1));
                }
            }
            else
            {
                value2 = pow(-1, signInt2) * (1 + binaryToDecimal2(mantissa2, mantissaBits)) * pow(2, binaryToDecimal(exponent2, totalBits - mantissaBits - 1));
            }
        }

        // Calculate the special case and normal case when adding two values.
        int b[64];
        double tempInf = (-1) * INFINITY;
        if (((value1 == INFINITY) && (value2 == tempInf)) || ((value1 == tempInf) && (value2 == INFINITY)))
        {
            // The case: +inf -inf = NAN
            sum = NAN;
            int ii;
            b[0] = 0;
            for (ii = 1; ii < totalBits; ii++)
            {
                b[ii] = 1;
            }
        }
        else if ((value1 == INFINITY) || (value2 == INFINITY))
        {
            if ((value1 != tempInf) || (value2 != tempInf))
            {
                // The case:  Inf + (any value or inf) = inf 
                sum = INFINITY;
                int ii;
                b[0] = 0;
                for (ii = 1; ii < (totalBits - mantissaBits); ii++)
                {
                    b[ii] = 1;
                }
                for (ii = (totalBits - mantissaBits); ii < totalBits; ii++)
                {
                    b[ii] = 0;
                }
            }
        }
        else if ((value1 == tempInf) || (value2 == tempInf))
        {
            if ((value1 != (INFINITY)) || (value2 != (INFINITY)))
            {
                // The case: -inf + (any value or -inf) = -inf 
                sum = tempInf;
                int ii;
                for (ii = 0; ii < (totalBits - mantissaBits); ii++)
                {
                    b[ii] = 1;
                }
                for (ii = (totalBits - mantissaBits); ii < totalBits; ii++)
                {
                    b[ii] = 0;
                }
            }
        }
        else if ((value1 == NAN) || (value2 == NAN))
        {
            // The case: NAN + (any value) = NAN
            sum = NAN;
            int ii;
            b[0] = 0;
            for (ii = 1; ii < totalBits; ii++)
            {
                b[ii] = 1;
            }
        }
        else 
        {
            // Regular addition
            sum = value1 + value2;
        

            // Convert back to binary and Hex.
            int dIntegral = (int)sum;
            double fractionPart = sum - dIntegral;
            int numExponentPart = 0;

            int remainder1;
            int i = 0;
            int a[64] = {0};

            if (sum > 0)
            {
                b[0] = 0;
            }
            else
            {
                b[0] = 1;
            }
            
            // Convert the integer part of sum to binary a[].
            int expoBit = totalBits - mantissaBits - 2;
            while (dIntegral)
            {
                remainder1 = dIntegral % 2;
                dIntegral = dIntegral / 2;
                a[expoBit] = remainder1;
                expoBit--;
                i++;
            }
            numExponentPart = i - 1;
            
            // Convert the fraction part of sum to binary a[].
            while (fractionPart != 0)
            {
                fractionPart *= 2;
                if (fractionPart >= 1)
                {
                    a[i] = 1;
                    fractionPart = fractionPart - 1; 
                }
                else
                {
                    a[i] = 0;
                }
                i++;
            }

            
            int exponentBits3 = totalBits - mantissaBits - 1;
            int m3 = pow(2, exponentBits3 - 1) - 1;
            numExponentPart = numExponentPart + m3;
            int remainder2;
            int  k = 1;

            // Convert the exponent part into binary b[].
            int j = totalBits - mantissaBits - 1;
            while (numExponentPart)
            {
                remainder2 = numExponentPart % 2;
                numExponentPart = numExponentPart / 2;
                b[j] = remainder2;
                j--;
            }
            
            // Convert a[] into binary b[].
            int start = totalBits - mantissaBits;

            for(int l = 0; l < mantissaBits; l++)
            {
                b[start] = a[k];
                start++;
                k++;
            }
        }

        int count = totalBits / 4;
        int hexNumber[count];

        // Print the results.
        printf("Binary 1: %s\n", binary1);
        printf("Binary 2: %s\n", binary2);
        printf("Value 1: %f\n", value1);
        printf("Value 2: %f\n", value2);
        printf("Sum: %f\n", sum);
        printf("Binary Sum: ");
        for (int e = 0; e < totalBits; e++)
        {
            printf("%d", b[e]);
        }
        printf("\n");
        printf("Hex Sum: ");
        for (int x = 0; x < count; x++)
        {
            int y = 4 * x;
            b[y] = b[y] * 8;
            b[y + 1] = b[y + 1] * 4;
            b[y + 2] = b[y + 2] * 2;
            b[y + 3] = b[y + 3] * 1;
            hexNumber[x] = b[y] + b[y + 1] + b[y + 2] + b[y + 3];
            printf("%X", hexNumber[x]);
        }
        printf("\n");
    }
    else
    {
        printf("Invalid operation\n");
        return 1;
    }
    
    return 0;
}

This project is to implement a new standard for representing floating-point numbers. 
The program will take user-provided values representing the total number of bits in the representation and the number of bits devoted to the mantissa. 
The program can be divided into three parts: convert, minmax, and addhex. 

Convert: 
First, this part will check the length of the bit string first. After that, it will split the string into three parts: sign, exponent, and mantissa.
Second, it will check whether the value is Inf, NAN, or –Inf. If not, it would be the normal case.
Finally, according the standard of floating point number, the function, binaryToDecimal() and binaryToDecimal2() are used to convert the binary value of exponent and mantissa, and then the program will calculate the final decimal value.

Minmax:
The program will use the total number of bits and the number of bits of the mantissa to calculate the minimum and maximum of positive values.
There are 4 for-loops to assign the 0 or 1 into the char array based on the condition above.
Use the same method mentioned in Convert to calculate the positive minimum and maximum values.

Addhex:
First, hexToBinary() can convert the hex value passed by argv[4] and argv[5].
Second, two binary values are splitted into three parts: sign, exponent and mantissa.
Third, two binary numbers are converted to decimal number, and it also check whether the binary value is the special case of Inf, NAN, or –Inf. 
Forth, the program adds two values, and it will check whether the sum is special case or normal case. If it is the special case, which is Inf, NAN, or –Inf, the program assigns the binary value of sum. If it is he normal case, the program will convert the decimal value into binary value, and it split the value into the parts of sign, exponent, and mantissa. Here, we can acquire the result of binary sum. 
Finally, the program uses the binary sum to convert it into hex value.

Run:
./newfloat 12 7 convert 010010110000
./newfloat 32 23 minmax
./newfloat 8 4 addhex 45 45

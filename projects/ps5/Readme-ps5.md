# PS5: DNA Alignment

## Contact
Name: Meriem Elkoudi
Section:
Time to Complete:

Partner: Wendy Carvalho (section 202)

## Description
This project uses dynamic programming to compare two strings and find the longest common subsequence between them (aka the consecutive letters they have in common). This is called the edit distance, and the program is built around a class that has this name. This class is also able to calculate the penalty of inserting gaps, having aligned characters, and having misaligned character through the penalty() function and it does so in the optDistance() function, when calculating the optimal distance between characters. It is also able to align the strings and print out the best solution based on the edit distance and the matrix that was created. This process is very common in bioinformatics when analyzing DNA.

### Features
The assignment was done using the slides on Dynamic Programming as a basic. We decided to implement our matrix using the Needleman-Wunsch method, creating a n * m matrix based on the algorithm provided in the Dynamic Programming slides. The aligment was done also based on the slides, by tracing steps back starting from the bottom right to the top left, starting from the highest matrix index until it reaches _matrix[0][0]. Depending on the direction the traversal makes the program go, a gap, or a letter is placed for the output.  

### Testing
testPenalty() checks if the penalty() function returns the correct cost when comparing two characters, important for building the matrix as it is crucial in finding the edit distance.

testMin3() checks if min3() successfully returns the min value of the three arguments input, which is important for building the matrix again, as the distances should be optimal, and that won't happen if min3() returns the wrong minimum value.

testOptDistance() checks that in fact optDistance() returns the correct edit distance for a known case, assuring that it is doing the proper traversal through the matrix to not only calculate this edit distance, but to return this edit distance.

testAlignment() checks that alignment() correctly outputs the strings according to their optimal edit distance, with hyphens representing gaps in the appropriate locations, and the rest of the characters correctly aligned or misaligned.

Lastly, testCutEnds() checks if the matrix built by the program is missing a row, a column, or both, which would be bad for edit distance calculations and string alignment. 

### Issues
Partner (Wendy) was not able to use valgrind on her computer as valgrind does not yet support the m1 chip. I was also not able to run ecoli100000.txt, as my computer ran out of memory. When I (Meriem) attempted running the program and finding the time, memory, and distance for ecoli20000.txt, ecoli50000.txt, and ecoli100000.txt, my program was killed, therefore the data output for these was not able to be found. 

## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Input: fli8.txt
TACAGTTACC
TAAGGTCA

Expected output:
Edit distance = 6
T T 0
A A 0
C - 2
A A 0
G G 0
T G 1
T T 0
A - 2
C C 0
C A 1

Actual output:
Edit distance = 6
T T 0
A A 0
C - 2
A A 0
G G 0
T G 1
T T 0
A - 2
C C 0
C A 1

Did my program run correctly: yes

### Specs
Your Computer
Memory: (ex: 8gb, DDR4)
Processors: (ex: i5-8500 @ 3.00 GHz x6)
Operating System:

Partner's Computer
Memory: 8GB
Processors: M1 Apple Silicon @ 3.2 GHz
Operating System: mac-os-ventura

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

| data file     | distance | memory (mb) | time (seconds) | partner time |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  |   118    |     24.08   |    0.269016    |   0.290235   |
|ecoli5000.txt  |   160    |     95.77   |    1.25264     |   1.10079    |
|ecoli10000.txt |   223    |     382.2   |    4.92366     |   5.13382    |
|ecoli20000.txt |   3135   |    1.49(GB) |    17.312      |   18.5185    |
|ecoli50000.txt |   n/a    |     n/a     |     killed     |   130.871    |
|ecoli100000.txt|   n/a    |     n/a     |     killed     |     n/a      |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of your program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
 - a = 4.727 * 10^-8
 - b = 2
 - largest N = 8282721

a * N^2 = 31557600 seconds (1 day)

Based on my data, if we consider N to be the size of the string, and b to determine the size of the matrix, N^2, then b is 2. Therefore, when solving for a, the result is approximately 4.727 * 10^-8. When considering a day to have 31557600 seconds and putting this on the right side of the equation, N is found to be approximately 8282721.

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.

The variable a should be the size of an int (in bytes) since we are working with a matrix of ints and N^2 simply represents the size of the matrix if the strings are of the same length (M=N). Therefore, if my computer is limited to 8GB of RAM (1GB = 1 * 10^9 bytes, so 8GB = 8 * 10^9 bytes), then the largest N it can handle is:

 - a = 4
 - b = 2
 - largest N = 44721

4*44721^2 is 7999871364, which is less than 8 * 10^9. Any number for N above that that allows it to still be a whole number would not be possible. 

### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

## Pair Programming
We switched about 5 times. Navigating can be complicated if you don't know the direction to take the code in or what should be done next. It can also be complicated if you do know but you're not able to get the direction across. You both have to be on the same page. Navigating, therefore, is easier when you know what the code should look like.

Driving is only challenging when you're not sure of how something should look (but there's where you lean on the navigator for assistance).

## Extra Credit
The difference between min3 and std::min is that std::min takes two arguments and finds the minimum between the two of them. The custom min3() for this assignment takes three values to be compared and finds the minimum of them. It does this by performing std::min() on two of these values, and then performing std::min() once more for the returned value of the previous computation and the third value.

## Acknowledgements
Used the slides about dynamic programming for reference when writing optDistance() and alignment().

# PS1: LFSR / PhotoMagic

## Contact
Name: Wendy Carvalho

Section: 202

Time to Complete: 7h

## Description
The first part of this project implements the so-called "LFSR", which uses 3 tap positions to add a new bit (0 or 1) to the 1st position of a 16-bit seed through XORs. To add this new bit, it shifts every bit to the left once, as it cannot exceed the # of bits initially determined. The project has two primary functions, step() and generate(int k), which are defined in a class called FibLFSR (which holds this bit seed—its original value, its successive states, and size). The function step() performs these XORs once, and, therefore, shifts only one bit to the left and adds one bit at the right. The function generate(int k) does arithmetic and performs step k amount of times, moving k bits to the left and creating k new bits. The program also saves the results of these new bits added to the right–the exact new bit for step(), and the value of the bits added for generate(). This project also incorporates the Boost framework tests in order to check the efficiency of these functions.
The second part of this project can encode and decode an image by calling a transform function which calls the mentioned generate function by XORing each rgb component at each pixel of an imported image with the result of calling generate(8), which generates an 8-bit number. The program creates a texture of the image before encoding, and another texture after encoding and displays the before and after at the same time, using two small windows.

### Features
My first thought was to store the seed in an integer array because that seemed the simplest to work with, and dynamically allocating memory for it is easy to do. Looking at the project after having finished it, now I would choose to use a vector for it instead, but the program already seems to work. Since the initial seed is passed in as a string, I used the function c_str() to convert it into an array of chars (stored in bitCharacters), and then this would be stored in the int array bits. Since bitCharacters is a char array, each char had to have '0' subtracted from it to get its ASCII value so it could be stored properly as either a 0 or a 1 in the bits array. In addition to keeping the seed in this array called bits, after storing the initial seed in it, I reversed it so that the 0th element would be the 15th, and so on. This made it easier to specify which bits to XOR (the tap positions). 
For the encoding part, I based it off of the pixels.cpp file provided on Blackboard that negates an image. Through that, I realized you can iterate through each pixel of a photo (first the rows, incrementing the y, then incrementing x and restarting the y coordinate) and XOR each rgb component at that specific pixel with the generate function. The transform function takes an image and a seed, both provided by std::cin, and modifies the image. The image is then imported into a texture and saved as an output file as well, that has a name provided also by std::cin.

### Issues
Everything works as expected.

### Tests
I've added the following 5 tests to test.cpp:

1. testStringSize makes sure that the size of the seed used stored properly in a FibLFSR object is equal to the length of the original seed. 

2. testStepState checks that the 16 bits update (left shift) properly after calling step(), comparing that state stored to the expected state.

3. testOstream checks that the overloaded operator<< function outputs the FibLFSR bits properly.

4. testStepEqualsGenerate compares two FibLFSR objects, checking that the result of calling step n times on one object is equal to calling generate(n) on another object.

5. testGenerateKBits checks that after calling generate(n), the number of bits generated is in fact equal to n.

6. testTransform checks that a pixel's rgb values are not the same as after the image gets transformed.

### Extra Credit
As mentioned beforehand, the process to store the initial string seed into the int array involved having a middle step that is the char array bitCharacters. Also, each time step() is called, the new state of the seed is stored in a string called currentState. I've also added an int member seedSize to store the length of the seed (in case more than 16 bits should be used in the future). To be able to access seedSize and currentState, I've also included accessor functions for them (getState() and getSeedSize()). I also added a function to access the initial seed, getInitialSeed() for testing purposes. Of course, I also added a destructor because I dynamically allocated memory for the member arrays of FibLFSR.

## Acknowledgements
Converting a string to a char array: https://www.geeksforgeeks.org/convert-string-char-array-cpp/#
I referred to "Unit Tests.pdf" on Blackboard for the testing portion of this project and "pixels.cpp" to understand how to iterate through the pixels of an image. 
I also looked through the SFML Documentation to learn about different Image features: https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Image.php#a9fd329b8cd7d4439e07fb5d3bb2d9744



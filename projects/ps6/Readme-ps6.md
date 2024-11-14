# PS6: RandWriter

## Contact
Name: Wendy Carvalho
Section: 202
Time to Complete: 7 hours


## Description
This program is designed to generate random text using Markov chain modeling. By analyzing input text character by character, it constructs maps of k-grams and their corresponding frequencies, capturing the probability of a character appearing after a k-gram. This allows it to generate new text that closely resembles the input data. It creates the maps based on the order of the Markov model (k) and the length of the generated text (L) input via the command-line.

### Features
My major decisions including deciding to use a normal map instead of an unordered_map, only because iterations/traversals through it are faster.

I also attempted to use just std::minstd_rand0 _gen as was done in the in-class Snake activity, but this generated the same random character. After some researching, I decided to use the <chrono> library, and this generated more randomness. 

At first I was creating two maps, one for k-grams, and another for k+1-grams with each of their frequencies, but after I referenced the pdf given about how to loop through a map and decided doing a map of maps would be much easier specifically for the k+1-grams. With this, when creating the k-grams map, I could also update the frequency of when a character after the k-gram was found and create the k+1-grams map that way.

Another major decision was the lambda function before it became a lambda. I wanted to use the random number generated and count through the k+1-grams map if the kgram needed was found (in the generate function). After reaching the random number generated by counting through the frequency, the program references at which character it reaches this number, and this would then be the random character.

### Testing
testOrderK tests that the correct order is stored inside the RandWriter object.
testKRand tests that the krand() function returns an appropriate random letter based on the kgram given.
testKRandNoThrow checks that the program doesn't throw an exception when the kgram is of equal length k.
testKRandThrow checks that the program does throw an exception when the kgram is not of length k.
testFreq, testFreq2, and testFreqWChar check that the maps have the correct frequencies for the k-gram map and the k+1-gram map
testGenerateLength checks that the string produced by generate() is of the length provided as an argument and no more or less.
testGenerateStart checks that the beginning of the string produced by generate() has the kgram provided.

I used the exception invalid_argument, mostly, because the errors were more commonly produced to due them being invalid for the specified parameter (such as the kgram being shorter than the previously specified order).

My code passed the tests.

### Lambda
The lambda function findRandChar(), inside generate() iterates through a map of k-grams and their associated characters and frequencies. It captures the variables cnt, randK, randChar, and kgram by reference through scope. Within the lambda, it iterates over each k-gram in the provided map, incrementing cnt by the frequency of each character encountered until cnt reaches or exceeds the target value randK. At that point, the corresponding character is assigned to randChar, and the loop exits early to avoid unnecessary iterations. Essentially, it finds the character corresponding to the desired cumulative frequency randK within the provided k-gram map.

### Issues
I had trouble understanding the whole concept of Markov Models and how to create and iterate through a map in order to produce them. The pdf file and the slides helped, but, mainly, doing some things by hand helped me code better, I realized.

I also learned that invalid_argument would be better than just runtime_error as an exception in the scenarios mentioned above, as it is more specific an accurate.

### Extra Credit
Nothing.

## Acknowledgements
Using find() with strings: https://cplusplus.com/reference/string/string/find/
Randomness: https://cplusplus.com/reference/random/uniform_int_distribution/
            https://cplusplus.com/reference/chrono/time_point/time_since_epoch/
Exceptions: https://en.cppreference.com/w/cpp/error/invalid_argument
Referenced Information Theory slides 
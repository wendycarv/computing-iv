# PS3a: Sokoban

## Contact
Name: Wendy Carvalho
Section: 202
Time to Complete: 2 days


## Description
Sokoban is a classic puzzle game where the player must strategically push boxes onto designated storage locations within a maze-like environment. 

The game begins by reading in a level file, which contains information about the layout of the game board. Each character in the level file represents a different type of tile on the game board, such as walls, ground spaces, boxes, storage locations (also referred to as targets in this write-up), and the player's starting position. Upon reading the level file, the program constructs a grid-based representation of the game board. This grid stores the positions of various elements, allowing for efficient manipulation and rendering of the game environment. This is done using a vector of vectors to store static tiles, a vector of sf::Vector2is for the box locations, and a simple sf::Vector2i for the player location. 

Using the SFML framework, the program renders the game board onto a graphical window. Textures and sprites are utilized to visually represent each type of tile, including walls, ground spaces, boxes, storage locations, and the player character. 

The player can navigate the game board pressing arrow keys or WASD,  interacting with boxes and navigating around obstacles like walls. One of the core mechanics of this game is the ability to push boxes around the board. When the player character moves into a position adjacent to a box, they can push the box in the direction of their movement, provided that there is empty space for the box to occupy. 

As the player navigates the game board and pushes boxes onto designated storage locations, the program continuously checks whether all boxes have been successfully placed onto their respective storage locations. Once all boxes are in place, the level is considered completed, and the player wins the game.

### Features
This program is able to use the command-line to open a level file by using the argument argv[1]. I set this program up so that when reading in the file content of each level it is stored into a string. I did this initially to get rid of any new line characters, since I used getline(). 

Then this string was used to create grids. The program iterates through the string and each immovable tile (wall, ground, storage location) is stored into a vector of vectors of chars called staticTiles. I did this because even though there will be boxes or a player on top of one of these tiles, they should still be in the background and stored separately. In those same iterations, if a player character or box character was read, their location was stored as a sf::Vector2i (a vector of sf::Vector2is in the case of the boxes, since there may be many). I wanted these objects of different categories to be stored separately. I made the player and the boxes into vectors because they can and will be moved throughout the gameplay, so it is easier to set up their initial positions this way. 

Also, an enum type for Directions was created to be passed in as the argument for the moveplayer() function. Using event handling inside main.cpp, the direction taken in by the keyboard (using arrow keys or WASD) is passed into movePlayer(), and this functions handles moving the player and boxes if that applies, and determines whether or not these are possible (if there are no obstacles in the way). This function updates the player's location stored inside the Sokoban class, and so when the draw function is called again inside main, draw updates the player's location visually on the window. 

Additionally, the program provides a functionality to reset the game state, allowing the player to restart the current level if they wish to try again or if they become stuck.

### Memory
As mentioned beforehand, I stored the game grid into a vector of vector of chars for the immovable tiles, a vector of sf::Vector2fs for the boxes (since they can be moved), and a simple sf::Vector2f for the player's initial position. I decided to do it this way because vectors of vectors are easier to manipulate and don't require memory allocation. They can resize dynamically without the need for manual memory allocation. 

Several textures are saved within the program for each different tile and player direction, but only 3 sprites are used to decrease the amount of memory used: one for the static tiles, one for the boxes, and one for the player.

### Lambdas
A lambda was implemented in the isWon() function. A lambda function named "isBoxAtTarget" is declared, and it takes a const sf::Vector2i& parameter named box. Inside the function, it extracts the x and y coordinates from this box and checks if the character at the position staticTiles[y][x] is equal to 'a', indicating that a box is at a target location. The function returns true if this condition is met, and false otherwise.
It uses the std::all_of algorithm to check is all elements in the boxes vector satisfies this condition by taking boxes.begin(), boxes.end(), the boxes vector, and the lambda function isBoxAtTarget. It iterates over each element in the boxes vector and applies the isBoxAtTarget lambda function to check if the box meets the conditions. Therefore, if all boxes are at 'a' locations, std::all_of returns true, indicating that the game is won.
The game is also won if there are more boxes than storage locations, but the boxes storage locations are filled. Another lambda function was implemented in the same isWon() function called "isStorageFull" to account for this scenario. The lambda iterates over each tile of the game grid (staticTiles) using nested loops. It checks each tile to see if it represents a storage location (denoted by the character 'a'). Then, for each storage location found, it searches through the boxes vector to see if there is a box at that location. If a box is found at the current storage location, it continues to the next storage location. If no box is found at any storage location, the lambda returns false, indicating that at least one storage location is not filled. If all storage locations are found to be filled with boxes, the lambda returns true, indicating that all storage locations are filled.
Therefore, the function isWon() returns true if either one of these described scenarios are true. 


### Issues
The program works fully. The only trouble I had was learning how to implement a vector of vectors, which was only challenging because I made some simple mistakes in the program like putting a closing curly brace for one of my for loops in the wrong location which made the first time accessing the vector of vectors not possible. After fixing this and using the auto keyword at certain points to make sure the program was doing the correct thing, I realized it was simple. This program also forced me to learn how to use breakpoints in VSCode, which I was only familiar with in XCode.  

An issue I've noticed is that when the game is won, the victory music starts playing but it lags the window a bit and the "You win!" text takes an extra second or two to show up.

### Extra Credit
1. I added a timer on the top left corner to count the time elapsed since the SFML window has been open using the Clock and Time classes. 
2. I also made the character change its texture to face the direction it's moving in by loading a single texture in the Sokoban class whenever a move button is pressed.
3. I added a victory sound when the game is won by using the Audio feature in SFML. The source for the audio is acknowledged below. 
4. I added an undo button using the key z by adding it to the event handling I used for the reset feature. The undo button calls the undo() function which can undo the last move done by the player, and a box move if that was done. I stored the previous player positions in a vectorof pairs of a bool and a sf::Vector2i. The function just accesses the last element in this vector and assigns it to the playerPosition accessed by the draw function, which basically redraws the player in its last position. If the bool is equal to true, it means that the player pushed the box and therefore the box's position should also be reverted. I stored the previous box positions in a vector of pairs of an int and a sf::Vector2i. A vector of pairs maintains the order of insertion and allows for repeated values. The repeated values would be the indexes of the boxes being stored. So if a box is moved twice, its index will be stored twice, although with different positions. Then, by using an auto element to access the last element of the vector of pairs called previousBLoc, the index element is accessed using ".first", and this is the index of the boxes vector which is reassigned the value of ".second", which is the previous sf::Vector2i value it had. So any time undo() is called, as long as these vectors aren't empty, the positions are replaced and redrawn. 
5. The extra feature I added was music playing in the background using sf::Music, and it stops playing when the game is won, as the victory sound plays instead. 

## Acknowledgements
Text class properties: https://learnsfml.com/basics/graphics/how-to-center-text/
Reference for using push_back() on 2d vector: https://cplusplus.com/forum/beginner/203568/
Traversing through a 2d vector: https://stackoverflow.com/questions/1784573/iterator-for-2d-vector
Clock class reference: https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Clock.php#a123e2627f2943e5ecaa1db0c7df3231b
Centering text: https://learnsfml.com/basics/graphics/how-to-center-text/#example-code
std::pair reference: https://stackoverflow.com/questions/7897050/adding-to-a-vector-of-pair
Playing sound/music: https://www.sfml-dev.org/tutorials/2.6/audio-sounds.php
Debugging sound: https://en.sfml-dev.org/forums/index.php?topic=20611.0
Victory music: https://pixabay.com/sound-effects/level-win-6416/
Background music: https://pixabay.com/sound-effects/8bit-music-for-game-68698/
Arial font copied from my computer font book, included in the submission
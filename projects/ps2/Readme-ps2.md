# PS2: Pythagorean Tree

## Contact
Name: Wendy Carvalho and Meriem Elkoudi
Section: 202
Time to Complete: 8 hours

## Description
This project uses the SFML library to create a Pythagoras tree (also known as a type of fractal), using shapes and their transformations to do so through recursive functions. 

### Features
To acheive the Pythagoras tree, we used RectangleShapes. Initially, we tried using ConvexShapes but realized they were more complicated than needed be. With RectangleShape, we essentially passed in the "parent" square through a function called PTreeHelper, which "copied" the parent into a new RectangleShape, resized it, and accumulated its transformations (rotations and positions along the x and y axes). The getTransformation().transofrmationPoint() functions were essential for this and made it easier to "locate" where the parent square was on the grid, using the top left vertex for the the children on the left side, and the top right vertex for the children on the right side. Each time the recursive function was called, the square would get rotated again by 45º.

To resize the window, not only did we multiply the length entered by a constant for the width and height of the window, but if the length entered was greater than 200, it is also scaled a bit down to account for the fact that the window may eventually not fit one's computer screen.

### Issues
This project was very tiresome if only because it took a lot of research to figure out that the transformPoint() function would be a lifesaver to start the new child from where the parent was and  simply make it smaller and rotate it, rather than moving the child a little more on the x and y axes, which although worked in the beginning, we ended up realizing would not work forever the larger the depth got, as the tree starts to rotate inward instead of outward.  Also, figuring out how setOrigin() can affect an object was also crucial in order to make sure the squares would rotate and be positioned as we expected. 

Also, we initially thought that for the lefthand children it would be appropriate to rotate by 45º, but this proved to be wrong and had to be the opposite, -45º, and vice versa. 

Through this project, we also learned about color operations through the extra credit portion mentioned below. 

The program does not seem to have any issues, although the resizing of the screen may look different depending on the computer.

### Extra Credit
The only extra thing we did was adding a color gradient to the tree. The pTree() function initializes the first parent square to a brown color. Then, each time the recursive function gets called, the child squares' colors have color components added to them (+20 for the green component, and +6 for the blue component). This way, the tree does indeed look like a tree. 

### Changes
I did the second extra credit which uses different angles rather than just the default 45˚ to compose the PTree by using cossine for the left children and sine for the right children, rather than using the same value for both. This way, the children are different sizes depending on what side they originate from. I also changed the color manipulation, just because. 

I also altered the window resizing to accomodate these changes.

## Acknowledgements
Color manipulation:
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Color.php
https://learnsfml.com/basics/graphics/how-to-use-colors-in-sfml/
https://oprypin.github.io/crsfml/api/SF/Color.html
How to format color hexadecimals: 
https://en.sfml-dev.org/forums/index.php?topic=19009.0 
Moving objects relative to another object:
https://en.sfml-dev.org/forums/index.php?topic=27412.0
https://en.sfml-dev.org/forums/index.php?topic=15973.0
RectangleShape Class Reference:
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1RectangleShape.php
sf::Vector2f Class Reference:
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Vector2.php


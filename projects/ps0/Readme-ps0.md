# PS0: Hello SFML

## Contact
Name: Wendy Carvalho

Section: 202

Time to Complete: 2 hours


## Description
This project is an introduction to SFML. It's a prototype of a mini game that features an alien in a UFO that can shoot lasers. It responds to ADSW keys (left, right, down, up) to move around and the left mouse click to shoot said laser beams. 

### Features
I decided to make it a mini game since that is what came to mind when thinking about what to do with keystrokes. I wanted to make the initial sprite (alien) move by simply bobbing it up and down through updating it's y position, since any other movement I wanted to make possible via the user's keystrokes. I also wanted the sprite (alien) to flip horizontally whenever the left or right key were pressed so that it [the sprite] would face that direction. I did this by updating it's scale to 1 or -1 each time it happened (if the sprite was not already facing that direction). 
I also decided to make it a little more interactive by adding laser beams, as normal games would usually have an "attack" feature. At first I had it so it was only one sprite of a laser beam that I would use the same scale mechanism to flip it depending on the direction the alien is facing, but I found that this made it so sometimes the laser beam would change directions on screen. So, instead, I used two sprites for the laser beams, one facing each direction, and the program "draws" each of them independently.

### Issues
There are two problems I've encountered: when A or D are pressed, left or right, respectively, the sprite "jumps" a bit away from its initial x position, which is shouldn't do. I tried to set up it's new position after the keystroke is pressed so that it would be drawn in the same area before it was flipped, but that did not seem to work. The other problem is that the laser beams don't always show up on screen after pressing left click. There can be a sort of delay and I think it may have to do with the frames. They also don't show up if you don't move the alien using the keystrokes right after loading the program. Lastly, if you change direction too quickly in the beginning of the program and shoot lasers, you might see one flying at the top of the window instead of out of the UFO. 

### Extra Feature
The extra feature I added was making the program respond to the left mouse click. This makes the previously mentioned laser beams show up. They consist of two separate sprites: a laser beam facing left or right. They are drawn according to when the left mouse click is pressed and the direction the alien sprite is facing.

## Integrity
Read the University policy Academic Integrity, and answer the following question:

There are six examples of academic misconduct, labeled (a) through (f). Other than (a), "Seeks to claim credit for the work or efforts of another without authorization or citation," which of these do you think would most apply to this class, and why? Write approx. 100-200 words. Note: there is no single correct answer to this. I am looking for your opinion.

I think that example six, "Submits own work or consults the work of others through on-line sources, phones, or other technology without instructor permission" also applies to this class. There is a difference between consulting someone without looking at their code directly (simply discussing how to solve a problem, asking questions), and blatantly searching up a problem online and copying and pasting the code into an assignment for a class. The former is okay, but the latter is misconduct. Also, there is no learning involved through taking someone else's work. Additionally, submitting your own work for a class online gives other people the opportunity to use it for misconduct (submitting it as their own work). Posting work online such as through GitHub should be of work non-related to classes, and if it is, it should be kept private. 

## Acknowledgements
All the assistance I got was through sfml-dev.org and one stack exchange website for game development:

Class List: https://www.sfml-dev.org/documentation/2.4.2/annotated.php
Transformable Class: https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Transformable.php#a73f9739bc6e74db2cea154bc8e94ec46
Keyboard Class: https://www.sfml-dev.org/documentation/2.4.2/classsf_1_1Keyboard.php#acb4cacd7cc5802dec45724cf3314a142a9d06fa7ac9af597034ea724fb08b991e
Moving sprites using the keyboard with move function: https://en.sfml-dev.org/forums/index.php?topic=20971.0
Flipping sprites: https://gamedev.stackexchange.com/questions/169759/how-can-i-flip-a-sprite-in-sfml


### Credits
Alien: https://i.pinimg.com/originals/68/81/49/688149f4135010e22c67004d39d0cbb1.png
Laser beam: https://antelope.beauty/pixel-art-laser

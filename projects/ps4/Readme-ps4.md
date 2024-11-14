# PS4: N-Body Simulation

## Contact
Name: Wendy Carvalho
Section: 202
Time to Complete: 8 hours (total)


## Description
This project so far creates a number of celestial body objects specified by a file that is read in by redirect input and a single universe that holds these celestial bodies. It stores their positions, velocities, masses, and displays their image from a file. 

In the second part of this project, these celestial bodies are also animated, showing, for example, the rotation each planet does around the sun given a certain amount of seconds until it reaches a larger amount of time, both given by the command line. This is done by, essentially, calculating the net force that each particle has on each other to then calculate each of their new positions and velocities.

This project works fully, to my knowledge.

### Features
For part A of this assignment, I decided to use shared_ptrs stored inside a vector to manage the Celestial Bodys of a Universe, as the professor advised this would be a good thing to do and I was trying to figure out a smart way to create these Celestial Bodys since the amount needed is not known until the program is done reading the file that has lines dedicated to each one. 

I also calculated the net force for each object inside a function called step() implemented in part b, which defines the new positions and velocities for each particle as their forces are affected by one another. After calculating each net force, the positions and velocities are calculated and changed.

There is a timer in the upper left corner that shows the time elapsed throughout the life of the program, which is calculated using the given ∆t until it reaches the value T. The program, at the end, outputs the final state of the system (number of particles, radius, positions, velocities, and masses for each particle). 

### Memory
I used smart pointers (std::shared_ptr) to store Celestial Bodys since many of them need to be created from reading a file but it is not known necessarily how many celestial bodies are in a file and how many need to be created. Nor is it known who has ownership of these celestial bodies at every given moment. This was the best way to store them, and they were placed inside a vector that is a member variable of Universe. This way, each time a shared_ptr of a Celestial Body was created, it was pushed back onto this vector for later access.

### Issues
I had trouble initially figuring out how to use smart pointers, but the cppstories link in the acknowledgements helped figure out how to manage Celestial Body objects. I also had some trouble figuring out the "formatting" and "flipping" tests.

For part b, I had trouble only with carefully considering each part that needed to be calculated and stored to make the particles move and had to be implemented after each net force was calculated. I also had trouble figuring out what the boost test cases wanted.

### Extra Credit
I added music by using sf::Music. I also displayed the time elapsed on the screen with units (seconds) in the upper left corner, which is incremented by dt until it reaches the totalTime input by the command line.

Lastly, I created my own universe file called blackhole.txt. I initially wanted to create a universe file inspired by the book (and now TV show) called 3-Body Problem (when it really should be called 4-Body Problem). What is now the black hole used to be a planet (although technically the exoplanet should be moving also, I decided I quite liked this version instead, with a stable particle in the middle instead). It was difficult to figure out how to manipulate the values properly to get the system I wanted–although this is probably expected of an N-Body System where is N is greater than 2. Decreasing the speed made the orbit decay faster. Without any speed at all, the particles pull right into each other. A high speed meant they would escape the orbit quickly. I made the mass of the exoplanet be much higher than that of the stars so it wouldn't be affected by the stars and thus stay in place, but the stars would be pulled by its gravity (much like our own solar system). By playing around with the speed of the stars, purposely making one's y velocity smaller than the other (but not 0), it makes it so that each star takes turns looping around the planet. This output then reminded be of the behavior of a blackhole, something with a big mass just pushing things around. So I put a blackhole.gif in the middle instead. 

## Acknowledgements
Shared_ptr explanation: https://www.cppstories.com/2014/05/vector-of-objects-vs-vector-of-pointers/
sf::View class reference: https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1View.php#aa2006fa4269078be4fd5ca999dcb6244
viewport behavior: https://en.sfml-dev.org/forums/index.php?topic=9778.0
viewport visual explanation / tutorial by SFML developer: https://github.com/SFML/SFML/wiki/Tutorial%3A-Using-View
Background image: https://www.spacespheremaps.com/wp-content/uploads/2D_pixelart_starfield_detail_image.png
Music: "https://pixabay.com/users/penguinmusic-24940186/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=14194", Oleksandr Stepanovfrom Pixabay
Font for time shown on screen: https://fonts.google.com/specimen/Roboto
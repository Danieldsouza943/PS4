# PS4: Sokoban Game
## Contact
Name: Daniel Dsouza
Section: 201
Time to Complete: almost 10-11 hours

## Description
This project implements a tile-based Sokoban game where the player pushes boxes into designated storage locations. This program is a full game with added gameplay mechanics like player movement, box pushing, detecting win conditions, and the ability to reset the game or replay the level.

### Features
For this assignment, I chose not to use dynamically allocated assets, as they didn’t seem necessary given the project scope. Instead, I organized the textures in a map for easy access, and used a vector of vectors to store the level layout. I designed a custom structure, Grid, to maintain the game state, making it more modular and manageable. Additionally, I stored the textures in a static member variable, allowing them to be shared across multiple instances of the class. This setup would enable drawing multiple levels simultaneously if needed.

### Memory
I chose to store the level as a 2D vector of characters, using each character to represent a specific tile. Textures were organized in a map, with each character mapped directly to its corresponding texture, allowing quick access to textures based on the character index. To manage the game state, I created a Grid struct that maintains the positions of all tiles that need to be drawn, each stored in separate vectors. Within the class, I used a stack of Grid instances to track the game state, making it straightforward to implement undo and reset functions. I decided not to use smart pointers, as they were not necessary for completing this assignment.

### Lambdas
I used lambdas in conjunction with algorithm library functions in the Draw function to draw the different sprites in the correct locations.

### Issues
I encountered issues with handling box movement, especially ensuring that the player could push only one box at a time and that boxes moved only when there was an open space behind them, but i resolved it. I had some issues at the beginning but managed to fix them all before the submission deadline. Currently trying to implement the victory sign display and a winning buzzer sound for when the player wins the game.

### Extra Credit
I successfully added a timer that is displayed on the top of the window as it records the time passed since the game started in MM:SS format. Added an undo feature as well that will undo a move every time you press 'U' unless it is the first move. The player changes direction while moving.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Professor Daly's Discord channel, Youtube.com (The Cherno).

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
Arial.ttf from Windows 10 font library: https://docs.microsoft.com/en-us/typography/font-list/arial

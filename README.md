# Filler
42 school algorithm project.

##### Score 123/100

The goal of this project is to create a filler player. Filler is a two player game that consist of placing randomly created pieces on the gameboard with specific rules: 1. The piece must fit within the grid. 2. Exactly one square of the piece must overlap with the players on squares. 3. The piece may not be stacked on top of the enemy. 4. The game ends when a player is unable to place a piece on the board.

In essence filler is a game where you attempt to conquer as much territory as possible and make sure you always have available positions where to place the next piece. This makes it quite an interesting algorithm challenge since the you can approach it in so many different ways. Perhaps your algorithm attempts to seal off half of the map and survive until the bitter end, perhaps you try to box your opponent in so they can't place any more pieces or maybe you try to breach into your opponents area and take over the space they were saving for late game.

### Features
- Pretty good filler player (currently undefeated within Hive-Helsinki)
- Implementation of heat map
- Command line visualizer

### The game
![game](/images/filler.jpg)

Seen in the image above is a game underway. Each '.' represents an empty square, 'O' is marker for player 1 and 'X' is marker for player two. To play the game, at least one player is required and the game master ruby executable (filler_vm.rb(2)). The game master supplies the player(s) with random pieces and updates the game board after each piece is placed, it also keeps track if a player fails to place a piece or places it in illegal position. This repository has both the new (vm2) and old (vm) game masters, it is recommended to use the old one (filler_vm.rb) since the new one does not work well with the champions provided. Some of the champions refuse to place any pieces with the new executable and it also stops the game before the winning player can attempt to fill out the remaining field. The following format is used to run the ruby executable:

##### filler_vm.rb -f mapfile -p1 player1 -p2 player2
If one wishes to use the visualizer, makefile can be run with "make visu" and the game output can be piped to visu.exe. Example:

##### filler_vm.rb -f maps/map01 -p1 jmakela.filler -p2 players/superjeannot.filler | visu.exe
This way one can view very basic visualization (the image above). Visu.exe also supports -h option to visualize the heat map (the image below) and -s option to record the game to "visu.txt".

### The algorithm
![heat](/images/heatmap.jpg)

I decided to use aggressive approach when designing my player. I calculate values for each square in the field in the following way: green is the cheapest, next cheapest is yellow, then red and finally purple. The closer the piece is to the enemy player, the cheaper it is and since we will always attempt to place piece to the cheapest available position, it guarantees we keep moving towards the enemy and once we reach the enemy territory, we start to circle around the enemy and box them in. Afterwards we attempt to fill out the board as optimally as possible.

In the above image, our player and territory is white and enemy is black. You can see that the green (cheapest) area is circling the enemy player, with one layer of yellow right next to the enemy territory. Around the green territory, there is yellow (more costly) and finally around the edges behind our player is red (very costly).

The heat map is designed to create one layer of slightly more expensive squares right next to the enemy. The reason for this is that in my testing, I found out that since the pieces are random, it is more beneficial to keep away from the enemy. First of all leaving the space empty allows the enemy player to waste a piece by placing it against us, instead of circling around us, secondly, if you are unlucky with the pieces, it is possible that the enemy gets a piece that can "hook around" your piece and box you in, even if only momentarily, having this happen can be disasterous since it decreases the available positions where you could put your own piece and allows the enemy to keep encircling you. Leaving the one layer free decreases the chances of this happening.

### Note
The filler players are designed to work with schools MacOS and it is possible that they do not work well in windows/linux environments.

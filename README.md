Hearts C++ card game:

Fun card game that a user can play against 3 computers. Good luck!

To play:
1. Run 'HeartsGame.exe' directly in Windows command prompt. Or in a C++ compatible IDE like VSCode run './HeartsGame.exe'.
2. If step 1 doesn't work. Make sure all of the included files are in the same folder location. Run 'g++ main.cpp CardClass.cpp PlayerClass.cpp -o your_file_name' in a C++ compatible IDE. Then './your_file_name'. 
3. You will be the user.
4. Each player is dealt 13 cards.
5. Player with 2 of CLUBS begins game.
6. Every round has a leading suit which is determined by the first play of that round. Every player after the first player has to play a card with that same suit unless they don't have a card matching the leading suit.
7. The player who plays the highest value card that matches the leading suit that round takes all the cards and sums their points up. That player will also start the next round.
8. Game lasts 13 rounds with each player playing 1 card each every round.
9. At the end of the game the player with the least amount of points is the winner.

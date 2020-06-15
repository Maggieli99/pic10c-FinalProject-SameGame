# Pic 10c FinalProject: The Same Game

## Idea & Introduction

<img width="400" alt="Screen Shot 2020-06-14 at 19 40 32" src="https://user-images.githubusercontent.com/63526495/84612947-ee8fd900-ae76-11ea-8908-b8caed6d1c27.png">
<img width="400" alt="Screen Shot 2020-06-14 at 19 32 18" src="https://user-images.githubusercontent.com/63526495/84612534-c3f15080-ae75-11ea-865e-71eaa4d5f4ac.png">


My final project is a classical game called The Same Game. In this game, players need to find groups of two or more blocks with the same color that are next to each other vertically or horizontally. Once they find such blocks and clicks on them, the 
blocks will be removed from the game board. Then all of the blocks that are above the ones removed will fall down. If an entire column is removed, all columns to the right will shift to the left. The goal is to remove all the blocks on the play board with the least number of clicks. The game is over when all the remaining blocks that are adjacent to each other are of different colors or there are no blocks left. 

This is a classical game that I played so much on my father's phone when I was little, so I am really interested in 
constructing my own Same Game and tring to give it some simple features to make it more playable.

## Process & Struggles

The instruction(https://www.cprogramming.com/tutorial/game_programming/same_game_part1.html) I followed requires the use of
Visual Studio. Since I am a Mac user and use Xcode for almost all of my assignment, it is the first time that I coded a whole 
project with Visual Studio on a Windows system. I used Visual Studio 2019 with a template of MFC application to create the
game. 

MFC stands for Microsoft Foundation Class. It is an easy-to-use library when we want to create a simple application like this game. It will make it easy to create an application with a true Windows look and feel. 

With the help of this tutorial: https://www.youtube.com/watch?v=csgO95sbSfA, I connected Visual Studio 2019 with my Github account.

With the help of part 1 of the instruction, I created classes for the game view, game document, and game board. Document and View classes are special architectures for the MFC Application wizard. Using this two class, we seperate the actual application data from the displaying of the data to user. Document class contains all of the data. View class get the data from Document class and displays it to the user. The View class also handles the user's interaction with the game and modifies the data in the Document class accordingly. In this game, the data is mostly our game board. So I used the GameBoard class to setup the board and update the board in the process of playing.

#### Struggle: 
In my Board class there is an array COLOREF type. A COLOREF is a 32-bit unsigned integer that contains RGBA color values for MFC application. In the constructor I used the RGB macro to create COLOREF value. But when I ran the code, I got the error saying "identifier "COLOREF" not find.
#### Solution: 
Add header:  #include <wtypes.h>
https://docs.microsoft.com/en-us/windows/win32/gdi/colorref

#### Struggle:
In my View class I needed to resize my window to the correct size in the OnInitialUpdate function. Since the View class inheris a default OnInitialUpdate function. I needed to to override it. The instruction tells me to do it by opening up the Properties Window from the View class header file and selecting the "Overrides" section. But probably because I missed some parts when I set up the MFC application, my Properties Window do not have the "Overrides" option for me.
#### Working around:
Add the OnInitialUpdate function manually. Make it virtual for the View class.

With the help of part 2 of the instruction, I implemented the event driving program using MFC. In this project, I want my game to respond to player's mouse click on the game board. So I added the OnLButtonDown event handler so that once the player clicks on valid blocks, the blocks will be deleted and the game board will be updated. Similar to the above struggle, the instruction does it through the Properties Window, but I added the event handler manually.

#### Struggle:
After I added the OnLButtonDown event handler and ran the code, the mouse click still did not work. Blocks are never deleted no matter where I clicked on. 
#### Solution: 
I checked my OnLButtonDown function and made sure that there was nothing wrong with this event handler. This means the reason of this problem occurring is that the event handler did not get the message(signal) when mouse is clicked. I fixed this problem by adding the ON_MW_LBUTTONDOWN() in the message map of the View class source file. ON_MW_LBUTTONDOWN is a message sent by the MFC framework every time the user clicks the left mouse button down. Without this message, OnLButtonDown event handler will never know when a mouse is clicked.
http://forums.codeguru.com/showthread.php?349415-OnLButtonDown-never-gets-called

Up to this point, my Same Game is playable with 3 colors. Then I added menus to control difficulty levels so that players can play with 3, 4, and 5 colors.

<img width="300" alt="Screen Shot 2020-06-14 at 19 32 36" src="https://user-images.githubusercontent.com/63526495/84612549-ce134f00-ae75-11ea-981e-b73096bd178a.png">

#### Struggle:
In order to add different color levels, I set up the event handlers for ON_COMMAND and ON_COMMAND_UPDATE_UI types of events for menus. But after I setup them and ran the code, I found that the number of colors of the blocks did not change when I chose a different level. The number of colors is always the number I assigned to m_nColors in the constructor of GameBoard class.
#### Solution:
I checked and made sure that my event handlers can get the message ON_COMMAND and ON_COMMAND. So I thought about when is the number of colors decided in my code. My event handler get the number of colors from GetNumColors() in the Document class. The GetNumColors() got the information of color from the GameBoard object "my_board". Thus I knew that there is something wrong with my SetNumColors function of the GameBoard class and I corrected the mistake in this function.

Correcting the mistake itself is easy for this problem. But the process that I found the mistake is worth mentioning. Sometimes, a seemingly intractable problem is the result of a pretty minor error that is hard to find. So we really need to have patience and know how the project is constructed in order to get to the root of the problem.

## Improvement

I created a variable "score" in the View class to store the current score of the player. I decided that every time a player deletes n blocks, he or she get (n - 1)^2 points. Also, when game is over, a MessageBox will show up telling the player number of blocks remaining and the score of the player. The other content of the MessageBox is little different based on how well the player plays. 

<img width="400" alt="Screen Shot 2020-06-14 at 19 32 54" src="https://user-images.githubusercontent.com/63526495/84612564-d9667a80-ae75-11ea-9a34-18cdd45ce71c.png">

<img width="400" alt="Screen Shot 2020-06-14 at 19 33 11" src="https://user-images.githubusercontent.com/63526495/84612572-e3887900-ae75-11ea-92fc-c0f48495e626.png">

## Connections

In this project, I used MFC to create my game. It is actually similar when we use Qt to create graphical user interfaces. When we need event driven programming, for Qt, it uses connect function to connect a signal and a slot. A signal is emitted when a particular event occurs. And the slot will recieve the signal and get called. For MFC, we call slot a event handler. It will get called when it recieve the particular message(signal) in the message map. When I met the problem that my mouse click did not work, I thought about how Qt handle the event and then it helped me to find the solution for solving the problem.

## Needed Improvement

The game currently will only show the totol score of the player when the game is over. If I am going to keep on working with this project, I want the real time score to show at a corner of the game board.

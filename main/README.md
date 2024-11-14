# CoMo
Cognitive Mouse <br>
Authors: Jasmin Eder, Dorothea Mauracher <br>
2023
## main
The starting menu includes a first selection of the left or right hand that is used. Therefore just press the thumb with the corresponding hand and the left or right hand is detected and buttons are adapted automatically. Then a menu opens where 2 different games (memoryGame or reactionGame) can be selected in 3 different modes (visual, tactile, or combined). With the index finger the menu can be scrolled and with the thumb the current game in the current mode is selected.

## definitions
Variables and PIN values are defined here and used in all other files. Here, also the thresholds for the force sensors can be adapted.

## memoryGame
Memory game like 'Ich packe meinen Koffer' or 'Simon says'. A sequence of stimuli is shown to the user who has to repeat the sequence by pushing the buttons in the correct order. First one stimulus is activated (either visual, tactile, or combined) and then the user needs to react by pushing the corresponding button. If the button was correct, the sequence gets elongated by one stimulus and the whole sequence is shown to the user again. Afterwards the user has to input the whole sequence. If correct, the sequence gets elongated again, if the input was false, the game is over and the score is printed.

## reactionGame
This game is used to evaluate the stimuli and the reaction of the user. Therefore, 20 different stimuli are activated in a pseudo-random order. While one stimulus is activated, the user has to react by pushing the corresponding button. The stimulus remains until the correct button has been pushed. Wrong pushes are detected automatically and afterwards displayed. After 20 stimuli the reaction time is shown. The reaction time is calculated measuring only the time the user needs to push the button. The push itself is not counted there.

### Troubleshooting
The current RAM and storage of the arduino nano is too little to also control the display. Therefore, the menu and output is shown in the serial monitor. However, the code is already implemented in show.cpp and show.h <br>
The thumb may be not recognized and either the threshold needs to be adapted or something in the hardware might be broken as the thumbs are connected internally.

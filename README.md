# UBomber

A simple spinoff off Dyna-Blaster aka Bomberman mechanics.

Completed features:

Static top-down view on the level (Bonus: camera that pans in/out depending on distance between players in the level)

• One pre-defined map (Bonus: procedural generated maps)

• “Couch Co-Op”: Two players play on one machine using different keys to control two characters

o Make the characters distinguishable somehow (color, nameplate, …)

o Optimally with both players using the keyboard, no gamepad

• Implementation of different pickups

o Longer bomb blasts

o More bombs

o Faster run speed

o Remote-controlled bombs (timed power-up, around 10 seconds)

• Bomb placing by the player

o Player is starting with only one bomb that can be active at a time

o Placing a bomb subtracts one from the count, when the bomb explodes the count goes up again

o Amount is upgradable with pickups

o Once the remote detonator has been picked up only one bomb can be active until the power-up runs out

• Player death when standing in bomb blast

• Bomb blasts

o Should not be spherical but linear in the four main directions

o Can penetrate players/pickups when going off (killing/destroying them)

o Are stopped by walls

o Trigger other bombs

• Differentiation between destructible and indestructible walls, destructible walls can spawn random pickups (~30% chance to spawn something) upon destruction

• Win conditions:

o Show win screen when only one player is alive

o Show a map timer, that counts down and ends the round

o Show draw when the last players die in the same bomb blast (or chained bombs) or multiple players are alive when the timer runs out

o After round end, freeze game in its current state

• Reset option on end screen

o Starts another round

o Previous score should be saved


Not completed features:

• Bonus: AI enemies that behave like a player

Reason:

Preparing a good AI would take a significant amount of time. 

Mostly about:

Generating real time map interpretation for AI, 

Work on pathfinding algorithms (default one would be too simple), 

Prediction of player moves, 

Prediction of bomb placement and their range.


Project is based on blank tempate from UE4.

Only code that is not 100% mine is about hacking game to support 2 players on single keyboard:

https://wiki.unrealengine.com/Local_Multiplayer_Tips

I had alse made use of an idea on creating shared camera from this article:

https://wiki.unrealengine.com/Creating_a_shared_camera_for_multiplayer_games


Time spent: 20 hours


Possible next steps:

Player and monster AI

4 players support

Online game support

Add models and animations

Add textures for walls, floor and bomb

Best results saved and displayed in ranking

Non-square map generation support

Better camera panning algorithm (I've been playing massively with aspect ratio, but couldn't achieve a good result in the offered timeframe)

Possibly Steam support

Single / multi player campaign

<img src="project-logo.png" align="right" />
# Real-Time 3D Graphics - OpenGL

Writting in C/C++ the graphical application is based on various libraries to create a real virtual word. The environment includes 3D objects and animations played, 3D sounds played at different locations and simulated ambient light to give 3D object the real-life effect. 

## Introduction

The game action takes place in a city where the player has to collect the coins scattered on the city sidewalks by crossing the streets and avoiding the moving cars. Each sidewalk has obstacles which needs to be avoided by going back on the street. Sounds are played when a car gets closer to the player to signal a warning message.  

## Requirements

- Visual Studio 2013
- OpenGL Driver v3.3
- VC++ compiler

## Installation

Open the **.sln** file fo the project and compile the **Coursework project**. This action will first build the **Zeno library** which acts as a dependency for the main project.

## Objectives

Element | Status | Comments
--- | --- | ---
Software Design Document | Done | All 5 sections are completed
Reasonable Coding Standard | Yes | Hungarian style, CameCase style and Comments + Indentations
3D Skybox | Yes | Centered on the origin of the scene
3D Player | Yes	| An MD2 model with animations for walking and idle
Lighting | Yes | The Phong shader
3D Terrain | No	| Flat but suggestive to the game theme. It consists of one 3DS model repeated 6 times to create a highway.
Collision Detection | Yes | Axis Aligned Bounding Boxes
Object-Oriented Approach | Yes | Libraries functionality is wrapped in classes, applied different object-oriented principals
User Interface | Yes | Clickable buttons and background images for main menu state
Animations | Yes | The player character
Sound | Yes | 3D Sound and Background
Game Elements | Yes |Gold coins scattered around the scene
Computer Controlled Models | Yes | Vehicles that needs to be avoided by the player

## How To Play

1. Intro screen:
  - **Space key** to continue or wait 3 seconds to change to the Main Menu screen

2. Main Menu screen:
  -	**Escape key** to exit the game or press the Quit button by using the left mouse button
  -	**Space key** to go to Character Select screen. Here the player needs to wait for the characters models to be loaded. This action will happen only once

3. Character Select screen:
  -	**Return key** to move to the next character available. Models are presented in circle order, after the last model, the next model that come is the first one
  -	**Space key** to go to Level screen or press the Go button by using the left mouse button. Here the player needs to wait for all the game models to be loaded. This action will happen only once

4. Level screen:
  -	**W key** moves the character forward in the direction of the camera
  -	**S key** moves the character backward in the opposite direction of the camera
  -	**A key** moves the character to the left
  -	**D key** moves the character to the right
  -	**Q key** rotates the camera around the character in the left direction
  -	**R key** rotates the camera around the character in the right direction

5. Game Over screen:
  -	**Space** key to change to the Main Menu screen

## Screenshots

[YouTube Video](https://www.youtube.com/watch?v=_dTcpk8F0GU)

Screenshot 1
<img src="screenshot-1.png" align="center" />

Screenshot 2
<img src="screenshot-2.png" align="center" />

Screenshot 3
<img src="screenshot-3.png" align="center" />

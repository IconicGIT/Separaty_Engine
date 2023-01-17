<h1 align="center"> Separaty Engine </h1> 

---

![Separaty-WORDv3](https://user-images.githubusercontent.com/73245381/211687452-410cb772-8116-43b8-b9e5-d8b126ef543a.png)

## Description

Separaty Engine is a game engine made in C++ for learning purposes. 

This project has been created by UPC-CITM students in our 3rd year of the Video Game Design and Development degree offered by the CITM, year where we find the videogame engines subject, in which this project is carried out. A project that is developed with the objective of improving our programming skills to be more efficient and clean. 

In order to do so, we have focused in the basic internal tools, functions and processes that we normally do not take into account during the development of a videogame. It is for this reason that we have had to learn and develop internal and basic aspects such as game object management, rendering, structures... 

It is important to highlight that our engine is free to use and everyone can give us feedback to continue improving it!

Obviously, we believe that this is not necessary to emphasize, but we will say it anyway:           
**This Engine will be Better than Unity one day!**

## Developers

![Developers](https://user-images.githubusercontent.com/73245381/211890076-90d159a0-6f1d-4ae7-9c49-06c86e508146.jpg)

**Brandon Arandia**

*Which has been in charge of the innermost part of the engine, developing the creation and management of:* 
  * *Game Objects*
  * *Editor Tools*
  * *Texture Import*
  * *Model Import*
  * *Scene Seralitzation*
  * *Custom file format*
  * *Resource Managment*
  
    - Github account: [IconicGIT](https://github.com/IconicGIT)
    
**Gerard Martinez**

*Which has been in charge of the design and interface of the engine, developing the creation and management of:* 
  * *Game Objects Hierarchy*
  * *Editor Tools*
  * *Camera Control*
  * *Texture Import*
  * *Game viewport & editor viewport*
  * *Transformation*
  * *Resource Managment*
 
    - Github account: [GerardMartinez02](https://github.com/GerardMartinez02)
 
Although as you can see, there are many steps in which we have worked as a team to achieve the objective, since the two of us have had a lot to do with their creation.
    
## Main core sub-system

### Game Objects and Components:
Game Object and Component structure similar to other engines lets the user have a more comfortable experience when using the engine and leads to a more productive work.

### Mouse Picking: (Still in beta testing)
Objects can easyly be selected in the scene window by clicking on them. 

### Extense Configuration: 
The user can easily customize the engine settings so the engine can adapt to the user needs. It is able change the style of the engine, the FPS...

### Own File Format: 
In order to make file management faster Separaty Engine uses it's own file format which increases the load and unload speed reducing waiting times. Thus avoiding loading all unnecessary fbx information each time.

### Easy Import: 
Importing in Separaty Engine is easy, just drag and drop any model or texture you need onto the engine and it will be automatically imported. If you want any file or texture to be imported without having to drag and drop you can easily select your files in the inspector editor. 

### Scene Management: 
Save your work by saving it into a scene. Then load again to pick up where you left off. 

### Camera Culling: (Still in beta testing)
Why should we waste resources printing objects which won't even be on screen? That's the question which leads to a camera culling implementation which will discard objects out of camera view printing only those which can be seen. To visualize the process Separaty Engine lets you choose if you want camera culling to be applied only on the main camera or also on the editor camera.

### Resource Management: 
Memory management is very important in computer games, so in order to save some those resources which won't be used won't be loaded until they are required and at the time they stop being used they will be unloaded from memory.


## Assignment 3 sub-system

In this module, we have been able to implement the creation and customization of particles. As we wanted its main feature to be customization, that's why we considered adding a lot of variables to the particles, in order to create really good particles for Project 3.

### Customization
One of our primary goals of this module is the customization of said particles. In our engine you will be able to edit many aspects of the particles, including their intial position, their velocity along each axis, their acceleration, lifetime, amount of particles spawned and the rate at which these are spawned.

This is done throught the inspector, where the component Particle Emitter will be shown in case the gameobject has one. Here there will be a list of the active submodules of the Emitter.

Each submodule is responsible of sending a certain type of particle to the emitter to create. Each submodule is independent, and there you will be able to edit aspects such as the texture and origin, along with the aspects stated earlier. For many parameters, you will be able to choose between a single source of a range of data. In case of selecting the last one, the particle will select a value between the two limits given. These aspects serve to give dynamism to the particles.

The submodule also sets the main texture that its pack of particles will use. This can be edited in the Particle Texture dropdown menu. Here you will be able to load an image to set as the particle texture. In this section you can also trim the in rows and columns, as well as to choose the amount of textures that the loader will generate from the original texture. This will useful for the coming Animation feature.

### Delta Time
As we know, the particle sub-system is based on the delta-time to move correctly the particles. Because of this reason we decided to focus on making the delta time as useful as possible.

For starters, in the Application Data window the slider for the FPS amount has been increased greatly. In changing this value, the application will move laggier, or at maximum speed! For high Hz screens, set the amount hight to experience the true smoothness ;).

Also, a Play bar has been added. This serves to animate the particles, and by using its controllers you can increase or decrease the velocity at which they move!
It also provides a Step button. When pressing it when in play mode, but in pause, it will advance exactly one frame.

### How it works?
The Particle System is contained within one header and one .cpp file. Here are stored all the classes that make the system possible, as well as its own structs and functions, that makes the system very independent and modular. It only depends on Opengl, Glew and a few lines of Dear ImGui.

The system is mainly formed by 4 elements:

### The System
The ParticleSystem class is in charge of initializing, creating, storing and updating all the Emitters that it creates. Within one instance of it it is possible to access to all the components! Useful for modular-based applications, such as the one we usually have used in class in other years.

### The Emitters
The Emitters are in charge of updating the particles and serve as a container that generates the particles shown, but acts as a controllable instance. This is the main component attached to a gameobject, and it is the container that stores the Submodules. It can contain multiple Submodules.

## The Submodules
A Submodule is a part of the Emitter that is in charge of giving shape to a set of particles and send them to the emitter. They are the main area of customization, and includes many dropbars with for changing the movement of the particles, of which the main ones are the Particle Set Attributes (to change movement) and the Particle Texture dropbar (to change and customize the texture used.)

Is is worth noting that a single Emitter can contain many Submodules, and a submodule can also contain other Submodules, which will be useful in the near future to enable even more customization possibilities!

## The Particle
The main protagonist of the sub-system. It has many attributes that inherit from the settings of the their respective submodule, which change their behavior in movement and in appareance. It is a small unit of data, something that lets the application to have thousands of them active.


## Video
![motores foto](https://user-images.githubusercontent.com/72080813/212988331-6b618b7d-127d-40b4-83b1-4e3539c41268.png)

https://drive.google.com/file/d/1DrUDyq5SE2Xm51iMvjQJOutWGux4JYAv/view?usp=sharing

## Links

Github - Code Repository:
- https://github.com/IconicGIT/Separaty_Engine/tree/Assignment3

Last Release:
- https://github.com/IconicGIT/Separaty_Engine/releases/tag/Assignment3

## License

MIT License
Copyright (c) 2022 Brandon Arandia & Gerard Martinez Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

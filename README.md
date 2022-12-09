# Separaty Engine

![Separaty-WORD](https://user-images.githubusercontent.com/73245381/198894291-2466b7b4-0d6c-4ee8-8536-7dc6e690152b.png)

## Description

Separaty Engine is a game engine made in C++ for learning purposes. 

This project has been created by UPC-CITM students with the objective of improving our programming skills to be more efficient and clean. For doing it, we have focused in the basic internal tools, functions and processes that we normally do not take into account during the development of a videogame.  

It is important to highlight that our engine is free to use and everyone can give us feedback to continue improving it!

Obviously, we believe that this is not necessary to emphasize, but we will say it anyway:                   **This Engine will be Better than Unity one day!**

---

Visit github page for detailed information regarding code and functionalities: https://iconicgit.github.io/Separaty_Engine/ 

## Separaty Manual (Quick Engine View)

Our engine has a Main Menu Bar that allows you to quickly access all the functions of the engine, beeing able have a lot of ways to navigate through it. Here you can see of it:

![Menu Bar](https://user-images.githubusercontent.com/73245381/198843251-b2b32e84-2060-4a4d-b6c2-6c5e747ffd7d.png)

### File

On the File Tab, you will find all the things related with the Scene and Project Creation. In addition to an Exit button.

![File](https://user-images.githubusercontent.com/73245381/198843165-52ad4904-8b7b-4944-b480-f52d53319da9.png)

- **New Scene**: Create new scene 

- **Open Scene**: Open an existing scene 

- **Save**: Save Scene

- **Load**: Load Scene

- **New Project**: Create new project

- **Open Project**: Open an existing scene 

- **Save Project**: Save the current project

- **Exit**: Close the engine

### Edit

On this part you can find all the Edit functionalities available in the Engine along with their shortcuts. As well as the buttons for the Project settings and Data.  

![Edit](https://user-images.githubusercontent.com/73245381/198843807-eb1c1d6c-4d46-4df6-b564-e38b66f48a2a.png)


- **Basic Editors**: All basic functionalities for editing. With their respective Shortcut. (Shortcuts are defined below) 

- **Project Settings...**: Opens the current Project Settings

- **Preferences**: Opens the Engine General Settings

- **Show Application Data**: Opens the Project Data

- **Controls**: Link to the controls of the engine / Opens a windows with the basic controls of the Engine

### Game Objetcs

In Game Objects you find the different lists of all the creatable objects. In them you can select the object to create.

![Game Objects](https://user-images.githubusercontent.com/73245381/206083048-7628989a-6046-450a-adbb-2d3e5329babc.png)

- **Create Empty**: Create an empty object

![Create Empty](https://user-images.githubusercontent.com/73245381/206081696-ccbec5e0-88c3-4b12-b595-4f79a5c36a05.png)

- **Create 3D Objects**: List of all available primitives

![3D Objects](https://user-images.githubusercontent.com/73245381/198844498-cda2e911-0641-4e70-a0ec-721062d1f59a.png) 

**Cube**: Create a cube game object

**Sphere**: Create a sphere game object

**Capsule**: Create a capsule game object

**Cylinder**: Create a cylinder game object

**Plane**: Create a plane game object

- **Effects**: List of all available effects

![Effects)](https://user-images.githubusercontent.com/73245381/198844616-dd3aaa63-ba58-4005-a87f-0ca079e2f16c.png)

**Particles**

- **Light**: List of all available lights

![Light](https://user-images.githubusercontent.com/73245381/198844792-860cb6f7-3fd8-47ef-b577-28c72ca8ebe7.png)

**Directional Light**: Light that gets emitted in a specific direction

**Point Light**: Light that gets emitted from a single point in all directions

**Spot Light**: Light that gets emitted to produce intense illumination in a well-defined area

**Area Light**: Light that gets emitted in a specific direction from within a set boundary, either a rectangle or circle

- **Audio**: List of all available audios

![Audio](https://user-images.githubusercontent.com/73245381/198845256-b57ba284-5f32-43e6-841b-506ce11a1513.png)

- **Camera**: Creates a camera 

![Camera)](https://user-images.githubusercontent.com/73245381/198845331-07f12eeb-d717-4b5b-ab6c-4ee39081a916.png)

### View

On the View Tab, you will find all the things related with the visualitzation of the Scene. Since you have the render options.

![View)](https://user-images.githubusercontent.com/73245381/198845521-335ba559-11fa-45b3-84cb-d94e06e2a366.png)

- **Render Options**: List of all available render options

![Render Options](https://user-images.githubusercontent.com/73245381/198845569-5daa69a8-208f-4949-8bc1-25e61613cdca.png)

**Ambient Oclussion**: Calculate how exposed each point in a scene is to ambient lighting

**Color Material**: Specifies which material parameters track the current color

**Cull Face**: Allows non-visible triangles of closed surfaces to be removed

**Depth Test**: Tests the depth value of the fragment against the content of the depth buffer

**Front**: Defines front-facing and back-facing polygons

**Lightning**: Simulates the bright spot of a light that appears on shiny objects

**Wireframe**: Creates an edge or skeletal representation of the object

- **Shaders**: List of all available shaders

![Shaders](https://user-images.githubusercontent.com/73245381/198845700-fd7a78db-91f8-40d4-b9ce-a94bf5bd07fb.png)

### Window

In the windows section you can find all the Editor Windows that can be used to working in the Project.  

![Window](https://user-images.githubusercontent.com/73245381/206082227-3ac99ed4-2956-4740-bf4d-3118755b102a.png)

- **Hierarchy**: Opens the Hierarchy Window

![Hierarchy](https://user-images.githubusercontent.com/73245381/206707461-f45ffbbf-bb4b-4fba-b9b3-222445c5277a.png)

In this window we can find all the Game Objects created in the scene. So we can see how many objects we have and their hierarchy.

In addition to the functionalities of adding childs and removing objects.

- **Inspector**: Opens the Inspector Window

![InspectorClosed](https://user-images.githubusercontent.com/73245381/206710532-a9ac584a-b310-4139-b95b-7f05bef5682d.PNG)
![Inspector](https://user-images.githubusercontent.com/73245381/206708610-f76c54e6-d6f2-4d61-ba7a-084ded31a094.png)

In the inspector window you can find all the components that each object in the scene has. As it can be seen in the images, each object ha:

An information window about it

A transform window to move the object around the scene

A mesh window to change his mesh 

A texture window to texturize it.

In addition to having an extra component if we have selected a camera type game object.

![Camera](https://user-images.githubusercontent.com/73245381/206739055-467e31f7-db93-43b9-9a56-ff84ab2c55c9.PNG)

In this component you can modify both the near and far planes of the frustum, in addition to the FOV of the camera.

As well as allowing interaction through cameras, since it allows you to choose the view port once you are in game mode. This is done by first selecting the option to set the camera as main camera and later selecting the use camera option, in order to indicate that you want to have its point of view.

- **Assets**: Opens the Assets Window

![Assets](https://user-images.githubusercontent.com/73245381/206724166-57afa46c-74de-4604-8d5e-53fc9ddc7186.png)

It contains a list with all the folders and assets saved in the project.
- **Show Output**: Opens the Debug Console

![Output](https://user-images.githubusercontent.com/73245381/206725415-fc71d4b5-df1b-4a93-a750-9553e055c1bc.png)

- **Play & Stop**: Opens the Play & Stop Window

![Stop](https://user-images.githubusercontent.com/73245381/206726305-4b1fa812-da63-4987-91ab-0b807a037c47.png)

![Play](https://user-images.githubusercontent.com/73245381/206726503-91c8fad2-0d3e-4c23-b682-4fb7abd4ddc5.png)

This window allows you to iterate through the game state and the editor state, to be able to see what the game scene would look like in real time.

### Help

Here you can find all the information about the Engine. In addition to direct links to contact us, report any bug or have a look to the Separaty Manual.

![Help](https://user-images.githubusercontent.com/73245381/198846310-b95a4c0f-641e-4f24-888f-ba1b0d3a9b90.png)

- **About us**: Opens the documentation of the engine

- **Separaty Manual**: Opens the tutorial/how to use the engine github page

- **Make any comment**: Opens the contact github page

- **Report a Bug**: Opens the issues github page

## Controls

### Camera Controls:

- **W**: Move Forward

- **A**: Move Left

- **S**: Move Backwards

- **D**: Move Right

- **Hold Shift**: Duplicate movement speed

- **Right Click + Left ALT**: Orbit around the selected object

    (If an object is not selected) Orbit around the center of the scene
    
- **Left Click + Left ALT**: Camera rotation

- **Mouse Wheel**: Zoom In/Out

- **F**: Focus the camera around the selected object

    (If an object is not selected) Focus around the center of the scene.
    
### Shortcuts:  

- **CTRL + Z**: Undo

- **CTRL + Y**: Redo

- **SHIFT + A**: Select All

- **SHIFT + D**: Deselect All

- **CTRL + X**: Cut

- **CTRL + C**: Copy

- **CTRL + V**: Paste

- **CTRL + D**: Duplicate

- **SHIFT + R**: Rename

- **SUPR**: Delete
    
    
## Developers

* Brandon Arandia

    - Github account: [IconicGIT](https://github.com/IconicGIT)
    
* Gerard Martinez

    - Github account: [GerardMartinez02](https://github.com/GerardMartinez02)

## License
### MIT License

Copyright (c) 2022 Brandon Arandia & Gerard Martinez
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Task 2

- **Transformation and Game Object hierarchy**

We have implemented the transforms and the game object hierarchy as requested in this Assignment, always trying to respect the parents and the childs since we believe that it is an important part to take into account when we talk about the transform of a game objects.

In addition to perfectly implementing the function of creating children and deleting objects.

We are also in the process of implementing an option to do Drag and Drop the names of the game objects in the hierarchy itself, in order to be able to place objects as parents/children of other objects directly from there.

- **Custom file format**

Still in progress.

- **Game viewport & editor viewport**

We have implemented a camera switch between the engine editor camera and the camera known as the game camera. Aditionally, we have also implemented a functionality to be able to have multiple cameras in the scene and decide for yourself which point of view you want to have.

Despite this, we are still implementing a method to be able to visualize the 2 cameras at the same time.

- **Scene serialization**

At this point, it seems that everything works find when we save the scene into a JSON file. Since it can load the children of the objects, the transform, the meshes, the textures and even the FOVs of the cameras.

In this way you can save the scene, close the program, and reopen it without problems once you press File->Load or do you use his short cut

- **Play / Stop**

We have implemented the change of camera at the time of pressing play/stop for seeing the scene through the game camera.

In addition to having left the timer and the change of his velocity ready for when we have to use it to see changes in real time at game mode.

- **Camera (10% each): component, mouse pick, frustum culling**

The camera component has been well implemented and perfectly follows all its required functionalities. The transformation, the changes in the FOV and Near/Far planes and the camera switch are working correctly.

On the other hand, we have implemented the mouse picking, but it should be noted that some things still need to be perfected. It is able to select objects without any problem, we have also put the line that the mouse draws every time you click to debug. The problem is that once the object is selected we have not yet implemented that it opens the hierarchy and the inspector.

The frustum culling is partially implemented, with the implementation of the object detection points in process. Pending to solve doubts in class.

- **Resource Management (includes inspector editing of component mesh & material)**

There is an “Assets” window that shows all user assets by a simple tree viewer, however we have left it commented waiting to resolve a doubt in the following class.

In addition, the screen where the imported assets are loaded can be found in the inspector. There is a list that shows in each component the appropriate asset loaded
once it has been imported. Also, taking into account the duplication of the imported models, since it does not allow it. 

We have also implemented a currently non-functional folder explorer that is commented out in the code. Simply due to problems of not detecting the fileSystem.h


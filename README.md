# Macro Box V1
The inspiration for this project was to design, print, assemble, and code a cheaper version of the popular [stream deck](https://www.elgato.com/en/stream-deck). Using Autodesk Inventor I created a 3D model of the housing I would use and populated it with models of the switches I intended to use to ensure all elements fitted together.

<img src="https://github.com/joshuabrown419/MacroBoxV1/blob/main/render.png" alt="render.png" style="height:300px;"/>

After slicing and printing the housing I attached the switches and soldered them to an arduino nano to be the brains of the box, pictured below is the assembled version.

<img src="https://github.com/joshuabrown419/MacroBoxV1/blob/main/prototype.jpg" alt="prototype.jpg" style="height:400px"/>

Using arduino studio I programmed arduino mini inside the box to emulate a keyboard, setting the switches to emulate uncommon buttons, such as the function keys beyond F12, in order to avoid conflicts with default keybindings. I also created a couple of different modes for the switches so that they could simulate a held button or repeated inputs.

In the next iteration of the project I would like to create an interface anyone can use from their computer to change the settings instead of needing to change and redeploy the code. I would also like to add some sort of rotaty input device to be used for controlling things such as volume.

Windows Programming Laboratory Work #3
======================================

Title
-----
Basics of Working with Mouse. GDI Primitives. Bezier Curve.

Contents
--------
-	Mouse
-	Device context
-	GDI Primitives
-	Line
-	Curve
-	Plane
-	Bitmap image
-	Bezier curve

Mandatory Objectives (completed)
--------------------------------
-	Draw few lines of different colors and weights
-	Draw a Bezier curve
-	Draw few plane objects (ex. circle, square, pie, polygon...) of different colors, weights, filled and not.
-	Draw 2 different objects using mouse

Objectives With Points (completed)
----------------------------------
-	Draw a custom bitmap image (1 pt.)
-	Add a switch (button, select list...) that will change mouse ability to draw objects (2 pt.)
-	Draw a Bezier curve using mouse (1 pt.)
-	Fill an object with a gradient (1 pt.)
-	Use mouse as an eraser of a adjustable width (2 pt.)

Creating the application
--------------------------
-	First I opened Paint and choose what functions I would like to have in my program. Since this is a much  more simplified version of Paint I chose the most basic tools like: pencil, brush, eraser, added some shapes and a dialog box for choosing a color. I also added two input labels for Eraser size and Border size.
-	Here is the mockup I made:
![mockup] (https://raw.github.com/TUM-FAF/FAF-121-Caraganciu-Dan/master/WP/Lab%233/Images/mockup.png)

 1.The drawing area.                     
 2.Custom bitmap image. 

 3.Instruments bar which contains: 
 
  -	**Pencil** is used for drawing a continuous line with the size of 1.
  -	**Brush** is used for drawing a continuous line with the size of 10.
  -	**Eraser** is used for erasing the drawing area.
  -	**Rectangle** draws a rectangle on the drawing area depending on how you click and drag the mouse on the               
    screen.Basically you draw the diagonal and the rectangle appears. 
  -	**Line** draws a straight line. When you left-click the first time you set the starting point and after you release you     set the end point of your line.
  -	**Ellipse** tool has the purpose of drawing an ellipse. 
  -	**Bezier curve** is used for drawing a curve. For this you click and drag two times in a row. 
 
 4.**Size and color** bar which contains:
  -	**Fill color check box** which sets whether to color the interior of a shape or not. Also you can choose which color to     use.(it’s unchecked by default)
  -	**Border color** allows you to choose the color of the pencil, brush or the border color of a shape.
  -	**Eraser size** input sets how big you want your eraser to be.
  -	**Border size** sets the size of the pencil. Also note that the Brush is set by default to 10 and is not changed by this     input. This input affects everything except for the Brush.   
 
 5.**Gradient**


Screenshots

![Capture] (https://raw.github.com/TUM-FAF/FAF-121-Caraganciu-Dan/master/WP/Lab%233/Images/Capture.PNG)

Conclusions
--------------------------
This laboratory work was even more interesting and I really enjoyed working on it. I was very addicted to do all the tasks but it was hard somehow to organize my thoughts in order to implement them all and I did just a part of them, but I will manage the rest of them in the near future (I hope).In this laboratory work I familiarized with some of drawing possibilities and the right way of working with the mouse. For me it is a new experience and of course I still have work to do for better results but right now I kind of feel accomplished. 

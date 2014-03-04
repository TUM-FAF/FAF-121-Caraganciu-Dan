Windows Programming Laboratory Work #1
======================================

Title
-----
Window. Window handling. Basic window’s form elements.

Introduction
------------
Purpose
*	Event-driven programming (message-oriented)
*	API
*	Windows applications development

Additional Purposes
*	Version Control Systems (GIT)
*	Programming Style Guidelines
*	Debugging
*	Testing

Mandatory Objectives
--------------------
*	Create a Windows application
*	Choose Programming Style Guidelines that you'll follow
*	Add 2 buttons to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
*	Add 2 text inputs to window: one with default styles, one with custom styles (size, background, text color, font family, font size)
*	Add 2 text elements to window: one with default styles, one with custom styles (size, background, text color, font family, font size)

Objectives with Points
----------------------
*	Make elements to fit window on resize. **(1 pt.)**
*	Make elements to interact or change other elements. **(2 pt.)**
*	Change behavior of different window actions (at least 3). **(1 pt.)**

Creating the application
--------------------------
•	I started by reading the recommended chapters from the  book ("Programming Windows, 5th Edition", by Charles Petzold) so that I could understand the basics and begin my first laboratory work.

•	I checked the laboratory works done by students from the previous year so I could get an idea of my own by inspiring from them.

•	The application is basically for storing the data about students of a group that has laboratory works on Windows Programming. It allows students to choose either the blue pill or red pill in order to be classified. Choosing the blue pill means that you will have to create a more simplified program but with the condition that you also make the report with specific standards. Choosing the red pill means that your application will be more complex and interesting but on the other hand your report will be more simplified.  So my application has two text labels, 6 buttons (two  ADD buttons, two RESET buttons, BLUE button and  RED button), two field inputs, and one header title.

•	The UI elements are mixed and different, they have different styles and fonts, different sizes.

•	For this laboratory work  I used C style guide.

•	In order to explain the application I made a mock-up using paint:





1.	The Window’s Title.
2.	After pressing the Maximize button a message box will appear instead of maximizing the window.
3.	By pressing the Close button the user will be asked if he really wants to close the window.
4.	After pressing the RED Pill button the user will be asked if he is sure of his choice and after that a message box      will appear.
5.	After pressing the BLUE Pill button a message box will appear.
6.	Read-only multiline text label, with vertical scrollbar which stores the list of people who chose the red pill.
7.	Read-only multiline text label, with vertical scrollbar which stores the list of people who chose the blue pill.
8.	The field input is made in HTML5 placeholder form. The placeholder text is the grey text that you see in the input      field and it is used to give a hint to the users on what input is expected in that field. Once users start typing in     the input field, new text will appear and the placeholder will disappear.
9.	Analogical to 9.
10.	Adds  the text written in the field input on the text label.
11.	Analogical to 10.
12.	Resets the text label for red pill list.
13.	Resets the text label for blue pill list.


![mockup] (https://raw.github.com/TUM-FAF/FAF-121-Caraganciu-Dan/master/WP/Lab%231/Images/mockup.png)

Result Application
------------------
This is a screen shot of the application in the virtual Windows 7 environment:

![appimg] (https://raw.github.com/TUM-FAF/FAF-121-Caraganciu-Dan/master/WP/Lab%231/Images/appwindow.png)

Conclusion
------------------
This laboratory work turned out to be much more interesting and less complicated than it first seemed to be. I have learned a lot of new things like what is window and how to create it. My application has nice executable stuff in my opinion. I was inspired by the new method of execution of the laboratory works with “blue pill and red pill” so I came up with the idea of making two lists of students with their choice. I wanted to give a purpose to this application and not just put a box where you write any random stuff.
I think this laboratory work gave a nice experience on Event-driven programming and a good foundation on which to build more complex tasks.

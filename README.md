The following project was built in the span of two weeks by Nicholas Hoang, Jake Petersen, and Darshil Sheth. The goal of this project is to build a MUD (Multi-User Dungeon), similar to text-based games
of which were one of the earlier networked based games played before GUIs were developed in the modern day video games of today. In this project, we used an ESP32 as our main form of displayed 
information and function as a video game system, as well as having navigation be built using a D-pad esque system (in our case, we didn't have a direct D-pad set up, so
we opted to use a number pad and made each of the corresponding numbers be North, South, West, and South). Said control input would be sent to the server using UDP socket 
communication, and the text description of any room entered will be displayed on the LCD attached to the ESP 32 using MQTT services.
In this case, we use the Google Cloud Protocols-Compute Engine Instance to act as a server to establish the c daemon server file and allow all of the functions
to happen.

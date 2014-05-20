of3DStudio
==========

An openFrameworks application to visualize 3D objects, lights and materials


About
-----

The main goal of this oF app is to provide a simple way to study the effects of light on various objects and materials.

To do this, it implements a contextual menu allowing to easily navigate through lights, objects and their materials, change their properties, add new ones, or remove them.

The menu is made with [ofxUI](https://github.com/rezaali/ofxUI).


The main purpose of this OF app is to study the effects of lights and mater

How to run it
-------------

This is an openFrameworks application. To make it run, you need to have a working distribution of openFrameworks.

Then, use the openFrameworks project generator to create a new project using ofxUI (be sure to have this addon installed and working).

It should then be enough to replace the default src/ folder by the repository one. You should be able to compile the project.

This project has been reported to work with :

* openFrameworks 0.8.1
* Linux Ubuntu 13.04 (64 bits)
* Windows 7 (64 bits)


Improvements
------------

In the future, the application should be able to handle the following features:

* Textures
* Shaders

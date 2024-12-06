# Unreal Engine 2024 - AI Lectures

This folder contains Unreal Engine project and slides used during AI related lectures at Faculty of Mathematics and Physics, Charles University as part of Unreal Engine lectures in autumn semester 2024

## Slides

AILecture.pdf

## Unreal Engine Project

AILecture.uproject

The project contains content for 2 lectures
* Lecture 1
    * Introduction to AI COntroller
    * Pathplanning
    * Movement control
    * Sensing
    * Environment Query System
* Lecture 2
    * State Trees

### Lecture 1
The lecture goal was to create a "patroling behaviour" where an AI character is moving through set of waypoints around a building.
The next goal was to create a reaction of the AI character reacts to seeing player.
The last goal was to make the AI character to flee upon seeing the player as far as possible to a place where the player can not see the AI character.
The map and the blueprints relevant to this lecture can be found in `Content\AILecture1`.

### Lecture 2
The goal of this lecture was to create a behaviour of AI character based on simple trigers:
* Hunger
* Thirst
* Tiredness
* Danger

This was achieved by creating simple State Tree sending the AI character to different places in the map.
The map and the blueprints relevant to this lecture can be found in `Content\AILecture2`.



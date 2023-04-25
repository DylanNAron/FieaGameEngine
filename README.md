# FieaGameEngine
Custom Data Driven game engine written in C++. Featuring custom implementations of stl containers, custom data structures, data parsing system, and Gameobjects that have various components resembling a standard game engine with actions, reactions and an event system.

## The Engine:
-At the core of the engine there are the classes:
  -**RTTI** - custom base class for runtime type information
  -**Datum** - A homogeneous polymorphic container whose type can be determined at runtime through use of a discriminated union.
  -**Scope** - A table of strings & datums which forms a dynamic hierarchical database. Datums can be scopes so we can have trees of scopes.
  -**Attributed** - A scope derived class which can have prescribed & auxiliary attributes. This allows us to mirror native c++ into a scripting language.
  -**TypeRegistry** - singleton that maanges attributed derived classes.
-Our scripting language of choice is Json so we have created:
  -**Parsing System** - utilizing the chain of responsibily pattern, created a generic parser which in our case we use to parse Scopes from Json.
  -**Factory** - implementation of the abstract factory design pattern so we can create objects based on their name in our scripting language.
-Now that we have the core and scripting basis of our engine we have several components created that resemble a modern Game Engine:
  -**GameObject** - attributed derived class that represents the basis for a "noun" in game. Contains attributes name, transform, child game objects, and actions.
  -**Action** - component that represents the "verbs" in our game. to allow an object to implement a type of action.
  -**EventSystem** - utilizing the observer design pattern, created an event system that can notify subscribers, and allow for game objects to have reactions.
  

### Custom Implementation of STL Containers:
Singly linked List, Vector, Hashmap, Stack

### Carious Design Patterns Implemented:
Singleton, Factory, Observer, Chain of Responsibility

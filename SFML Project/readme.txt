BASIC INSTRUCTION:
Use ARRAY KEYS to control the ship
Use SPACE KEY to shoot
Use key Q and E speed switch back and forth between maps.
Destroy invaders to pass wave.
Player dies if runs out of lives

FEATURES:
Behavior of enemies and player
Enemies will fire only when directly above the player(have accuracy modifier to simulate natural behavior)
Enemies move back and forth (left to right), whenever they drop, their speed increases (both firerate and moving speed)
More waves passed, Higher the speed of enemies.
Items will randomly spawn on the screen
-1 hp if player gets hit by a bullet, or collide with an enemy.
Enemy immediately gets destroyed if collide with the player.

PROJECT'S STRUCTURE DESCRIPTION:
The project is structured around the entities component system and factory design pattern.
Each GameObject has predefined components attached to it
(ex: player has graphics, transform,update, rect collider components)

Visual studio file filter explained:
Components: hold all the components source file
Core: physics engine, modules to make the game functions
Screens: hold all the screen (ex: game,select...)
UI: hold all the UI
InputHandlers: Input from keyboard, mouse,..

CURRENT STATUS:
Core gameplay seems to work just fine
Fps is stable

Limitation:
Item has yet to be picked up
Perpetuating explosion animation
Explosion misplaced
Hard to edit level

Bug Report:
Items can't be picked up yet.
Item spawning issues.
Level transition is unstable.
Hard to replicate bugs. (crash while reading *player position)
Editor mode: (Working progress)

FUTURE PLAN:
Add different kind of items, enemies, bullet. (apply factory, type object, prototype pattern)
Optimizing performance (if perf drops)
Make editor mode.
Refactor codes, get rid of redundunt classes and components
Expand the project (more things happen on the screen).
*Change structure of the world files.
Change type identifier from const string -> enum

FLOW OF THE PROGRAM (perplexed part)
GameObject has many properties(ex: draw only when GraphicsCom was provided)
start is the function to activate all the nescesary components

GameObjectBlueprint holds setter and getter of properties of a typical GameObject
-> passed in to the factory to produced fully operational GameObject

GameObjectFactory will build the GameObject due to specification, add components(and initialize of nescesary)
-> push GameObject to vector

GameObjectSharer responsibles for sharing vector<GameObject> across the game. 
findFirstObjectWithTag() jump the the first instance of the specific type of object(ex: invader, player,... )

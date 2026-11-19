# Project 3: Build Your Own Voxel World

## The idea

Build a standalone, first-person voxel sandbox in C++, inspired by Minecraft. The player enters a procedurally generated world, explores different landscapes, gathers resources, builds shelter, and develops the tools needed to survive and explore farther. The world should feel like a place worth spending time in: forests stretch across hills, caves lead underground, water cuts through the terrain, and the player's buildings become lasting parts of the landscape.

This project reinterprets CS61B's **Build Your Own World (BYOW)** as a substantial 3D game. BYOW supplies the educational foundation: generate an interesting world, let a player interact with it, preserve their progress, and organize a growing program thoughtfully. Minecraft supplies the broad experience and visual direction. Luanti and Mineclonia supply concrete examples of how mature projects solve engineering and gameplay problems.

The intended result is a smaller, cohesive Minecraft-style game with its own implementation and identity. Development starts with a simple playable world and expands toward terrain variety, survival, creatures, and polished graphics.

## The player experience

A new game begins with a seed and a fresh landscape. You might spawn near a forest overlooking a lake, with a rocky hillside nearby. You can walk around, look freely, jump, and interact with blocks. Trees provide material for early tools and construction; exposed stone hints at resources below the surface.

Your first goal is to establish a foothold. Gather materials, craft basic tools, and build somewhere to return to. As daylight fades, lighting and creature behavior change the atmosphere and give shelter a purpose. Later, descend into caves, discover ores, improve your equipment, and explore other biomes. Building and exploration remain worthwhile alongside survival.

When you return to a saved game, your shelter, mined tunnels, collected items, and position are still there. The world develops a history through your actions.

Gameplay runs continuously, with familiar mouse-and-keyboard first-person controls. Menus, inventory, crafting, and the HUD should make the world easy to understand and interact with.

## Implementation references

The project uses three references with different responsibilities:

| Reference | What to learn from it | Role in this project |
| --- | --- | --- |
| [Luanti](https://github.com/luanti-org/luanti), formerly Minetest | A voxel engine implemented primarily in C++, including world storage, terrain generation, rendering, and lighting | Reference for the engine and world-generation architecture |
| [Mineclonia](https://codeberg.org/mineclonia/mineclonia), a game written in Lua for Luanti | Minecraft-style blocks, items, crafting, survival, creatures, and progression; also game-specific generation | Reference for gameplay systems and how they fit together |
| [Radiance](https://github.com/Minecraft-Radiance/Radiance), with its C++ Vulkan renderer [MCVR](https://github.com/Minecraft-Radiance/MCVR) | Advanced rendering, hardware ray tracing, lighting, reflections, and transparent materials | Selected reference for the optional advanced rendering extension |

Our engine and gameplay will be written in C++. Here, using Luanti as the basis means studying its approach and adapting useful ideas into a smaller engine of our own. Mineclonia serves the same role for the game built on that engine. Reading its Lua code can clarify a rule or system before designing a C++ implementation.

These references should answer concrete questions as they arise: how to represent a portion of the world, how a biome selects surface materials, how a crafting recipe is described, or how a creature switches between wandering and chasing. The project grows one understandable system at a time.

## Combining the game with BYOW

The [original BYOW assignment](../Instructions.html) remains the educational reference. Its main ideas translate into the following project requirements:

| BYOW idea | Requirement for this game |
| --- | --- |
| Generate varied worlds from a seed | The same seed and generation settings reproduce the initial landscape; different seeds produce meaningfully different worlds. |
| Arrange spaces into an explorable environment | Terrain, caves, and generated structures create interesting routes and discoverable spaces. The player begins somewhere usable. |
| Give the player an avatar and meaningful interaction | Support movement, collision, exploration, and interaction with blocks and objects. |
| Present useful information through an interface | Provide a clear way to create or load a world, plus a HUD showing the selected item, targeted block, and relevant survival information. |
| Save and resume the world | Preserve the player's progress and changes to the environment across sessions. |
| Extend the world creatively | Develop building, crafting, survival, creatures, and visual features into a coherent experience. |
| Design and manage a substantial program | Separate responsibilities, choose suitable data structures, document important decisions, and develop through working increments. |

The original rooms-and-hallways exercise becomes a broader problem of generating spaces that are varied and enjoyable to explore. Caves, ruins, and connected underground chambers are natural ways to carry that idea into a voxel world. The assignment's exact controls, grading conventions, and turn-based behavior are outside this reinterpretation.

## World generation and exploration

The world consists of blocks with different properties: stone is solid, water behaves differently from solid terrain, and trees combine several block types. Divide the world into **chunks**, manageable regions that can be generated, drawn, saved, and loaded separately. This makes a world larger than the immediately visible area practical.

Generation develops in layers. Start with terrain height and basic surface materials, then add biome differences, vegetation, caves, ores, and structures. A biome influences the character of a region—its terrain, ground cover, trees, and resources. An initial range of plains, forests, and rocky or mountainous areas should make traveling worthwhile.

Caves create underground spaces to explore and reasons to mine. Water contributes to the landscape through lakes, coastlines, or rivers. Begin with stable bodies of water; flowing water can become a later system once terrain and block editing work reliably.

Generation and player changes must work together. Crossing a chunk boundary should feel natural, and returning to a previously visited area should preserve what the player built or removed.

## Building and survival

Block interaction is the foundation of the game. The player can target, remove, collect, and place blocks, with an inventory and hotbar connecting these actions. Building should feel responsive enough that constructing a small house is enjoyable on its own.

Crafting gives resources a purpose. A small set of materials, recipes, and tools establishes an understandable progression: gather wood, make early tools, acquire stone, and reach more valuable underground resources. Tools can differ in effectiveness and the materials they can harvest.

Survival introduces health, food, danger, and recovery. A day/night cycle creates changing conditions, while creatures make the world feel inhabited. Start with one passive creature and one hostile creature, each with clear behavior. Their movement, interactions, and relationship to the player's resources matter more than a large roster.

The first complete survival experience should support a simple arc: explore, gather, craft, build shelter, survive a night, and return from a cave with useful resources. Further systems can extend that experience once it works well.

## Visual direction

Aim for a polished Minecraft-like appearance: consistent block scale, cohesive pixel textures, readable terrain, and lighting that gives the landscape depth. The visual ambition is part of the project, alongside generation and gameplay.

Early improvements should include a coherent sky and fog, daylight changes, convincing block shading, transparent water, and clear feedback when targeting or breaking blocks. Later work can explore shadows, ambient occlusion, animated vegetation, particles, and richer water rendering. Each addition should support the established look and remain usable during ordinary exploration and building.

Performance is part of that experience. Drawing a forest, entering a new region, or modifying a wall should feel responsive. Measure the systems that cause visible slowdowns and improve them as the world becomes more demanding.

## Development stages

1. **A playable block world.** Open a 3D scene, move a first-person player through it, handle collision, and break and place blocks. This establishes the interaction everything else depends on.
2. **A generated landscape.** Add seeds, chunks, terrain, trees, and several block types. Explore beyond the starting area and save changes to the world.
3. **A world worth exploring.** Add biomes, caves, ores, bodies of water, and selected structures. Improve transitions between regions and the atmosphere of the landscape.
4. **A survival game.** Connect inventory, crafting, tools, health, food, creatures, and the day/night cycle into the first complete survival experience.
5. **A polished experience.** Refine graphics, sound, interfaces, creature behavior, and performance through actual play.
6. **Optional advanced rendering extension.** Study Radiance and MCVR to develop the stylized lighting, water, atmosphere, and ray-tracing systems described below.

Each stage leaves a working game that can be played and evaluated. The first stage is also the initial skeleton: a world representation, renderer, player controller, block interaction, and a game loop. Additional systems get a place in the design when they become useful.

## Optional advanced rendering extension: Radiance

The long-term graphics ambition is a richly lit, stylized voxel world: sunlight streams through trees, leaves and grass sway in the wind, water reflects the landscape, and torchlight gives underground spaces warmth and depth. Preserve the block shapes, pixel textures, and expressive colors that make the world recognizable while developing more sophisticated lighting and materials.

**Radiance is the selected rendering reference.** Study its [MCVR C++ renderer](https://github.com/Minecraft-Radiance/MCVR) for Vulkan rendering and hardware ray tracing, and its [Advanced shader source](https://github.com/Minecraft-Radiance/Shaderpack-Advanced) for lighting, atmosphere, and water. As with Luanti and Mineclonia, adapt the ideas to our standalone game. Radiance's Minecraft integration provides context for the implementation rather than a ready-made dependency for this engine.

The extension's visual targets are animated leaves and grass, volumetric fog and god rays, reflective and refractive water, richer shadows, and ray-traced lighting or reflections. These are goals for our renderer; individual effects can use different techniques and be developed independently. Choose the target GPU and platform before implementing the hardware ray-tracing stage, then evaluate quality and performance in the same forest, water, and cave scenes used to guide the visual style.

This is an optional graphics project beyond the core playable game. It can grow through small rendering experiments once the world and gameplay provide useful scenes to render.

## What the project should demonstrate

A successful version lets someone create a seeded world, explore varied terrain, alter the landscape, build a home, participate in a basic survival loop, and save and resume their progress. Its systems should feel connected, and its code should be understandable enough to extend.

Use the accompanying [design document](Design.md) to explain major decisions about world storage, generation, gameplay, rendering, and persistence. Validate what a player relies on: reproducible starting terrain, reliable movement and block interaction, consistent chunk boundaries, preserved builds after loading, and usable performance in a representative world.

The learning goal is to understand how data structures, algorithms, graphics, and software design combine to create a world that behaves convincingly.

## Reference starting points

- [Original CS61B BYOW specification](../Instructions.html): the educational foundation.
- [Luanti engine source](https://github.com/luanti-org/luanti) and [world-generation source](https://github.com/luanti-org/luanti/tree/master/src/mapgen): engine organization and generation mechanisms.
- [Luanti's basic data structures](https://docs.luanti.org/for-engine-devs/basic-data-structures/): how a mature engine represents its world.
- [Mineclonia](https://codeberg.org/mineclonia/mineclonia) and its [GitHub mirror](https://github.com/mineclonia-mirror/mineclonia): gameplay rules and systems built on a voxel engine.
- [Radiance](https://github.com/Minecraft-Radiance/Radiance), [MCVR](https://github.com/Minecraft-Radiance/MCVR), and [Advanced shaders](https://github.com/Minecraft-Radiance/Shaderpack-Advanced): selected references for the optional advanced rendering extension. MCVR is primarily GPL-3.0 with exceptions documented in its [license](https://github.com/Minecraft-Radiance/MCVR/blob/main/LICENSE.md); the Advanced shader repository uses GPL-3.0.

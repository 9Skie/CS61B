# Voxel World: Design Notes

Use this document alongside the [game concept](Instructions.md). Fill in decisions as each part of the game takes shape. Keep it focused on how the current implementation works and what the next playable stage needs.

## Current direction

- Current playable stage:
- Next experience the player should be able to have:
- C++ version, build tools, and graphics libraries:
- Target platform:

## Main systems

Describe each system's responsibility, the data it owns, and how other systems interact with it. Begin with the world, renderer, player, and block interaction; add gameplay and persistence as they develop.

| System | Responsibility | Main data structures | Connections to other systems |
| --- | --- | --- | --- |
| | | | |

Explain important ownership choices, especially what happens when chunks unload or creatures disappear.

## World and generation

- How are blocks and chunks represented and located?
- How does a seed produce the initial terrain?
- How are biomes, vegetation, caves, water, and structures added?
- How do neighboring chunks fit together?
- How are generated terrain and player edits stored together?

Include a sketch or a small example when it explains the generation process better than prose.

## Player and gameplay

- How do movement, collision, targeting, and block editing work?
- How are blocks, items, inventories, recipes, and tools defined?
- How do health, food, creatures, and daylight affect play?
- What can the player accomplish in the current version?

Describe the rules that connect these systems into a playable experience.

## Rendering and presentation

The selected reference for the optional advanced rendering extension is [Radiance](https://github.com/Minecraft-Radiance/Radiance), especially its [MCVR C++ renderer](https://github.com/Minecraft-Radiance/MCVR) and [Advanced shaders](https://github.com/Minecraft-Radiance/Shaderpack-Advanced).

- How are visible block surfaces turned into geometry?
- How does editing a block update what is drawn?
- How are textures, lighting, water, and the sky handled?
- What information does the HUD communicate?
- What currently limits smooth exploration or building?

When starting the extension, record the target GPU and graphics API, the first effect being developed, and a representative scene for comparing its appearance and performance. The visual goals include moving vegetation, god rays, reflective water, and ray-traced lighting while preserving the game's stylized appearance.

## Saving and loading

Describe what a save contains, including the world seed, player progress, and world changes. Explain how loading restores a playable session and how saves behave as the project evolves.

## Verification through play and focused checks

Record useful scenarios and their results: revisit an edited region, reload a built shelter, cross chunk boundaries, recreate terrain from a seed, craft and use a tool, or survive a night. Add focused automated checks where they help catch errors in generation, coordinates, inventory, or persistence.

## Reference notes

For each useful Luanti, Mineclonia, or Radiance/MCVR example, record the source location, the idea learned, and how this implementation adapts it. Identify any reused code or assets and their licenses.

## Next steps

Record the next playable improvement, unresolved design choices, and known problems that affect the player.

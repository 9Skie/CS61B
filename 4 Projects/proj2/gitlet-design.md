# Gitlet Design Document — C++17

**Name**:

Write your design before implementing commands, and revise it as it changes.
See [the C++ assignment](Instructions.html). These are prompts, not a prescribed
solution; choose the classes and storage layout that fit your design.

## Classes and Data Structures

### Class or module 1

**Responsibility**:

#### Fields

For each field, give its C++ type, purpose, owner, and whether it is persisted.

#### Public operations

Describe inputs, outputs, side effects, and errors.

### Class or module 2

**Responsibility**:

#### Fields

#### Public operations

## Ownership and Lifetimes

- Which values are copied, moved, or passed by reference?
- Do any references outlive their owners?
- How do files and other resources get closed on an error?
- Which relationships are represented by persisted IDs rather than pointers?

## Algorithms

For each command, outline its steps and the data structures it uses. Identify
validation that must happen before any state changes, and analyze the runtime
against the assignment's requirements. Explain how shared operations are reused.

For merge, describe how you find a split point and handle each file-state case.

## Persistence

- Draw your `.gitlet` directory layout.
- Define each record's fields, byte encoding, and decoding rules.
- Explain how equal logical objects produce identical bytes and IDs.
- Explain how you represent timestamps and order map entries when serializing.
- Identify which state is read/written for each command.
- Explain how one commit can be loaded without loading its entire ancestry.

## Testing

- List the behaviors covered by your own `.in` tests.
- Cover specified errors, empty files, binary contents, and fresh invocations.
- Cover branching, reset, merge conflicts, and untracked-file protections.

## Optional Extension: Dear ImGui GUI

Complete this section if you implement the
[Dear ImGui extension](Instructions.html#dear-imgui-extension).

- Sketch the branch list, commit graph, commit details, and staging panels.
- Describe how you traverse both parents of merge commits, lay out the graph,
  and select commits by ID.
- Identify the repository operations and queries shared by the CLI and GUI.
- Explain how the selected working directory determines all repository paths.
- Separate temporary interface state from persisted Gitlet data. Describe when
  the view refreshes and how it handles changes made through the CLI.
- Describe the optional GUI build and its dependencies, keeping the ordinary
  CLI build independent.
- If you add command buttons, explain how actions use the same validation and
  error behavior as the CLI, and how you check the results through both interfaces.


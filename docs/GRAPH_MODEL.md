# Graph Model

## 1. Vertex definition

Each vertex represents one schedulable **class session**. Multiple sessions of the same course are distinct vertices when they need independent placement.

Recommended in-memory fields:

- `classId`
- `courseId`
- `lecturerId`
- `studentGroupIds`
- `requiredCapacity`
- `requiredRoomType` (optional)

## 2. Edge definition

An undirected edge `u -- v` means the two class sessions must not receive the same time-slot color.

MVP automatic edge reasons:

1. `shared_lecturer`
2. `shared_student_group`

The graph should retain edge reasons for visualization/diagnostics when practical.

Room competition is **not** automatically a graph edge because multiple rooms may be available in the same time slot. Room feasibility is checked in the room-assignment stage.

## 3. Coloring interpretation

A color is an abstract time-slot index. After coloring:

- color `0` maps to an active time slot;
- color `1` maps to another active time slot;
- and so on.

A coloring that uses more colors than available active time slots is infeasible for the current dataset.

## 4. Baseline algorithm — Greedy

MVP baseline uses deterministic Greedy Coloring. Recommended ordering:

1. descending vertex degree;
2. stable tie-break by `classId`.

The algorithm selects the smallest available color not used by already-colored neighbors.

## 5. Improvement — DSATUR

DSATUR repeatedly selects the uncolored vertex with:

1. highest saturation degree (number of distinct neighbor colors);
2. then highest graph degree;
3. then stable `classId` tie-break.

It assigns the smallest legal color.

## 6. Correctness invariant

For every edge `(u, v)` in a valid coloring:

`color(u) != color(v)`.

This invariant must be tested directly.

## 7. Explainability

Graph visualization should let a user inspect:

- vertex/class identity;
- color/time slot;
- edge endpoints;
- edge reason where available.

The project prioritizes an understandable graph over a highly optimized opaque representation.

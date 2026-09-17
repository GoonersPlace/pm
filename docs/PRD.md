# PRD — Smart Timetable Scheduler

**Status:** Draft v0.1  
**Product:** Web-based timetable scheduler using Conflict Graph + Graph Coloring  
**Primary user:** Scheduler/Admin  

> `docs/PRD.md` and `docs/SRS.md` are co-primary product sources of truth. If they conflict, implementation must stop and request owner clarification.

## 1. Problem

Manual timetable construction is difficult because classes may compete for lecturers, rooms, student groups, and available time slots. The project models these incompatibilities as a conflict graph and uses graph coloring plus simple heuristics to generate valid schedules that are easy to explain in a Discrete Mathematics / Graph Theory context.

## 2. MVP goals

The MVP shall:

1. Manage basic input data: courses/classes, lecturers, rooms, student groups, and time slots.
2. Build a Conflict Graph from incompatible classes.
3. Assign time slots using Graph Coloring.
4. Validate hard constraints.
5. Assign compatible rooms.
6. Produce at least one valid timetable when the input is feasible.
7. Display the timetable in a browser.
8. Display the Conflict Graph for demonstration/learning.
9. Score valid timetables using a small, explicit set of soft constraints.
10. Compare the transparent Greedy baseline with a DSATUR improvement.

## 3. MVP non-goals

The MVP does not include:

- AI/LLM/RAG/agents as product features;
- realtime collaboration or WebSocket features;
- direct integration with a real university SIS;
- native mobile application;
- automatic email/notification delivery;
- large-scale optimization guarantees;
- Genetic Algorithms, Simulated Annealing, Machine Learning, or other advanced optimizers unless the scope is explicitly expanded;
- user management or complex RBAC;
- production-grade authentication.

## 4. User

### Scheduler/Admin

A single MVP role that can:

- enter/edit timetable data;
- generate schedules;
- inspect conflicts;
- compare algorithm results;
- inspect validation errors and soft-constraint scores.

## 5. Demo authentication

Authentication is only a simple demo gate. Any syntactically valid Gmail address and non-empty password is accepted. The application does not store or manage user accounts in MVP.

## 6. Core user flows

### 6.1 Prepare data

Scheduler enters lecturers, rooms, student groups, course/class sessions, and time slots.

### 6.2 Build graph

System derives edges from hard incompatibilities such as shared lecturer or overlapping student groups and displays the resulting graph.

### 6.3 Generate timetable

Scheduler chooses the supported algorithm (Greedy baseline or DSATUR), runs generation, and receives either:

- a valid timetable plus score/diagnostics; or
- a structured explanation that the available slots/resources cannot satisfy the current hard constraints.

### 6.4 Evaluate timetable

The system shows hard-constraint validation and a soft-constraint score breakdown.

## 7. Hard constraints

MVP hard constraints are defined in detail in `SCHEDULING_RULES.md` and include at minimum:

- a lecturer cannot teach two classes in the same time slot;
- a room cannot host two classes in the same time slot;
- overlapping student groups cannot attend two classes in the same time slot;
- assigned room capacity must satisfy class demand;
- assigned room type must satisfy class requirement when a type is specified;
- each scheduled class receives exactly one allowed time slot and one compatible room.

## 8. MVP soft constraints

Initial scoring rules are intentionally simple and explainable:

1. Minimize gaps for student groups.
2. Minimize gaps for lecturers.
3. Discourage very early/late slots.
4. Balance student-group daily load.
5. Spread multiple sessions of the same course across different days when possible.

Weights live in configuration, not hard-coded scheduling logic. Exact defaults are documented in `SCHEDULING_RULES.md`.

## 9. Success criteria

The MVP is successful when it can demonstrate, on representative sample data:

- correct conflict-graph construction;
- valid Graph Coloring output when feasible;
- deterministic hard-constraint validation;
- understandable graph/timetable visualization;
- score breakdown for soft constraints;
- a visible comparison between Greedy and DSATUR;
- automated tests covering critical scheduling logic.

## 10. Product principles

- Explainability over sophisticated optimization.
- Simplicity over abstraction.
- Correctness before performance.
- Do not silently relax constraints to obtain a schedule.
- A failed/unsatisfiable result is preferable to an invalid timetable.

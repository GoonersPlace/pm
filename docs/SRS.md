# SRS — Smart Timetable Scheduler

**Status:** Draft v0.1  
**System type:** Web application  
**Backend:** C++20 + Qt 6  
**Database:** SQLite  

> This SRS and `PRD.md` are co-primary behavior sources of truth. A conflict between them requires owner clarification before implementation proceeds.

## 1. System overview

The system lets a scheduler/admin enter academic scheduling data, constructs a conflict graph, applies Graph Coloring to assign time slots, assigns compatible rooms, validates the schedule, evaluates soft constraints, and visualizes both the timetable and graph.

## 2. Functional requirements

### FR-001 — Demo login

The system shall expose a login flow for the single `scheduler/admin` role.

- A syntactically valid email ending in `@gmail.com` and a non-empty password shall be accepted in MVP demo mode.
- The system shall not persist user accounts or passwords.
- This mechanism shall be labeled as demo-only and shall not be represented as production security.

### FR-010 — Lecturer management

The scheduler shall be able to create, list, update, and remove lecturers subject to referential-integrity rules.

### FR-011 — Room management

The scheduler shall manage rooms with at least: name, capacity, optional room type, and active state.

### FR-012 — Student-group management

The scheduler shall manage student groups used to detect timetable conflicts.

### FR-013 — Course/class-session management

The scheduler shall manage classes/sessions with at least:

- course identity/name;
- lecturer;
- required capacity;
- optional required room type;
- one or more participating student groups;
- number/session identity sufficient to distinguish multiple sessions.

### FR-014 — Time-slot management

The scheduler shall manage discrete time slots containing day, start time, end time, and active state.

### FR-020 — Conflict graph construction

The system shall represent each class session as a graph vertex. It shall create an edge between two class sessions when they cannot share the same time slot due to a graph-level hard conflict, including:

- same lecturer; or
- at least one shared student group.

Additional approved conflict rules may add edges but shall not be added silently.

### FR-021 — Graph visualization

The web UI shall display graph vertices and edges with enough metadata to explain why a conflict edge exists.

### FR-030 — Greedy coloring

The system shall provide a simple Greedy Coloring baseline. Its ordering rule shall be deterministic for the same input.

### FR-031 — DSATUR coloring

The system shall provide DSATUR as the first improvement algorithm and allow comparison with the Greedy baseline.

### FR-032 — Time-slot feasibility

A coloring result requiring more colors than active time slots shall not be reported as a valid timetable. The system shall report a structured scheduling failure.

### FR-033 — Room assignment

After time-slot assignment, the system shall assign each class a compatible available room such that room hard constraints are satisfied. Failure to find a compatible room shall invalidate the candidate schedule.

### FR-040 — Hard-constraint validation

Before a generated timetable is accepted, the system shall validate every hard constraint listed in `SCHEDULING_RULES.md`. No soft-constraint score may override a hard-constraint violation.

### FR-050 — Soft-constraint evaluation

For a hard-valid timetable, the system shall calculate a total penalty and a per-rule penalty breakdown for the approved MVP soft constraints.

### FR-060 — Timetable display

The frontend shall show generated entries in a readable weekly timetable/table view with at least class/course, lecturer, time slot, room, and relevant student group information.

### FR-070 — Persistence

Input entities and generated schedules shall be persisted in SQLite using versioned migrations as the schema source of truth.

## 3. API requirements

- REST API base path: `/api/v1`.
- Public request/response contracts are documented in `API.md`.
- Success/error responses shall use consistent envelopes.
- Input validation failures shall use structured 4xx responses.
- Internal errors shall not expose stack traces, secrets, SQL queries, or filesystem details.

## 4. Quality requirements

### NFR-001 — Explainability

Scheduling algorithms and score components shall remain understandable enough to demonstrate how a result was produced.

### NFR-002 — Maintainability

The scheduling engine shall be separated from HTTP/UI code and should use standard C++ types where practical.

### NFR-003 — Correctness

Automated tests shall cover graph construction, Greedy/DSATUR coloring, constraint checking, scoring, empty input, impossible input, and representative edge cases.

### NFR-004 — Test targets

Target coverage guidance:

- scheduling/business logic overall: 70%+;
- Conflict Graph: 80%+;
- Graph Coloring: 80%+;
- Constraint checking: 80%+;
- scoring/evaluation: 75%+.

Coverage is a quality indicator, not a substitute for meaningful test cases.

### NFR-005 — Security boundary

The demo login is not production-grade. The system shall validate inputs and avoid leaking sensitive runtime information. `.env` secret values shall never be exposed through logs or API responses.

### NFR-006 — Performance

The MVP shall prioritize correctness and clarity for classroom/demo-sized datasets rather than large-scale scheduling optimization.

## 5. Out of scope

See `PRD.md` §3. Any implementation that introduces an out-of-scope system feature requires explicit owner approval.

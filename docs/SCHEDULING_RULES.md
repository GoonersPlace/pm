# Scheduling Rules

## 1. Hard constraints

A candidate timetable is invalid if any hard constraint fails.

### HC-01 Lecturer exclusivity
A lecturer cannot teach more than one class in the same time slot.

### HC-02 Student-group exclusivity
A student group cannot attend more than one class in the same time slot.

### HC-03 Room exclusivity
A room cannot host more than one class in the same time slot.

### HC-04 Room capacity
`room.capacity >= class.requiredCapacity`.

### HC-05 Room type compatibility
If a class specifies `requiredRoomType`, the assigned room must have that type.

### HC-06 One placement per class
Each scheduled class receives exactly one active time slot and exactly one compatible active room.

### HC-07 Time-slot validity
The assigned time slot must exist and be active.

### HC-08 Room validity
The assigned room must exist and be active.

Hard constraints may not be converted to penalties without an explicit product decision.

## 2. MVP soft constraints

Soft constraints only rank schedules that already satisfy all hard constraints.

Penalty lower is better. Default weights are configuration values, not magic numbers inside algorithms.

| ID | Soft constraint | Default weight | Penalty idea |
|---|---|---:|---|
| SC-01 | Student-group gaps | 5 | +weight per idle slot between the group's first/last class in a day |
| SC-02 | Lecturer gaps | 3 | +weight per idle slot between lecturer classes in a day |
| SC-03 | Very early/late slots | 2 | +weight per class in configured edge-of-day slot |
| SC-04 | Daily load balance | 2 | +weight for load exceeding preferred classes/day threshold |
| SC-05 | Same-course spread | 1 | +weight when multiple sessions of same course are placed on same day when avoidable |

Initial defaults live in `backend/config/scheduling_defaults.json`.

## 3. Why this set is appropriate for MVP

These rules are:

- easy to explain in a demo;
- measurable without advanced optimization libraries;
- independent enough to show a score breakdown;
- useful for comparing Greedy and DSATUR schedules;
- small enough to avoid turning the project into a general optimization platform.

## 4. Score contract

For hard-valid schedules:

```text
totalPenalty = sum(rulePenalty[rule])
```

API/UI should expose:

- total penalty;
- each rule penalty;
- relevant counts/diagnostics when useful.

Do not compare soft scores for a hard-invalid schedule as though it were a valid candidate.

## 5. Constraint changes

Adding/removing a hard or soft constraint, changing semantic interpretation, or changing default weights in a way that changes expected product behavior requires owner approval and updates to this file plus tests.

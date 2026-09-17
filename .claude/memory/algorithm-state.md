# Algorithm State

## Accepted strategy

1. Build a Conflict Graph from shared lecturer/student-group incompatibilities.
2. Use deterministic Greedy Coloring as baseline.
3. Use DSATUR as the first improvement.
4. Map colors to active time slots.
5. Assign compatible rooms.
6. Validate all hard constraints.
7. Score valid schedules with approved soft constraints.

## MVP soft constraints

- student-group gaps (weight 5);
- lecturer gaps (weight 3);
- early/late slots (weight 2);
- daily load balance (weight 2);
- same-course spread (weight 1).

Weights are configurable and changes that alter expected behavior require approval.

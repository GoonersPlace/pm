# UI Guidelines

The project has no external Figma file yet. Coding agents may design the UI autonomously **within these rules**.

## 1. Product character

A practical academic scheduling tool: clear, structured, data-dense enough for timetable work, but not visually cluttered.

## 2. Layout

Recommended navigation:

- Dashboard
- Data
  - Courses / Classes
  - Lecturers
  - Student Groups
  - Rooms
  - Time Slots
- Generate Schedule
- Timetable
- Conflict Graph
- Evaluation

Desktop is primary. Tablet/mobile should remain functionally usable with stacked layouts and horizontal scrolling for timetable grids where necessary.

## 3. Components

Prefer reusable shadcn/ui-compatible patterns:

- Button
- Input
- Select
- Dialog
- Table
- Tabs
- Badge
- Card
- Alert
- Tooltip

Do not add a new npm package merely for a component without approval.

## 4. Visualization

Conflict Graph should visually distinguish vertices/time-slot colors, but color must not be the only source of meaning. Provide labels/legend/tooltips.

Timetable cells should show:

- course/class;
- lecturer;
- room;
- student group(s) where space permits.

## 5. Algorithm diagnostics

The Generate/Evaluation views should make the project demonstrable:

- selected algorithm;
- number of vertices/edges;
- colors used;
- hard-constraint status;
- total soft penalty;
- penalty breakdown;
- failure reason for infeasible schedules.

## 6. Accessibility

- semantic form labels;
- keyboard-accessible controls;
- visible focus states;
- sufficient contrast;
- status text/icons in addition to color;
- meaningful empty/error/loading states.

## 7. Styling

Use Tailwind utility classes and a small token set. Avoid arbitrary one-off colors/spacing where a shared token/component would work. Prioritize clarity over decorative animation.

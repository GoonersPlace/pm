PRAGMA foreign_keys = ON;

CREATE TABLE lecturers (
    lecturer_id TEXT PRIMARY KEY,
    name TEXT NOT NULL,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE rooms (
    room_id TEXT PRIMARY KEY,
    name TEXT NOT NULL UNIQUE,
    capacity INTEGER NOT NULL CHECK (capacity > 0),
    room_type TEXT,
    is_active INTEGER NOT NULL DEFAULT 1 CHECK (is_active IN (0, 1)),
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE student_groups (
    student_group_id TEXT PRIMARY KEY,
    name TEXT NOT NULL UNIQUE,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE courses (
    course_id TEXT PRIMARY KEY,
    code TEXT NOT NULL UNIQUE,
    name TEXT NOT NULL,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE classes (
    class_id TEXT PRIMARY KEY,
    course_id TEXT NOT NULL,
    lecturer_id TEXT NOT NULL,
    session_label TEXT NOT NULL,
    required_capacity INTEGER NOT NULL CHECK (required_capacity > 0),
    required_room_type TEXT,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (course_id) REFERENCES courses(course_id) ON DELETE RESTRICT,
    FOREIGN KEY (lecturer_id) REFERENCES lecturers(lecturer_id) ON DELETE RESTRICT,
    UNIQUE (course_id, session_label)
);

CREATE TABLE class_student_groups (
    class_id TEXT NOT NULL,
    student_group_id TEXT NOT NULL,
    PRIMARY KEY (class_id, student_group_id),
    FOREIGN KEY (class_id) REFERENCES classes(class_id) ON DELETE CASCADE,
    FOREIGN KEY (student_group_id) REFERENCES student_groups(student_group_id) ON DELETE RESTRICT
);

CREATE TABLE time_slots (
    time_slot_id TEXT PRIMARY KEY,
    day_of_week INTEGER NOT NULL CHECK (day_of_week BETWEEN 1 AND 7),
    start_time TEXT NOT NULL,
    end_time TEXT NOT NULL,
    is_early INTEGER NOT NULL DEFAULT 0 CHECK (is_early IN (0, 1)),
    is_late INTEGER NOT NULL DEFAULT 0 CHECK (is_late IN (0, 1)),
    is_active INTEGER NOT NULL DEFAULT 1 CHECK (is_active IN (0, 1)),
    CHECK (start_time < end_time),
    UNIQUE (day_of_week, start_time, end_time)
);

CREATE TABLE schedules (
    schedule_id TEXT PRIMARY KEY,
    algorithm TEXT NOT NULL CHECK (algorithm IN ('greedy', 'dsatur')),
    color_count INTEGER NOT NULL CHECK (color_count >= 0),
    total_penalty INTEGER NOT NULL DEFAULT 0 CHECK (total_penalty >= 0),
    score_breakdown_json TEXT NOT NULL DEFAULT '{}',
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE schedule_entries (
    schedule_id TEXT NOT NULL,
    class_id TEXT NOT NULL,
    time_slot_id TEXT NOT NULL,
    room_id TEXT NOT NULL,
    PRIMARY KEY (schedule_id, class_id),
    FOREIGN KEY (schedule_id) REFERENCES schedules(schedule_id) ON DELETE CASCADE,
    FOREIGN KEY (class_id) REFERENCES classes(class_id) ON DELETE RESTRICT,
    FOREIGN KEY (time_slot_id) REFERENCES time_slots(time_slot_id) ON DELETE RESTRICT,
    FOREIGN KEY (room_id) REFERENCES rooms(room_id) ON DELETE RESTRICT,
    UNIQUE (schedule_id, time_slot_id, room_id)
);

CREATE INDEX idx_classes_lecturer ON classes(lecturer_id);
CREATE INDEX idx_class_groups_group ON class_student_groups(student_group_id);
CREATE INDEX idx_schedule_entries_slot ON schedule_entries(schedule_id, time_slot_id);

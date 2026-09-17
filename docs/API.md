# API Contract

**Base path:** `/api/v1`  
**Style:** REST/JSON

## 1. Response envelopes

Success:

```json
{
  "success": true,
  "data": {},
  "message": "OK"
}
```

Error:

```json
{
  "success": false,
  "error": {
    "code": "VALIDATION_ERROR",
    "message": "Invalid request",
    "details": {}
  }
}
```

Do not expose stack traces, raw SQL, secret values, or internal filesystem paths.

## 2. Initial endpoints

### GET `/health`

Returns API health information.

### POST `/auth/login`

Demo-only login.

Request:

```json
{
  "email": "scheduler@gmail.com",
  "password": "anything-non-empty"
}
```

Rules:

- email must be syntactically valid and end with `@gmail.com`;
- password must be non-empty;
- no user lookup or password storage occurs.

Response data:

```json
{
  "role": "scheduler_admin",
  "token": "demo-session-token"
}
```

The token mechanism is only an MVP demo gate and must not be described as secure production authentication.

## 3. Planned resource endpoints

The following contracts are planned but should be finalized before implementation details expand:

- `/lecturers`
- `/rooms`
- `/student-groups`
- `/courses`
- `/classes`
- `/time-slots`
- `/schedules`

## 4. Scheduling endpoints

### POST `/schedules/generate`

Planned request:

```json
{
  "algorithm": "greedy"
}
```

Allowed algorithm identifiers in MVP:

- `greedy`
- `dsatur`

Planned result includes:

- schedule identifier;
- algorithm;
- entries;
- number of colors/time slots used;
- hard-validation result;
- total soft penalty;
- per-rule penalty breakdown;
- diagnostics for failure when no valid schedule is produced.

### GET `/schedules/{scheduleId}`

Returns a persisted generated schedule.

### GET `/conflict-graph`

Planned result includes vertices, edges, and edge reasons for visualization.

## 5. Contract change rule

Endpoint paths, field names/types, response envelope shape, and public behavior cannot be changed by an agent without owner approval. Implementation may change internally without approval if the contract remains intact.

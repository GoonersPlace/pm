# Local Demo and ngrok

## 1. Run backend

```bash
cmake -S . -B build
cmake --build build
./build/backend/smart_timetable_api
```

The API binds to `127.0.0.1:8080` by default.

## 2. Run frontend

```bash
cd frontend
npm install
npm run dev
```

Vite runs on `127.0.0.1:5173` and proxies `/api/*` to the local C++ API. This avoids needing to expose the Qt HTTP server directly or add CORS complexity for the local demo.

## 3. Expose the demo with ngrok

For classroom/demo use, tunnel the **frontend port** rather than the backend port:

```bash
ngrok http 5173
```

The browser talks to `/api/v1` on the same frontend origin and Vite proxies those requests to the backend on localhost.

This setup is for temporary demonstration only, not production hosting.

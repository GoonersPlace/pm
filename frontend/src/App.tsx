import { FormEvent, useState } from 'react'
import { demoLogin } from './api'
import { Button } from './components/ui/button'

function Dashboard() {
  const cards = [
    ['Conflict Graph', 'Build and inspect class conflicts before coloring.'],
    ['Generate Timetable', 'Compare Greedy Coloring with DSATUR.'],
    ['Validation', 'Hard constraints must pass before scoring.'],
    ['Evaluation', 'Inspect soft-constraint penalty breakdowns.'],
  ]

  return (
    <main className="mx-auto max-w-6xl p-6 md:p-10">
      <header className="mb-8 flex flex-col gap-2">
        <span className="text-sm font-medium text-slate-500">Scheduler/Admin</span>
        <h1 className="text-3xl font-semibold tracking-tight">Smart Timetable Scheduler</h1>
        <p className="max-w-2xl text-slate-600">
          Generate explainable schedules with conflict graphs, Greedy Coloring, and DSATUR.
        </p>
      </header>

      <section className="grid gap-4 md:grid-cols-2">
        {cards.map(([title, description]) => (
          <article key={title} className="rounded-xl border border-slate-200 bg-white p-5 shadow-sm">
            <h2 className="font-semibold">{title}</h2>
            <p className="mt-2 text-sm leading-6 text-slate-600">{description}</p>
          </article>
        ))}
      </section>

      <section className="mt-8 rounded-xl border border-dashed border-slate-300 bg-white p-6">
        <h2 className="font-semibold">Bootstrap status</h2>
        <p className="mt-2 text-sm text-slate-600">
          The repository is ready for incremental implementation. CRUD screens, generation APIs,
          timetable visualization, and graph visualization are intentionally left as task-driven work.
        </p>
      </section>
    </main>
  )
}

export default function App() {
  const [email, setEmail] = useState('scheduler@gmail.com')
  const [password, setPassword] = useState('demo')
  const [error, setError] = useState<string | null>(null)
  const [authenticated, setAuthenticated] = useState(false)
  const [submitting, setSubmitting] = useState(false)

  async function onSubmit(event: FormEvent<HTMLFormElement>) {
    event.preventDefault()
    setError(null)
    setSubmitting(true)
    try {
      await demoLogin(email, password)
      setAuthenticated(true)
    } catch (caught) {
      setError(caught instanceof Error ? caught.message : 'Login failed')
    } finally {
      setSubmitting(false)
    }
  }

  if (authenticated) {
    return <Dashboard />
  }

  return (
    <main className="flex min-h-screen items-center justify-center p-6">
      <section className="w-full max-w-md rounded-2xl border border-slate-200 bg-white p-6 shadow-sm">
        <div className="mb-6">
          <p className="text-sm font-medium text-slate-500">Demo access</p>
          <h1 className="mt-1 text-2xl font-semibold">Smart Timetable Scheduler</h1>
          <p className="mt-2 text-sm leading-6 text-slate-600">
            MVP accepts any valid Gmail address and a non-empty password. This is not production authentication.
          </p>
        </div>

        <form className="space-y-4" onSubmit={onSubmit}>
          <label className="block">
            <span className="mb-1 block text-sm font-medium">Gmail</span>
            <input
              type="email"
              value={email}
              onChange={(event) => setEmail(event.target.value)}
              className="w-full rounded-lg border border-slate-300 px-3 py-2 outline-none focus:border-slate-900"
              required
            />
          </label>

          <label className="block">
            <span className="mb-1 block text-sm font-medium">Password</span>
            <input
              type="password"
              value={password}
              onChange={(event) => setPassword(event.target.value)}
              className="w-full rounded-lg border border-slate-300 px-3 py-2 outline-none focus:border-slate-900"
              required
            />
          </label>

          {error ? <p role="alert" className="text-sm text-red-700">{error}</p> : null}

          <Button type="submit" disabled={submitting} className="w-full">
            {submitting ? 'Signing in…' : 'Enter scheduler'}
          </Button>
        </form>
      </section>
    </main>
  )
}

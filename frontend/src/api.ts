export type ApiSuccess<T> = {
  success: true
  data: T
  message: string
}

export type ApiError = {
  success: false
  error: {
    code: string
    message: string
    details: Record<string, unknown>
  }
}

export type LoginResult = {
  role: 'scheduler_admin'
  token: string
}

const apiBaseUrl = import.meta.env.VITE_API_BASE_URL ?? '/api/v1'

export async function demoLogin(email: string, password: string): Promise<LoginResult> {
  const response = await fetch(`${apiBaseUrl}/auth/login`, {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ email, password }),
  })

  const payload = (await response.json()) as ApiSuccess<LoginResult> | ApiError
  if (!payload.success) {
    throw new Error(payload.error.message)
  }
  return payload.data
}

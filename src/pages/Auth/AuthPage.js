import LoginPage from './LoginPage';
import RegisterPage from './RegisterPage';
import { Routes, Route } from 'react-router-dom';

export function AuthPage() {
  return (
    <div>
      <Routes>
        <Route path="login" element={<LoginPage />} />
        <Route path="register" element={<RegisterPage />} />
      </Routes>
    </div>
  );
}

// Добавьте default export
export default AuthPage;
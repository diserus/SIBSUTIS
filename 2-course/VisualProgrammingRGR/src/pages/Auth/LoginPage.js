import { useState } from 'react';
import { useAuth } from '../../context/AuthContext';
import { useNavigate } from 'react-router-dom';
import { TextField, Button, Typography, Box } from '@mui/material';

export default function LoginPage() {
  const [username, setUsername] = useState('');
  const [password, setPassword] = useState('');
  const [error, setError] = useState('');
  const { login } = useAuth();
  const navigate = useNavigate();

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');
    try {
      await login({ username, password });
      navigate('/articles');
    } catch (err) {
      setError(err.message || 'Login failed');
    }
  };

  return (
    <Box sx={{ maxWidth: 400, mx: 'auto', mt: 8, p: 3 }}>
      <Typography variant="h4" gutterBottom>Вход</Typography>
      {error && <Typography color="error">{error}</Typography>}
      <form onSubmit={handleSubmit}>
        <TextField label="Логин" fullWidth margin="normal" required value={username} onChange={(e) => setUsername(e.target.value)} />
        <TextField label="Пароль" type="password" fullWidth margin="normal" required value={password} onChange={(e) => setPassword(e.target.value)} />
        <Button type="submit" variant="contained" fullWidth sx={{ mt: 2 }}>Войти</Button>
      </form>
      <Box sx={{ mt: 4, textAlign: 'center' }}>
        <Typography variant="body2">
          Нет аккаунта?{' '}
          <Button onClick={() => navigate('/auth/register')}>Регистрация</Button>
        </Typography>
      </Box>
    </Box>
    
  );
}
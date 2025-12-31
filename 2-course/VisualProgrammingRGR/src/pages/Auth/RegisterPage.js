// src/pages/Auth/RegisterPage.js
import { useState } from 'react';
import { Button, TextField, Typography, Box, CircularProgress,MenuItem } from '@mui/material';
import { useNavigate } from 'react-router-dom';
import apiClient from '../../api/client';

export default function RegisterPage() {
  const [formData, setFormData] = useState({
    username: '',
    email: '',
    password: '',
    fullName: '',
    biography: '',
    role: 0,
  });
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState('');
  const navigate = useNavigate();

  const handleChange = (e) => {
    const { name, value } = e.target;
    setFormData((prev) => ({
      ...prev,
      [name]: value
    }));
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);
    setError('');

    try {
      const response = await apiClient.post('/api/users/register', formData);
      console.log('Registration success:', response.data);
      navigate('/auth/login');
    } catch (err) {
      setError(err.response?.data?.message || 'Registration failed');
    } finally {
      setLoading(false);
    }
  };

  return (
    <Box sx={{ maxWidth: 400, mx: 'auto', mt: 8, p: 3 }}>
      <Typography variant="h4" gutterBottom align="center">
        Регистрация
      </Typography>

      {error && (
        <Typography color="error" align="center" sx={{ mb: 2 }}>
          {error}
        </Typography>
      )}

      <form onSubmit={handleSubmit}>
        <TextField
          label="Имя пользователя"
          name="username"
          value={formData.username}
          onChange={handleChange}
          fullWidth
          margin="normal"
          required
        />

        <TextField
          label="Email"
          name="email"
          type="email"
          value={formData.email}
          onChange={handleChange}
          fullWidth
          margin="normal"
          required
        />

        <TextField
          label="Полное имя"
          name="fullName"
          value={formData.fullName}
          onChange={handleChange}
          fullWidth
          margin="normal"
          required
        />

        <TextField
          label="Биография"
          name="biography"
          value={formData.biography}
          onChange={handleChange}
          fullWidth
          margin="normal"
          multiline
          rows={3}
          helperText="Краткая информация о себе"
        />

        <TextField
          label="Пароль"
          name="password"
          type="password"
          value={formData.password}
          onChange={handleChange}
          fullWidth
          margin="normal"
          required
        />

        <TextField
          select
          label="Role"
          name="role"
          value={formData.role}
          onChange={handleChange}
          fullWidth
          margin="normal"
          required
        >
          <MenuItem value={0}>Author</MenuItem>
          <MenuItem value={1}>Reviewer</MenuItem>
          <MenuItem value={2}>Administrator</MenuItem>
        </TextField>

        <Button
          type="submit"
          variant="contained"
          fullWidth
          disabled={loading}
          sx={{ mt: 2, height: 48 }}
        >
          {loading ? <CircularProgress size={24} /> : 'Зарегистрироваться'}
        </Button>
      </form>

      <Box sx={{ mt: 4, textAlign: 'center' }}>
        <Typography variant="body2">
          Уже есть аккаунт?{' '}
          <Button onClick={() => navigate('/auth/login')}>Войти</Button>
        </Typography>
      </Box>
    </Box>
  );
}
// src/api/client.js
import axios from 'axios';

const apiClient = axios.create({
  baseURL: process.env.REACT_APP_API_URL || 'http://localhost:5207',
});

// Добавляем интерцептор для обработки ошибок
apiClient.interceptors.response.use(
  response => response,
  error => {
    if (error.response?.status === 401) {
      // Обработка неавторизованных запросов
      console.error('Unauthorized request');
    }
    return Promise.reject(error);
  }
);

export const getCurrentUser = async () => {
  const response = await apiClient.get('/api/users/me');
  return response.data;
};

export default apiClient;
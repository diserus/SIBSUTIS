// src/context/AuthContext.js
import React, { useState, useEffect } from 'react';
import apiClient from '../api/client';

const AuthContext = React.createContext();

export const AuthProvider = ({ children }) => {
  const [user, setUser] = useState(null);
  const [isInitialized, setIsInitialized] = useState(false);

  useEffect(() => {
    const initializeAuth = async () => {
      const storedUser = localStorage.getItem('user');
      if (storedUser) {
        try {
          const parsedUser = JSON.parse(storedUser);
          // Можно добавить запрос к серверу для проверки актуальности данных
          setUser(parsedUser);
        } catch (error) {
          console.error('Error parsing user data:', error);
          localStorage.removeItem('user');
        }
      }
      setIsInitialized(true);
    };

    initializeAuth();
  }, []);

  const login = async (credentials) => {
    try {
      const response = await apiClient.post('/api/users/login', credentials);
      const userData = response.data;
      setUser(userData);
      localStorage.setItem('user', JSON.stringify(userData));
    } catch (error) {
      throw new Error('Invalid username or password');
    }
  };

  const register = async (userData) => {
    const response = await apiClient.post('/api/users/register', userData);
    return response.data;
  };

  const logout = () => {
    setUser(null);
    localStorage.removeItem('user');
  };

  const value = {
    user,
    isAuthenticated: !!user,
    isInitialized,
    login,
    register,
    logout,
  };

  return (
    <AuthContext.Provider value={value}>
      {children}
    </AuthContext.Provider>
  );
};

export const useAuth = () => React.useContext(AuthContext);
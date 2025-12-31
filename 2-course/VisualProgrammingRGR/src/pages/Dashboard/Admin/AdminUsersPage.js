// src/pages/Dashboard/Admin/AdminUsersPage.js
import { useState, useEffect } from 'react';
import {
  Table, TableBody, TableCell, TableContainer, TableHead,
  TableRow, Paper, Typography, Box, Chip, IconButton
} from '@mui/material';
import { Block, CheckCircle, Delete } from '@mui/icons-material';
import apiClient from '../../../api/client';
import { useAuth } from '../../../context/AuthContext';

export default function AdminUsersPage() {
  const { user } = useAuth();
  const [users, setUsers] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
  const fetchUsers = async () => {
    try {
      const response = await apiClient.get('/api/admin/users');

      // Логируем для проверки
      console.log('Raw users data:', response.data);

      // Фильтруем: исключаем пользователей с role === 2
      const filteredUsers = response.data.filter(u => Number(u.role) !== 2);

      // Преобразуем статусы и приводим к числу
      const mappedUsers = filteredUsers.map(u => ({
        ...u,
        statusLabel: Number(u.status) === 0 ? 'Active' : 'Blocked',
        status: Number(u.status),
        role: Number(u.role)
      }));

      setUsers(mappedUsers);
    } catch (error) {
      console.error('Error fetching users:', error);
    } finally {
      setLoading(false);
    }
  };

  fetchUsers();
}, []);

  const handleBlockUser = async (userId) => {
    try {
      await apiClient.post(`/api/admin/users/${userId}/block`);
      setUsers(users.map(u =>
        u.id === userId ? { ...u, status: 1, statusLabel: 'Blocked' } : u
      ));
    } catch (error) {
      console.error('Error blocking user:', error);
    }
  };

  const handleUnblockUser = async (userId) => {
    try {
      await apiClient.post(`/api/admin/users/${userId}/unblock`);
      setUsers(users.map(u =>
        u.id === userId ? { ...u, status: 0, statusLabel: 'Active' } : u
      ));
    } catch (error) {
      console.error('Error unblocking user:', error);
    }
  };

  const handleDeleteUser = async (userId) => {
    try {
      await apiClient.delete(`/api/admin/users/${userId}`);
      setUsers(users.filter(u => u.id !== userId));
    } catch (error) {
      console.error('Error deleting user:', error);
    }
  };

  if (loading) return <Typography>Loading...</Typography>;

  return (
    <Box sx={{ p: 3 }}>
      <Typography variant="h4" gutterBottom>User Management</Typography>

      <TableContainer component={Paper}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>Username</TableCell>
              <TableCell>Full Name</TableCell>
              <TableCell>Email</TableCell>
              <TableCell>Role</TableCell>
              <TableCell>Status</TableCell>
              <TableCell>Actions</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {users.map((user) => (
              <TableRow key={user.id}>
                <TableCell>{user.username}</TableCell>
                <TableCell>{user.fullName}</TableCell>
                <TableCell>{user.email}</TableCell>
                <TableCell>{user.role}</TableCell>
                <TableCell>
                  <Chip
                    label={user.statusLabel}
                    color={user.status === 0 ? 'success' : 'error'}
                    size="small"
                  />
                </TableCell>
                <TableCell>
                  {user.status === 0 ? (
                    <IconButton
                      color="error"
                      onClick={() => handleBlockUser(user.id)}
                      title="Block User"
                    >
                      <Block />
                    </IconButton>
                  ) : (
                    <IconButton
                      color="success"
                      onClick={() => handleUnblockUser(user.id)}
                      title="Unblock User"
                    >
                      <CheckCircle />
                    </IconButton>
                  )}
                  <IconButton
                    color="error"
                    onClick={() => handleDeleteUser(user.id)}
                    title="Delete User"
                  >
                    <Delete />
                  </IconButton>
                </TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </Box>
  );
}
import { useState, useEffect } from 'react';
import {
  Table, TableBody, TableCell, TableContainer, TableHead,
  TableRow, Paper, Typography, Button
} from '@mui/material';
import { useAuth } from '../../../context/AuthContext';
import apiClient from '../../../api/client';
import { Link as RouterLink } from 'react-router-dom';

export default function ArticlesPage() {
  const { user, isAuthenticated } = useAuth();
  const [articles, setArticles] = useState([]);

  useEffect(() => {
    if (!isAuthenticated || !user?.id) return;

    const fetchArticles = async () => {
      try {
        const response = await apiClient.get(`/api/articles/author/${user.id}`);
        setArticles(response.data);
      } catch (error) {
        console.error('Ошибка загрузки статей:', error);
        alert('Ошибка загрузки статей. Пожалуйста, попробуйте позже.');
      }
    };

    fetchArticles();
  }, [isAuthenticated, user?.id]);

  if (!isAuthenticated) {
    return <Typography color="error">You need to log in to view this page.</Typography>;
  }

  const fixDateFormat = (dateString) => {
    return dateString.replace(/^(\d{4}-\d{2}-\d{2})(\d{2}:\d{2}:\d{2}\.\d+)$/, '$1T$2');
  };

  return (
    <div>
      <Typography variant="h4" gutterBottom>My Articles</Typography>
      <Button
        variant="contained"
        component={RouterLink}
        to="/submit-article"
        sx={{ mb: 3 }}
      >
        Submit New Article
      </Button>
      <TableContainer component={Paper}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>Title</TableCell>
              <TableCell>Status</TableCell>
              <TableCell>Date</TableCell>
              <TableCell>Actions</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {articles && articles.length > 0 ? (
              articles.map((article) => (
                <TableRow key={article.id}>
                  <TableCell>{article.title || 'Без названия'}</TableCell>
                  <TableCell>{article.status || 'Pending'}</TableCell>
                  <TableCell>
                    {article.submittedAt 
                      ? new Date(fixDateFormat(article.submittedAt)).toLocaleString('ru-RU', {
                          year: 'numeric',
                          month: 'numeric',
                          day: 'numeric',
                          hour: '2-digit',
                          minute: '2-digit'
                        }) 
                      : 'Дата не указана'}
                  </TableCell>
                  <TableCell>
                    <Button 
                      component={RouterLink} 
                      to={`/articles/${article.id}`}
                      variant="outlined"
                      size="small"
                    >
                      View
                    </Button>
                  </TableCell>
                </TableRow>
              ))
            ) : (
              <TableRow>
                <TableCell colSpan={4} align="center">
                  No articles found
                </TableCell>
              </TableRow>
            )}
          </TableBody>
        </Table>
      </TableContainer>
    </div>
  );
}
// src/pages/Dashboard/Admin/AdminArticlesPage.js
import { useState, useEffect } from 'react';
import {
  Table, TableBody, TableCell, TableContainer, TableHead,
  TableRow, Paper, Typography, Button, Box, IconButton
} from '@mui/material';
import { Delete } from '@mui/icons-material';
import apiClient from '../../../api/client';
import { ArticleStatusBadge } from '../../../components/ArticleStatusBadge';

export default function AdminArticlesPage() {
  const [articles, setArticles] = useState([]);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchArticles = async () => {
      try {
        const response = await apiClient.get('/api/admin/articles');
        setArticles(response.data);
      } catch (error) {
        console.error('Error fetching articles:', error);
      } finally {
        setLoading(false);
      }
    };

    fetchArticles();
  }, []);

  const handleDeleteArticle = async (articleId) => {
    try {
      await apiClient.delete(`/api/admin/articles/${articleId}`);
      setArticles(articles.filter(a => a.id !== articleId));
    } catch (error) {
      console.error('Error deleting article:', error);
    }
  };

  if (loading) return <Typography>Loading...</Typography>;

  return (
    <Box sx={{ p: 3 }}>
      <Typography variant="h4" gutterBottom>Article Management</Typography>
      
      <TableContainer component={Paper}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>Title</TableCell>
              <TableCell>Status</TableCell>
              <TableCell>Submitted At</TableCell>
              <TableCell>Actions</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {articles.map((article) => (
              <TableRow key={article.id}>
                <TableCell>{article.title}</TableCell>
                <TableCell>
                  <ArticleStatusBadge status={article.status} />
                </TableCell>
                <TableCell>
                  {new Date(article.submittedAt).toLocaleString()}
                </TableCell>
                <TableCell>
                  <IconButton 
                    color="error" 
                    onClick={() => handleDeleteArticle(article.id)}
                    title="Delete Article"
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
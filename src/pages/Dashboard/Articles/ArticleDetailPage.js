import { useState, useEffect } from 'react';
import { useParams } from 'react-router-dom';
import { Typography, Paper, Button, Box, CardMedia } from '@mui/material';
import { Link } from 'react-router-dom';
import apiClient from '../../../api/client';

export default function ArticleDetailPage() {
  const { id } = useParams();
  const [article, setArticle] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchArticle = async () => {
      try {
        const response = await apiClient.get(`/api/articles/${id}`);
        setArticle(response.data);
      } catch (err) {
        setError('Не удалось загрузить статью');
        console.error('Ошибка загрузки статьи:', err);
      } finally {
        setLoading(false);
      }
    };

    fetchArticle();
  }, [id]);

  if (loading) return <Typography>Загрузка...</Typography>;
  if (error) return <Typography color="error">{error}</Typography>;
  if (!article) return <Typography>Статья не найдена</Typography>;

  const imageUrl = article.imagePath 
    ? `${apiClient.defaults.baseURL}/${article.imagePath.replace(/\\/g, '/')}`
    : null;

  return (
    <Box sx={{ p: 3, maxWidth: 800, mx: 'auto' }}>
      <Typography variant="h4" gutterBottom>{article.title}</Typography>
      
      {imageUrl && (
        <Box sx={{ 
          display: 'flex', 
          justifyContent: 'center',
          mb: 3,
          borderRadius: 2,
          overflow: 'hidden',
          boxShadow: 3
        }}>
          <CardMedia
            component="img"
            sx={{ 
              maxHeight: '60vh',
              width: 'auto',
              maxWidth: '100%',
              objectFit: 'contain'
            }}
            image={imageUrl}
            alt="Изображение статьи"
          />
        </Box>
      )}

      <Paper sx={{ p: 3, mb: 3 }}>
        <Typography paragraph>{article.abstract}</Typography>
      </Paper>

      <Button 
        variant="contained" 
        component={Link} 
        to="/articles"
        sx={{ mt: 2 }}
      >
        Назад к списку статей
      </Button>
    </Box>
  );
}
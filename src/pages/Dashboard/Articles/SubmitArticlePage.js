import { useState } from 'react';
import { TextField, Button, Typography, Box, Checkbox, FormControlLabel } from '@mui/material';
import { useAuth } from '../../../context/AuthContext';
import apiClient from '../../../api/client';

export default function SubmitArticlePage() {
  const { user } = useAuth();
  const [article, setArticle] = useState({
    title: '',
    abstract: '',
    fileFormat: '',
    tags: '',
    isOriginal: false,
    category: 'technology'
  });
  const [isSubmitting, setIsSubmitting] = useState(false);
const [image, setImage] = useState(null);
const handleSubmit = async (e) => {
  e.preventDefault();

  if (!article.isOriginal) {
    alert('Подтвердите оригинальность работы');
    return;
  }

  setIsSubmitting(true);

   try {
    const formData = new FormData();
    formData.append('Title', article.title.trim());
    formData.append('Abstract', article.abstract.trim()); 
    formData.append('FileFormat', 'pdf'); 
    formData.append('Image', image); 

    const response = await apiClient.post(`/api/articles?authorId=${user.id}`, formData, {
      headers: {
        'Content-Type': 'multipart/form-data'
      }
    });

    if ([200, 201].includes(response.status)) {
      alert('Статья успешно отправлена!');
      setArticle({
        title: '',
        abstract: '',
        fileFormat: '',
        tags: '',
        isOriginal: false,
        category: 'technology'
      });
      setImage(null); // Сброс состояния файла
    } else {
      alert(`Ошибка сервера: ${response.status}`);
    }
  } catch (error) {
    console.error('Полная ошибка:', error);
    if (error.response?.data) {
      alert("Ошибка сервера:\n" + error.response.data);
    } else {
      alert("Произошла неизвестная ошибка.");
    }
  } finally {
    setIsSubmitting(false);
  }
};


  return (
    <Box component="form" onSubmit={handleSubmit} sx={{ maxWidth: 800, mx: 'auto', p: 3 }}>
      <Typography variant="h4" gutterBottom>Submit Article</Typography>
      
      <TextField
        label="Enter article title"
        fullWidth
        margin="normal"
        required
        value={article.title}
        onChange={(e) => setArticle({...article, title: e.target.value})}
      />
      
      <TextField
        select
        label="Category"
        fullWidth
        margin="normal"
        SelectProps={{ native: true }}
        value={article.category}
        onChange={(e) => setArticle({...article, category: e.target.value})}
      >
        <option value="technology">Technology</option>
        <option value="science">Science</option>
        <option value="health">Health</option>
      </TextField>
      
      <TextField
        label="Write your article content here"
        fullWidth
        margin="normal"
        multiline
        rows={10}
        required
        value={article.abstract}
        onChange={(e) => setArticle({...article, abstract: e.target.value})}
      />
      
      <Box sx={{ my: 2 }}>
  <Typography variant="subtitle1">Featured Image:</Typography>
  <input 
    type="file" 
    accept="image/*" 
    onChange={(e) => setImage(e.target.files[0])} 
  />
</Box>
      
      <TextField
        label="Enter tags separated by commas"
        fullWidth
        margin="normal"
        value={article.tags}
        onChange={(e) => setArticle({...article, tags: e.target.value})}
      />
      
      <FormControlLabel
        control={
          <Checkbox 
            checked={article.isOriginal} 
            onChange={(e) => setArticle({...article, isOriginal: e.target.checked})} 
          />
        }
        label="I confirm that this article is my original work and I have read and agree to submission guidelines"
      />
      
      <Box sx={{ mt: 3 }}>
        <Button 
          type="submit" 
          variant="contained" 
          disabled={isSubmitting || !article.isOriginal}
          sx={{ mr: 2 }}
        >
          {isSubmitting ? 'Submitting...' : 'Submit for Review'}
        </Button>
        <Button 
          onClick={() => {
            setArticle({
              title: '',
              abstract: '',
              fileFormat: '',
              tags: '',
              isOriginal: false,
              category: 'technology'
            });
          }}
          sx={{ mr: 2 }}
        >
          Cancel
        </Button>
      </Box>
    </Box>
  );
}
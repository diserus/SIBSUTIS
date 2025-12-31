import { useState, useEffect } from 'react';
import { Table, TableBody, TableCell, TableContainer, TableHead, TableRow, Paper, Typography, Avatar, Box } from '@mui/material';
import apiClient from '../../../api/client';
import { useAuth } from '../../../context/AuthContext';

const statusMap = {
  0: 'Pending Review',
  1: 'In Progress',
  2: 'Reviewed'
};

export default function ReviewsPage() {
  const { user } = useAuth();
  const [reviews, setReviews] = useState([]);

  useEffect(() => {
    const fetchReviews = async () => {
      try {
        const response = await apiClient.get(`/api/reviews/reviewer/${user.id}`);
        setReviews(response.data);
      } catch (error) {
        console.error('Error fetching reviews:', error);
      }
    };
    fetchReviews();
  }, [user.id]);

  return (
    <div>
      <Typography variant="h4" gutterBottom>Review Articles</Typography>
      
      <TableContainer component={Paper}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>Reviewer</TableCell>
              <TableCell>Article Title</TableCell>
              <TableCell>Review Date</TableCell>
              <TableCell>Category</TableCell>
              <TableCell>Status</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {reviews.map((review) => (
              <TableRow key={review.id}>
                <TableCell>
                  <Box sx={{ display: 'flex', alignItems: 'center' }}>
                    <Avatar sx={{ mr: 2 }} />
                    {review.reviewer?.fullName}
                  </Box>
                </TableCell>
                <TableCell>{review.article?.title}</TableCell>
                <TableCell>{new Date(review.createdAt).toLocaleDateString()}</TableCell>
                <TableCell>{review.article?.category}</TableCell>
                <TableCell>{statusMap[review.status]}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </div>
  );
}
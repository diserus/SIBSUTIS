import { Typography, Box, Button } from '@mui/material';
import { Link } from 'react-router-dom';

export default function NotFoundPage() {
  return (
    <Box sx={{ textAlign: 'center', mt: 8 }}>
      <Typography variant="h4" gutterBottom>
        Page Not Found
      </Typography>
      <Button component={Link} to="/articles" variant="contained">
        Go to Home
      </Button>
    </Box>
  );
}
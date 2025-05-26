import { useState, useEffect } from 'react';
import { TextField, Button, Typography, Box, Avatar } from '@mui/material';
import apiClient from '../../../api/client';
import { useAuth } from '../../../context/AuthContext';

export default function ProfilePage() {
  const { user } = useAuth();
  const [profile, setProfile] = useState({
    fullName: '',
    email: '',
    biography: '',
    specialization: ''
  });
  const [isEditing, setIsEditing] = useState(false);

  useEffect(() => {
    const fetchProfile = async () => {
      try {
        const response = await apiClient.get(`/api/users/me/${user.id}`);
        setProfile(response.data);
      } catch (error) {
        console.error('Error fetching profile:', error);
      }
    };
    fetchProfile();
  }, [user.id]);

  const handleSave = async () => {
    try {
      await apiClient.put(`/api/users/${user.id}`, profile);
      setIsEditing(false);
    } catch (error) {
      console.error('Error updating profile:', error);
    }
  };

  return (
    <Box sx={{ maxWidth: 800, mx: 'auto', p: 3 }}>
      <Box sx={{ display: 'flex', alignItems: 'center', mb: 4 }}>
        <Avatar sx={{ width: 80, height: 80, mr: 3 }} />
        <Typography variant="h5">{profile.fullName}</Typography>
      </Box>

      <TextField
        label="Full Name"
        fullWidth
        margin="normal"
        value={profile.fullName}
        onChange={(e) => setProfile({...profile, fullName: e.target.value})}
        disabled={!isEditing}
      />
      
      <TextField
        label="Email"
        fullWidth
        margin="normal"
        value={profile.email}
        disabled={!isEditing}
      />
    
      
      <TextField
        label="Bio"
        fullWidth
        margin="normal"
        multiline
        rows={4}
        value={profile.biography}
        onChange={(e) => setProfile({...profile, biography: e.target.value})}
        disabled={!isEditing}
      />

      <Box sx={{ mt: 3 }}>
        {isEditing ? (
          <>
            <Button variant="contained" onClick={handleSave} sx={{ mr: 2 }}>
              Save Changes
            </Button>
            <Button variant="outlined" onClick={() => setIsEditing(false)}>
              Cancel
            </Button>
          </>
        ) : (
          <Button variant="contained" onClick={() => setIsEditing(true)}>
            Edit Profile
          </Button>
        )}
      </Box>
    </Box>
  );
}
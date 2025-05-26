import { AppBar, Toolbar, Typography, Button, Box, Link, Avatar, styled } from '@mui/material';
import { Outlet, useLocation } from 'react-router-dom';
import { useAuth } from '../../context/AuthContext';
import { Link as RouterLink } from 'react-router-dom';

const StyledLink = styled(Link)(({ theme, isactive }) => ({
  color: 'inherit',
  textDecoration: 'none',
  '&:hover': {
    textDecoration: 'underline',
  },
  ...(isactive === 'true' && {
    textDecoration: 'underline',
    textUnderlineOffset: '4px',
  }),
}));

export default function DashboardLayout() {
  const { user, logout } = useAuth();
  const location = useLocation();

  return (
    <div>
      <AppBar position="static">
        <Toolbar sx={{ display: 'flex', flexDirection: 'column', alignItems: 'flex-start', py: 2 }}>
          <Box sx={{ 
            display: 'flex', 
            alignItems: 'center', 
            width: '100%',
            mb: 2,
          }}>
            <Avatar sx={{ width: 80, height: 80, mr: 2 }} />
            <Typography variant="h5">{user?.fullName}</Typography>
          </Box>
          
          <Box sx={{ 
            display: 'flex', 
            gap: 4,
            width: '100%',
            pt: 2,
          }}>
            {user?.role !== 2 && (
              <>
                <StyledLink 
                  component={RouterLink} 
                  to="/profile" 
                  isactive={(location.pathname === '/profile').toString()}
                >
                  Profile
                </StyledLink>
                <StyledLink 
                  component={RouterLink} 
                  to="/articles" 
                  isactive={(location.pathname === '/articles').toString()}
                >
                  My Articles
                </StyledLink>
                <StyledLink 
                  component={RouterLink} 
                  to="/submit-article" 
                  isactive={(location.pathname === '/submit-article').toString()}
                >
                  Submit Article
                </StyledLink>
                <StyledLink 
                  component={RouterLink} 
                  to="/reviews" 
                  isactive={(location.pathname === '/reviews').toString()}
                >
                  Review Articles
                </StyledLink>
              </>
            )}
            
            {user?.role === 2 && (
              <>
                <StyledLink 
                  component={RouterLink} 
                  to="/admin/users" 
                  isactive={(location.pathname === '/admin/users').toString()}
                >
                  Manage Users
                </StyledLink>
                <StyledLink 
                  component={RouterLink} 
                  to="/admin/articles" 
                  isactive={(location.pathname === '/admin/articles').toString()}
                >
                  Manage Articles
                </StyledLink>
              </>
            )}

            <Box sx={{ flexGrow: 1 }} />
            <Button color="inherit" onClick={logout}>
              Logout
            </Button>
          </Box>
        </Toolbar>
      </AppBar>
      <Box sx={{ p: 3 }}>
        <Outlet />
      </Box>
    </div>
  );
}
import React from 'react';
import { BrowserRouter as Router, Routes, Route, NavLink, Navigate } from 'react-router-dom';
import CommentsPage from './pages/CommentsPage';
import PostsPage from './pages/PostsPage';
import AlbumsPage from './pages/AlbumsPage';
import TodosPage from './pages/TodosPage';
import UsersPage from './pages/UsersPage';
import './App.css'; // сюда можешь запихать стили для боковой панели

const App = () => {
  return (
    <Router>
      <div style={{ display: 'flex', height: '100vh' }}>
        {/* Боковая панель */}
        <nav
          style={{
            width: '200px',
            padding: '20px',
            background: '#f0f0f0',
            borderRight: '1px solid #ddd',
          }}
        >
          <h3>Навигация</h3>
          <ul style={{ listStyle: 'none', padding: 0 }}>
            <li><NavLink to="/comments">Comments</NavLink></li>
            <li><NavLink to="/posts">Posts</NavLink></li>
            <li><NavLink to="/albums">Albums</NavLink></li>
            <li><NavLink to="/todos">Todos</NavLink></li>
            <li><NavLink to="/users">Users</NavLink></li>
          </ul>
        </nav>

        {/* Основной контент */}
        <main style={{ flex: 1, padding: '20px' }}>
          <Routes>
            <Route path="/" element={<Navigate to="/comments" />} />
            <Route path="/comments" element={<CommentsPage />} />
            <Route path="/posts" element={<PostsPage />} />
            <Route path="/albums" element={<AlbumsPage />} />
            <Route path="/todos" element={<TodosPage />} />
            <Route path="/users" element={<UsersPage />} />
          </Routes>
        </main>
      </div>
    </Router>
  );
};

export default App;

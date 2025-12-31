import React from 'react';
import { NavLink } from 'react-router-dom';

const Navigation = () => {
  return (
    <nav style={{ width: '200px', borderRight: '1px solid #ccc', padding: '20px' }}>
      <ul style={{ listStyle: 'none', padding: 0 }}>
        <li><NavLink to="/">Comments</NavLink></li>
        <li><NavLink to="/posts">Posts</NavLink></li>
        <li><NavLink to="/albums">Albums</NavLink></li>
        <li><NavLink to="/todos">Todos</NavLink></li>
        <li><NavLink to="/users">Users</NavLink></li>
      </ul>
    </nav>
  );
};

export default Navigation;

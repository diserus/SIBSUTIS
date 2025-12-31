import React from 'react';

const BookCard = ({ title, authors, coverImage }) => {
  return (
    <div style={styles.card}>
      {coverImage && <img src={coverImage} alt={title} style={styles.cover} />}
      <h2 style={styles.title}>{title}</h2>
      <p style={styles.authors}>{authors.join(', ')}</p>
    </div>
  );
};

const styles = {
  card: {
    width: '200px',
    margin: '10px',
    padding: '10px',
    border: '1px solid #ccc',
    borderRadius: '5px',
    textAlign: 'center',
  },
  cover: {
    width: '100%',
    height: 'auto',
    borderRadius: '5px',
  },
  title: {
    fontSize: '18px',
    margin: '10px 0',
  },
  authors: {
    fontSize: '14px',
    color: '#555',
  },
};

export default BookCard;
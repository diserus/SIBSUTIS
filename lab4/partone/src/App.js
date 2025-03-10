import React, { useEffect, useState } from 'react';
import BookCard from './BookCard';

const App = () => {
  const [books, setBooks] = useState([]);

  useEffect(() => {
    // Загрузка данных о книгах
    fetch('https://fakeapi.extendsclass.com/books')
      .then(response => response.json())
      .then(data => {
        const booksWithCovers = data.map(book => ({
          ...book,
          coverImage: null, // Пока что изображение отсутствует
        }));
        setBooks(booksWithCovers);

        // Загрузка обложек для каждой книги
        booksWithCovers.forEach((book, index) => {
          fetch(`https://www.googleapis.com/books/v1/volumes?q=isbn:${book.isbn}`)
            .then(response => response.json())
            .then(googleData => {
              if (googleData.items && googleData.items[0].volumeInfo.imageLinks) {
                const coverImage = googleData.items[0].volumeInfo.imageLinks.thumbnail;
                setBooks(prevBooks => {
                  const newBooks = [...prevBooks];
                  newBooks[index].coverImage = coverImage;
                  return newBooks;
                });
              }
            });
        });
      });
  }, []);

  return (
    <div style={styles.container}>
      {books.map(book => (
        <BookCard
          key={book.id}
          title={book.title}
          authors={book.authors}
          coverImage={book.coverImage}
        />
      ))}
    </div>
  );
};

const styles = {
  container: {
    display: 'flex',
    flexWrap: 'wrap',
    justifyContent: 'center',
    padding: '20px',
  },
};

export default App;
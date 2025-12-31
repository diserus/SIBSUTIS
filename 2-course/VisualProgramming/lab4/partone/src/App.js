import React, { useEffect, useState } from 'react';
import BookCard from './BookCard';
import SearchAndSortControls from './SearchAndSortControls';

const App = () => {
  const [books, setBooks] = useState([]);
  const [searchQuery, setSearchQuery] = useState('');
  const [sortField, setSortField] = useState('title');
  const [sortOrder, setSortOrder] = useState('asc');

  useEffect(() => {
    fetch('https://fakeapi.extendsclass.com/books')
      .then(response => response.json())
      .then(data => {
        const booksWithCovers = data.map(book => ({
          ...book,
          coverImage: null,
        }));
        setBooks(booksWithCovers);

        booksWithCovers.forEach((book, index) => {
          fetch(`https://www.googleapis.com/books/v1/volumes?q=isbn:${book.isbn}`)
            .then(response => response.json())
            .then(googleData => {
              if (googleData.items?.[0]?.volumeInfo?.imageLinks?.thumbnail) {
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

  // Фильтрация книг
  const filteredBooks = books.filter(book => {
    const query = searchQuery.toLowerCase();
    const titleMatch = book.title.toLowerCase().includes(query);
    const authorsMatch = book.authors.join(', ').toLowerCase().includes(query);
    return titleMatch || authorsMatch;
  });

  // Сортировка книг
  const sortedBooks = [...filteredBooks].sort((a, b) => {
    let valueA, valueB;
    if (sortField === 'title') {
      valueA = a.title;
      valueB = b.title;
    } else {
      valueA = a.authors.join(', ');
      valueB = b.authors.join(', ');
    }
    const compareResult = valueA.localeCompare(valueB);
    return sortOrder === 'asc' ? compareResult : -compareResult;
  });

  return (
    <div>
      <SearchAndSortControls
        searchQuery={searchQuery}
        onSearchChange={(e) => setSearchQuery(e.target.value)}
        sortField={sortField}
        onSortFieldChange={(e) => setSortField(e.target.value)}
        sortOrder={sortOrder}
        onSortOrderChange={(e) => setSortOrder(e.target.value)}
      />
      <div style={styles.container}>
        {sortedBooks.map(book => (
          <BookCard
            key={book.id}
            title={book.title}
            authors={book.authors}
            coverImage={book.coverImage}
          />
        ))}
      </div>
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
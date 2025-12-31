import React from 'react';

const SearchAndSortControls = ({
  searchQuery,
  onSearchChange,
  sortField,
  onSortFieldChange,
  sortOrder,
  onSortOrderChange,
}) => {
  return (
    <div style={styles.container}>
      <input
        type="text"
        placeholder="Поиск по названию или автору"
        value={searchQuery}
        onChange={onSearchChange}
        style={styles.searchInput}
      />
      <div style={styles.sortContainer}>
        <select value={sortField} onChange={onSortFieldChange} style={styles.select}>
          <option value="title">Сортировать по названию</option>
          <option value="authors">Сортировать по автору</option>
        </select>
        <select value={sortOrder} onChange={onSortOrderChange} style={styles.select}>
          <option value="asc">По возрастанию</option>
          <option value="desc">По убыванию</option>
        </select>
      </div>
    </div>
  );
};

const styles = {
  container: {
    padding: '20px',
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
    gap: '10px',
  },
  searchInput: {
    width: '300px',
    padding: '8px',
    borderRadius: '5px',
    border: '1px solid #ccc',
  },
  sortContainer: {
    display: 'flex',
    gap: '10px',
  },
  select: {
    padding: '8px',
    borderRadius: '5px',
    border: '1px solid #ccc',
  },
};

export default SearchAndSortControls;
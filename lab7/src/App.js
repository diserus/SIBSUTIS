import React, { useState, useEffect, useOptimistic } from 'react';
import DataSet from '../src/DataSet';

const API_URL = 'https://jsonplaceholder.typicode.com/comments';

const App = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [selectedRows, setSelectedRows] = useState(new Set()); // Добавляем состояние для выбранных строк
  const [optimisticData, addOptimisticData] = useOptimistic(data);

  const headers = [
    { key: 'id', label: 'ID' },
    { key: 'name', label: 'Name' },
    { key: 'email', label: 'Email' },
    { key: 'body', label: 'Body' },
  ];

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await fetch(API_URL);
        if (!response.ok) throw new Error('Network response was not ok');
        const jsonData = await response.json();
        setData(jsonData);
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    };

    fetchData();
  }, []);

  const handleRowSelect = (selectedRows) => {
    setSelectedRows(new Set(selectedRows.map((_, index) => index)));
    console.log('Selected rows:', selectedRows);
  };

  const handleAdd = async (newItem) => {
    const tempId = Date.now(); // Временный ID для оптимистичного обновления
    
    try {
      // Оптимистичное обновление
      addOptimisticData([...data, { ...newItem, id: tempId }]);
      
      const response = await fetch(API_URL, {
        method: 'POST',
        body: JSON.stringify(newItem),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });
      
      if (!response.ok) throw new Error('Failed to add item');
      
      const createdItem = await response.json();
      
      // Заменяем временный ID на реальный
      setData(prevData => prevData.map(item => item.id === tempId ? createdItem : item));
    } catch (err) {
      console.error('Error adding item:', err);
      // Откатываем изменения в случае ошибки
      setData(data);
    }
  };

  const handleDelete = async (itemsToDelete) => {
    const deletedIds = itemsToDelete.map(item => item.id);
    
    try {
      // Оптимистичное обновление
      setData(prevData => prevData.filter(item => !deletedIds.includes(item.id)));
      setSelectedRows(new Set()); // Очищаем выделение после удаления
      
      // Отправляем запросы на удаление для каждого элемента
      await Promise.all(
        itemsToDelete.map(item =>
          fetch(`${API_URL}/${item.id}`, {
            method: 'DELETE',
          })
        )
      );
    } catch (err) {
      console.error('Error deleting items:', err);
      // Откатываем изменения в случае ошибки
      setData(data);
    }
  };

  const handleUpdate = async (updatedItem) => {
    const originalItem = data.find(item => item.id === updatedItem.id);
    
    try {
      // Оптимистичное обновление
      setData(prevData =>
        prevData.map(item => (item.id === updatedItem.id ? updatedItem : item))
      );
      
      const response = await fetch(`${API_URL}/${updatedItem.id}`, {
        method: 'PATCH',
        body: JSON.stringify(updatedItem),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });
      
      if (!response.ok) throw new Error('Failed to update item');
    } catch (err) {
      console.error('Error updating item:', err);
      // Откатываем изменения в случае ошибки
      setData(prevData =>
        prevData.map(item => (item.id === updatedItem.id ? originalItem : item))
      );
    }
  };

  const handleAddNew = () => {
    const newItem = {
      name: 'New Comment',
      email: 'new@example.com',
      body: 'This is a new comment',
    };
    handleAdd(newItem);
  };

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div>
      <div style={{ marginBottom: '20px' }}>
        <button onClick={handleAddNew}>Add New Comment</button>
        <button 
          onClick={() => handleDelete(
            Array.from(selectedRows).map(index => optimisticData[index])
          )}
          disabled={selectedRows.size === 0}
        >
          Delete Selected
        </button>
      </div>
      
      <DataSet 
        data={optimisticData}
        headers={headers}
        onRowSelect={handleRowSelect}
        onUpdate={handleUpdate}
        renderCell={(value, row, colIndex) => {
          if (colIndex === 1) { // Name column
            return <strong>{value}</strong>;
          }
          if (colIndex === 3) { // Body column
            return <div style={{ maxWidth: '300px', whiteSpace: 'pre-wrap' }}>{value}</div>;
          }
          return value;
        }}
      />
    </div>
  );
};

export default App;
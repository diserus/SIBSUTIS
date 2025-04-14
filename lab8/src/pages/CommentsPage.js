// pages/CommentsPage.jsx
import React, { useState, useEffect, useOptimistic } from 'react';
import DataSet from '../components/DataSet';

const API_URL = 'https://jsonplaceholder.typicode.com/comments';

const CommentsPage = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);
  const [selectedRows, setSelectedRows] = useState(new Set());
  const [showAddForm, setShowAddForm] = useState(false);
  const [newItem, setNewItem] = useState({
    name: '',
    email: '',
    body: '',
  });

  const [optimisticData, addOptimisticData] = useOptimistic(
    data,
    (currentData, newItem) => [...currentData, newItem]
  );

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

  const handleRowSelect = (selectedItems) => {
    setSelectedRows(new Set(selectedItems));
  };

  const handleAdd = async () => {
    const tempId = Date.now();
    const itemToAdd = { ...newItem, id: tempId };

    try {
      addOptimisticData(itemToAdd);
      setData((prev) => [...prev, itemToAdd]);

      const response = await fetch(API_URL, {
        method: 'POST',
        body: JSON.stringify(newItem),
        headers: {
          'Content-type': 'application/json; charset=UTF-8',
        },
      });

      if (!response.ok) throw new Error('Failed to add item');

      const createdItem = await response.json();

      setData((prevData) =>
        prevData.map((item) => (item.id === tempId ? createdItem : item))
      );

      setNewItem({ name: '', email: '', body: '' });
      setShowAddForm(false);
    } catch (err) {
      console.error('Error adding item:', err);
      setData((prevData) => prevData.filter((item) => item.id !== tempId));
    }
  };

  const handleUpdate = async (updatedItem) => {
    const originalItem = data.find((item) => item.id === updatedItem.id);
    try {
      setData((prevData) =>
        prevData.map((item) => (item.id === updatedItem.id ? updatedItem : item))
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
      setData((prevData) =>
        prevData.map((item) => (item.id === updatedItem.id ? originalItem : item))
      );
    }
  };

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setNewItem((prev) => ({ ...prev, [name]: value }));
  };

  if (loading) return <div>Loading...</div>;
  if (error) return <div>Error: {error}</div>;

  return (
    <div>
      <div style={{ marginBottom: '20px' }}>
        <button onClick={() => setShowAddForm(!showAddForm)}>
          {showAddForm ? 'Cancel' : 'Add New Comment'}
        </button>
      </div>

      {showAddForm && (
        <div
          style={{
            marginBottom: '20px',
            padding: '10px',
            border: '1px solid #ccc',
            borderRadius: '4px',
          }}
        >
          <h3>Add New Comment</h3>
          <div style={{ marginBottom: '10px' }}>
            <label>Name: </label>
            <input
              type="text"
              name="name"
              value={newItem.name}
              onChange={handleInputChange}
              style={{ width: '100%', padding: '8px' }}
            />
          </div>
          <div style={{ marginBottom: '10px' }}>
            <label>Email: </label>
            <input
              type="email"
              name="email"
              value={newItem.email}
              onChange={handleInputChange}
              style={{ width: '100%', padding: '8px' }}
            />
          </div>
          <div style={{ marginBottom: '10px' }}>
            <label>Body: </label>
            <textarea
              name="body"
              value={newItem.body}
              onChange={handleInputChange}
              style={{ width: '100%', padding: '8px', minHeight: '100px' }}
            />
          </div>
          <button
            onClick={handleAdd}
            disabled={!newItem.name || !newItem.email || !newItem.body}
          >
            Submit
          </button>
        </div>
      )}

      <DataSet
        data={optimisticData}
        headers={headers}
        onRowSelect={handleRowSelect}
        onUpdate={handleUpdate}
        renderCell={(value, row, colIndex) => {
          if (colIndex === 1) return <strong>{value}</strong>;
          if (colIndex === 3)
            return <div style={{ maxWidth: '300px', whiteSpace: 'pre-wrap' }}>{value}</div>;
          return value;
        }}
      />
    </div>
  );
};

export default CommentsPage;

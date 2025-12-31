// UsersPage.jsx
import React, { useEffect, useState } from 'react';
import DataSet from '../components/DataSet';
import AddForm from '../components/AddForm';
import * as Yup from 'yup';

const API_URL = 'https://jsonplaceholder.typicode.com/users';

const UsersPage = () => {
  const [data, setData] = useState([]);
  const [selectedRows, setSelectedRows] = useState(new Set());

  useEffect(() => {
    fetch(API_URL)
      .then(res => res.json())
      .then(setData)
      .catch(console.error);
  }, []);

  const handleAdd = async (values, { resetForm }) => {
    const response = await fetch(API_URL, {
      method: 'POST',
      body: JSON.stringify(values),
      headers: { 'Content-type': 'application/json; charset=UTF-8' },
    });
    const created = await response.json();
    setData(prev => [...prev, created]);
    resetForm();
  };

  const handleUpdate = (updatedItem) => {
    setData(prev =>
      prev.map((item) => (item.id === updatedItem.id ? updatedItem : item))
    );
  };

  return (
    <div>
      <h2>Users</h2>
      <AddForm
        initialValues={{ name: '', username: '', email: '' }}
        validationSchema={Yup.object({
          name: Yup.string().required('Required'),
          username: Yup.string().required('Required'),
          email: Yup.string().email('Invalid email').required('Required'),
        })}
        onSubmit={handleAdd}
        fields={[
          { name: 'name', label: 'Name' },
          { name: 'username', label: 'Username' },
          { name: 'email', label: 'Email' },
        ]}
      />

      <DataSet
        data={data}
        headers={[
          { key: 'id', label: 'ID' },
          { key: 'name', label: 'Name' },
          { key: 'username', label: 'Username' },
          { key: 'email', label: 'Email' },
        ]}
        onRowSelect={(items) => setSelectedRows(new Set(items))}
        onUpdate={handleUpdate}
      />
    </div>
  );
};

export default UsersPage;

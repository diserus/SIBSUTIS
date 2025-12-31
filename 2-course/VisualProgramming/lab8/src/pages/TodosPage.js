// TodosPage.jsx
import React, { useEffect, useState } from 'react';
import DataSet from '../components/DataSet';
import AddForm from '../components/AddForm';
import * as Yup from 'yup';

const API_URL = 'https://jsonplaceholder.typicode.com/todos';

const TodosPage = () => {
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
      <h2>Todos</h2>
      <AddForm
        initialValues={{ title: '', userId: '', completed: false }}
        validationSchema={Yup.object({
          title: Yup.string().required('Required'),
          userId: Yup.number().required('Required').typeError('Must be a number'),
        })}
        onSubmit={handleAdd}
        fields={[
          { name: 'title', label: 'Title' },
          { name: 'userId', label: 'User ID' },
        ]}
      />

      <DataSet
        data={data}
        headers={[
          { key: 'id', label: 'ID' },
          { key: 'title', label: 'Title' },
          { key: 'completed', label: 'Completed' },
          { key: 'userId', label: 'User ID' },
        ]}
        onRowSelect={(items) => setSelectedRows(new Set(items))}
        onUpdate={handleUpdate}
      />
    </div>
  );
};

export default TodosPage;
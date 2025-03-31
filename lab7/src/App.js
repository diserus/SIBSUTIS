import React from 'react';
import DataSet from '../src/DataSet';

const App = () => {
  const data = [
    {  name: 'Петя', age: 25, city: 'Москва' },
    {  name: 'Вася', age: 30, city: 'Лондон' },
    {  name: 'Саша', age: 28, city: 'Париж' },
  ];

  const headers = [
    { key: 'name', label: 'Name' },
    { key: 'age', label: 'Age' },
    { key: 'city', label: 'City' },
  ];

  const handleRowSelect = (selectedRows) => {
    console.log('Selected rows:', selectedRows);
  };

  return (
    <div>
      <DataSet 
        data={data}
        headers={headers}
        onRowSelect={handleRowSelect}
        renderCell={(value, row, colIndex) => {
          if (colIndex === 1) { // Age column
            return <strong>{value}</strong>;
          }
          return value;
        }}
      />
      <br></br>
      <DataSet 
        data={data}
        onRowSelect={handleRowSelect}
      />
    </div>
  );
};

export default App;
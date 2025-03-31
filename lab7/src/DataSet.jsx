import React, { useState } from 'react';
import PropTypes from 'prop-types';
import '../src/DataSet.css';

const DataSet = ({
  data = [],
  headers = [],
  renderHeader = (header, index) => header.label || header,
  renderCell = (value, row, colIndex) => value,
  onRowSelect,
}) => {
  // Если заголовки не переданы, берем ключи из первого элемента данных
  const derivedHeaders = headers.length > 0 
    ? headers 
    : data.length > 0 
      ? Object.keys(data[0]).map(key => ({ key, label: key })) 
      : [];

  const [selectedRows, setSelectedRows] = useState(new Set());

  const handleRowClick = (index, event) => {
    // Проверяем, был ли клик по области выделения (первая ячейка)
    const isSelectionArea = event.target.closest('.data-set__selection-area');
    
    if (!isSelectionArea) return;

    event.stopPropagation();

    const newSelectedRows = new Set(selectedRows);
    
    if (event.ctrlKey || event.metaKey) {
      // При зажатом Ctrl добавляем/удаляем строку из выделения
      if (newSelectedRows.has(index)) {
        newSelectedRows.delete(index);
      } else {
        newSelectedRows.add(index);
      }
    } else {
      // Без Ctrl выделяем только одну строку
      if (newSelectedRows.has(index) && newSelectedRows.size === 1) {
        newSelectedRows.clear();
      } else {
        newSelectedRows.clear();
        newSelectedRows.add(index);
      }
    }

    setSelectedRows(newSelectedRows);
    
    if (onRowSelect) {
      onRowSelect(Array.from(newSelectedRows).map(i => data[i]));
    }
  };

  return (
    <div className="data-set">
      <table className="data-set__table">
        <thead>
          <tr>
            <th className="data-set__selection-header"></th>
            {derivedHeaders.map((header, index) => (
              <th key={index}>
                {renderHeader(header, index)}
              </th>
            ))}
          </tr>
        </thead>
        <tbody>
          {data.map((row, rowIndex) => (
            <tr 
              key={rowIndex}
              className={`data-set__row ${selectedRows.has(rowIndex) ? 'data-set__row--selected' : ''}`}
              onClick={(e) => handleRowClick(rowIndex, e)}
            >
              <td className="data-set__selection-area">
                <div className="data-set__selection-indicator"></div>
              </td>
              {derivedHeaders.map((header, colIndex) => {
                const value = row[header.key];
                return (
                  <td key={colIndex}>
                    {renderCell(value, row, colIndex)}
                  </td>
                );
              })}
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
};

DataSet.propTypes = {
  data: PropTypes.arrayOf(PropTypes.object).isRequired,
  headers: PropTypes.arrayOf(
    PropTypes.oneOfType([
      PropTypes.string,
      PropTypes.shape({
        key: PropTypes.string.isRequired,
        label: PropTypes.string,
      }),
    ])
  ),
  renderHeader: PropTypes.func,
  renderCell: PropTypes.func,
  onRowSelect: PropTypes.func,
};

export default DataSet;
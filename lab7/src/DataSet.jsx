import React, { useState, useEffect } from 'react';
import PropTypes from 'prop-types';
import '../src/DataSet.css';

const DataSet = ({
  data = [],
  headers = [],
  renderHeader = (header, index) => header.label || header,
  renderCell = (value, row, colIndex) => value,
  onRowSelect,
  onUpdate,
}) => {
  const derivedHeaders = headers.length > 0 
    ? headers 
    : data.length > 0 
      ? Object.keys(data[0]).map(key => ({ key, label: key })) 
      : [];

  const [selectedRows, setSelectedRows] = useState(new Set());
  const [editingCell, setEditingCell] = useState(null);

  const handleRowClick = (index, event) => {
    const isSelectionArea = event.target.closest('.data-set__selection-area');
    const isEditableCell = event.target.closest('.data-set__editable-cell');
    
    if (isEditableCell) return;
    if (!isSelectionArea) return;

    event.stopPropagation();

    const newSelectedRows = new Set(selectedRows);
    
    if (event.ctrlKey || event.metaKey) {
      if (newSelectedRows.has(index)) {
        newSelectedRows.delete(index);
      } else {
        newSelectedRows.add(index);
      }
    } else {
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

  const handleCellDoubleClick = (rowIndex, colKey) => {
    setEditingCell({ rowIndex, colKey });
  };

  const handleCellBlur = (rowIndex, colKey, value) => {
    setEditingCell(null);
    
    if (onUpdate) {
      const updatedItem = { ...data[rowIndex], [colKey]: value };
      onUpdate(updatedItem);
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
                const isEditing = editingCell?.rowIndex === rowIndex && editingCell?.colKey === header.key;
                
                return (
                  <td 
                    key={colIndex}
                    className="data-set__editable-cell"
                    onDoubleClick={() => handleCellDoubleClick(rowIndex, header.key)}
                  >
                    {isEditing ? (
                      <input
                        type="text"
                        defaultValue={value}
                        autoFocus
                        onBlur={(e) => handleCellBlur(rowIndex, header.key, e.target.value)}
                        onKeyDown={(e) => {
                          if (e.key === 'Enter') {
                            handleCellBlur(rowIndex, header.key, e.target.value);
                          }
                        }}
                      />
                    ) : (
                      renderCell(value, row, colIndex)
                    )}
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
  onUpdate: PropTypes.func,
};

export default DataSet;
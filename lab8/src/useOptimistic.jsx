import { useState, useEffect, useCallback } from 'react';

export const useOptimistic = (initialData) => {
  const [data, setData] = useState(initialData);
  const [originalData, setOriginalData] = useState(initialData);

  // Добавление с оптимистичным обновлением
  const addOptimisticData = useCallback((newItem) => {
    setData(prev => [...prev, newItem]);
  }, []);

  // Удаление с оптимистичным обновлением
  const removeOptimisticData = useCallback((idsToRemove) => {
    setData(prev => prev.filter(item => !idsToRemove.includes(item.id)));
  }, []);

  // Обновление с оптимистичным обновлением
  const updateOptimisticData = useCallback((predicate, newData) => {
    setData(prev => prev.map(item => predicate(item) ? newData : item));
  }, []);

  // Откат изменений
  const rollback = useCallback(() => {
    setData(originalData);
  }, [originalData]);

  // Обновление originalData при изменении initialData
  useEffect(() => {
    setOriginalData(initialData);
    setData(initialData);
  }, [initialData]);

  return [data, addOptimisticData, removeOptimisticData, updateOptimisticData, rollback];
};
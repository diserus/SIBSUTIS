// src/components/ArticleStatusBadge.js
import { Chip } from '@mui/material';

const statusColors = {
  Pending: 'default',
  NeedsRevision: 'warning',
  Accepted: 'success',
  Rejected: 'error',
};

const statusText = {
  Pending: 'Не рецензировано',
  NeedsRevision: 'На доработке',
  Accepted: 'Принято',
  Rejected: 'Отклонено',
};

export const ArticleStatusBadge = ({ status }) => {
  return (
    <Chip
      label={statusText[status] || status}
      color={statusColors[status] || 'default'}
    />
  );
};
import { Routes, Route, Navigate } from 'react-router-dom';
import ProtectedRoute from './components/ProtectedRoute';
import DashboardLayout from './pages/Dashboard/DashboardLayout';
import AuthPage from './pages/Auth/AuthPage';
import ArticlesPage from './pages/Dashboard/Articles/ArticlesPage';
import ProfilePage from './pages/Dashboard/Profile/ProfilePage';
import SubmitArticlePage from './pages/Dashboard/Articles/SubmitArticlePage';
import ReviewsPage from './pages/Dashboard/Reviews/ReviewsPage';
import NotFoundPage from './pages/NotFoundPage';
import ArticleDetailPage from './pages/Dashboard/Articles/ArticleDetailPage';
import AdminUsersPage from './pages/Dashboard/Admin/AdminUsersPage'; // Новый компонент
import AdminArticlesPage from './pages/Dashboard/Admin/AdminArticlePage'; // Новый компонент

export default function AppRouter() {
  return (
    <Routes>
      {/* Публичные маршруты */}
      <Route path="/auth/*" element={<AuthPage />} />

      {/* Защищенные маршруты */}
      <Route element={<ProtectedRoute />}>
        <Route element={<DashboardLayout />}>
          <Route index element={<Navigate to="/articles" replace />} />
          <Route path="profile" element={<ProfilePage />} />
          <Route path="articles" element={<ArticlesPage />} />
          <Route path="articles/:id" element={<ArticleDetailPage />} />
          <Route path="submit-article" element={<SubmitArticlePage />} />
          <Route path="reviews" element={<ReviewsPage />} />

          <Route path="admin/users" element={<AdminUsersPage />} />
          <Route path="admin/articles" element={<AdminArticlesPage />} />
        </Route>
      </Route>

      {/* Перенаправления */}
      <Route path="/" element={<Navigate to="/articles" replace />} />
      <Route path="*" element={<NotFoundPage />} />
    </Routes>
  );
}
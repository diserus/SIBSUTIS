using ReviewSystem.Models;

namespace ReviewSystem.Repositories
{
    public interface IArticleRepository
    {
        Task<List<Article>> GetAllAsync();
        Task<Article?> GetByIdAsync(int id);
        Task<List<Article>> GetByAuthorIdAsync(int authorId);
        Task<List<Article>> GetByStatusAsync(ArticleStatus status);
        Task<Article> AddAsync(Article article);
        Task UpdateAsync(Article article);
        Task DeleteAsync(int id);
        Task UpdateStatusAsync(int id, ArticleStatus status);
    }
}
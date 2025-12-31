using ReviewSystem.Models;

namespace ReviewSystem.Repositories
{
    public interface IReviewRepository
    {
        Task<List<Review>> GetAllAsync();
        Task<Review?> GetByIdAsync(int id);
        Task<List<Review>> GetByArticleIdAsync(int articleId);
        Task<List<Review>> GetByReviewerIdAsync(int reviewerId);
        Task<List<Review>> GetPendingReviewsAsync();
        Task<List<Review>> GetCompletedReviewsByReviewerAsync(int reviewerId);
        Task<List<Review>> GetInProgressReviewsByReviewerAsync(int reviewerId);
        Task<Review> AddAsync(Review review);
        Task UpdateAsync(Review review);
        Task DeleteAsync(int id);
        Task<Review?> AcceptReviewRequestAsync(int reviewId, int reviewerId);
        Task CompleteReviewAsync(int reviewId, string content, ArticleStatus recommendation);
    }
}
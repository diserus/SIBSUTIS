using Microsoft.EntityFrameworkCore;
using ReviewSystem.Data;
using ReviewSystem.Models;

namespace ReviewSystem.Repositories
{
    public class ReviewRepository : IReviewRepository
    {
        private readonly ApplicationDbContext _context;

        public ReviewRepository(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<List<Review>> GetAllAsync()
        {
            return await _context.Reviews
                .Include(r => r.Article)
                .Include(r => r.Reviewer)
                .ToListAsync();
        }

        public async Task<Review?> GetByIdAsync(int id)
        {
            return await _context.Reviews
                .Include(r => r.Article)
                .Include(r => r.Reviewer)
                .FirstOrDefaultAsync(r => r.Id == id);
        }

        public async Task<List<Review>> GetByArticleIdAsync(int articleId)
        {
            return await _context.Reviews
                .Include(r => r.Reviewer)
                .Where(r => r.ArticleId == articleId)
                .ToListAsync();
        }

        public async Task<List<Review>> GetByReviewerIdAsync(int reviewerId)
        {
            return await _context.Reviews
                .Include(r => r.Article)
                .Where(r => r.ReviewerId == reviewerId)
                .ToListAsync();
        }

        public async Task<List<Review>> GetPendingReviewsAsync()
        {
            return await _context.Reviews
                .Include(r => r.Article)
                .Where(r => r.Status == ReviewStatus.Pending)
                .ToListAsync();
        }

        public async Task<List<Review>> GetCompletedReviewsByReviewerAsync(int reviewerId)
        {
            return await _context.Reviews
                .Include(r => r.Article)
                .Where(r => r.ReviewerId == reviewerId && r.Status == ReviewStatus.Completed)
                .ToListAsync();
        }

        public async Task<List<Review>> GetInProgressReviewsByReviewerAsync(int reviewerId)
        {
            return await _context.Reviews
                .Include(r => r.Article)
                .Where(r => r.ReviewerId == reviewerId && r.Status == ReviewStatus.InProgress)
                .ToListAsync();
        }

        public async Task<Review> AddAsync(Review review)
        {
          

            _context.Reviews.Add(review);
            await _context.SaveChangesAsync();
            return review;
        }

        public async Task UpdateAsync(Review review)
        {
            _context.Entry(review).State = EntityState.Modified;
            await _context.SaveChangesAsync();
        }

        public async Task DeleteAsync(int id)
        {
            var review = await _context.Reviews.FindAsync(id);
            if (review != null)
            {
                _context.Reviews.Remove(review);
                await _context.SaveChangesAsync();
            }
        }

        public async Task<Review?> AcceptReviewRequestAsync(int reviewId, int reviewerId)
        {
            var review = await _context.Reviews.FindAsync(reviewId);
            if (review != null && review.Status == ReviewStatus.Pending)
            {
                review.ReviewerId = reviewerId;
                review.Status = ReviewStatus.InProgress;
                await _context.SaveChangesAsync();
                return review;
            }
            return null;
        }

        public async Task CompleteReviewAsync(int reviewId, string content, ArticleStatus recommendation)
        {
            var review = await _context.Reviews.FindAsync(reviewId);
            if (review != null)
            {
                review.Content = content;
                review.Recommendation = recommendation;
                review.Status = ReviewStatus.Completed;
                review.CompletedAt = DateTime.UtcNow;
                
                // Обновляем статус статьи в соответствии с рекомендацией
                var article = await _context.Articles.FindAsync(review.ArticleId);
                if (article != null)
                {
                    article.Status = recommendation;
                    article.UpdatedAt = DateTime.UtcNow;
                }
                
                await _context.SaveChangesAsync();
            }
        }
    }
}
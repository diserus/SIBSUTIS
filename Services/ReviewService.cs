using ReviewSystem.Models;
using ReviewSystem.Repositories;

namespace ReviewSystem.Services
{
    public class ReviewService
    {
        private readonly IReviewRepository _reviewRepository;

        public ReviewService(IReviewRepository reviewRepository)
        {
            _reviewRepository = reviewRepository;
        }

        public async Task<List<Review>> GetAllReviewsAsync()
        {
            return await _reviewRepository.GetAllAsync();
        }

        public async Task<Review?> GetReviewByIdAsync(int id)
        {
            return await _reviewRepository.GetByIdAsync(id);
        }

        public async Task<List<Review>> GetReviewsByArticleIdAsync(int articleId)
        {
            return await _reviewRepository.GetByArticleIdAsync(articleId);
        }

        public async Task<List<Review>> GetReviewsByReviewerIdAsync(int reviewerId)
        {
            return await _reviewRepository.GetByReviewerIdAsync(reviewerId);
        }

        public async Task<List<Review>> GetPendingReviewsAsync()
        {
            return await _reviewRepository.GetPendingReviewsAsync();
        }

        public async Task<List<Review>> GetCompletedReviewsByReviewerAsync(int reviewerId)
        {
            return await _reviewRepository.GetCompletedReviewsByReviewerAsync(reviewerId);
        }

        public async Task<List<Review>> GetInProgressReviewsByReviewerAsync(int reviewerId)
        {
            return await _reviewRepository.GetInProgressReviewsByReviewerAsync(reviewerId);
        }

        public async Task<Review?> AcceptReviewRequestAsync(int reviewId, int reviewerId)
        {
            return await _reviewRepository.AcceptReviewRequestAsync(reviewId, reviewerId);
        }

        public async Task CompleteReviewAsync(int reviewId, string content, ArticleStatus recommendation)
        {
            await _reviewRepository.CompleteReviewAsync(reviewId, content, recommendation);
        }

        public async Task<Review> AddReviewAsync(Review review)
        {
            return await _reviewRepository.AddAsync(review);
        }

        public async Task UpdateReviewAsync(Review review)
        {
            await _reviewRepository.UpdateAsync(review);
        }

        public async Task DeleteReviewAsync(int id)
        {
            await _reviewRepository.DeleteAsync(id);
        }
    }
}
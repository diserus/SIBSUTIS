using ReviewSystem.Models;

namespace ReviewSystem.Models.DTOs
{
    public class ReviewSubmitDTO
    {
        public string Content { get; set; } = string.Empty;
        public ArticleStatus Recommendation { get; set; }
    }

    public class ReviewResponseDTO
    {
        public int Id { get; set; }
        public int ArticleId { get; set; }
        public string ArticleTitle { get; set; } = string.Empty;
        public int ReviewerId { get; set; }
        public string ReviewerName { get; set; } = string.Empty;
        public string Content { get; set; } = string.Empty;
        public ReviewStatus Status { get; set; }
        public ArticleStatus Recommendation { get; set; }
        public DateTime CreatedAt { get; set; }
        public DateTime? CompletedAt { get; set; }

        public static ReviewResponseDTO FromReview(Review review)
        {
            return new ReviewResponseDTO
            {
                Id = review.Id,
                ArticleId = review.ArticleId,
                ArticleTitle = review.Article?.Title ?? string.Empty,
                ReviewerId = review.ReviewerId,
                ReviewerName = review.Reviewer?.FullName ?? string.Empty,
                Content = review.Content,
                Status = review.Status,
                Recommendation = review.Recommendation,
                CreatedAt = review.CreatedAt,
                CompletedAt = review.CompletedAt
            };
        }
    }
}
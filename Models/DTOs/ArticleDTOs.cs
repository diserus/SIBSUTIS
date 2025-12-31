using ReviewSystem.Models;

namespace ReviewSystem.Models.DTOs
{
    public class ArticleSubmitDTO
    {
        public string Title { get; set; } = string.Empty;
        public string Abstract { get; set; } = string.Empty;
        public string FileFormat { get; set; } = string.Empty;

        // Новое поле для изображения
        public IFormFile? Image { get; set; }
    }


    public class ArticleUpdateDTO
    {
        public string? Title { get; set; }
        public string? Abstract { get; set; }
    }

    public class ArticleResponseDTO
    {
        public int Id { get; set; }
        public string Title { get; set; } = string.Empty;
        public string? ImagePath { get; set; } = string.Empty;
        public string Abstract { get; set; } = string.Empty;
        public string FileFormat { get; set; } = string.Empty;
        public int AuthorId { get; set; }
        public string AuthorName { get; set; } = string.Empty;
        public ArticleStatus Status { get; set; }
        public DateTime SubmittedAt { get; set; }
        public DateTime? UpdatedAt { get; set; }
        public List<ReviewBriefDTO> Reviews { get; set; } = new List<ReviewBriefDTO>();


        public static ArticleResponseDTO FromArticle(Article article)
        {
            var dto = new ArticleResponseDTO
            {
                Id = article.Id,
                Title = article.Title,
                Abstract = article.Abstract,
                FileFormat = article.FileFormat,
                AuthorId = article.AuthorId,
                AuthorName = article.Author?.FullName ?? string.Empty,
                Status = article.Status,
                SubmittedAt = article.SubmittedAt,
                UpdatedAt = article.UpdatedAt,
                ImagePath = article.ImagePath ?? string.Empty

            };

            if (article.Reviews != null)
            {
                foreach (var review in article.Reviews)
                {
                    dto.Reviews.Add(new ReviewBriefDTO
                    {
                        Id = review.Id,
                        ReviewerId = review.ReviewerId,
                        ReviewerName = review.Reviewer?.FullName ?? string.Empty,
                        Status = review.Status
                    });
                }
            }

            return dto;
        }
    }

    public class ReviewBriefDTO
    {
        public int Id { get; set; }
        public int ReviewerId { get; set; }
        public string ReviewerName { get; set; } = string.Empty;
        public ReviewStatus Status { get; set; }
    }

    public class ArticleBriefDTO
    {
        public int Id { get; set; }
        public string Title { get; set; } = string.Empty;
        public ArticleStatus Status { get; set; }
        public DateTime SubmittedAt { get; set; }

        public static ArticleBriefDTO FromArticle(Article article)
        {
            return new ArticleBriefDTO
            {
                Id = article.Id,
                Title = article.Title,
                Status = article.Status,
                SubmittedAt = article.SubmittedAt
            };
        }
    }
}
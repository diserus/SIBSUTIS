namespace ReviewSystem.Models
{
    public enum ReviewStatus
    {
        Pending,         // Ожидает рецензирования
        InProgress,      // В процессе рецензирования
        Completed        // Рецензирование завершено
    }

    public class Review
    {
        public int Id { get; set; }
        public int ArticleId { get; set; }
        public Article? Article { get; set; }
        public int ReviewerId { get; set; }
        public User? Reviewer { get; set; }
        public string Content { get; set; } = string.Empty;
        public ReviewStatus Status { get; set; } = ReviewStatus.Pending;
        public ArticleStatus Recommendation { get; set; } = ArticleStatus.Pending;
        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
        public DateTime? CompletedAt { get; set; }
    }
}
namespace ReviewSystem.Models
{
    public enum ArticleStatus
    {
        Pending,         // Не рецензировано
        NeedsRevision,   // Отправлено на доработку
        Accepted,        // Принято к публикации
        Rejected         // Отклонено
    }

    public class Article
    {
        public int Id { get; set; }
        public string Title { get; set; } = string.Empty;
        public string Abstract { get; set; } = string.Empty;
        public string FilePath { get; set; } = string.Empty;
        public string FileFormat { get; set; } = string.Empty;
        public int AuthorId { get; set; }
        public User? Author { get; set; }
        public ArticleStatus Status { get; set; } = ArticleStatus.Pending;
        public DateTime SubmittedAt { get; set; } = DateTime.UtcNow;
        public DateTime? UpdatedAt { get; set; }
        public List<Review> Reviews { get; set; } = new List<Review>();

        public string? ImagePath { get; set; }
    }
}
namespace ReviewSystem.Models
{
    public enum UserRole
    {
        Author,
        Reviewer,
        Administrator
    }

    public enum UserStatus
    {
        Active,
        Blocked
    }

    public class User
    {
        public int Id { get; set; }
        public string Username { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty; // В реальном приложении нужно хранить хеш пароля
        public string Email { get; set; } = string.Empty;
        public string FullName { get; set; } = string.Empty;
        public UserRole Role { get; set; }
        public UserStatus Status { get; set; } = UserStatus.Active;
        public string? Biography { get; set; }
        public string? ProfilePicture { get; set; }
        public DateTime RegisteredAt { get; set; } = DateTime.UtcNow;
    }
}
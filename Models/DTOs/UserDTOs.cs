using ReviewSystem.Models;

namespace ReviewSystem.Models.DTOs
{
    public class UserRegisterDTO
    {
        public string Username { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty;
        public string Email { get; set; } = string.Empty;
        public string FullName { get; set; } = string.Empty;
        public UserRole Role { get; set; } = UserRole.Author;
        public string? Biography { get; set; }
    }

    public class UserLoginDTO
    {
        public string Username { get; set; } = string.Empty;
        public string Password { get; set; } = string.Empty;
    }

    public class UserUpdateDTO
    {
        public string? Email { get; set; }
        public string? FullName { get; set; }
        public string? Biography { get; set; }
        public string? Password { get; set; }
    }

    public class UserResponseDTO
    {
        public int Id { get; set; }
        public string Username { get; set; } = string.Empty;
        public string Email { get; set; } = string.Empty;
        public string FullName { get; set; } = string.Empty;
        public UserRole Role { get; set; }
        public UserStatus Status { get; set; }
        public string? Biography { get; set; }
        public string? ProfilePicture { get; set; }
        public DateTime RegisteredAt { get; set; }

        public static UserResponseDTO FromUser(User user)
        {
            return new UserResponseDTO
            {
                Id = user.Id,
                Username = user.Username,
                Email = user.Email,
                FullName = user.FullName,
                Role = user.Role,
                Status = user.Status,
                Biography = user.Biography,
                ProfilePicture = user.ProfilePicture,
                RegisteredAt = user.RegisteredAt
            };
        }
    }
}
using ReviewSystem.Models;
using ReviewSystem.Repositories;

namespace ReviewSystem.Services
{
    public class UserService
    {
        private readonly IUserRepository _userRepository;

        public UserService(IUserRepository userRepository)
        {
            _userRepository = userRepository;
        }

        public async Task<List<User>> GetAllUsersAsync()
        {
            return await _userRepository.GetAllAsync();
        }

        public async Task<User?> GetUserByIdAsync(int id)
        {
            return await _userRepository.GetByIdAsync(id);
        }

        public async Task<User?> AuthenticateAsync(string username, string password)
        {
            var user = await _userRepository.GetByUsernameAsync(username);
            if (user != null && user.Password == password) // В реальном приложении нужно использовать хеширование
            {
                return user;
            }
            return null;
        }

        public async Task<User?> RegisterUserAsync(User user)
        {
            // Проверяем, что пользователь с таким именем или email не существует
            var existingUser = await _userRepository.GetByUsernameAsync(user.Username);
            if (existingUser != null)
            {
                return null;
            }

            existingUser = await _userRepository.GetByEmailAsync(user.Email);
            if (existingUser != null)
            {
                return null;
            }

            return await _userRepository.AddAsync(user);
        }

        public async Task UpdateUserAsync(User user)
        {
            await _userRepository.UpdateAsync(user);
        }

        public async Task DeleteUserAsync(int id)
        {
            await _userRepository.DeleteAsync(id);
        }

        public async Task BlockUserAsync(int id)
        {
            await _userRepository.BlockUserAsync(id);
        }

        public async Task UnblockUserAsync(int id)
        {
            await _userRepository.UnblockUserAsync(id);
        }
    }
}
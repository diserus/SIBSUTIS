using ReviewSystem.Models;
using ReviewSystem.Repositories;

namespace ReviewSystem.Services
{
    public class ArticleService
    {
        private readonly IArticleRepository _articleRepository;
        private readonly IReviewRepository _reviewRepository;

        public ArticleService(IArticleRepository articleRepository, IReviewRepository reviewRepository)
        {
            _articleRepository = articleRepository;
            _reviewRepository = reviewRepository;
        }

        public async Task<List<Article>> GetAllArticlesAsync()
        {
            return await _articleRepository.GetAllAsync();
        }

        public async Task<Article?> GetArticleByIdAsync(int id)
        {
            return await _articleRepository.GetByIdAsync(id);
        }

        public async Task<List<Article>> GetArticlesByAuthorIdAsync(int authorId)
        {
            return await _articleRepository.GetByAuthorIdAsync(authorId);
        }

        public async Task<Article> SubmitArticleAsync(Article article)
        {
            var savedArticle = await _articleRepository.AddAsync(article);
            return savedArticle;
        }

        public async Task UpdateArticleAsync(Article article)
        {
            await _articleRepository.UpdateAsync(article);
        }

        public async Task DeleteArticleAsync(int id)
        {
            await _articleRepository.DeleteAsync(id);
        }

        public async Task UpdateArticleStatusAsync(int id, ArticleStatus status)
        {
            await _articleRepository.UpdateStatusAsync(id, status);
        }
    }
}
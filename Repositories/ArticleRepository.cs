using Microsoft.EntityFrameworkCore;
using ReviewSystem.Data;
using ReviewSystem.Models;

namespace ReviewSystem.Repositories
{
    public class ArticleRepository : IArticleRepository
    {
        private readonly ApplicationDbContext _context;

        public ArticleRepository(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<List<Article>> GetAllAsync()
        {
            return await _context.Articles
                .Include(a => a.Author)
                .ToListAsync();
        }

        public async Task<Article?> GetByIdAsync(int id)
        {
            return await _context.Articles
                .Include(a => a.Author)
                .Include(a => a.Reviews)
                    .ThenInclude(r => r.Reviewer)
                .FirstOrDefaultAsync(a => a.Id == id);
        }

        public async Task<List<Article>> GetByAuthorIdAsync(int authorId)
        {
            return await _context.Articles
                .Include(a => a.Author)
                .Where(a => a.AuthorId == authorId)
                .ToListAsync();
        }

        public async Task<List<Article>> GetByStatusAsync(ArticleStatus status)
        {
            return await _context.Articles
                .Include(a => a.Author)
                .Where(a => a.Status == status)
                .ToListAsync();
        }

        public async Task<Article> AddAsync(Article article)
        {
            _context.Articles.Add(article);
            await _context.SaveChangesAsync();
            return article;
        }

        public async Task UpdateAsync(Article article)
        {
            article.UpdatedAt = DateTime.UtcNow;
            _context.Entry(article).State = EntityState.Modified;
            await _context.SaveChangesAsync();
        }

        public async Task DeleteAsync(int id)
        {
            var article = await _context.Articles.FindAsync(id);
            if (article != null)
            {
                _context.Articles.Remove(article);
                await _context.SaveChangesAsync();
            }
        }

        public async Task UpdateStatusAsync(int id, ArticleStatus status)
        {
            var article = await _context.Articles.FindAsync(id);
            if (article != null)
            {
                article.Status = status;
                article.UpdatedAt = DateTime.UtcNow;
                await _context.SaveChangesAsync();
            }
        }
    }
}
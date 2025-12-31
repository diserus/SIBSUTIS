using Microsoft.EntityFrameworkCore;
using ReviewSystem.Data;
using ReviewSystem.Repositories;
using ReviewSystem.Services;
using Microsoft.OpenApi.Models;
using Microsoft.AspNetCore.Http.Features;

var builder = WebApplication.CreateBuilder(args);


// Добавляем сервисы
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen(c =>
{
    c.SwaggerDoc("v1", new OpenApiInfo { Title = "ReviewSystem API", Version = "v1" });
    c.OperationFilter<SwaggerFileOperationFilter>();
});

builder.Services.AddCors(options =>
{
    options.AddDefaultPolicy(policy =>
    {
        policy.AllowAnyOrigin()
              .AllowAnyHeader()
              .AllowAnyMethod();
    });
});

// Добавляем контекст базы данных
builder.Services.AddDbContext<ApplicationDbContext>(options =>
    options.UseNpgsql(builder.Configuration.GetConnectionString("DefaultConnection")));

// Регистрируем репозитории
builder.Services.AddScoped<IUserRepository, UserRepository>();
builder.Services.AddScoped<IArticleRepository, ArticleRepository>();
builder.Services.AddScoped<IReviewRepository, ReviewRepository>();

// Регистрируем сервисы
builder.Services.AddScoped<UserService>();
builder.Services.AddScoped<ArticleService>();
builder.Services.AddScoped<ReviewService>();

var app = builder.Build();

var uploadsPath = Path.Combine(Directory.GetCurrentDirectory(), "Uploads", "Images");
if (!Directory.Exists(uploadsPath))
{
    Directory.CreateDirectory(uploadsPath);
    Console.WriteLine($"Создана директория: {uploadsPath}");
}

// Настройка раздачи статических файлов
app.UseStaticFiles(new StaticFileOptions
{
    FileProvider = new Microsoft.Extensions.FileProviders.PhysicalFileProvider(
        Path.Combine(Directory.GetCurrentDirectory(), "Uploads")),
    RequestPath = "/Uploads"
});

if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseCors();
app.UseHttpsRedirection();

// Включаем буферизацию для возможности повторного чтения тела запроса
app.Use(async (context, next) =>
{
    context.Request.EnableBuffering();
    await next();
});

ConfigureUserEndpoints(app);
ConfigureArticleEndpoints(app);
ConfigureReviewEndpoints(app);
ConfigureAdminEndpoints(app);

app.Run();

void ConfigureUserEndpoints(WebApplication app)
{
    var userApi = app.MapGroup("/api/users");

    // Регистрация нового пользователя
    userApi.MapPost("/register", async (UserService userService, ReviewSystem.Models.DTOs.UserRegisterDTO userDto) =>
    {
        var user = new ReviewSystem.Models.User
        {
            Username = userDto.Username,
            Password = userDto.Password,
            Email = userDto.Email,
            FullName = userDto.FullName,
            Role = userDto.Role,
            Biography = userDto.Biography
        };
        var createdUser = await userService.RegisterUserAsync(user);
        if (createdUser == null)
        {
            return Results.BadRequest("Пользователь с таким именем или email уже существует");
        }
        return Results.Created($"/api/users/{createdUser.Id}",
            ReviewSystem.Models.DTOs.UserResponseDTO.FromUser(createdUser));
    });

    // Аутентификация пользователя
    userApi.MapPost("/login", async (UserService userService, ReviewSystem.Models.DTOs.UserLoginDTO loginDto) =>
    {
        var user = await userService.AuthenticateAsync(loginDto.Username, loginDto.Password);
        if (user == null)
        {
            return Results.Unauthorized();
        }
        if (user.Status == ReviewSystem.Models.UserStatus.Blocked)
        {
            return Results.Forbid();
        }
        return Results.Ok(ReviewSystem.Models.DTOs.UserResponseDTO.FromUser(user));
    });

    // Получение информации о текущем пользователе
    userApi.MapGet("/me/{id}", async (UserService userService, int id) =>
    {
        var user = await userService.GetUserByIdAsync(id);
        if (user == null)
        {
            return Results.NotFound();
        }
        return Results.Ok(ReviewSystem.Models.DTOs.UserResponseDTO.FromUser(user));
    });

    // Обновление информации о пользователе
    userApi.MapPut("/{id}", async (UserService userService, int id, ReviewSystem.Models.DTOs.UserUpdateDTO userDto) =>
    {
        var user = await userService.GetUserByIdAsync(id);
        if (user == null)
        {
            return Results.NotFound();
        }
        if (userDto.Email != null) user.Email = userDto.Email;
        if (userDto.FullName != null) user.FullName = userDto.FullName;
        if (userDto.Biography != null) user.Biography = userDto.Biography;
        if (userDto.Password != null) user.Password = userDto.Password;
        await userService.UpdateUserAsync(user);
        return Results.Ok(ReviewSystem.Models.DTOs.UserResponseDTO.FromUser(user));
    });
}

void ConfigureArticleEndpoints(WebApplication app)
{
    var articleApi = app.MapGroup("/api/articles");

    // Получение всех статей
    articleApi.MapGet("/", async (ArticleService articleService) =>
    {
        var articles = await articleService.GetAllArticlesAsync();
        return Results.Ok(articles.Select(a => ReviewSystem.Models.DTOs.ArticleBriefDTO.FromArticle(a)));
    });

    // Получение статьи по ID
    articleApi.MapGet("/{id}", async (ArticleService articleService, int id) =>
    {
        var article = await articleService.GetArticleByIdAsync(id);
        if (article == null)
        {
            return Results.NotFound();
        }
        return Results.Ok(ReviewSystem.Models.DTOs.ArticleResponseDTO.FromArticle(article));
    });

    // Получение статей автора
    articleApi.MapGet("/author/{authorId}", async (ArticleService articleService, int authorId) =>
    {
        var articles = await articleService.GetArticlesByAuthorIdAsync(authorId);
        return Results.Ok(articles.Select(a => ReviewSystem.Models.DTOs.ArticleBriefDTO.FromArticle(a)));
    });

    // Отправка новой статьи с изображением
    articleApi.MapPost("/", async (ArticleService articleService, int authorId, HttpRequest request) =>
    {
        var form = await request.ReadFormAsync();
        var title = form["Title"];
        var abstractText = form["Abstract"];
        var fileFormat = form["FileFormat"];
        var image = form.Files["Image"];

        string? imagePath = null;

        if (image != null && image.Length > 0)
        {
            try
            {
                // Создаем папку, если ее нет
                var uploadsFolder = Path.Combine(Directory.GetCurrentDirectory(), "Uploads", "Images");
                Directory.CreateDirectory(uploadsFolder);

                // Генерируем уникальное имя файла
                var fileName = $"{Guid.NewGuid()}{Path.GetExtension(image.FileName)}";
                imagePath = Path.Combine("Uploads", "Images", fileName).Replace("\\", "/");

                // Полный путь для сохранения
                var fullPath = Path.Combine(Directory.GetCurrentDirectory(), imagePath);

                // Сохраняем файл
                using (var stream = new FileStream(fullPath, FileMode.Create))
                {
                    await image.CopyToAsync(stream);
                }

                Console.WriteLine($"Изображение сохранено по пути: {imagePath}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при сохранении изображения: {ex.Message}");
                return Results.Problem("Не удалось сохранить изображение");
            }
        }

        var article = new ReviewSystem.Models.Article
        {
            Title = title,
            Abstract = abstractText,
            FileFormat = fileFormat,
            AuthorId = authorId,
            FilePath = $"Uploads/Articles/{Guid.NewGuid()}.{fileFormat}",
            ImagePath = imagePath // Теперь здесь будет корректный путь или null
        };

        var createdArticle = await articleService.SubmitArticleAsync(article);
        return Results.Created($"/api/articles/{createdArticle.Id}",
            ReviewSystem.Models.DTOs.ArticleResponseDTO.FromArticle(createdArticle));
    });

    // Обновление статьи
    articleApi.MapPut("/{id}", async (ArticleService articleService, int id, int authorId, ReviewSystem.Models.DTOs.ArticleUpdateDTO articleDto) =>
    {
        var article = await articleService.GetArticleByIdAsync(id);
        if (article == null)
        {
            return Results.NotFound();
        }
        if (article.AuthorId != authorId)
        {
            return Results.Forbid();
        }
        if (articleDto.Title != null) article.Title = articleDto.Title;
        if (articleDto.Abstract != null) article.Abstract = articleDto.Abstract;
        article.UpdatedAt = DateTime.UtcNow;
        await articleService.UpdateArticleAsync(article);
        return Results.Ok(ReviewSystem.Models.DTOs.ArticleResponseDTO.FromArticle(article));
    });

    // Удаление статьи
    articleApi.MapDelete("/{id}", async (ArticleService articleService, int id, int authorId) =>
    {
        var article = await articleService.GetArticleByIdAsync(id);
        if (article == null)
        {
            return Results.NotFound();
        }
        if (article.AuthorId != authorId)
        {
            return Results.Forbid();
        }
        await articleService.DeleteArticleAsync(id);
        return Results.NoContent();
    });
}

void ConfigureReviewEndpoints(WebApplication app)
{
    var reviewApi = app.MapGroup("/api/reviews");

    // Получение всех рецензий рецензента
    reviewApi.MapGet("/reviewer/{reviewerId}", async (ReviewService reviewService, int reviewerId) =>
    {
        var reviews = await reviewService.GetReviewsByReviewerIdAsync(reviewerId);
        return Results.Ok(reviews.Select(r => ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(r)));
    });

    // Получение завершенных рецензий рецензента
    reviewApi.MapGet("/reviewer/{reviewerId}/completed", async (ReviewService reviewService, int reviewerId) =>
    {
        var reviews = await reviewService.GetCompletedReviewsByReviewerAsync(reviewerId);
        return Results.Ok(reviews.Select(r => ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(r)));
    });

    // Получение рецензий в работе у рецензента
    reviewApi.MapGet("/reviewer/{reviewerId}/in-progress", async (ReviewService reviewService, int reviewerId) =>
    {
        var reviews = await reviewService.GetInProgressReviewsByReviewerAsync(reviewerId);
        return Results.Ok(reviews.Select(r => ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(r)));
    });

    // Получение рецензии по ID
    reviewApi.MapGet("/{id}", async (ReviewService reviewService, int id) =>
    {
        var review = await reviewService.GetReviewByIdAsync(id);
        if (review == null)
        {
            return Results.NotFound();
        }
        return Results.Ok(ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(review));
    });

    // Получение доступных запросов на рецензирование
    reviewApi.MapGet("/pending", async (ReviewService reviewService) =>
    {
        var reviews = await reviewService.GetPendingReviewsAsync();
        return Results.Ok(reviews.Select(r => ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(r)));
    });

    // Принятие запроса на рецензирование
    reviewApi.MapPost("/{reviewId}/accept", async (ReviewService reviewService, int reviewId, int reviewerId) =>
    {
        var review = await reviewService.AcceptReviewRequestAsync(reviewId, reviewerId);
        if (review == null)
        {
            return Results.BadRequest("Рецензия недоступна для принятия");
        }
        return Results.Ok(ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(review));
    });

    // Отправка рецензии
    reviewApi.MapPost("/{reviewId}/complete", async (ReviewService reviewService, int reviewId, int reviewerId, ReviewSystem.Models.DTOs.ReviewSubmitDTO reviewDto) =>
    {
        var review = await reviewService.GetReviewByIdAsync(reviewId);
        if (review == null)
        {
            return Results.NotFound();
        }
        if (review.ReviewerId != reviewerId || review.Status != ReviewSystem.Models.ReviewStatus.InProgress)
        {
            return Results.Forbid();
        }
        await reviewService.CompleteReviewAsync(reviewId, reviewDto.Content, reviewDto.Recommendation);
        review = await reviewService.GetReviewByIdAsync(reviewId);
        return Results.Ok(ReviewSystem.Models.DTOs.ReviewResponseDTO.FromReview(review!));
    });
}

void ConfigureAdminEndpoints(WebApplication app)
{
    var adminApi = app.MapGroup("/api/admin");

    // Получение всех пользователей
    adminApi.MapGet("/users", async (UserService userService) =>
    {
        var users = await userService.GetAllUsersAsync();
        return Results.Ok(users.Select(u => ReviewSystem.Models.DTOs.UserResponseDTO.FromUser(u)));
    });

    // Создание нового пользователя
    adminApi.MapPost("/users", async (UserService userService, ReviewSystem.Models.DTOs.UserRegisterDTO userDto) =>
    {
        var user = new ReviewSystem.Models.User
        {
            Username = userDto.Username,
            Password = userDto.Password,
            Email = userDto.Email,
            FullName = userDto.FullName,
            Role = userDto.Role,
            Biography = userDto.Biography
        };
        var createdUser = await userService.RegisterUserAsync(user);
        if (createdUser == null)
        {
            return Results.BadRequest("Пользователь с таким именем или email уже существует");
        }
        return Results.Created($"/api/users/{createdUser.Id}",
            ReviewSystem.Models.DTOs.UserResponseDTO.FromUser(createdUser));
    });

    // Блокировка пользователя
    adminApi.MapPost("/users/{id}/block", async (UserService userService, int id) =>
    {
        var user = await userService.GetUserByIdAsync(id);
        if (user == null)
        {
            return Results.NotFound();
        }
        await userService.BlockUserAsync(id);
        return Results.Ok();
    });

    // Разблокировка пользователя
    adminApi.MapPost("/users/{id}/unblock", async (UserService userService, int id) =>
    {
        var user = await userService.GetUserByIdAsync(id);
        if (user == null)
        {
            return Results.NotFound();
        }
        await userService.UnblockUserAsync(id);
        return Results.Ok();
    });

    // Удаление пользователя
    adminApi.MapDelete("/users/{id}", async (UserService userService, int id) =>
    {
        var user = await userService.GetUserByIdAsync(id);
        if (user == null)
        {
            return Results.NotFound();
        }
        await userService.DeleteUserAsync(id);
        return Results.NoContent();
    });

    // Получение всех статей
    adminApi.MapGet("/articles", async (ArticleService articleService) =>
    {
        var articles = await articleService.GetAllArticlesAsync();
        return Results.Ok(articles.Select(a => ReviewSystem.Models.DTOs.ArticleBriefDTO.FromArticle(a)));
    });

    // Удаление статьи
    adminApi.MapDelete("/articles/{id}", async (ArticleService articleService, int id) =>
    {
        var article = await articleService.GetArticleByIdAsync(id);
        if (article == null)
        {
            return Results.NotFound();
        }
        await articleService.DeleteArticleAsync(id);
        return Results.NoContent();
    });
}
const express = require('express');
const app = express();
const PORT = process.env.PORT || 3000;


app.use(express.json());

let users = [
  { id: 1, name: 'Иван Иванов', email: 'ivan@example.com' },
  { id: 2, name: 'Петр Петров Владимирович', email: 'petr@example.com' }
];

let nextId = 3;

app.use((req, res, next) => {
  console.log(`${new Date().toISOString()} - ${req.method} ${req.path}`);
  next();
});

app.get('/api/health', (req, res) => {
  res.json({ 
    status: 'OK', 
    timestamp: new Date().toISOString(),
    uptime: process.uptime()
  });
});
app.get('/api/name', (req, res) => {
  res.json({ 
    status: 'Konstantin', 
    timestamp: new Date().toISOString(),
    uptime: process.uptime()
  });
});
app.get('/api/users', (req, res) => {
  res.json(users);
});

app.get('/api/users/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const user = users.find(u => u.id === id);
  
  if (!user) {
    return res.status(404).json({ error: 'Пользователь не найден' });
  }
  
  res.json(user);
});

app.post('/api/users', (req, res) => {
  const { name, email } = req.body;
  
  if (!name  ||!email) {
    return res.status(400).json({ error: 'Имя и email обязательны' });
  }
  
  const newUser = {
    id: nextId++,
    name,
    email
  };
  
  users.push(newUser);
  res.status(201).json(newUser);
});

app.put('/api/users/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const userIndex = users.findIndex(u => u.id === id);
  
  if (userIndex === -1) {
    return res.status(404).json({ error: 'Пользователь не найден' });
  }
  
  const { name, email } = req.body;
  
  if (!name || !email) {
    return res.status(400).json({ error: 'Имя и email обязательны' });
  }
  
  users[userIndex] = { id, name, email };
  res.json(users[userIndex]);
});

app.delete('/api/users/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const userIndex = users.findIndex(u => u.id === id);
  
  if (userIndex === -1) {
    return res.status(404).json({ error: 'Пользователь не найден' });
  }
  
  users.splice(userIndex, 1);
  res.status(204).send();
});

app.use((req, res) => {
  res.status(404).json({ error: 'Маршрут не найден' });
});

app.use((err, req, res, next) => {
  console.error('Ошибка:', err);
  res.status(500).json({ error: 'Внутренняя ошибка сервера' });
});

const server = app.listen(PORT, () => {
  console.log(`Сервер запущен на порту ${PORT}`);
  console.log(`Доступно по адресу: http://localhost:${PORT}`);
});

const gracefulShutdown = (signal) => {
  console.log(`\nПолучен сигнал ${signal}. Завершение работы...`);
  //d
  server.close((err) => {
    if (err) {
      console.error('Ошибка при завершении:', err);
      process.exit(1);
    }
    
    console.log('HTTP сервер закрыт.');
    console.log('Приложение завершено корректно.');
    process.exit(0);
  });
  
  setTimeout(() => {
    console.error('Принудительное завершение из-за таймаута');
    process.exit(1);
  }, 10000);
};

process.on('SIGTERM', () => gracefulShutdown('SIGTERM'));
process.on('SIGINT', () => gracefulShutdown('SIGINT'));

process.on('uncaughtException', (error) => {
  console.error('Необработанное исключение:', error);
  gracefulShutdown('uncaughtException');
});

process.on('unhandledRejection', (reason, promise) => {
  console.error('Необработанный промис:', reason);
  gracefulShutdown('unhandledRejection');
});
//ds
import orderBy from './orderBy.js';

const users = [
    { name: 'Артем', age: 25 },
    { name: 'Петя', age: 30 },
    { name: 'Артем', age: 20 },
    { name: 'Вася', age: 35 }
];

try {
    const sortedUsers = orderBy(users, ['name', 'age']);
    console.log(users);
    console.log(sortedUsers);
} catch (error) {
    console.error(error.message);
}
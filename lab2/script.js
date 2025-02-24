import orderBy from './orderBy.js';

const users = [
    { name: 'Alice', age: 25 },
    { name: 'Bob', age: 30 },
    { name: 'Alice', age: 20 },
    { name: 'Charlie', age: 35 }
];

try {
    const sortedUsers = orderBy(users, ['name', 'age']);
    console.log(users);
    console.log(sortedUsers);
} catch (error) {
    console.error(error.message);
}
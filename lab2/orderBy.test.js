import orderBy from './orderBy.js';

test('Сортировка массива объектов по свойствам "name" и "age"', () => {
    const users = [
        { name: 'Alice', age: 25 },
        { name: 'Bob', age: 30 },
        { name: 'Alice', age: 20 },
        { name: 'Charlie', age: 35 }
    ];

    const sortedUsers = orderBy(users, ['name', 'age']);

    expect(sortedUsers).toEqual([
        { name: 'Alice', age: 20 },
        { name: 'Alice', age: 25 },
        { name: 'Bob', age: 30 },
        { name: 'Charlie', age: 35 }
    ]);
});

test('Выброс исключения, если массив содержит не объекты', () => {
    const invalidArray = [
        { name: 'Alice', age: 25 },
        'Not an object',
        { name: 'Bob', age: 30 }
    ];

    expect(() => orderBy(invalidArray, ['name', 'age'])).toThrow(
        'Все элементы массива должны быть объектами'
    );
});

test('Выброс исключения, если у объекта отсутствует свойство', () => {
    const usersWithMissingProperty = [
        { name: 'Alice', age: 25 },
        { name: 'Bob' },
        { name: 'Charlie', age: 35 }
    ];

    expect(() => orderBy(usersWithMissingProperty, ['name', 'age'])).toThrow(
        'Свойство "age" отсутствует в одном из объектов'
    );
});
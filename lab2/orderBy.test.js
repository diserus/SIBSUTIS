const orderBy = require('./orderBy');

test('Сортировка по одному свойству', () => {
    const input = [
        { name: 'Вася', age: 25 },
        { name: 'Петя', age: 22 },
        { name: 'Артем', age: 30 }
    ];
    const expected = [
        { name: 'Артем', age: 30 },
        { name: 'Вася', age: 25 },
        { name: 'Петя', age: 22 }
    ];
    expect(orderBy(input, ['name'])).toEqual(expected);
});

test('Сортировка по нескольким свойствам', () => {
    const input = [
        { name: 'Вася', age: 25 },
        { name: 'Петя', age: 22 },
        { name: 'Вася', age: 20 }
    ];
    const expected = [
        { name: 'Вася', age: 20 },
        { name: 'Вася', age: 25 },
        { name: 'Петя', age: 22 }
    ];
    expect(orderBy(input, ['name', 'age'])).toEqual(expected);
});

test('Исключение при передаче не массива объектов', () => {
    const input = [1, 2, 3,{ name: 'Вася', age: 25 }];
    expect(() => orderBy(input, ['name'])).toThrow('Первый аргумент должен быть массивом объектов');
});

test('Исключение при отсутствии свойства в объекте', () => {
    const input = [
        { name: 'Вася', age: 25 },
        { name: 'Петя' }
    ];
    expect(() => orderBy(input, ['name', 'age'])).toThrow('Объект не содержит свойства "age"');
});
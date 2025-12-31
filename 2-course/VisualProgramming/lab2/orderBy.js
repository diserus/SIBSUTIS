function orderBy(arr, props) {
    if (!Array.isArray(arr) || !arr.every(item => typeof item === 'object' && item !== null)) {
        throw new Error('Первый аргумент должен быть массивом объектов');
    }
    for (const obj of arr) {
        for (const prop of props) {
            if (!(prop in obj)) {
                throw new Error(`Объект не содержит свойства "${prop}"`);
            }
        }
    }

    return arr.slice().sort((a, b) => {
        for (const prop of props) {
            if (a[prop] < b[prop]) return -1;
            if (a[prop] > b[prop]) return 1;
        }
        return 0;
    });
}

module.exports = orderBy;
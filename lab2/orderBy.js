// orderBy.js

function orderBy(array, properties) {
    if (!array.every(item => typeof item === 'object' && item !== null)) {
        throw new Error('Все элементы массива должны быть объектами');
    }
    for (const obj of array) {
        for (const prop of properties) {
            if (!(prop in obj)) {
                throw new Error(`Свойство "${prop}" отсутствует в одном из объектов`);
            }
        }
    }
    const sortedArray = [...array];
    sortedArray.sort((a, b) => {
        for (const prop of properties) {
            if (a[prop] < b[prop]) return -1;
            if (a[prop] > b[prop]) return 1;
        }
        return 0;
    });

    return sortedArray;
}

export default orderBy;
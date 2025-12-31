const calcStatsFromAPI = require('./calcStatsFromAPI');
const loadData = require('./loadData'); // Импортируем модуль
const calcStats = require('./calcStats'); // Импортируем модуль

describe('calcStatsFromAPI', () => {
    it('should call loadData once and return correct stats', async () => {
        // Фиксированные данные, которые будет возвращать loadData
        const mockData = [
            {
                breed: 'Turkish Van',
                country: 'developed in the United Kingdom (founding stock from Turkey)',
                origin: 'Natural',
                coat: 'Semi-long',
                pattern: 'Van'
            },
            {
                breed: 'York Chocolate',
                country: 'United States (New York)',
                origin: 'Natural',
                coat: 'Long',
                pattern: 'Solid'
            }
        ];

        // Ожидаемый результат, который возвращает calcStats
        const expectedStats = {
            'developed in the United Kingdom (founding stock from Turkey)': 1,
            'United States (New York)': 1
        };

        // Создаем spy на loadData и подменяем его реализацию
        const loadDataSpy = jest.spyOn(loadData, 'default').mockResolvedValue(mockData);

        // Вызываем функцию, которую тестируем
        const result = await calcStatsFromAPI();

        // Проверяем, что loadData был вызван один раз
        expect(loadDataSpy).toHaveBeenCalledTimes(1);

        // Проверяем, что результат функции calcStatsFromAPI соответствует ожидаемому
        expect(result).toEqual(expectedStats);

        // Восстанавливаем оригинальную реализацию loadData
        loadDataSpy.mockRestore();
    });
});
function calcStats(catsInfo)
{
    const statistics = {};

    for (const item of catsInfo) {
        const country = item.country;
        if (statistics[country]) {
            statistics[country]++;
        } else {
            statistics[country] = 1;
        }
    }
    return statistics;
}

module.exports = calcStats;
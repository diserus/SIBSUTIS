const loadData = require('./loadData').default;
const calcStats = require('./calcStats').default;

async function calcStatsFromAPI() {
    const datas = await loadData(); 
    const stats = calcStats(datas); 
    return stats;
}

module.exports = calcStatsFromAPI;
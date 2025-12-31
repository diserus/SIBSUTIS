async function loadData() {
    let datas =[];
    for (i=1;i<=4;i++)
    {
        let response = await fetch(`https://catfact.ninja/breeds?page=${i}`);
        let result = await response.json();
        datas = datas.concat(result.data);
    }
    
    return datas;
}

module.exports = loadData;
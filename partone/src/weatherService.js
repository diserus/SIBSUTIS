const API_KEY = '15eac45481ab56758d0da0cc4d3fd052'; // Replace with your actual API key

export const fetchWeatherData = async (lat, lon) => {
  try {
    // Using the 5-day forecast API as required
    const response = await fetch(
      `https://api.openweathermap.org/data/2.5/forecast?lat=${lat}&lon=${lon}&appid=${API_KEY}&units=metric`
    );
    
    if (!response.ok) {
      throw new Error('Failed to fetch weather data');
    }
    
    const data = await response.json();
    
    // Process the data to group by day and add current weather
    return processWeatherData(data);
  } catch (error) {
    console.error("Error fetching weather data:", error);
    throw error;
  }
};

// Mock data for testing to avoid API rate limits
export const getMockWeatherData = () => {
  return {
    city: {
      name: "Moscow",
      country: "RU"
    },
    current: {
      temp: 27,
      feels_like: 28,
      humidity: 80,
      wind_speed: 5,
      pressure: 756.0,
      weather: [
        {
          id: 801,
          main: "Clouds",
          description: "few clouds",
          icon: "02d"
        }
      ],
      dt: Math.floor(Date.now() / 1000)
    },
    hourly: [
      { dt: Math.floor(Date.now() / 1000), temp: 27, weather: [{ id: 801, main: "Clouds", description: "few clouds", icon: "02d" }] },
      { dt: Math.floor(Date.now() / 1000) + 3600, temp: 28, weather: [{ id: 801, main: "Clouds", description: "few clouds", icon: "02d" }] },
      { dt: Math.floor(Date.now() / 1000) + 7200, temp: 27, weather: [{ id: 500, main: "Rain", description: "light rain", icon: "10d" }] },
      { dt: Math.floor(Date.now() / 1000) + 10800, temp: 26, weather: [{ id: 500, main: "Rain", description: "light rain", icon: "10d" }] },
      { dt: Math.floor(Date.now() / 1000) + 14400, temp: 25, weather: [{ id: 800, main: "Clear", description: "clear sky", icon: "01d" }] },
      { dt: Math.floor(Date.now() / 1000) + 18000, temp: 25, weather: [{ id: 800, main: "Clear", description: "clear sky", icon: "01n" }] },
      { dt: Math.floor(Date.now() / 1000) + 21600, temp: 24, weather: [{ id: 800, main: "Clear", description: "clear sky", icon: "01n" }] },
      { dt: Math.floor(Date.now() / 1000) + 25200, temp: 23, weather: [{ id: 800, main: "Clear", description: "clear sky", icon: "01n" }] }
    ],
    daily: [
      {
        dt: Math.floor(Date.now() / 1000) + 86400,
        temp: { min: 22, max: 26 },
        weather: [{ id: 801, main: "Clouds", description: "few clouds", icon: "02d" }],
        pop: 20
      },
      {
        dt: Math.floor(Date.now() / 1000) + 172800,
        temp: { min: 21, max: 26 },
        weather: [{ id: 801, main: "Clouds", description: "few clouds", icon: "02d" }],
        pop: 20
      },
      {
        dt: Math.floor(Date.now() / 1000) + 259200,
        temp: { min: 21, max: 26 },
        weather: [{ id: 801, main: "Clouds", description: "few clouds", icon: "02d" }],
        pop: 20
      },
      {
        dt: Math.floor(Date.now() / 1000) + 345600,
        temp: { min: 20, max: 26 },
        weather: [{ id: 500, main: "Rain", description: "light rain", icon: "10d" }],
        pop: 30
      },
      {
        dt: Math.floor(Date.now() / 1000) + 432000,
        temp: { min: 20, max: 26 },
        weather: [{ id: 500, main: "Rain", description: "light rain", icon: "10d" }],
        pop: 30
      },
      {
        dt: Math.floor(Date.now() / 1000) + 518400,
        temp: { min: 20, max: 26 },
        weather: [{ id: 500, main: "Rain", description: "light rain", icon: "10d" }],
        pop: 30
      },
      {
        dt: Math.floor(Date.now() / 1000) + 604800,
        temp: { min: 20, max: 26 },
        weather: [{ id: 800, main: "Clear", description: "clear sky", icon: "01d" }],
        pop: 10
      }
    ]
  };
};

const processWeatherData = (data) => {
  if (!data || !data.list || !data.list.length) {
    throw new Error("Invalid data structure from API");
  }

  // Current weather (using the first forecast item)
  const current = {
    temp: data.list[0].main.temp,
    feels_like: data.list[0].main.feels_like,
    humidity: data.list[0].main.humidity,
    wind_speed: data.list[0].wind.speed,
    pressure: data.list[0].main.pressure,
    weather: data.list[0].weather,
    dt: data.list[0].dt
  };

  // Hourly forecast (every 3 hours, up to 24 hours)
  const hourly = data.list.slice(0, 8).map(item => ({
    dt: item.dt,
    temp: item.main.temp,
    weather: item.weather,
    pop: item.pop * 100 // Precipitation probability in %
  }));

  // Daily forecast (group by days)
  const dailyForecasts = {};
  const today = new Date().toLocaleDateString();
  
  data.list.forEach(item => {
    const date = new Date(item.dt * 1000).toLocaleDateString();
    if (date === today) return; // Skip today
    
    if (!dailyForecasts[date]) {
      dailyForecasts[date] = {
        dt: item.dt,
        temp: {
          min: item.main.temp_min,
          max: item.main.temp_max
        },
        weather: item.weather,
        pop: item.pop * 100
      };
    } else {
      dailyForecasts[date].temp.min = Math.min(dailyForecasts[date].temp.min, item.main.temp_min);
      dailyForecasts[date].temp.max = Math.max(dailyForecasts[date].temp.max, item.main.temp_max);
      dailyForecasts[date].pop = Math.max(dailyForecasts[date].pop, item.pop * 100);
    }
  });

  return {
    city: {
      name: data.city.name,
      country: data.city.country
    },
    current,
    hourly,
    daily: Object.values(dailyForecasts).slice(0, 7) // Maximum 7 days
  };
};
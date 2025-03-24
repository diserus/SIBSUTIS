import { useState, useEffect } from 'react';
import { format } from 'date-fns';
import './App.css';
import CitySelector from './CitySelector';
import useWeather from './useWeather';
import AnimatedBackground from './AnimatedBackground';

function App() {
  const [selectedCity, setSelectedCity] = useState(null);
  const { weatherData, loading, error, fetchWeather, useMockData, toggleMockData } = useWeather();
  const [isDaytime, setIsDaytime] = useState(true);

  // Detect if it's daytime based on current time
  useEffect(() => {
    const checkDayTime = () => {
      const hours = new Date().getHours();
      setIsDaytime(hours >= 6 && hours < 20);
    };
    
    checkDayTime();
    const intervalId = setInterval(checkDayTime, 60 * 60 * 1000); // Check every hour
    
    return () => clearInterval(intervalId);
  }, []);

  // Fetch weather data when city changes
  useEffect(() => {
    if (selectedCity) {
      fetchWeather(selectedCity.lat, selectedCity.lon);
    }
  }, [selectedCity, fetchWeather]);

  // Default to Moscow if no city is selected
  useEffect(() => {
    if (!selectedCity && !weatherData) {
      // Moscow coordinates
      setSelectedCity({
        name: "Moscow, RU",
        lat: 55.7558,
        lon: 37.6173
      });
    }
  }, [selectedCity, weatherData]);

  // Get weather condition for styling
  const getWeatherCondition = () => {
    if (!weatherData || !weatherData.current || !weatherData.current.weather) return 'clear';
    
    const mainCondition = weatherData.current.weather[0].main.toLowerCase();
    
    if (mainCondition.includes('rain') || mainCondition.includes('drizzle')) return 'rain';
    if (mainCondition.includes('snow')) return 'snow';
    if (mainCondition.includes('cloud')) return 'clouds';
    if (mainCondition.includes('clear')) return 'clear';
    if (mainCondition.includes('thunder')) return 'thunderstorm';
    
    return 'clear'; // Default
  };

  const weatherCondition = getWeatherCondition();
  const appClassName = `app ${weatherCondition} ${isDaytime ? 'day' : 'night'}`;

  return (
    <div className={appClassName}>
      <AnimatedBackground weatherCondition={weatherCondition} isDaytime={isDaytime} />
      
      {/* Header with date and city selector */}
      <div className="header">
        <div className="date-container">
          <div className="day-name">{format(new Date(), 'EEEE')}</div>
          <div className="current-date">{format(new Date(), 'MMMM d, yyyy')}</div>
        </div>
        <CitySelector onSelect={setSelectedCity} />
      </div>

      {/* Toggle mock data button (for development) */}
      <div className="mock-data-toggle">
        <button onClick={toggleMockData}>
          {useMockData ? 'Using Mock Data' : 'Using Real API'}
        </button>
      </div>

      {/* Loading and error states */}
      {loading && !weatherData && <div className="loading">Loading weather data...</div>}
      {error && <div className="error">{error}</div>}
      
      {/* Weather data display */}
      {weatherData && (
        <div className="weather-container">
          {/* City name */}
          <div className="city-name">
            {selectedCity?.name || `${weatherData.city.name}, ${weatherData.city.country}`}
          </div>
          
          {/* Current weather (large block) */}
          <div className="current-weather">
            <div className="current-temp">{Math.round(weatherData.current.temp)}°</div>
            <div className="weather-icon">
              <img 
                src={`https://openweathermap.org/img/wn/${weatherData.current.weather[0].icon}@4x.png`} 
                alt={weatherData.current.weather[0].description}
              />
            </div>
            <div className="weather-description">
              {weatherData.current.weather[0].description}
            </div>
          </div>

          {/* Hourly forecast (horizontal scroll) */}
          <div className="hourly-forecast">
            <h3>Hourly Forecast</h3>
            <div className="hourly-scroll">
              {weatherData.hourly.map((hour, index) => (
                <div key={index} className="hour-item">
                  <div>{format(new Date(hour.dt * 1000), 'HH:mm')}</div>
                  <img 
                    src={`https://openweathermap.org/img/wn/${hour.weather[0].icon}.png`} 
                    alt={hour.weather[0].description}
                  />
                  <div>{Math.round(hour.temp)}°</div>
                </div>
              ))}
            </div>
          </div>

          {/* Weather details */}
          <div className="weather-details">
            <div className="detail-item">
              <span>Humidity</span>
              <span>{weatherData.current.humidity}%</span>
            </div>
            <div className="detail-item">
              <span>Wind</span>
              <span>{Math.round(weatherData.current.wind_speed)} m/s</span>
            </div>
            <div className="detail-item">
              <span>Pressure</span>
              <span>{weatherData.current.pressure} hPa</span>
            </div>
          </div>

          {/* Weekly forecast */}
          <div className="weekly-forecast">
            <h3>7-Day Forecast</h3>
            {weatherData.daily.map((day, index) => (
              <div key={index} className="day-item">
                <div>{format(new Date(day.dt * 1000), 'EEE, d')}</div>
                <img 
                  src={`https://openweathermap.org/img/wn/${day.weather[0].icon}.png`} 
                  alt={day.weather[0].description}
                />
                <div className="day-temps">
                  <span>{Math.round(day.temp.max)}°</span>
                  <span className="min-temp">{Math.round(day.temp.min)}°</span>
                </div>
              </div>
            ))}
          </div>
        </div>
      )}
    </div>
  );
}

export default App;
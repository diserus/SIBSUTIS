import { format } from 'date-fns';
import WeatherIcon from '../src/WeatherIcon';

const WeatherDisplay = ({ weatherData }) => {
  return (
    <div className="weather-display">
      {/* Текущая погода */}
      <div className="current-weather">
        <div className="location">
          {weatherData.city.name}, {weatherData.city.country}
        </div>
        <div className="main-info">
          <WeatherIcon code={weatherData.current.weather[0].icon} size="xl" />
          <div className="temperature">{Math.round(weatherData.current.temp)}°</div>
        </div>
        <div className="description">
          {weatherData.current.weather[0].description}
        </div>
      </div>

      {/* Почасовой прогноз */}
      <div className="hourly-forecast">
        <h3>Hourly Forecast</h3>
        <div className="hours-container">
          {weatherData.hourly.map((hour) => (
            <div key={hour.dt} className="hour-item">
              <div>{format(new Date(hour.dt * 1000), 'HH:mm')}</div>
              <WeatherIcon code={hour.weather[0].icon} size="sm" />
              <div>{Math.round(hour.main.temp)}°</div>
            </div>
          ))}
        </div>
      </div>

      {/* Детали погоды */}
      <div className="weather-details">
        <h3>Weather Details</h3>
        <div className="details-grid">
          <div className="detail-item">
            <span>Humidity</span>
            <span>{weatherData.current.humidity}%</span>
          </div>
          <div className="detail-item">
            <span>Wind</span>
            <span>{Math.round(weatherData.current.wind.speed * 3.6)} km/h</span>
          </div>
          <div className="detail-item">
            <span>Feels Like</span>
            <span>{Math.round(weatherData.current.feels_like)}°</span>
          </div>
          <div className="detail-item">
            <span>Pressure</span>
            <span>{weatherData.current.pressure} hPa</span>
          </div>
        </div>
      </div>

      {/* Недельный прогноз */}
      <div className="weekly-forecast">
        <h3>7-Day Forecast</h3>
        {weatherData.daily.map((day) => (
          <div key={day.dt} className="day-item">
            <div>{format(new Date(day.dt * 1000), 'EEEE')}</div>
            <WeatherIcon code={day.weather[0].icon} size="sm" />
            <div className="day-temps">
              <span>{Math.round(day.temp.max)}°</span>
              <span className="min-temp">{Math.round(day.temp.min)}°</span>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default WeatherDisplay;
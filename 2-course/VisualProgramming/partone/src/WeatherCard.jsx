import { format } from 'date-fns';
import WeatherIcon from '../src/WeatherIcon';

const WeatherCard = ({ day, isDaytime }) => {
  const date = new Date(day.forecasts[0].dt * 1000);
  const dayName = format(date, 'EEE');
  
  const middayForecast = day.forecasts.find(f => {
    const hours = new Date(f.dt * 1000).getHours();
    return hours >= 11 && hours <= 14;
  }) || day.forecasts[0];

  return (
    <div className="weather-card">
      <div className="day-name">{dayName}</div>
      <WeatherIcon 
        code={middayForecast.weather[0].icon} 
        size="md"
        animate={false}
      />
      <div className="day-temps">
        <span className="day-temp-max">
          {Math.round(middayForecast.main.temp_max)}°
        </span>
        <span className="day-temp-min">
          {Math.round(middayForecast.main.temp_min)}°
        </span>
      </div>
    </div>
  );
};

export default WeatherCard;
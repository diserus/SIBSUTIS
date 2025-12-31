import { format } from 'date-fns';
import WeatherIcon from '../src/WeatherIcon';

const HourlyForecast = ({ hourly }) => {
  if (!hourly || !Array.isArray(hourly)) {
    return <div className="hourly-forecast">No hourly data available</div>;
  }

  return (
    <div className="hourly-forecast">
      <h2 className="section-title">Hourly Forecast</h2>
      <div className="hourly-container">
        {hourly.slice(0, 12).map((hour) => (
          <div key={hour.dt} className="hour-item">
            <div className="hour">{format(new Date(hour.dt * 1000), 'HH:mm')}</div>
            <WeatherIcon code={hour.weather[0].icon} size="sm" />
            <div className="temp">{Math.round(hour.temp)}°</div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default HourlyForecast;
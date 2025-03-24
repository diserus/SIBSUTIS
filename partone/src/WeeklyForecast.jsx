import { format } from 'date-fns';
import WeatherIcon from '../src/WeatherIcon';

const WeeklyForecast = ({ daily }) => {
  if (!daily || !Array.isArray(daily)) {
    return <div className="weekly-forecast">No weekly forecast available</div>;
  }

  return (
    <div className="weekly-forecast">
      <h2 className="section-title">7-Day Forecast</h2>
      <div className="week-container">
        {daily.map((day) => (
          <div key={day.dt} className="day-item">
            <div className="day-name">{format(new Date(day.dt * 1000), 'EEE')}</div>
            <WeatherIcon code={day.weather[0].icon} size="sm" />
            <div className="temps">
              <span className="max-temp">{Math.round(day.temp.max)}°</span>
              <span className="min-temp">{Math.round(day.temp.min)}°</span>
            </div>
          </div>
        ))}
      </div>
    </div>
  );
};

export default WeeklyForecast;
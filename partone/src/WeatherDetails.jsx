const WeatherDetails = ({ current }) => {
    return (
      <div className="weather-details">
        <h2 className="section-title">Weather Details</h2>
        <div className="details-grid">
          <div className="detail-item">
            <span>Humidity</span>
            <span className="value">{current.humidity}%</span>
          </div>
          <div className="detail-item">
            <span>Wind</span>
            <span className="value">{Math.round(current.wind_speed * 3.6)} km/h</span>
          </div>
          <div className="detail-item">
            <span>Feels Like</span>
            <span className="value">{Math.round(current.feels_like)}°</span>
          </div>
          <div className="detail-item">
            <span>Pressure</span>
            <span className="value">{current.pressure} hPa</span>
          </div>
        </div>
      </div>
    );
  };
  
  export default WeatherDetails;
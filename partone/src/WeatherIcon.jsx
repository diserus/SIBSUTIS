import { useEffect, useState } from 'react';

const WeatherIcon = ({ code, size = 'md', animate = true }) => {
  const [iconUrl, setIconUrl] = useState('');
  const [isDaytime, setIsDaytime] = useState(true);

  useEffect(() => {
    // Determine if icon should be day or night version
    const time = code.slice(-1);
    setIsDaytime(time === 'd');
    
    const sizeMap = {
      sm: '',
      md: '@2x',
      lg: '@3x',
      xl: '@4x'
    };
    
    setIconUrl(`https://openweathermap.org/img/wn/${code}${sizeMap[size]}.png`);
  }, [code, size]);

  return (
    <div className={`weather-icon-container ${size} ${animate ? 'animate' : ''} ${isDaytime ? 'day' : 'night'}`}>
      <img 
        src={iconUrl} 
        alt="Weather icon" 
        className="weather-icon"
        draggable="false"
      />
    </div>
  );
};

export default WeatherIcon;
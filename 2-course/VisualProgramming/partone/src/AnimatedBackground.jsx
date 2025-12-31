import { useEffect, useState } from 'react';

const AnimatedBackground = ({ weatherCondition, isDaytime }) => {
  const [particles, setParticles] = useState([]);

  useEffect(() => {
    // Create weather-specific particles
    const createParticles = () => {
      let count = 0;
      
      if (weatherCondition === 'rain') {
        count = 100;
      } else if (weatherCondition === 'snow') {
        count = 50;
      } else if (weatherCondition === 'thunderstorm') {
        count = 30;
      }
      
      const newParticles = [];
      for (let i = 0; i < count; i++) {
        newParticles.push({
          id: i,
          left: Math.random() * 100,
          delay: Math.random() * 5,
          duration: 2 + Math.random() * 3,
          size: weatherCondition === 'snow' ? 
                `${5 + Math.random() * 5}px` : 
                `${1 + Math.random() * 2}px`
        });
      }
      setParticles(newParticles);
    };

    createParticles();
  }, [weatherCondition]);

  // Render lightning flashes for thunderstorms
  const renderLightning = () => {
    if (weatherCondition !== 'thunderstorm') return null;
    
    return (
      <div className="lightning-container">
        {[...Array(3)].map((_, index) => (
          <div 
            key={index}
            className="lightning-flash"
            style={{
              animationDelay: `${3 + Math.random() * 10}s`,
              left: `${20 + Math.random() * 60}%`
            }}
          />
        ))}
      </div>
    );
  };

  // Render clouds
  const renderClouds = () => {
    if (weatherCondition !== 'clouds' && weatherCondition !== 'rain' && weatherCondition !== 'snow') return null;
    
    return (
      <div className="clouds-container">
        {[...Array(5)].map((_, index) => (
          <div 
            key={index}
            className="cloud"
            style={{
              top: `${10 + Math.random() * 30}%`,
              left: `${index * 20}%`,
              opacity: 0.5 + Math.random() * 0.5,
              animationDuration: `${80 + Math.random() * 40}s`,
              animationDelay: `${index * 5}s`,
              transform: `scale(${0.5 + Math.random() * 0.5})`
            }}
          />
        ))}
      </div>
    );
  };

  // Render sun or moon
  const renderCelestial = () => {
    if (weatherCondition !== 'clear') return null;
    
    return (
      <div 
        className={isDaytime ? "sun" : "moon"}
        style={{
          top: '10%',
          right: '10%'
        }}
      />
    );
  };

  if (weatherCondition === 'rain') {
    return (
      <>
        {renderClouds()}
        <div className="weather-particles rain">
          {particles.map(p => (
            <div 
              key={p.id}
              className="rain-drop"
              style={{
                left: `${p.left}%`,
                animationDelay: `${p.delay}s`,
                animationDuration: `${p.duration}s`,
                height: p.size,
                width: p.size
              }}
            />
          ))}
        </div>
      </>
    );
  }

  if (weatherCondition === 'snow') {
    return (
      <>
        {renderClouds()}
        <div className="weather-particles snow">
          {particles.map(p => (
            <div 
              key={p.id}
              className="snow-flake"
              style={{
                left: `${p.left}%`,
                animationDelay: `${p.delay}s`,
                animationDuration: `${p.duration}s`,
                width: p.size,
                height: p.size
              }}
            />
          ))}
        </div>
      </>
    );
  }

  if (weatherCondition === 'thunderstorm') {
    return (
      <>
        {renderClouds()}
        {renderLightning()}
        <div className="weather-particles rain">
          {particles.map(p => (
            <div 
              key={p.id}
              className="rain-drop"
              style={{
                left: `${p.left}%`,
                animationDelay: `${p.delay}s`,
                animationDuration: `${p.duration}s`,
                height: p.size,
                width: p.size
              }}
            />
          ))}
        </div>
      </>
    );
  }

  if (weatherCondition === 'clouds') {
    return renderClouds();
  }

  if (weatherCondition === 'clear') {
    return renderCelestial();
  }

  return null;
};

export default AnimatedBackground;
import { useState, useEffect, useCallback } from 'react';
import { fetchWeatherData, getMockWeatherData } from './weatherService';

const useWeather = () => {
  const [weatherData, setWeatherData] = useState(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);
  const [useMockData, setUseMockData] = useState(false); // Toggle for using mock data

  const fetchWeather = useCallback(async (lat, lon) => {
    setLoading(true);
    setError(null);
    
    try {
      // Use mock data if enabled (to avoid API rate limits during development)
      const data = useMockData 
        ? getMockWeatherData() 
        : await fetchWeatherData(lat, lon);
      
      setWeatherData(data);
    } catch (err) {
      setError(err.message);
      console.error("Error fetching weather:", err);
    } finally {
      setLoading(false);
    }
  }, [useMockData]);

  // Set up automatic weather updates every 3 hours
  useEffect(() => {
    if (!weatherData) return;
    
    // Get the coordinates from the current weather data
    const updateInterval = 3 * 60 * 60 * 1000; // 3 hours in milliseconds
    
    const intervalId = setInterval(() => {
      if (weatherData && weatherData.city) {
        // Get the coordinates from the last request
        const { lat, lon } = weatherData.city.coord || { lat: null, lon: null };
        if (lat && lon) {
          console.log('Automatically updating weather data...');
          fetchWeather(lat, lon);
        }
      }
    }, updateInterval);
    
    // Clean up the interval when component unmounts
    return () => clearInterval(intervalId);
  }, [weatherData, fetchWeather]);

  // Toggle between real and mock data
  const toggleMockData = () => {
    setUseMockData(prev => !prev);
  };

  return { 
    weatherData, 
    loading, 
    error, 
    fetchWeather, 
    useMockData, 
    toggleMockData 
  };
};

export default useWeather;
const API_KEY = '15eac45481ab56758d0da0cc4d3fd052'; // Replace with your actual API key

/**
 * Fetches city data based on search query using OpenWeather Geocoding API
 * @param {string} query - Search query (city name)
 * @param {number} limit - Maximum number of results to return
 * @returns {Promise<Array>} - Array of city objects with name, lat, lon, country, state
 */
export const searchCities = async (query, limit = 5) => {
  try {
    const response = await fetch(
      `https://api.openweathermap.org/geo/1.0/direct?q=${encodeURIComponent(query)}&limit=${limit}&appid=${API_KEY}`
    );
    
    if (!response.ok) {
      throw new Error('Failed to fetch cities');
    }
    
    return await response.json();
  } catch (error) {
    console.error('Error searching cities:', error);
    return [];
  }
};

/**
 * Gets city data by coordinates using OpenWeather Reverse Geocoding API
 * @param {number} lat - Latitude
 * @param {number} lon - Longitude
 * @returns {Promise<Object|null>} - City object or null if not found
 */
export const getCityByCoordinates = async (lat, lon) => {
  try {
    const response = await fetch(
      `https://api.openweathermap.org/geo/1.0/reverse?lat=${lat}&lon=${lon}&limit=1&appid=${API_KEY}`
    );
    
    if (!response.ok) {
      throw new Error('Failed to fetch city data');
    }
    
    const data = await response.json();
    return data.length > 0 ? data[0] : null;
  } catch (error) {
    console.error('Error getting city by coordinates:', error);
    return null;
  }
};
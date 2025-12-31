import { useState, useEffect, useRef } from 'react';
import { searchCities } from './geocodingService';
import './App.css';

const CitySelector = ({ onSelect }) => {
  const [query, setQuery] = useState('');
  const [suggestions, setSuggestions] = useState([]);
  const [showSuggestions, setShowSuggestions] = useState(false);
  const [loading, setLoading] = useState(false);
  const suggestionsRef = useRef(null);

  // Close suggestions when clicking outside
  useEffect(() => {
    const handleClickOutside = (event) => {
      if (suggestionsRef.current && !suggestionsRef.current.contains(event.target)) {
        setShowSuggestions(false);
      }
    };

    document.addEventListener('mousedown', handleClickOutside);
    return () => {
      document.removeEventListener('mousedown', handleClickOutside);
    };
  }, []);

  const handleSearch = async (e) => {
    e.preventDefault();
    if (!query.trim()) return;
    
    try {
      setLoading(true);
      const cities = await searchCities(query);
      if (cities.length > 0) {
        onSelect({
          name: `${cities[0].name}, ${cities[0].country}`,
          lat: cities[0].lat,
          lon: cities[0].lon
        });
        setQuery('');
        setSuggestions([]);
      }
    } catch (error) {
      console.error("Error fetching city:", error);
    } finally {
      setLoading(false);
    }
  };

  const handleInputChange = async (e) => {
    const value = e.target.value;
    setQuery(value);
    
    if (value.length >= 3) {
      try {
        const cities = await searchCities(value);
        setSuggestions(cities);
        setShowSuggestions(true);
      } catch (error) {
        console.error("Error fetching suggestions:", error);
      }
    } else {
      setSuggestions([]);
      setShowSuggestions(false);
    }
  };

  const handleSuggestionClick = (city) => {
    onSelect({
      name: `${city.name}, ${city.country}`,
      lat: city.lat,
      lon: city.lon
    });
    setQuery('');
    setSuggestions([]);
    setShowSuggestions(false);
  };

  return (
    <div className="city-selector">
      <form onSubmit={handleSearch}>
        <div className="search-container">
          <input
            type="text"
            value={query}
            onChange={handleInputChange}
            placeholder="Search city..."
            className="search-input"
          />
          <button type="submit" className="search-button" disabled={loading}>
            {loading ? '...' : '🔍'}
          </button>
        </div>
      </form>
      
      {showSuggestions && suggestions.length > 0 && (
        <div className="suggestions-container" ref={suggestionsRef}>
          <ul className="suggestions-list">
            {suggestions.map((city, index) => (
              <li 
                key={`${city.name}-${city.lat}-${city.lon}-${index}`}
                onClick={() => handleSuggestionClick(city)}
                className="suggestion-item"
              >
                {city.name}, {city.state ? `${city.state}, ` : ''}{city.country}
              </li>
            ))}
          </ul>
        </div>
      )}
    </div>
  );
};

export default CitySelector;
from requests import Session
from requests.exceptions import ConnectionError, Timeout, TooManyRedirects
import json

url = 'https://pro-api.coinmarketcap.com/v1/cryptocurrency/listings/latest'
parameters = {
    'start':'1',
    'limit':'100',
    'convert':'USD'
}
headers = {
    'Accepts': 'application/json',
    'X-CMC_PRO_API_KEY': '382a7521-8554-4b9c-b4d1-7e2cfcdd1edf',
}

session = Session()
session.headers.update(headers)
def find_crypto_by_name(name: str, data: list):
    name = name.strip().lower()
    for crypto in data:
        if crypto['name'].lower() == name or crypto['symbol'].lower() == name:
            return crypto
    return 0
try:
    response = session.get(url, params=parameters)
    data = json.loads(response.text)['data']
    while True:
        user_input = input("\nВведите название криптовалюты (или 'q' для завершения): ").strip()
        if user_input.lower() == 'q':
            break

        crypto = find_crypto_by_name(user_input, data)

        if crypto:
            print(f"\nИнформация о {crypto['name']} ({crypto['symbol']}):")
            print(f"Цена: ${crypto['quote']['USD']['price']}")
            print(f"Рыночная капитализация: ${crypto['quote']['USD']['market_cap']}")
            print(f"Объем токенов в обороте: {crypto['circulating_supply']} {crypto['symbol']}")
        else:
            print("Криптовалюта не найдена в списке.")
except (ConnectionError, Timeout, TooManyRedirects) as e:
    print(e)
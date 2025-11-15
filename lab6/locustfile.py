from locust import HttpUser, task, between
from requests.auth import HTTPBasicAuth
import json
import urllib3

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

class OpenBMCTester(HttpUser):
    wait_time = between(1, 3)
    host = "https://127.0.0.1:2443"  

    auth = HTTPBasicAuth("root", "0penBmc")

    @task(1)
    def get_system_info(self):
        """Запрос информации о системе"""
        with self.client.get(
            "/redfish/v1/Systems/system",
            auth=self.auth,
            verify=False,
            catch_response=True,
            name="OpenBMC: Get System Info"
        ) as response:

            if response.status_code in [200, 201, 202, 204]:
                try:
                    data = response.json()
                    if "Id" in data and "Name" in data:
                        response.success()
                    else:
                        response.failure("Invalid system info structure")
                except json.JSONDecodeError:
                    response.failure("Invalid JSON")
            else:
                response.failure(f"Status code: {response.status_code}")

    @task(2)
    def get_power_state(self):
        """Запрос состояния питания PowerState"""
        with self.client.get(
            "/redfish/v1/Systems/system",
            auth=self.auth,
            verify=False,
            catch_response=True,
            name="OpenBMC: Get Power State"
        ) as response:

            if response.status_code in [200, 201, 202, 204]:
                try:
                    data = response.json()
                    state = data.get("PowerState")
                    if state in ["On", "Off", "PoweringOn", "PoweringOff"]:
                        response.success()
                    else:
                        response.failure(f"Invalid PowerState: {state}")
                except json.JSONDecodeError:
                    response.failure("Invalid JSON")
            else:
                response.failure(f"Status code: {response.status_code}")


class PublicAPITester(HttpUser):
    wait_time = between(1, 3)
    host = "https://jsonplaceholder.typicode.com"

    @task(1)
    def get_posts(self):
        """Получение списка постов"""
        with self.client.get(
            "/posts",
            catch_response=True,
            name="PublicAPI: Get Posts"
        ) as response:

            if response.status_code in [200, 201, 202, 204]:
                try:
                    data = response.json()
                    if isinstance(data, list) and len(data) > 0:
                        response.success()
                    else:
                        response.failure("Empty posts list")
                except json.JSONDecodeError:
                    response.failure("Invalid JSON")
            else:
                response.failure(f"Status code: {response.status_code}")

    @task(2)
    def get_weather(self):
        """Получение погоды через wttr.in"""
        with self.client.get(
            "https://wttr.in/Novosibirsk?format=j1",
            catch_response=True,
            name="PublicAPI: Get Weather"
        ) as response:

            if response.status_code in [200, 201, 202, 204]:
                try:
                    data = response.json()
                    if "current_condition" in data:
                        response.success()
                    else:
                        response.failure("Missing 'current_condition'")
                except json.JSONDecodeError:
                    response.failure("Invalid JSON")
            else:
                response.failure(f"Status code: {response.status_code}")

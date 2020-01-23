import time
import requests
import math
import random
import json

TOKEN = "BBFF-UkMCX6WNIUtY8Sjr7eFLzepOR5sfid"  #  TOKEN here
DEVICE_LABEL = "jangh"  #  device label here 
VARIABLE_LABEL_1 = "H"  #  first variable label here
VARIABLE_LABEL_2 = "T"  #  second variable label here
VARIABLE_LABEL_3 = "P"  #  third variable label here


def build_payload(variable_1, variable_2, variable_3):
    # Creates two random values for sending data
    value_1 = random.randint(36, 100)
    value_2 = random.randint(31, 100)
    value_3 = random.randint(1000, 1200)

    payload = {variable_1: value_1, 
           variable_2: value_2,
        variable_3: value_3}

    return payload


def post_request(payload):
    # Creates the headers for the HTTP requests
    url = "http://things.ubidots.com"
    url = "{}/api/v1.6/devices/{}".format(url, DEVICE_LABEL)
    headers = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"}
    """
    print (url)
    print (headers)
    print (payload)
    """
    # Makes the HTTP requests
    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, data=json.dumps(payload))
        status = req.status_code
    print(req.text)
        attempts += 1
        time.sleep(1)

    # Processes results
    if status >= 400:
        print("[ERROR] Could not send data after 5 attempts, please check your token credentials and internet connection")
        return False

    print("[INFO] request made properly, your device is updated")
    return True


def main():
    payload = build_payload(VARIABLE_LABEL_1, VARIABLE_LABEL_2, VARIABLE_LABEL_3)
    print("[INFO] Attemping to send data")
    post_request(payload)
    print("[INFO] finished")


if __name__ == '__main__':
    while (True):
        main()
        time.sleep(5)
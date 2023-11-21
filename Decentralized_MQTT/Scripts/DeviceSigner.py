Python 3.11.6 (tags/v3.11.6:8b6ee5b, Oct  2 2023, 14:57:12) [MSC v.1935 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license()" for more information.
>>> import RPi.GPIO as GPIO
... import time
... import paho.mqtt.client as mqtt
... from indy import crypto, wallet, did
... import json
... import asyncio
... import base64
... 
... def on_connect(client, userdata, flags, rc):
...     print("Connected with result code " + str(rc))
... 
... client = mqtt.Client()
... client.on_connect = on_connect
... 
... client.connect("192.168.0.23", 1883, 60)
... 
... client.loop_start()
... 
... GPIO.setmode(GPIO.BCM)
... TRIG = 23
... ECHO = 24
... 
... GPIO.setup(TRIG, GPIO.OUT)
... GPIO.setup(ECHO, GPIO.IN)
... 
... wallet_config = '{"id": "my_wallet11"}'
... wallet_credentials = '{"key": "wallet_key"}'
... 
... async def create_wallet_and_get_did():
...     try:
...         await wallet.create_wallet(wallet_config, wallet_credentials)
...     except:
...         print("Wallet already created")
... 
...     wallet_handle = await wallet.open_wallet(wallet_config, wallet_credentials)
...     did_info = '{"seed": "000000000000000000000000Steward1"}'
...     steward_did_info, _ = await did.create_and_store_my_did(wallet_handle, did_info)

    return wallet_handle, steward_did_info

async def sign_data(wallet_handle, steward_did, data):
    signer_key = await did.key_for_local_did(wallet_handle, steward_did)
    signature = await crypto.crypto_sign(wallet_handle, signer_key, data.encode())
    return base64.b64encode(signature)

async def main():
    wallet_handle, did_info = await create_wallet_and_get_did()
    try:
        while True:
            GPIO.output(TRIG, False)
            time.sleep(2)

            GPIO.output(TRIG, True)
            time.sleep(0.00001)
            GPIO.output(TRIG, False)

            while GPIO.input(ECHO) == 0:
                pulse_start = time.time()

            while GPIO.input(ECHO) == 1:
                pulse_end = time.time()

            pulse_duration = pulse_end - pulse_start
            distance = round(pulse_duration * 17150, 2)
            print(distance)

            # 데이터 서명
            signature = await sign_data(wallet_handle, did_info, str(distance))

            # 서명과 데이터를 함께 publish
            payload = {"distance": distance, "signature": signature.decode()}
            client.publish("myTopic1", json.dumps(payload))
            print(json.dumps(payload))

            time.sleep(3)
    finally:
        if wallet_handle is not None:
            # 프로그램 종료 시에 정리 작업 수행
            await wallet.close_wallet(wallet_handle)

try:
    asyncio.get_event_loop().run_until_complete(main())
except KeyboardInterrupt:
    pass
finally:
    # 프로그램 종료 시에 정리 작업 수행
    client.loop_stop()

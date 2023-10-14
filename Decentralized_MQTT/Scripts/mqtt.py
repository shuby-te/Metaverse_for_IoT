import paho.mqtt.client as mqtt

# 콜백 함수 정의
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("mytopic123")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# 여기에 MQTT 브로커 서버의 주소 입력
client.connect("broker.emqx.io", 1883, 60)

client.loop_forever()
